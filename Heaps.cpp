#include<iostream>
#include<vector>
#include<assert.h>

//��ѱȽ���
template<typename DateType>
class Max {
public:
	int operator()(const DateType& d1,const DateType& d2)const {
		return d1 > d2;
	}
};
//С�ѱȽ���
template<typename DateType>
class Min {
public:
	int operator()(const DateType& d1, const DateType& d2)const {
		return d1 < d2;
	}
};

//ģ������ֱ��ǣ��洢��Ԫ������ �Ƚ�������
template<typename DateType,typename Compare>
class Heap {
private:
	//�ײ�ʹ��vector�洢Ԫ��
	std::vector<DateType> _array;
public:
	//�޲ι���
	Heap(){}

	//���乹��
	template<typename Iterator>
	Heap(Iterator first,Iterator last)
		:_array(first,last)
	{
		//�ӵ�һ����Ҷ�ӽ�㿪ʼ���µ���
		for (int i = (_array.size() - 1) / 2; i >= 0; i--) {
			AdjustDown(i);
		}
	}

	//��ȡ�Ѷ�Ԫ��
	int top() {
		if (_array.size() == 0) {
			assert(0);
		}
		return _array[0];
	}
	//���п�
	bool empty() {
		return _array.empty();
	}

	//��ȡ����Ԫ�ظ���
	int size() {
		return _array.size();
	}

	//���������Ԫ��
	void push(const DateType& value) {
		_array.push_back(value);
		//�����һ��Ԫ�ؿ�ʼ���ϵ���
		AdjustUp(_array.size()-1);
	}
	
	//ɾ���Ѷ�Ԫ��
	void pop() {
		if (_array.empty()) {
			assert(0);
		}
		//�����Ѷ������һ��Ԫ��
		std::swap(_array[0],_array[_array.size()-1]);
		//ɾ���Ѷ�Ԫ��
		_array.pop_back();
		//���µ���
		AdjustDown(0);
	}

	//���ϵ���
	void AdjustUp(size_t child) {
		//��Ҫ�������Ľ���˫�׽����±�
		size_t parent = (child - 1) / 2;
		//�Ƚ���
		Compare compare;
		//ֻҪ�����㻹�к��ӣ��ͼ�������
		while (child) {
			if (compare(_array[child], _array[parent])) {
				//������ѵ����ʣ�����˫�׺ͺ���
				std::swap(_array[parent],_array[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else {
				//�����ʱ�Ѿ�����ѵ����ʣ�ֹͣ����
				return;
			}
		}
	}

	//���µ���
	void AdjustDown(size_t parent) {
		//Ҫ�����Ľ������ӽ����±�
		size_t child = parent * 2 + 1;
		//�Ƚ���
		Compare compare;
		//����Խ��
		while (child < _array.size()) {
			//������Һ��ӣ���ô����childָ��������С�ĺ��ӣ���ȡ�����Ǵ�ѻ���С��
			if (child + 1 < _array.size() && compare(_array[child+1], _array[child])) {
				child++;
			}

			if (compare(_array[child],_array[parent])) {
				//������ѵ�����
				std::swap(_array[parent],_array[child]);
				parent = child;
				child = parent*2+1;
			}
			else {
				//����ѵ����ʣ�ֱ���˳�
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
		std::cout <<"hp.top:" << hp.top() <<" hp.size��"<<hp.size() << std::endl;
		i++;
	}
}
