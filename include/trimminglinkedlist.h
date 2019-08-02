#ifndef __trimminglinkedlist_h__
#define __trimminglinkedlist_h__

#include<stdint.h>
#include<stddef.h>

template <class T>
class TrimmingNode {
private:
	T *item;
	TrimmingNode<T> *next;
	TrimmingNode<T> *previous;
public:
	TrimmingNode(T *item);
	~TrimmingNode();
	T *getItem();
	TrimmingNode<T> *getNext();
	TrimmingNode<T> *getPrevious();
	void setNext(TrimmingNode<T> *node);
	void setPrev(TrimmingNode<T> *node);
};

template <class T>
class TrimmingLinkedList {
private:
	TrimmingNode<T> *head;
	TrimmingNode<T> *tail;
	TrimmingNode<T> *curNode;
	uint32_t numElements;

public:
	TrimmingLinkedList();
	~TrimmingLinkedList();
	void add(T *item);
	T *getItemAtIDX(uint32_t idx);
	T *removeItemAtIDX(uint32_t idx);
	T *next();
	T *prev();
	T *curItem();
	T *first();
	T *last();
};
#endif
