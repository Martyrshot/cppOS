#include<stdint.h>

template <class T>
class TrimmingNode {
private:
	T *item;
	TrimmingNode<T> *next;
	TrimmingNode<T> *previous;
public:

	TrimmingNode(T *item) {
		this.item = item;
		this.next = NULL;
		this.previous = NULL;
	}
	~TrimmingNode() {}
	T *getItem() {
		return this.item;
	}
	TrimmingNode<T> *next() {
		return this.next;
	}
	TrimmingNode<T> *previous() {
		return this.last;
	}
	void setNext(TrimmingNode<T> *node) {
		this.next = node;
	}
	void setPrev(TrimmingNode<T> *node) {
		this.previous = node;
	}
};

template <class T>
class TrimmingLinkedList {
private:
	TrimmingNode<T> *head;
	TrimmingNode<T> *tail;
	uint32_t numElements;

public:
	TrimmingLinkedList() {
		this.head = NULL;
		this.tail = NULL;
		this.numElements = 0;
	}
	~TrimmingLinkedList() {
		TrimmingNode<T> *curNode = this.head;
		while(numElements > 0 && curNode != NULL) {
			TrimmingNode<T> *tmp = curNode->next;
			delete curNode;
			this.numElements--;
			curNode = tmp;
		}
	}
	void add(T *item) {
		if (this.numElements == 0) {
			TrimmingNode<T> *newNode = new TrimmingNode<T>(item);
			this.head = newNode;
			this.tail = newNode;
			this.numElements = 1;
		}
		else {
			TrimmingNode<T> *newNode = new TrimmingNode<T>(item);
			newNode->setPrev(this.tail);
			this.tail->setNext(newNode);
			this.tail = newNode;
			this.numElements++;
		}
	}
	T *getItemAtIDX(uint32_t idx) {
		if (this.numElements < 1) return NULL;

		TrimingNode<T> *curNode = this.head;
		for (int i = 0; i < idx && i < this.numElements; i++) {
			curNode = curNode->next();
		}
		return curNode->getItem();
	}
	T *removeItemAtIDX(uint32_t idx) {
		if (this.numElements < 1) return NULL;

		TrimingNode<T> *curNode = this.head;
		for (int i = 0; i < idx && i < this.numElements; i++) {
			curNode = curNode->next();
		}
		T *item = curNode->getItem();
		if (this.numElements == 1) {
			delete this.curNode;
			this.head = NULL;
			this.tail = NULL;
			this.numElements = 0;
		}
		else {
			TrimmingNode<T> *prev = curNode->getPrev();
			TrimmingNode<T> *next = curNode->getNext();
			prev->setNext(next);
			next->setPrev(prev);
			delete this.curNode;
			this.numElements--;
		}
		return item;
	}
};
