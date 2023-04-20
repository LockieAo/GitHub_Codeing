#include<iostream>
#include<vector>
#include<stack>
using namespace std;

//比较器，升序
template<typename T>
class Less {
public:
	int operator()(T& left,T& right) {
		return left < right;
	}
};

//比较器，降序
template<typename T>
class Greater {
public:
	int operator()(T& left, T& right) {
		return left > right;
	}
};


//打印函数
template<typename T>
void Show(vector<T>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


//冒泡排序
template<typename T,typename Compare=Less<T>>
void BubbleSort(vector<T>& arr, Compare compare=Less<T>()) {
	if (arr.size() == 0) {
		return;
	}
	//外循环，冒泡轮数
	for (int i = 0; i < arr.size() - 1; i++) {
		//内循环，每一轮进行相邻元素比较
		for (int j = 0; j < arr.size()-i-1; j++) {
			if (!compare(arr[j], arr[j + 1])) {
				swap(arr[j],arr[j+1]);
			}
		}
	}

}


//插入排序
template<typename T, typename Compare = Less<T>>
void InsertSort(vector<T>& arr, Compare compare=Less<T>()) {
	if (arr.size() == 0) {
		return;
	}

	for (int i = 1; i < arr.size(); i++) {
		//保存前一个元素的下标
		int index = i - 1;
		//保存要寻找合适位置的元素
		int num = arr[i];
		while (index >=0 && !compare(arr[index],num)) {
			//如果index下标的元素和num不构成指定的大小关系，就继续搬移
			arr[index+1] = arr[index];
			index--;
		}
		//找到num合适位置
		arr[index + 1] = num;
	}
}

//希尔排序
template<typename T, typename Compare = Less<T>>
void ShellSort(vector<T>& arr, Compare compare = Less<T>()) {
	if (arr.size() == 0) {
		return;
	}


	//分组间隔
	int gap = arr.size();

	while (gap >= 1) {
		//Knuth提出的分组间隔更新方式
		gap = gap / 3 + 1;
		//分组从gap下标开始，保证该元素前面有一个已经有序的元素
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

//选择排序
template<typename T, typename Compare = Less<T>>
void SelectSort(vector<T>& arr,Compare compare = Less<T>()) {
	if (arr.size() == 0) {
		return;
	}

	//left 和 right是闭区间 [left,right]
	int left = 0;
	int right = arr.size() - 1;


	while (left < right) {
		//存储该区间最大元素下标，最小元素下标
		T Max = left;
		T Min = left;
		//寻找该区间最大元素，最小元素下标
		for (int i = left; i <= right; i++) {
			if (!compare(arr[i],arr[Max])) {
				Max = i;
			}

			if (compare(arr[i], arr[Min])) {
				Min = i;
			}
		}
		//Max如果是right，就不需要交换
		if (Max != right) {
			//防止Min指向right
			if (Min == right) {
				Min = Max;
			}
			swap(arr[Max],arr[right]);
		}

		//如果Min是left，就不需要交换
		if (Min != left) {
			swap(arr[Min],arr[left]);
		}
		//缩小区间
		left++;
		right--;
	}
}

//归并排序
template<typename T, typename Compare = Less<T>>
//归并数据
void MergeData(vector<T>& arr, int left,int mid, int right, Compare compare) {
	//要归并的子区间的前半部分 [left,mid)
	int begin1 = left;
	int end1 = mid;
	//要归并的子区间的后半部分 [mid,right)
	int begin2 = mid;
	int end2 = right;
	//临时数组，存储归并好的数据
	vector<T> temp(right-left);
	//临时数组下标
	int index = 0;

	while (begin1 < end1 && begin2 < end2) {
		if (compare(arr[begin1],arr[begin2])) {
			temp[index++] = arr[begin1++];
		}
		else {
			temp[index++] = arr[begin2++];
		}
	}

	//预防前后区间长度不一致的情况
	while (begin1 < end1) {
		temp[index++] = arr[begin1++];
	}

	while (begin2 < end2) {
		temp[index++] = arr[begin2++];
	}

	index = 0;
	//把临时数组的结果拷贝到原数组
	for (int i = left; i < right; i++) {
		arr[i] = temp[index++];
	}
}

template<typename T, typename Compare = Less<T>>
//归并排序主体 开区间[left,right)
void _MergeSort(vector<T>& arr,int left,int right,Compare compare) {
	//如果 right-left == 1，说明该区间只有一个元素，不需要再分
	if (right - left > 1) {
		int mid = (left + right) >> 1;
		//归并前半部分区间
		_MergeSort(arr,left,mid,compare);
		//归并后半部分区间
		_MergeSort(arr,mid,right,compare);
		//归并该区间数据
		MergeData(arr,left,mid,right,compare);
	}
}

template<typename T, typename Compare = Less<T>>
//归并排序
void MergeSort(vector<T>& arr,Compare compare=Less<T>()) {
	_MergeSort(arr,0,arr.size(),compare);
}

//快速排序

//三数取中法 [left,right)
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

//快速排序：hoare方法 [left,right）
template<typename T, typename Compare = Less<T>>
int Position1(vector<T>& arr,int left,int right,Compare compare=Less<T>()){
	int begin = left;
	int end = right - 1;
	//获取三个数中最中间一个元素的下标
	int mid = GetMiddleIndex(arr,left,right);
	//如果该下标不是end下标，就把他们进行交换
	if (mid != end) {
		swap(arr[mid],arr[end]);
	}
	//ket保存基准元素的值
	T key = arr[end];

	while (begin < end) {
		//如果是升序，那么begin从前向后寻找比基准元素大的元素的下标
		//如果是降序，那么begin从前向后寻找比基准元素小的元素的下标
		while (begin < end && compare(arr[begin], key)) {
			begin++;
		}
		//如果是升序，那么end从后向前寻找比基准元素小的元素的下标
		//如果是降序，那么end从后向前寻找比基准元素大的元素的下标
		while (begin < end && !compare(arr[end], key)) {
			end--;
		}
		//如果begin和end指向的不是同一个元素，那么就把他们进行交换
		if (begin != end) {
			swap(arr[begin],arr[end]);
		}
	}
	//循环退出，说明begin和end相遇，此时如果begin和基准元素的下标不同，就把他们进行交换，此时的begin就是基准元素的下标
	if (begin != right - 1) {
		swap(arr[begin],arr[right-1]);
	}
	//返回基准元素下标
	return begin;
}

//快速排序：挖坑法 [left,right）
template<typename T, typename Compare = Less<T>>
int Position2(vector<T>& arr, int left, int right, Compare compare = Less<T>()) {
	int begin = left;
	int end = right - 1;
	int mid = GetMiddleIndex(arr,left,right);

	if (mid != end) {
		swap(arr[mid],arr[end]);
	}

	T key = arr[end];
	//刚开始的时候，end位置是一个坑
	while (begin < end) {
		//如果是升序，那么begin从前向后寻找比基准元素大的元素的下标
		//如果是降序，那么begin从前向后寻找比基准元素小的元素的下标
		while (begin < end && compare(arr[begin], key)) {
			begin++;
		}
		//如果begin<end，说明找到了一个可以填end位置的坑的元素，那么begin成为新的坑
		if (begin < end) {
			arr[end] = arr[begin];
			end--;
		}

		//如果是升序，那么end从后向前寻找比基准元素小的元素的下标
		//如果是降序，那么end从后向前寻找比基准元素大的元素的下标
		while (begin < end && !compare(arr[end], key)) {
			end--;
		}

		//如果begin<end，说明找到了一个可以填begin位置的坑的元素，那么end成为新的坑
		if (begin < end) {
			arr[begin] = arr[end];
			begin++;
		}
	}
	//当begin==end，循环退出，此时说明它们同时指向同一个坑，这个坑就是key元素的合适的位置
	arr[begin] = key;
	return begin;

}

//快速排序：前后指针 [left,right）
template<typename T, typename Compare = Less<T>>
int Position3(vector<T>& arr, int left, int right, Compare compare = Less<T>()) {
	//便于理解，这里以升序为例
	//cur负责寻找prev后面的比基准值大的元素
	int cur = left;
	//prev指向该区间中目前为止的一连串的比基准值小的最后一个元素（prev和cur一旦不重合，那么它们之间的元素都是比基准值大的）
	int prev = cur - 1;

	int mid = GetMiddleIndex(arr,left,right);

	if (mid != (right-1)) {
		swap(arr[mid],arr[right-1]);
	}

	T key = arr[right-1];

	while (cur<right) {
		//如果cur指向的值小于基准值，那么接下来比较prev向前一步后是不是和cur重合
		if (compare(arr[cur],key) && ++prev!=cur) {
			//如果不重合，说明它们之间有元素，那些元素必定是比基准值大的元素，因此可以进行交换
			swap(arr[prev],arr[cur]);
		}
		//不管是否交换，cur都需要继续向前走
		cur++;
	}
	//因为prev下一个元素如果不是cur，说明是比基准值大的元素，如果prev不是最后一个元素，说明找到基准值的位置了
	if (++prev != right - 1) {
		swap(arr[prev],arr[right-1]);
	}

	return prev;

}

//快速排序递归版本 [left,right)
template<typename T, typename Compare = Less<T>>
void QuickSortRecursion(vector<T>& arr,int left,int right,Compare compare = Less<T>()) {
	if (right - left <= 1) {
		return;
	}
	else {
		//获取区间[left,right)中一个已经找到合适位置的元素的下标
		int div = Position3(arr,left,right,compare);
		//去给这个下标两边的区间的元素排序
		QuickSortRecursion(arr,left,div,compare);
		QuickSortRecursion(arr,div+1,right,compare);
	}
}

//快速排序循环版本 [left,right)
template<typename T, typename Compare = Less<T>>
void QuickSortCycle(vector<T>& arr, int left, int right, Compare compare = Less<T>()) {
	//栈
	stack<int> helps;
	//先入右界，再入左界
	helps.push(right);
	helps.push(left);

	while (!helps.empty()) {
		//先取左界
		left = helps.top();
		helps.pop();
		//后取右界
		right = helps.top();
		helps.pop();

		if (right - left <= 1) {
			//此时说明区间中只有一个元素，无需操作，千万不可以退出，因为栈中可能还有其他区间
		}
		else {
			//获取当前区间的基准元素的下标
			int div = Position1(arr,left,right,compare);

			//将基准元素右边的区间入栈，先入右界，再入左界。记得div要+1，因为div的位置已经找到了。
			helps.push(right);
			helps.push(div + 1);

			//将基准元素左边的区间入栈，先入右界，再入左界
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