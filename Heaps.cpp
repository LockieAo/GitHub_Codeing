#include<iostream>
#include<vector>
#include<assert.h>

//大堆比较器
template<typename DateType>
class Max {
public:
	int operator()(const DateType& d1,const DateType& d2)const {
		return d1 > d2;
	}
};
//小堆比较器
template<typename DateType>
class Min {
public:
	int operator()(const DateType& d1, const DateType& d2)const {
		return d1 < d2;
	}
};

//模板参数分别是：存储的元素类型 比较器类型
template<typename DateType,typename Compare>
class Heap {
private:
	//底层使用vector存储元素
	std::vector<DateType> _array;
public:
	//无参构造
	Heap(){}

	//区间构造
	template<typename Iterator>
	Heap(Iterator first,Iterator last)
		:_array(first,last)
	{
		//从第一个非叶子结点开始向下调整
		for (int i = (_array.size() - 1) / 2; i >= 0; i--) {
			AdjustDown(i);
		}
	}

	//获取堆顶元素
	int top() {
		if (_array.size() == 0) {
			assert(0);
		}
		return _array[0];
	}
	//堆判空
	bool empty() {
		return _array.empty();
	}

	//获取堆中元素个数
	int size() {
		return _array.size();
	}

	//向堆中添加元素
	void push(const DateType& value) {
		_array.push_back(value);
		//从最后一个元素开始向上调整
		AdjustUp(_array.size()-1);
	}
	
	//删除堆顶元素
	void pop() {
		if (_array.empty()) {
			assert(0);
		}
		//交换堆顶和最后一个元素
		std::swap(_array[0],_array[_array.size()-1]);
		//删除堆顶元素
		_array.pop_back();
		//向下调整
		AdjustDown(0);
	}

	//向上调整
	void AdjustUp(size_t child) {
		//将要被调整的结点的双亲结点的下标
		size_t parent = (child - 1) / 2;
		//比较器
		Compare compare;
		//只要这个结点还有孩子，就继续调整
		while (child) {
			if (compare(_array[child], _array[parent])) {
				//不满足堆的性质，交换双亲和孩子
				std::swap(_array[parent],_array[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else {
				//如果此时已经满足堆的性质，停止调整
				return;
			}
		}
	}

	//向下调整
	void AdjustDown(size_t parent) {
		//要调整的结点的左孩子结点的下标
		size_t child = parent * 2 + 1;
		//比较器
		Compare compare;
		//避免越界
		while (child < _array.size()) {
			//如果有右孩子，那么就让child指向最大或最小的孩子，这取决于是大堆还是小堆
			if (child + 1 < _array.size() && compare(_array[child+1], _array[child])) {
				child++;
			}

			if (compare(_array[child],_array[parent])) {
				//不满足堆的性质
				std::swap(_array[parent],_array[child]);
				parent = child;
				child = parent*2+1;
			}
			else {
				//满足堆的性质，直接退出
				return;
			}
		}
	}
};

int main() {
	std::vector<int> arr = { 9,8,2,6,4,7,5,3,1 };


	Heap<int,Min<int>> hp(arr.begin(),arr.end());
	
	while (hp.size() != 0) {
		std::cout << hp.top()<<std::endl;
		hp.pop();
	}
	
	Heap<int, Min<int>> hps;
	int i = 0;
	int num = arr.size()-1;

	while (i <= num) {
		hps.push(arr[i]);
		std::cout <<"hp.top:" << hp.top() <<" hp.size："<<hp.size() << std::endl;
		i++;
	}
}

