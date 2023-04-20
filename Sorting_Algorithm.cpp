#include<iostream>
#include<vector>
#include<stack>
using namespace std;

//�Ƚ���������
template<typename T>
class Less {
public:
	int operator()(T& left,T& right) {
		return left < right;
	}
};

//�Ƚ���������
template<typename T>
class Greater {
public:
	int operator()(T& left, T& right) {
		return left > right;
	}
};


//��ӡ����
template<typename T>
void Show(vector<T>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


//ð������
template<typename T,typename Compare=Less<T>>
void BubbleSort(vector<T>& arr, Compare compare=Less<T>()) {
	if (arr.size() == 0) {
		return;
	}
	//��ѭ����ð������
	for (int i = 0; i < arr.size() - 1; i++) {
		//��ѭ����ÿһ�ֽ�������Ԫ�رȽ�
		for (int j = 0; j < arr.size()-i-1; j++) {
			if (!compare(arr[j], arr[j + 1])) {
				swap(arr[j],arr[j+1]);
			}
		}
	}

}


//��������
template<typename T, typename Compare = Less<T>>
void InsertSort(vector<T>& arr, Compare compare=Less<T>()) {
	if (arr.size() == 0) {
		return;
	}

	for (int i = 1; i < arr.size(); i++) {
		//����ǰһ��Ԫ�ص��±�
		int index = i - 1;
		//����ҪѰ�Һ���λ�õ�Ԫ��
		int num = arr[i];
		while (index >=0 && !compare(arr[index],num)) {
			//���index�±��Ԫ�غ�num������ָ���Ĵ�С��ϵ���ͼ�������
			arr[index+1] = arr[index];
			index--;
		}
		//�ҵ�num����λ��
		arr[index + 1] = num;
	}
}

//ϣ������
template<typename T, typename Compare = Less<T>>
void ShellSort(vector<T>& arr, Compare compare = Less<T>()) {
	if (arr.size() == 0) {
		return;
	}


	//������
	int gap = arr.size();

	while (gap >= 1) {
		//Knuth����ķ��������·�ʽ
		gap = gap / 3 + 1;
		//�����gap�±꿪ʼ����֤��Ԫ��ǰ����һ���Ѿ������Ԫ��
		for (int i = gap; i < arr.size(); i++) {
			int index = i - gap;
			int num = arr[i];
			while (index >= 0 && !compare(arr[index], num)) {
				arr[index + gap] = arr[index];
				index = index-gap;
			}
			arr[index + gap] = num;
		}
		gap--;
	}
}

//ѡ������
template<typename T, typename Compare = Less<T>>
void SelectSort(vector<T>& arr,Compare compare = Less<T>()) {
	if (arr.size() == 0) {
		return;
	}

	//left �� right�Ǳ����� [left,right]
	int left = 0;
	int right = arr.size() - 1;


	while (left < right) {
		//�洢���������Ԫ���±꣬��СԪ���±�
		T Max = left;
		T Min = left;
		//Ѱ�Ҹ��������Ԫ�أ���СԪ���±�
		for (int i = left; i <= right; i++) {
			if (!compare(arr[i],arr[Max])) {
				Max = i;
			}

			if (compare(arr[i], arr[Min])) {
				Min = i;
			}
		}
		//Max�����right���Ͳ���Ҫ����
		if (Max != right) {
			//��ֹMinָ��right
			if (Min == right) {
				Min = Max;
			}
			swap(arr[Max],arr[right]);
		}

		//���Min��left���Ͳ���Ҫ����
		if (Min != left) {
			swap(arr[Min],arr[left]);
		}
		//��С����
		left++;
		right--;
	}
}

//�鲢����
template<typename T, typename Compare = Less<T>>
//�鲢����
void MergeData(vector<T>& arr, int left,int mid, int right, Compare compare) {
	//Ҫ�鲢���������ǰ�벿�� [left,mid)
	int begin1 = left;
	int end1 = mid;
	//Ҫ�鲢��������ĺ�벿�� [mid,right)
	int begin2 = mid;
	int end2 = right;
	//��ʱ���飬�洢�鲢�õ�����
	vector<T> temp(right-left);
	//��ʱ�����±�
	int index = 0;

	while (begin1 < end1 && begin2 < end2) {
		if (compare(arr[begin1],arr[begin2])) {
			temp[index++] = arr[begin1++];
		}
		else {
			temp[index++] = arr[begin2++];
		}
	}

	//Ԥ��ǰ�����䳤�Ȳ�һ�µ����
	while (begin1 < end1) {
		temp[index++] = arr[begin1++];
	}

	while (begin2 < end2) {
		temp[index++] = arr[begin2++];
	}

	index = 0;
	//����ʱ����Ľ��������ԭ����
	for (int i = left; i < right; i++) {
		arr[i] = temp[index++];
	}
}

template<typename T, typename Compare = Less<T>>
//�鲢�������� ������[left,right)
void _MergeSort(vector<T>& arr,int left,int right,Compare compare) {
	//��� right-left == 1��˵��������ֻ��һ��Ԫ�أ�����Ҫ�ٷ�
	if (right - left > 1) {
		int mid = (left + right) >> 1;
		//�鲢ǰ�벿������
		_MergeSort(arr,left,mid,compare);
		//�鲢��벿������
		_MergeSort(arr,mid,right,compare);
		//�鲢����������
		MergeData(arr,left,mid,right,compare);
	}
}

template<typename T, typename Compare = Less<T>>
//�鲢����
void MergeSort(vector<T>& arr,Compare compare=Less<T>()) {
	_MergeSort(arr,0,arr.size(),compare);
}

//��������

//����ȡ�з� [left,right)
template<typename T, typename Compare = Less<T>>
int GetMiddleIndex(vector<T>& arr,int left,int right) {
	int mid = (left+right) >> 1;

	if (arr[left] < arr[right - 1]) {
		if (arr[left] > arr[mid]) {
			return left;
		}
		else if (arr[mid] > arr[right-1]) {
			return right-1;
		}
		else {
			return mid;
		}
	}
	else {
		if (arr[left] < arr[mid]) {
			return left;
		}
		else if (arr[mid] < arr[right-1]) {
			return right - 1;
		}
		else {
			return mid;
		}
	}
	return 0;
}

//��������hoare���� [left,right��
template<typename T, typename Compare = Less<T>>
int Position1(vector<T>& arr,int left,int right,Compare compare=Less<T>()){
	int begin = left;
	int end = right - 1;
	//��ȡ�����������м�һ��Ԫ�ص��±�
	int mid = GetMiddleIndex(arr,left,right);
	//������±겻��end�±꣬�Ͱ����ǽ��н���
	if (mid != end) {
		swap(arr[mid],arr[end]);
	}
	//ket�����׼Ԫ�ص�ֵ
	T key = arr[end];

	while (begin < end) {
		//�����������ôbegin��ǰ���Ѱ�ұȻ�׼Ԫ�ش��Ԫ�ص��±�
		//����ǽ�����ôbegin��ǰ���Ѱ�ұȻ�׼Ԫ��С��Ԫ�ص��±�
		while (begin < end && compare(arr[begin], key)) {
			begin++;
		}
		//�����������ôend�Ӻ���ǰѰ�ұȻ�׼Ԫ��С��Ԫ�ص��±�
		//����ǽ�����ôend�Ӻ���ǰѰ�ұȻ�׼Ԫ�ش��Ԫ�ص��±�
		while (begin < end && !compare(arr[end], key)) {
			end--;
		}
		//���begin��endָ��Ĳ���ͬһ��Ԫ�أ���ô�Ͱ����ǽ��н���
		if (begin != end) {
			swap(arr[begin],arr[end]);
		}
	}
	//ѭ���˳���˵��begin��end��������ʱ���begin�ͻ�׼Ԫ�ص��±겻ͬ���Ͱ����ǽ��н�������ʱ��begin���ǻ�׼Ԫ�ص��±�
	if (begin != right - 1) {
		swap(arr[begin],arr[right-1]);
	}
	//���ػ�׼Ԫ���±�
	return begin;
}

//���������ڿӷ� [left,right��
template<typename T, typename Compare = Less<T>>
int Position2(vector<T>& arr, int left, int right, Compare compare = Less<T>()) {
	int begin = left;
	int end = right - 1;
	int mid = GetMiddleIndex(arr,left,right);

	if (mid != end) {
		swap(arr[mid],arr[end]);
	}

	T key = arr[end];
	//�տ�ʼ��ʱ��endλ����һ����
	while (begin < end) {
		//�����������ôbegin��ǰ���Ѱ�ұȻ�׼Ԫ�ش��Ԫ�ص��±�
		//����ǽ�����ôbegin��ǰ���Ѱ�ұȻ�׼Ԫ��С��Ԫ�ص��±�
		while (begin < end && compare(arr[begin], key)) {
			begin++;
		}
		//���begin<end��˵���ҵ���һ��������endλ�õĿӵ�Ԫ�أ���ôbegin��Ϊ�µĿ�
		if (begin < end) {
			arr[end] = arr[begin];
			end--;
		}

		//�����������ôend�Ӻ���ǰѰ�ұȻ�׼Ԫ��С��Ԫ�ص��±�
		//����ǽ�����ôend�Ӻ���ǰѰ�ұȻ�׼Ԫ�ش��Ԫ�ص��±�
		while (begin < end && !compare(arr[end], key)) {
			end--;
		}

		//���begin<end��˵���ҵ���һ��������beginλ�õĿӵ�Ԫ�أ���ôend��Ϊ�µĿ�
		if (begin < end) {
			arr[begin] = arr[end];
			begin++;
		}
	}
	//��begin==end��ѭ���˳�����ʱ˵������ͬʱָ��ͬһ���ӣ�����Ӿ���keyԪ�صĺ��ʵ�λ��
	arr[begin] = key;
	return begin;

}

//��������ǰ��ָ�� [left,right��
template<typename T, typename Compare = Less<T>>
int Position3(vector<T>& arr, int left, int right, Compare compare = Less<T>()) {
	//�������⣬����������Ϊ��
	//cur����Ѱ��prev����ıȻ�׼ֵ���Ԫ��
	int cur = left;
	//prevָ���������ĿǰΪֹ��һ�����ıȻ�׼ֵС�����һ��Ԫ�أ�prev��curһ�����غϣ���ô����֮���Ԫ�ض��ǱȻ�׼ֵ��ģ�
	int prev = cur - 1;

	int mid = GetMiddleIndex(arr,left,right);

	if (mid != (right-1)) {
		swap(arr[mid],arr[right-1]);
	}

	T key = arr[right-1];

	while (cur<right) {
		//���curָ���ֵС�ڻ�׼ֵ����ô�������Ƚ�prev��ǰһ�����ǲ��Ǻ�cur�غ�
		if (compare(arr[cur],key) && ++prev!=cur) {
			//������غϣ�˵������֮����Ԫ�أ���ЩԪ�رض��ǱȻ�׼ֵ���Ԫ�أ���˿��Խ��н���
			swap(arr[prev],arr[cur]);
		}
		//�����Ƿ񽻻���cur����Ҫ������ǰ��
		cur++;
	}
	//��Ϊprev��һ��Ԫ���������cur��˵���ǱȻ�׼ֵ���Ԫ�أ����prev�������һ��Ԫ�أ�˵���ҵ���׼ֵ��λ����
	if (++prev != right - 1) {
		swap(arr[prev],arr[right-1]);
	}

	return prev;

}

//��������ݹ�汾 [left,right)
template<typename T, typename Compare = Less<T>>
void QuickSortRecursion(vector<T>& arr,int left,int right,Compare compare = Less<T>()) {
	if (right - left <= 1) {
		return;
	}
	else {
		//��ȡ����[left,right)��һ���Ѿ��ҵ�����λ�õ�Ԫ�ص��±�
		int div = Position3(arr,left,right,compare);
		//ȥ������±����ߵ������Ԫ������
		QuickSortRecursion(arr,left,div,compare);
		QuickSortRecursion(arr,div+1,right,compare);
	}
}

//��������ѭ���汾 [left,right)
template<typename T, typename Compare = Less<T>>
void QuickSortCycle(vector<T>& arr, int left, int right, Compare compare = Less<T>()) {
	//ջ
	stack<int> helps;
	//�����ҽ磬�������
	helps.push(right);
	helps.push(left);

	while (!helps.empty()) {
		//��ȡ���
		left = helps.top();
		helps.pop();
		//��ȡ�ҽ�
		right = helps.top();
		helps.pop();

		if (right - left <= 1) {
			//��ʱ˵��������ֻ��һ��Ԫ�أ����������ǧ�򲻿����˳�����Ϊջ�п��ܻ�����������
		}
		else {
			//��ȡ��ǰ����Ļ�׼Ԫ�ص��±�
			int div = Position1(arr,left,right,compare);

			//����׼Ԫ���ұߵ�������ջ�������ҽ磬������硣�ǵ�divҪ+1����Ϊdiv��λ���Ѿ��ҵ��ˡ�
			helps.push(right);
			helps.push(div + 1);

			//����׼Ԫ����ߵ�������ջ�������ҽ磬�������
			helps.push(div);
			helps.push(left);
		}
	}
}


int main() {
	vector<int> arr = {5,1,2,1,6,3,87,2,3,87,354,3};
	//vector<int> arr = { 3,5,2,1};
	//BubbleSort(arr,Greater<int>());
	//InsertSort(arr, Greater<int>());
	//ShellSort(arr, Greater<int>());
	//SelectSort(arr,Greater<int>());
	//MergeSort(arr, Greater<int>());
	//QuickSortRecursion(arr,0,(int)arr.size());
	QuickSortCycle(arr, 0, (int)arr.size());
	Show(arr);
}