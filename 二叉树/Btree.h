#pragma once


/// <summary>
/// 二叉树的节点类
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class BNode {
private:
	BNode<T>* left, * right;
	T data;
public:
	BNode() :left(NULL), right(NULL) {}
	BNode(T item, BNode<T>* right = NULL, BNode<T>* left = NULL) :data(item), right(right), left(left) {}
	~BNode() {}
	T getData() { return data; }
	BNode<T>* getLeft() { return left; }
	BNode<T>* getRight() { return right; }
	void setData(T item) { data = item; }
	void setLeft(BNode<T>* lef) { left = lef; }
	void setRight(BNode<T>* rig) { right = rig; }
};
