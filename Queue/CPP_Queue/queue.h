//
//  queue.h
//  CPP_Queue
//
//  Created by Anton Velikodnyy on 7/15/17.
//  Copyright © 2017 Anton Velikodnyy. All rights reserved.
//

#ifndef queue_h
#define queue_h
#include <String>

template < class U >
class node {
public:
	
	/**
	 *	Shorthand for unique ptr managing node.
	 */
	using node_ptr = std::unique_ptr<node>;
	
	//----------------------------------------------------------------------------
	/**
	 *	Constructor of this {@code node} class.
	 *
	 *	@param data, reference to the object given
	 *	@param next, sets another node as the next reference of this node.
	 */
	node (U const& data) {
		this->data = data;
	}
	
	/**
	 *	Converts the data stored in this node to a printble string.
	 *
	 *	@return data in string form.
	 */
	std::string to_string () {
		return std::to_string ( data );
	}
	
private:
	
	/**
	 *	Grants access to AVL class
	 */
	template < class T >	friend class Queue;
	
	/**
	 *	Stores a generic object.
	 */
	U data;
	
	/**
	 *	Ownership pointer to next node of the chain
	 */
	node_ptr next;
	
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	Queue is an object which creates and manages a chain of nodes stored
 *	in memory.
 *	<p>
 *	This class accepts any data type and can only directly access the
 *	head of the chain of nodes it manages.
 */
template <class T>
class Queue {
	
public:
	
	Queue()
	{};
	~Queue()
	{ delete *head_node;}
	
	/**
	 *	Inserts node instance at the start of the chain.
	 */
	void first_in (T &&data);
	
	/**
	 *	Removes node instance located at the end of the chain.
	 */
	void first_out();

	/*
	 *	Checks to see if this class is managing chain of nodes.
	 */
	bool is_empty();
	
	/**
	 *	Converts the chain of nodes, through itteration, into a string.
	 */
	std::string to_string ();
	
	
	
private:

	/**
	 *	Shorthand for a unique pointer to a node.
	 */
	using node_ptr = std::unique_ptr<node<T>>;
	
	/**
	 *	Ownership pointer to start of chain.
	 */
	node<T>* head_node;
	
	/**
	 *	Converts the chain of node from head_node to tail_node, into a string.
	 */
	std::string to_string_forward (node_ptr const& current, std::string& list);

};



//----------------------------------------------------------------------------
/**
 *	Inserts node instance at the start of the chain.
 *	<p>
 *	If the chain is empty, the following actions occur:
 *	<p><ol>
 *	<li>node instance created.
 *	<li>This class' head_node becomes the owner of this node.
 *	</ol><p>
 *	If the chain is not empty, the following actions occur:
 *	<p><ol>
 *	<li>fresh_node is crated with its next being head_node's next.
 *	<li>head_node becomes the owner of this new node.
 *	<li>This reference gains the link to this new node.
 *	</ol><p>
 *
 *	@param data  is an Object, who's data-type matches the initially declared
 *	data-type of this class, to be referenced.
 */
template	<class T>
void Queue<T>::first_in(T &&data) {
	if (is_empty()) {
		head_node = std::make_unique<node<T>>(data).get();							//new node is created
		head_node -> next.reset(head_node);
	}
	else {
		auto fresh_node = std::make_unique<node<T>>(data);
		std::swap ( head_node -> next, fresh_node -> next);
		std::swap ( head_node -> next, fresh_node );
		head_node = head_node -> next .get();
	}
}

//----------------------------------------------------------------------------
/**
 *	Removes node instance located at the end of the chain.
 *	<p>
 *	If the chain is empty, the following actions occur.
 *	<p></ol>
 *	<li>If head_node and head_node are the same, both are set to null.
 *	<li>Else head_node 
 *	</ol><p>
 */
template <class T>
void Queue<T>::first_out () {
	if (!is_empty()) {
		if ( head_node == head_node -> next.get() ){
			head_node = nullptr;
		}
		else {
			head_node -> next = std::move ( head_node -> next -> next);

		}
	}
}

//----------------------------------------------------------------------------
/**
 *	Checks to see if this class is managing a chain of nodes.
 *
 *	@return true if chain of nodes exists, false otherwise.
 */
template <class T>
bool Queue<T>::is_empty() {
	return !head_node;
}

//----------------------------------------------------------------------------
/**
 *	Converts the chain of nodes, through recursion, into a string.
 *	<p>
 *	The order of the node instances are printed from head_node to tail_node.
 *	Then again from tail_node to head_node.
 *	<p>
 *	Returns an emtpy string ("") if chain is empty.
 *
 *	@return String that contains all the values in the chain of Nodes.
 */
template <class T>
std::string Queue<T>::to_string() {
	std::string list = "";
	if (!is_empty())  
  	list = to_string_forward(head_node->next, list) + head_node->to_string();
	return list;
}

/**
 *	Converts the chain of node from head_node to tail_node, into a string.
 *
 *	@param current  reference to the node who's data is being read into list
 *	@param list  string which stores the output of this chain
 *	@return string which has recursed through the chain.
 */
template <class T>
std::string Queue<T>::to_string_forward (node_ptr const& current, std::string& list) {
	if (current.get() != head_node)
		to_string_forward(current->next, list.append(current->to_string()));
	return list;
}

#endif /* queue_h */
