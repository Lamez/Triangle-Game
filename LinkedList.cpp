#include <iostream>
#include "ListNode.cpp"
using namespace std;
template <class T>
class LinkedList{
	private:
		ListNode<T> *head;
	public:
		int size;
		LinkedList(){
			head = NULL;
			size = 0;
		}
		~LinkedList();
		void append(T);
		void insert(T);
		void deleteNode(T);
		//void removeAt(int);
		void display() const;
		bool isNull();
		T find(int index);
		T& operator[] (const int index);

};

template <class T>
void LinkedList<T>::append(T value){
	ListNode<T> *newNode;
	ListNode<T> *nodePtr;
	newNode = new ListNode<T>(value);
	newNode->value = value;
	newNode->next = NULL;
	if(!head)
		head = newNode;
	else{
		nodePtr = head;
		while(nodePtr->next)
			nodePtr = nodePtr->next;
		nodePtr->next = newNode;
	}
	size++;
}

template <class T>
void LinkedList<T>::insert(T value){
	ListNode<T> *newNode;
	ListNode<T> *nodePtr;
	ListNode<T> *prevNode = NULL;

	newNode = new ListNode<T>(value);
	if(!head){
		head = newNode;
		newNode->next = NULL;
	}else{
		nodePtr = head;
		prevNode = NULL;
		while(nodePtr != NULL && nodePtr->value < value){ //watch out for this line
			prevNode = nodePtr;
			nodePtr = nodePtr->next;
		}
		if(prevNode == NULL){
			head = newNode;
			newNode->next = nodePtr;
		}else{
			prevNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
	size++;
}

template <class T>
void LinkedList<T>::deleteNode(T value){
	ListNode<T> *nodePtr;
	ListNode<T> *prevNode;
	if(head != NULL){
		if(head->value == value){
			nodePtr = head->next;
			delete head;
			head = nodePtr;
		}else{
			nodePtr = head;
			while(nodePtr != NULL && nodePtr->value != value){
				prevNode = nodePtr;
				nodePtr = nodePtr->next;
			}
			if(nodePtr){
				prevNode->next = nodePtr->next;
				delete nodePtr;
			}
		}
	}
	size--;
}

/*template <class T>
void LinkedList<T>::removeAt(int index){
	ListNode<T> *nodePtr;
	ListNode<T> *prevNode;
	if(head != NULL){
		if(index == 0){
			nodePtr = head->next;
			delete head;
			head = nodePtr;
		}else{
			nodePtr = head;
			int i = 0;
			while(nodePtr != NULL && i != index){
				prevNode = nodePtr;
				nodePtr = nodePtr->next;
				i++;
			}
			if(nodePtr){
				prevNode->next = nodePtr->next;
				delete nodePtr;
			}
		}
        size--;
	}
}*/

template <class T>
void LinkedList<T>::display() const{
	ListNode<T> *nodePtr;
	nodePtr = head;
	int i = 1;
	while(nodePtr){
		cout << "(" << i << ")" << endl;
		cout << nodePtr->value << endl; //this may give error
		nodePtr = nodePtr->next;
		i++;
	}
}

template <class T>
LinkedList<T>::~LinkedList(){
	ListNode<T> *nodePtr;
	ListNode<T> *nextNode;
	nodePtr = head;
	while(nodePtr != NULL){
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

template <class T>
T LinkedList<T>::find(int index){
	if(index <= size - 1 || index >= size - 1){
		ListNode<T> *nodePtr;
		nodePtr = head;
		int count = 0;
		while(nodePtr != NULL){
			if(index == count)
				break;
			count++;
			nodePtr = nodePtr->next;
		}
		return nodePtr->value;
	}else
		throw "index is out of bounds";
}
template <class T>
bool LinkedList<T>::isNull(){
    return head == NULL;
}
template <class T>
T& LinkedList<T>::operator[] (const int index){
	if(index <= size - 1 || index >= size - 1){
		ListNode<T> *nodePtr;
		nodePtr = head;
		int count = 0;
		while(nodePtr != NULL){
			if(index == count)
				break;
			count++;
			nodePtr = nodePtr->next;
		}
		return nodePtr->value;
	}else
		throw "index is out of bounds";
}
