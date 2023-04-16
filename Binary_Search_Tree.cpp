//默认二叉搜索树结点不重复
#include<iostream>
#include<vector>

//二叉搜索树的结点
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

//二叉搜索树
template<typename T>
class BSTree {
	typedef TreeNode<T> Node;
private:
	Node* _root;
public:
	//构造
	BSTree()
		:_root(nullptr)
	{}
	//析构
	~BSTree()
	{
		//调用树的删除函数
		Destory(_root);
	}
	//树的删除函数
	void Destory(Node*& root) {
		if (nullptr != root) {
			Destory(root->_left);
			Destory(root->_right);
			delete root;
			root = nullptr;
		}
	}

	//插入
	bool Insert(const T& _value) {
		//插入的是空树
		if (nullptr == _root) {
			_root = new Node(_value);
			return true;
		}

		//插入的不是空树
		Node* child = _root;
		Node* parent = nullptr;

		while (nullptr != child) {
			//保存待插入结点的双亲结点
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

		//判断应该插入双亲结点的哪一边
		if (_value < parent->_val) {
			parent->_left = child;
		}
		else {
			parent->_right = child;
		}
		return true;
	}

	//查找函数
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

	//中序遍历，此处使用重载函数
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

	
	//删除
	bool Erase(const T& _value) {
		//空树
		if (nullptr == _root) {
			return false;
		}

		//非空树

		Node* child = _root;
		Node* parent = nullptr;
		//寻找待删除结点，parent保存待删除结点的双亲结点，child则是待删除结点

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

		//没有该结点
		if (nullptr == child) {
			return false;
		}

		//分类删除
		if (nullptr == child->_left) {
			//要被删除的结点：（1）只有右孩子 （2）是叶子结点

			//判断要删除的是否是根结点
			if (nullptr == parent) {
				_root = _root->_right;
				return true;
			}

			//不是根节点
			//判断要删除的结点是双亲的左孩子还是右孩子

			if (parent->_left == child) {
				parent->_left = child->_right;
			}
			else {
				parent->_right = child->_right;
			}
			
		}
		else if (nullptr == child->_right) {
			//要被删除的结点：只有左孩子

			//判断要删除的是否是根节点
			if (nullptr == parent) {
				_root = _root->_left;
				return true;
			}

			//判断要删除的结点是双亲结点的左孩子还是右孩子
			if (parent->_left == child) {
				parent->_left = child->_left;
			}
			else {
				parent->_right = child->_left;
			}
			
		}
		else {
			//要被删除的结点：左右孩子都存在
			//因此需要寻找替代节点，这里从右子树找，找右子树的最小结点，即最左侧节点，那么这个结点绝不会有左孩子
			
			//保存替代结点
			Node* DelNode = child->_right;
			//parent保存待删除结点的双亲结点
			parent = child;

			//寻找右子树的最左侧节点
			while (nullptr != DelNode->_left) {
				parent = DelNode;
				DelNode = DelNode->_left;
			}
			//用替代结点的值给待删除结点赋值
			child->_val = DelNode->_val;

			//先从逻辑上删除替代节点：替代结点是没有左子树的
			if (DelNode == parent->_left) {
				parent->_left = DelNode->_right;
			}
			else {
				parent->_right = DelNode->_right;
			}
			//用child保存替代结点
			child = DelNode;
			
		}
		//删除待删除结点
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


