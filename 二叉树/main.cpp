#include<iostream>
#include<stack>
#include"Btree.h"
using namespace std;

/// <summary>
/// ��������ģ����
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class BTree {
private:
	BNode<T>* root;//��¼���ڵ�
	//BNode<T>* current;//��¼��ǰ�ڵ�
public:
	BTree() :root(NULL) {}
	BTree(T value) :root(new BNode<T>* (T)) {}
	~BTree() { destroy(root); }
	void destroy(BNode<T>* cur);//����current�ڵ㼰�������������ݹ�ʵ��
	void makeTree();//���ڹ������������ʱ��
	void preorderNonRecursive();//����ջ���ǰ������ķǵݹ��㷨
	void inorderNonRecursive();//�ǵݹ��������
	void postorderNonRecursive();//�ǵݹ�������
};

template<class T>
void BTree<T>::destroy(BNode<T>*current) {
	//�ݹ����ٴ�current��ʼ�Ķ�����
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
	//��ȷ������������
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
/// ��������ķǵݹ�ģʽ������ʵ�ַ���
/// 1. ��¼��һ�����ʽڵ�
/// 2. ���ñ��
/// ������õ�һ�ַ���
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
void BTree<T>::postorderNonRecursive() {
	BNode<T>* current = root, * last=NULL;//�ֱ��¼��ǰ�ڵ����һ���ڵ�
	if (current == NULL)
		return;
	stack<BNode<T>*>st;
	st.push(NULL);
	while (current || !st.empty()) {
		while (current) {//���������ߵ��ף�Ҷ�ӽ��Ҳ���ջ
			st.push(current);
			current = current->getLeft();
		}
		while (!st.empty()) {
			current = st.top();
			st.pop();
			//���ڵ������������������ѱ����ʣ�����Է��ʸýڵ�
			if (current == NULL)
				break;
			if (current->getRight() == NULL || current->getRight() == last) {
				cout << current->getData()<<' ';
				last = current;//�޸���һ�����ʵĽڵ�
			}
			else {//����˵����һ�����ʵĽڵ���������
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
