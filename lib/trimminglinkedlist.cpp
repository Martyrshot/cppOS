#include<trimminglinkedlist.h>

/****************************************************************************************************
 * TRIMMINGNODE IMPLEMENTATION
****************************************************************************************************/

template <class T>
TrimmingNode<T>::TrimmingNode(T *item) {
	this->item = item;
	this->next = NULL;
	this->previous = NULL;
}
template <class T>
TrimmingNode<T>::~TrimmingNode() {}
template <class T>
T *TrimmingNode<T>::getItem() {
	return this->item;
}
template <class T>
TrimmingNode<T> *TrimmingNode<T>::getNext() {
	return this->next;
}
template <class T>
TrimmingNode<T> *TrimmingNode<T>::getPrevious() {
	return this->last;
}
template <class T>
void TrimmingNode<T>::setNext(TrimmingNode<T> *node) {
	this->next = node;
}
template <class T>
void TrimmingNode<T>::setPrev(TrimmingNode<T> *node) {
	this->previous = node;
}

/****************************************************************************************************
 * TRIMMINGLINKEDLIST IMPLEMENTATION
****************************************************************************************************/

template <class T>
TrimmingLinkedList<T>::TrimmingLinkedList() {
	this->head = NULL;
	this->tail = NULL;
	this->curNode = NULL;
	this->numElements = 0;
}
template <class T>
TrimmingLinkedList<T>::~TrimmingLinkedList() {
	TrimmingNode<T> *curNode = this->head;
	while(numElements > 0 && curNode != NULL) {
		TrimmingNode<T> *tmp = curNode->next;
		delete curNode;
		this->numElements--;
		curNode = tmp;
	}
}
template <class T>
void TrimmingLinkedList<T>::add(T *item) {
	if (this->numElements == 0) {
		TrimmingNode<T> *newNode = new TrimmingNode<T>(item);
		this->head = newNode;
		this->tail = newNode;
		this->numElements = 1;
	}
	else {
		TrimmingNode<T> *newNode = new TrimmingNode<T>(item);
		newNode->setPrev(this->tail);
		this->tail->setNext(newNode);
		this->tail = newNode;
		this->numElements++;
	}
}
template <class T>
T *TrimmingLinkedList<T>::getItemAtIDX(uint32_t idx) {
	if (this->numElements < 1) return NULL;
	this->first();
	for (int i = 0; i < idx && i < this->numElements; i++) {
		this->next();
	}
	return this->curItem();
}
template <class T>
T *TrimmingLinkedList<T>::removeItemAtIDX(uint32_t idx) {
	if (this->numElements < 1) return NULL;
	this->first();
	for (int i = 0; i < idx && i < this->numElements; i++) {
		this->next();
	}
	T *item = this->curItem;
	if (this->numElements == 1) {
		delete this->curNode;
		this->head = NULL;
		this->tail = NULL;
		this->numElements = 0;
	}
	else {
		TrimmingNode<T> *prev = curNode->getPrev();
		TrimmingNode<T> *next = curNode->getNext();
		if (prev != NULL)
			prev->setNext(next);
		if (next != NULL)
			next->setPrev(prev);
		delete this->curNode;
		this->curNode = prev;
		this->numElements--;
	}
	return item;
}
template <class T>
T *TrimmingLinkedList<T>::next() {
	if (this->curItem == NULL) return NULL;
	this->curNode = this->curNode->getNext();
	if (this->cutItem == NULL) return NULL;
	return this->curNode->getItem();
}
template <class T>
T *TrimmingLinkedList<T>::prev() {
	if (this->curItem == NULL) return NULL;
	this->curNode = this->curNode->getPrev();
	if (this->cutItem == NULL) return NULL;
	return this->curNode->getItem();
}
template <class T>
T *TrimmingLinkedList<T>::curItem() {
	if (this->curItem == NULL) return NULL;
	return this->curNode->getItem();
}
template <class T>
T *TrimmingLinkedList<T>::first() {
	this->curItem = this->head;
	if (this->curItem == NULL) return NULL;
	return this->curNode->getItem();
}
template <class T>
T *TrimmingLinkedList<T>::last() {
	this->curItem = this->last;
	if (this->curItem == NULL) return NULL;
	return this->curNode->getItem();
}
