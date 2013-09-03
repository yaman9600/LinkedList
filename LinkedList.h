/*
	LinkedList.h - Generic LinkedList implementation
	Works better with FIFO, because LIFO will need to
	search the entire List to find the last one;

	For instructions, go to https://github.com/ivanseidel/LinkedList

	Created by Ivan Seidel Gomes, March, 2013.
	Released into the public domain.
*/


#ifndef LinkedList_h
#define LinkedList_h

template<class T>
struct ListNode
{
	T data;
	ListNode<T> *next;
};

template <typename T>
class LinkedList{

protected:
	int _size;
	ListNode<T> *root;
	ListNode<T>	*last;

	// Helps "get" method, by saving last position
	ListNode<T> *lastNodeGot;
	int lastIndexGot;
	// isCached should be set to FALSE
	// everytime the list suffer changes
	bool isCached;

	ListNode<T>* getNode(int index);

public:
	LinkedList();
	~LinkedList();

	/*
		Returns current size of LinkedList
	*/
	int size();
	/*
		Adds a T object in the specified index;
		Unlink and link the LinkedList correcly;
		Increment _size
	*/
	bool add(int index, T);
	/*
		Adds a T object in the end of the LinkedList;
		Increment _size;
	*/
	bool add(T);
	/*
		Adds a T object in the start of the LinkedList;
		Increment _size;
	*/
	bool unshift(T);
	/*
		Set the object at index, with T;
		Increment _size;
	*/
	bool set(int index, T);
	/*
		Remove object at index;
		If index is not reachable, returns false;
		else, decrement _size
	*/
	T remove(int index);
	/*
		Remove last object;
	*/
	T pop();
	/*
		Remove first object;
	*/
	T shift();
	/*
		Get the index'th element on the list;
		Return Element if accessible,
		else, return false;
	*/
	T get(int index, bool useCached);

	/*
		Clear the entire array
	*/
	void clear();

};

// Initialize LinkedList with false values
template<typename T>
LinkedList<T>::LinkedList()
{
	root=false;
	last=false;
	_size=0;
}

// Clear Nodes and free Memory
template<typename T>
LinkedList<T>::~LinkedList()
{
	ListNode<T>* tmp;
	while(root!=false)
	{
		tmp=root;
		root=root->next;
		delete tmp;
	}
	last = false;
	_size=0;
	isCached = false;
}

/*
	Actualy "logic" coding
*/

template<typename T>
ListNode<T>* LinkedList<T>::getNode(int index){
	int _pos = 0;
	ListNode<T>* current = root;
	while(_pos < index && current){
		current = current->next;

		_pos++;
	}
	return current;
}

template<typename T>
int LinkedList<T>::size(){
	return _size;
}

template<typename T>
bool LinkedList<T>::add(int index, T _t){

	// if(index == 0)
	// 	return shift(_t);

	if(index > _size)
		return add(_t);

	ListNode<T> *tmp = new ListNode<T>(),
				 *_prev = getNode(index-1);
	tmp->data = _t;
	tmp->next = _prev->next;
	_prev->next = tmp;

	_size++;
	isCached = false;

	return true;
}

template<typename T>
bool LinkedList<T>::add(T _t){

	ListNode<T> *tmp = new ListNode<T>();
	tmp->data = _t;
	tmp->next = false;
	if(root){
		// Already have elements inserted
		last->next = tmp;
		last = tmp;
	}else{
		// First element being inserted
		root = tmp;
		last = tmp;
	}

	_size++;
	isCached = false;

	return true;
}

template<typename T>
bool LinkedList<T>::unshift(T _t){

	if(_size == 0)
		return add(_t);

	ListNode<T> *tmp = new ListNode<T>();
	tmp->next = root;
	tmp->data = _t;
	
	_size++;
	isCached = false;
	
	return true;
}

template<typename T>
bool LinkedList<T>::set(int index, T _t){
	// Check if index position is in bounds
	if(index < 0 || index >= _size)
		return false;

	getNode(index)->data = _t;
	return true;
}

template<typename T>
T LinkedList<T>::pop(){
	if(_size <= 0)
		return false;
	
	isCached = false;

	if(_size >= 2){
		ListNode<T> *tmp = getNode(_size - 2);
		T ret = tmp->next->data;
		delete(tmp->next);
		tmp->next = false;
		last = tmp;
		_size--;
		return ret;
	}else{
		// Only one element left on the list
		T ret = root->data;
		delete(root);
		root = false;
		last = false;
		_size = 0;
		return ret;
	}
}

template<typename T>
T LinkedList<T>::shift(){
	if(_size <= 0)
		return false;

	if(_size > 1){
		ListNode<T> *_next = root->next;
		T ret = root->data;
		delete(root);
		root = _next;
		_size --;
		isCached = false;

		return ret;
	}else{
		// Only one left, then pop()
		return pop();
	}

}

template<typename T>
T LinkedList<T>::remove(int index){
	if(index < 0 || index >= _size)
		return false;

	if(index == 0)
		return shift();

	if(index - 1 == _size)
		return pop();

	ListNode<T> *tmp = getNode(index - 1);
	ListNode<T> *toDelete = tmp->next;
	tmp->next = tmp->next->next;
	delete(toDelete);
	_size--;
	isCached = false;

	return false;
}

template<typename T>
T LinkedList<T>::get(int index, bool useCached = false){
	ListNode<T> *tmp = getNode(index);

	/*if(useCached && index == lastIndexGot + 1){
		tmp = tmp->next;
	}else{
		tmp = getNode(index);
	}*/

	// lastIndexGot = index;
	// lastNodeGot = tmp;

	return (tmp ? tmp->data : false);
}

template<typename T>
void LinkedList<T>::clear(){
	while(size() > 0)
		shift();
}

#endif