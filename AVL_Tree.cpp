//AVL��������Ĭ��Ԫ��Ψһ
#include<iostream>
#include<vector>

template<typename T>
struct TreeNode {
	T _value;
	//ƽ�����ӣ��������߶ȼ��������߶�
	int _bf;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode* _parent;

	TreeNode(const T& value)
		:_value(value)
		, _bf(0)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};

template<typename T>
class AVLTree {
	typedef TreeNode<T> Node;
private:
	Node* _root;
public:
	//����
	AVLTree()
		:_root(nullptr)
	{}

	//����
	~AVLTree() {
		Destroy(_root);
	}

	//����AVL���ĺ���
	void Destroy(Node*& root) {
		if (nullptr != root) {
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
			root = nullptr;
		}
	}

	//����
	//�½����뵽�ϸ����������Ҳ࣬�ұ߸���ߵͣ������Ҫ����
	void RotateLeft(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;


		parent->_right = subRL;

		//���subRL���ڣ���Ҫ����subRL��˫�׽��ָ��
		if (nullptr != subRL) {
			subRL->_parent = parent;
		}

		subR->_left = parent;
		//˫�׽���˫��ָ��Ҳ��Ҫ�ı�
		parent->_parent = subR;

		//˫�׽���˫�ף����游�ڵ�
		Node* pparent = parent->_parent;
		subR->_parent = pparent;

		//����游�ڵ㲻���ڣ�˵��ԭ����˫�׽���Ǹ���㣬���ں��ӽ��Ҫ��ɸ����
		if (nullptr == pparent) {
			_root = subR;
		}
		else {
			//�游�ڵ���ڣ��ж�ԭ����˫�׽�����游�����ĸ����ӣ�ȥ����λ��
			if (pparent->_left == parent) {
				pparent->_left = subR;
			}
			else {
				pparent->_right = subR;
			}
		}
		//����ƽ������
		parent->_bf = 0;
		subR->_bf = 0;
	}

	//�ҵ���
	//�½����뵽�ϸ���������࣬��߸��ұߵͣ������Ҫ�ҵ���
	void RotateRight(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;

		//���subLR���ڣ�����˫�׽��ָ��ָ��
		if (nullptr != subLR) {
			subLR->_parent = parent;
		}

		subL->_right = parent;
		parent->_parent = subL;

		//�游���
		Node* pparent = parent->_parent;
		subL->_parent = pparent;

		//�ж��游����Ƿ���ڣ��������ڣ���ôsubL�����µĸ����
		if (nullptr == pparent) {
			_root = subL;
		}
		else {
			if (pparent->_left == parent) {
				pparent->_left = subL;
			}
			else {
				pparent->_right = subL;
			}
		}
		//����ƽ������
		parent->_bf = 0;
		subL->_bf = 0;
	}

	//����˫��
	//�½����뵽�ϸ��������Ҳ�
	void RotateLR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//����subLR��ƽ������
		int BF = subLR->_bf;

		//����
		RotateLeft(subL);
		//����
		RotateRight(parent);

		//����subLR��ƽ�����ӽ���ƽ�����Ӹ���
		if (BF == 1) {
			parent->_bf = 1;
		}
		else {
			subL->_bf = -1;
		}
	}

	//����˫��
	//�½����뵽�ϸ����������
	void RotateRL(Node* parent) {

		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//����subRL��ƽ������
		int BF = subRL->_bf;

		//����subRΪ���Ľ�������
		RotateRight(subR);

		//����
		RotateLeft(parent);

		//����subRL��ƽ�����ӽ���ƽ�����ӵĸ���
		if (BF == -1) {
			subR->_bf = 1;
		}
		else {
			parent->_bf = -1;
		}

	}

	//����
	bool Insert(const T& value) {
		//����
		if (nullptr == _root) {
			_root = new Node(value);
			return true;
		}

		//�ǿ���

		Node* child = _root;
		Node* parent = nullptr;

		//Ѱ���ʺϵĲ���λ��
		while (child) {
			parent = child;

			if (child->_value > value) {
				child = child->_left;
			}
			else if (child->_value < value) {
				child = child->_right;
			}
			else {
				return false;
			}
		}
		//�ҵ����ʵĲ���λ��
		child = new Node(value);

		//ѡ������λ��
		if (child->_value > parent->_value) {
			parent->_right = child;

		}
		else {
			parent->_left = child;
		}

		child->_parent = parent;

		//����ƽ������
		while (parent) {

			//���뵽�ұߣ�˫�׵�ƽ���������ӣ��������
			if (child == parent->_left) {
				parent->_bf--;
			}
			else {
				parent->_bf++;
			}

			//���˫��ƽ�����ӱ��0��˵��֮ǰ�Ѿ���һ�����ӣ���ô�Ͳ���Ҫ�������ϸ����ˡ�
			if (parent->_bf == 0) {
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {
				//˫�׽��ƽ�����ӱ�Ϊ1 -1 ˵��֮ǰû�к��ӣ������к����ˣ���Ҫ���ϸ���
				child = parent;
				parent = child->_parent;
			}
			else {
				//˵��˫�׽����2 -2 ��Ҫ������ת�ˡ�

				
				if (parent->_bf == 2) {
					//˫�׽��ƽ��������2��˵���������ߣ���Ҫ���У����� or ����˫��
					if (child->_bf == 1) {
						//���ӽ��ƽ��������1��˵���½����뵽�˽ϸ����������Ҳ�
						RotateLeft(parent);
					}
					else {
						//���ӽ��ƽ�����Ӳ���1��˵���½����뵽�˽ϸ����������
						RotateRL(parent);
					}

				}
				else {
					//˫�׽��ƽ��������-2��˵���������ߣ���Ҫ���У��ҵ��� or ����˫��
					if (child->_bf == -1) {
						//���ӽ��ƽ��������-1��˵���½����뵽�˽ϸ����������
						RotateRight(parent);
					}
					else {
						//���ӽ��ƽ�����Ӳ���-1��˵���½����뵽�˽ϸ��������Ҳ�
						RotateLR(parent);
					}
				}
				break;
			}
			return true;
		}
	}

	//�������
	void MiddleOrder() {
		if (nullptr != _root) {
			MiddleOrder(_root);
		}
	}

	void MiddleOrder(Node*& root) {
		if (nullptr != root) {
			MiddleOrder(root->_left);
			std::cout << root->_value << " ";
			MiddleOrder(root->_right);
		}
	}
};

int main() {

/*
	std::vector<int> arr = { 6,7,8,9,2,3,0,1,4,5 };
	AVLTree<int> avl;

	for (int i = 0; i < arr.size(); i++) {
		avl.Insert(arr[i]);
		avl.MiddleOrder();
		std::cout << std::endl;
	}
*/
	AVLTree<int> avl;
	for (int i = 1000; i >= -100; i--) {
		avl.Insert(i);
		avl.MiddleOrder();
		std::cout << std::endl;
	}

}