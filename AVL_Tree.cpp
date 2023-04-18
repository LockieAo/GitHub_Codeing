//AVL树，树中默认元素唯一
#include<iostream>
#include<vector>

template<typename T>
struct TreeNode {
	T _value;
	//平衡因子，右子树高度减左子树高度
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
	//构造
	AVLTree()
		:_root(nullptr)
	{}

	//析构
	~AVLTree() {
		Destroy(_root);
	}

	//销毁AVL树的函数
	void Destroy(Node*& root) {
		if (nullptr != root) {
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
			root = nullptr;
		}
	}

	//左单旋
	//新结点插入到较高右子树的右侧，右边高左边低，因此需要左单旋
	void RotateLeft(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;


		parent->_right = subRL;

		//如果subRL存在，需要更改subRL的双亲结点指针
		if (nullptr != subRL) {
			subRL->_parent = parent;
		}

		subR->_left = parent;
		//双亲结点的双亲指针也需要改变
		parent->_parent = subR;

		//双亲结点的双亲，即祖父节点
		Node* pparent = parent->_parent;
		subR->_parent = pparent;

		//如果祖父节点不存在，说明原本的双亲结点是根结点，现在孩子结点要变成根结点
		if (nullptr == pparent) {
			_root = subR;
		}
		else {
			//祖父节点存在，判断原本的双亲结点是祖父结点的哪个孩子，去接替位置
			if (pparent->_left == parent) {
				pparent->_left = subR;
			}
			else {
				pparent->_right = subR;
			}
		}
		//更新平衡因子
		parent->_bf = 0;
		subR->_bf = 0;
	}

	//右单旋
	//新结点插入到较高左子树左侧，左边高右边低，因此需要右单旋
	void RotateRight(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;

		//如果subLR存在，更改双亲结点指针指向
		if (nullptr != subLR) {
			subLR->_parent = parent;
		}

		subL->_right = parent;
		parent->_parent = subL;

		//祖父结点
		Node* pparent = parent->_parent;
		subL->_parent = pparent;

		//判断祖父结点是否存在，若不存在，那么subL就是新的根结点
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
		//更新平衡因子
		parent->_bf = 0;
		subL->_bf = 0;
	}

	//左右双旋
	//新结点插入到较高左子树右侧
	void RotateLR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//保存subLR的平衡因子
		int BF = subLR->_bf;

		//左旋
		RotateLeft(subL);
		//右旋
		RotateRight(parent);

		//根据subLR的平衡因子进行平衡因子更新
		if (BF == 1) {
			parent->_bf = 1;
		}
		else {
			subL->_bf = -1;
		}
	}

	//右左双旋
	//新结点插入到较高右子树左侧
	void RotateRL(Node* parent) {

		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//保存subRL的平衡因子
		int BF = subRL->_bf;

		//将以subR为根的进行右旋
		RotateRight(subR);

		//左旋
		RotateLeft(parent);

		//根据subRL的平衡因子进行平衡因子的更新
		if (BF == -1) {
			subR->_bf = 1;
		}
		else {
			parent->_bf = -1;
		}

	}

	//插入
	bool Insert(const T& value) {
		//空树
		if (nullptr == _root) {
			_root = new Node(value);
			return true;
		}

		//非空树

		Node* child = _root;
		Node* parent = nullptr;

		//寻找适合的插入位置
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
		//找到合适的插入位置
		child = new Node(value);

		//选择插入的位置
		if (child->_value > parent->_value) {
			parent->_right = child;

		}
		else {
			parent->_left = child;
		}

		child->_parent = parent;

		//更新平衡因子
		while (parent) {

			//插入到右边，双亲的平衡因子增加，否则减少
			if (child == parent->_left) {
				parent->_bf--;
			}
			else {
				parent->_bf++;
			}

			//如果双亲平衡因子变成0，说明之前已经有一个孩子，那么就不需要继续向上更新了。
			if (parent->_bf == 0) {
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {
				//双亲结点平衡因子变为1 -1 说明之前没有孩子，现在有孩子了，需要向上更新
				child = parent;
				parent = child->_parent;
			}
			else {
				//说明双亲结点变成2 -2 需要进行旋转了。

				
				if (parent->_bf == 2) {
					//双亲结点平衡因子是2，说明右子树高，需要进行：左单旋 or 右左双旋
					if (child->_bf == 1) {
						//孩子结点平衡因子是1，说明新结点插入到了较高右子树的右侧
						RotateLeft(parent);
					}
					else {
						//孩子结点平衡因子不是1，说明新结点插入到了较高右子树左侧
						RotateRL(parent);
					}

				}
				else {
					//双亲结点平衡因子是-2，说明左子树高，需要进行：右单旋 or 左右双旋
					if (child->_bf == -1) {
						//孩子结点平衡因子是-1，说明新结点插入到了较高左子树左侧
						RotateRight(parent);
					}
					else {
						//孩子结点平衡因子不是-1，说明新结点插入到了较高左子树右侧
						RotateLR(parent);
					}
				}
				break;
			}
			return true;
		}
	}

	//中序遍历
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