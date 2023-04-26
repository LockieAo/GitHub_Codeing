#include<iostream>
#include<vector>
using namespace std;


template<typename T>
class UnionFindSet {
private:
	vector<T> _arr;
public:
	UnionFindSet(size_t size,T val)
		:_arr(size,val)
	{}

	//根据元素所在位置的下标，查找元素所在集合的根结点（查完之后进行路径压缩）
	int FindRoot(int index) {
		int root = index;
		//获取该下标所在集合的根结点
		while (_arr[root] >= 0) {
			root = _arr[root];
		}
		
		//路径压缩
		while (_arr[index] >= 0) {
			//获取该下标对应的双亲结点下标
			int parent = _arr[index];
			//将该下标对应的双亲结点的下标更新为该集合根结点下标
			_arr[index] = root;
			//更新index继续向上更新
			index = parent;
		}
		
		return root;
	}

	//查找所有元素中集合的个数
	size_t SetSize() {
		size_t count = 0;
		//如果该下标对应的值是负数，说明是该集合根结点
		for (int i = 0; i < _arr.size(); i++) {
			if (_arr[i] < 0) {
				count++;
			}
		}

		return count;
	}

	//给出两个元素的下标，合并两个元素的集合到同一个集合
	bool Union(int index1,int index2) {
		//获取两个元素的集合的根结点
		int root1 = FindRoot(index1);
		int root2 = FindRoot(index2);

		//判断两个元素是不是在同一个集合
		if (root1 == root2) {
			return false;
		}

		//把根结点中较小的一个作为新集合的根结点
		if (root1 > root2) {
			swap(root1,root2);
		}

		//合并集合，让一个集合的根结点作为另一个集合的子结点
		_arr[root1] += _arr[root2];
		_arr[root2] = root1;

		return true;
	}

	//判断两个元素是否在同一个集合
	bool Inset(int x1,int x2) {
		return FindRoot(x1) == FindRoot(x2);
	}

	//打印
	void Print() {
		for (int i = 0; i < _arr.size(); i++) {
			cout << _arr[i] << " ";
		}
		cout << endl;
	}
};

/*

int main() {
	UnionFindSet<int> ufs(10,-1);

	ufs.Union(0,6);
	ufs.Union(0,7);
	ufs.Union(0,8);


	ufs.Union(1,4);
	ufs.Union(1,9);


	ufs.Union(2,3);
	ufs.Union(2,5);

	ufs.Print();


	ufs.Union(0,1);

	ufs.Print();

	ufs.FindRoot(4);
	ufs.FindRoot(9);

	ufs.Print();
}
*/