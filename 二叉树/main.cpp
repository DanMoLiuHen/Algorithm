#include<iostream>
#include<stack>
#include"Btree.h"
using namespace std;

/// <summary>
/// 二叉树的模板类
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class BTree {
private:
	BNode<T>* root;//记录根节点
	//BNode<T>* current;//记录当前节点
public:
	BTree() :root(NULL) {}
	BTree(T value) :root(new BNode<T>* (T)) {}
	~BTree() { destroy(root); }
	void destroy(BNode<T>* cur);//析构current节点及其所有子树，递归实现
	void makeTree();//用于构造二叉树，临时的
	void preorderNonRecursive();//借助栈完成前序遍历的非递归算法
	void inorderNonRecursive();//非递归中序遍历
	void postorderNonRecursive();//非递归后序遍历
};

template<class T>
void BTree<T>::destroy(BNode<T>*current) {
	//递归销毁从current开始的二叉树
	if (current != root) {
		destroy(current->getRight());
		destroy(current->getLeft());
		delete current;
	}
}

template<class T>
void BTree<T>::makeTree() {
	const int n = 7;
	BNode<T>* a = new BNode<T>[n];
	for (int i = 0; i < n; i++) {
		a[i].setData(i);
	}
	root = &a[0];
	a[0].setLeft(&a[1]);
	a[0].setRight(&a[2]);
	a[1].setLeft(&a[3]);
	a[1].setRight(&a[4]);
	a[2].setLeft(&a[5]);
	a[2].setRight(&a[6]);
}

template<class T>
void BTree<T>::preorderNonRecursive() {
	BNode<T>* current = root;
	//先确定二叉树存在
	if (current == NULL)
		return;
	stack<BNode<T>*>st;
	st.push(NULL);
	while (current != NULL&&!st.empty()) {
		cout << current->getData()<<" ";
		if (current->getLeft() != NULL) {
			st.push(current->getRight());
			current = current->getLeft();
			continue;
		}
		if (current->getRight()) {
			current = current->getRight();
			continue;
		}
		current = st.top();
		st.pop();
	}
}

template<class T>
void BTree<T>::inorderNonRecursive() {
	BNode<T>* current = root;
	if (current == NULL)
		return;
	stack<BNode<T>*>st;
	while (current||!st.empty()) {
		while (current) {
			st.push(current);
			current = current->getLeft();
		}
		if (!st.empty()) {
			current = st.top();
			st.pop();
			cout << current->getData() << " ";
			current = current->getRight();
		}
	}
}

/// <summary>
/// 后序遍历的非递归模式有两种实现方法
/// 1. 记录上一个访问节点
/// 2. 采用标记
/// 这里采用第一种方法
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
void BTree<T>::postorderNonRecursive() {
	BNode<T>* current = root, * last=NULL;//分别记录当前节点和上一个节点
	if (current == NULL)
		return;
	stack<BNode<T>*>st;
	st.push(NULL);
	while (current || !st.empty()) {
		while (current) {//向左子树走到底，叶子结点也会进栈
			st.push(current);
			current = current->getLeft();
		}
		while (!st.empty()) {
			current = st.top();
			st.pop();
			//当节点无右子树或右子树已被访问，则可以访问该节点
			if (current == NULL)
				break;
			if (current->getRight() == NULL || current->getRight() == last) {
				cout << current->getData()<<' ';
				last = current;//修改上一个访问的节点
			}
			else {//否则说明上一个访问的节点是左子树
				st.push(current);
				current = current->getRight();
				break;
			}
		}
	}
}

int main() {
	BTree<int> a;
	a.makeTree();
	a.preorderNonRecursive();
	cout << endl;
	a.inorderNonRecursive();
	cout << endl;
	a.postorderNonRecursive();
	return 0;
}
