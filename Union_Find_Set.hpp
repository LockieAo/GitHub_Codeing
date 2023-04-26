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

	//����Ԫ������λ�õ��±꣬����Ԫ�����ڼ��ϵĸ���㣨����֮��ͽ���·��ѹ����
	int FindRoot(int index) {
		int root = index;
		//��ȡ���±����ڼ��ϵĸ����
		while (_arr[root] >= 0) {
			root = _arr[root];
		}
		
		//·��ѹ��
		while (_arr[index] >= 0) {
			//��ȡ���±��Ӧ��˫�׽���±�
			int parent = _arr[index];
			//�����±��Ӧ��˫�׽����±����Ϊ�ü��ϸ�����±�
			_arr[index] = root;
			//����index�������ϸ���
			index = parent;
		}
		
		return root;
	}

	//��������Ԫ���м��ϵĸ���
	size_t SetSize() {
		size_t count = 0;
		//������±��Ӧ��ֵ�Ǹ�����˵���Ǹü��ϸ����
		for (int i = 0; i < _arr.size(); i++) {
			if (_arr[i] < 0) {
				count++;
			}
		}

		return count;
	}

	//��������Ԫ�ص��±꣬�ϲ�����Ԫ�صļ��ϵ�ͬһ������
	bool Union(int index1,int index2) {
		//��ȡ����Ԫ�صļ��ϵĸ����
		int root1 = FindRoot(index1);
		int root2 = FindRoot(index2);

		//�ж�����Ԫ���ǲ�����ͬһ������
		if (root1 == root2) {
			return false;
		}

		//�Ѹ�����н�С��һ����Ϊ�¼��ϵĸ����
		if (root1 > root2) {
			swap(root1,root2);
		}

		//�ϲ����ϣ���һ�����ϵĸ������Ϊ��һ�����ϵ��ӽ��
		_arr[root1] += _arr[root2];
		_arr[root2] = root1;

		return true;
	}

	//�ж�����Ԫ���Ƿ���ͬһ������
	bool Inset(int x1,int x2) {
		return FindRoot(x1) == FindRoot(x2);
	}

	//��ӡ
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