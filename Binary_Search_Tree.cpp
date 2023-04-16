//Ĭ�϶�����������㲻�ظ�
#include<iostream>
#include<vector>

//�����������Ľ��
template<typename T>
struct TreeNode {
public:
	T _val;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode(const T& val)
		:_val(val)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

//����������
template<typename T>
class BSTree {
	typedef TreeNode<T> Node;
private:
	Node* _root;
public:
	//����
	BSTree()
		:_root(nullptr)
	{}
	//����
	~BSTree()
	{
		//��������ɾ������
		Destory(_root);
	}
	//����ɾ������
	void Destory(Node*& root) {
		if (nullptr != root) {
			Destory(root->_left);
			Destory(root->_right);
			delete root;
			root = nullptr;
		}
	}

	//����
	bool Insert(const T& _value) {
		//������ǿ���
		if (nullptr == _root) {
			_root = new Node(_value);
			return true;
		}

		//����Ĳ��ǿ���
		Node* child = _root;
		Node* parent = nullptr;

		while (nullptr != child) {
			//������������˫�׽��
			parent = child;

			if (_value < child->_val) {
				child = child->_left;
			}
			else if (_value > child->_val) {
				child = child->_right;
			}
			else {
				return false;
			}
		}

		child = new Node(_value);

		//�ж�Ӧ�ò���˫�׽�����һ��
		if (_value < parent->_val) {
			parent->_left = child;
		}
		else {
			parent->_right = child;
		}
		return true;
	}

	//���Һ���
	Node* Find(const T& _value) {
		Node* child = _root;

		while (nullptr != child) {
			if (child->_val == _value) {
				return child;
			}
			else if (child->_val > _value) {
				child = child->_left;
			}
			else {
				child = child->_right;
			}
		}
		return nullptr;
	}

	//����������˴�ʹ�����غ���
	void MiddleOrder() {
		MiddleOrder(_root);
	}

	void MiddleOrder(Node*& root) {
		if (root) {
			MiddleOrder(root->_left);
			std::cout << root->_val << " ";
			MiddleOrder(root->_right);
		}
	}

	
	//ɾ��
	bool Erase(const T& _value) {
		//����
		if (nullptr == _root) {
			return false;
		}

		//�ǿ���

		Node* child = _root;
		Node* parent = nullptr;
		//Ѱ�Ҵ�ɾ����㣬parent�����ɾ������˫�׽�㣬child���Ǵ�ɾ�����

		while (nullptr != child) {
			if (child->_val == _value) {
				break;
			}
			else if (child->_val > _value) {
				parent = child;
				child = child->_left;
			}
			else {
				parent = child;
				child = child->_right;
			}
		}

		//û�иý��
		if (nullptr == child) {
			return false;
		}

		//����ɾ��
		if (nullptr == child->_left) {
			//Ҫ��ɾ���Ľ�㣺��1��ֻ���Һ��� ��2����Ҷ�ӽ��

			//�ж�Ҫɾ�����Ƿ��Ǹ����
			if (nullptr == parent) {
				_root = _root->_right;
				return true;
			}

			//���Ǹ��ڵ�
			//�ж�Ҫɾ���Ľ����˫�׵����ӻ����Һ���

			if (parent->_left == child) {
				parent->_left = child->_right;
			}
			else {
				parent->_right = child->_right;
			}
			
		}
		else if (nullptr == child->_right) {
			//Ҫ��ɾ���Ľ�㣺ֻ������

			//�ж�Ҫɾ�����Ƿ��Ǹ��ڵ�
			if (nullptr == parent) {
				_root = _root->_left;
				return true;
			}

			//�ж�Ҫɾ���Ľ����˫�׽������ӻ����Һ���
			if (parent->_left == child) {
				parent->_left = child->_left;
			}
			else {
				parent->_right = child->_left;
			}
			
		}
		else {
			//Ҫ��ɾ���Ľ�㣺���Һ��Ӷ�����
			//�����ҪѰ������ڵ㣬������������ң�������������С��㣬�������ڵ㣬��ô�����������������
			
			//����������
			Node* DelNode = child->_right;
			//parent�����ɾ������˫�׽��
			parent = child;

			//Ѱ���������������ڵ�
			while (nullptr != DelNode->_left) {
				parent = DelNode;
				DelNode = DelNode->_left;
			}
			//���������ֵ����ɾ����㸳ֵ
			child->_val = DelNode->_val;

			//�ȴ��߼���ɾ������ڵ㣺��������û����������
			if (DelNode == parent->_left) {
				parent->_left = DelNode->_right;
			}
			else {
				parent->_right = DelNode->_right;
			}
			//��child����������
			child = DelNode;
			
		}
		//ɾ����ɾ�����
		delete child;
		return true;
	}
};
int main() {
	BSTree<int> bt;
	std::vector<int> arr = { 6,7,8,9,2,3,0,1,4,5 };

	for (int i = 0; i < arr.size(); i++) {
		bt.Insert(arr[i]);
		bt.MiddleOrder();
		std::cout << std::endl;
	}

	bt.Erase(6);
	bt.MiddleOrder();
	std::cout << std::endl;
	bt.Erase(3);
	bt.MiddleOrder();
}

