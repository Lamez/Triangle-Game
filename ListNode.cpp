#include <iostream> //for null..
template <class T>
class ListNode{
	public:
		T value;
		ListNode<T> *next;
		ListNode(T value){
			this->value = value;
			next = NULL;
		}
};
