/*  
 *	Created by Anton Velikodnyy & edited by Daniel Tellier on 6/27/17.
 *	Copyright © 2017 Anton Velikodnyy. All rights reserved.
 *	May be distributed for the use of teaching purposes.
 */

/**
 *	Container for the storage of data given.
 *	{@code Node} contains the pointer to the next and previous {@code Node}
 *	instances in the chain of nodes generated by {@List}.
 */
class Node<U> {
	
	/**
	 *	Stores a generic immutable object.
	 */
	private final U data;
	
	/**
	 *	Pointer to the next node in the chain.
	 */
	protected  Node next;
	
	/**
	 *	Pointer to the previous node in the chain.
	 */
	protected  Node prev;
	
	//----------------------------------------------------------------------------
	/**
	 *	Constructor of this {@code Node} class.
	 *
	 *	@param data  takes given object and stores in this Node.
	 *	@param next  sets another Node as the next pointer of this Node.
	 *	@param prev  sets another Node as the prev pointer of this Node.
	 */
	protected Node (U data, Node next, Node prev) {
		this.data = data;
		this.next = next;
		this.prev = prev;
	}
	
	/**
	 *	Prints the data that is stored in this Node.
	 *
	 *	@return data in string form.
	 */
	@Override
	public String toString () {
		return data.toString();
	}
}

/**
 *	List is an object which creates and manages a chain of nodes stored
 *	in memory.
 *	<p>
 *	This class accepts any data type and can only directly access the
 *	head or tail of the chain of nodes it manages.
 */
public class List<T>  {
	
	
	//----------------------------------------------------------------------------
  /**
   *	Stores pointer to starting Node of the chain.
   */
	private Node headNode = null;
	/**
	 *	Stores pointer to ending Node of the chain.
	 */
	private Node tailNode = null;

	//----------------------------------------------------------------------------
	/**
	 *	Inserts Node instance at the start of the chain.
	 *	<p>
	 *	If the chain is empty, the following actions occur:
	 *	<p><ol>
	 *	<li>Node instance created.
	 *	<li>This class' headNode becomes a pointer to this Node.
	 *	<li>This class' tailNode becomes a pointer to this headNode.
	 *	</ol><p>
	 *	If the chain is not empty, the following actions occur:
	 *	<p><ol>
	 *	<li>Node instance created with its next pointer being the headNode.
	 *	<li>The previous pointer of this headNode becomes the freshNode.
	 *	<li>This class' headNode becomes a pointer to the freshNode.
	 *	</ol><p>
	 *
	 *	@param data  is an Object, who's data-type matches the initially declared
	 *	data-type of this class, to be stored.
	 */
	public void firstIn (T data) {
		if (this.isEmpty()) {
			headNode = new Node (data, null, null);
			tailNode = headNode;
		}
		else {
			Node freshNode = new Node (data, headNode, null);
			headNode.prev = freshNode;
			headNode = freshNode;
		}
	}
	
	/**
	 *	Inserts Node instance at the end of the chain.
	 *	<p>
	 *	If the chain is empty, the following actions occur:
	 *	<p><ol>
	 *	<li>Node instance created.
	 *	<li>This class' headNode becomes a pointer to this Node.
	 *	<li>This class' tailNode becomes a pointer to this headNode.
	 *	</ol><p>
	 *	If the chain is not empty, the following actions occur:
	 *	<p><ol>
	 *	<li>Node instance created with its next pointer being the tailNode.
	 *	<li>The next pointer of this tailNode becomes the freshNode.
	 *	<li>This class' tailNode becomes a pointer to the freshNode.
	 *	</ol><p>
	 *
	 *	@param data  is an Object, who's data-type matches the initially declared
	 *	data-type of this class, to be stored.
	 */
	public void lastIn (T data) {
		if (this.isEmpty()) {
			headNode = new Node (data, null, null);
			tailNode = headNode;
		}
		else {
			Node freshNode = new Node (data, null, tailNode);
			tailNode.next = freshNode;
			tailNode = freshNode;
		}
	}
	
	//----------------------------------------------------------------------------
	/**
	 *	Removes Node instance located at the end of the chain.
	 *	<p>
	 *	If isEmpty()} is false, the following actions occur.
	 *	<p></ol>
	 *	<li>If headNode and tailNode are the same, both are set to null.
	 *	<li>Else tailNode is set to its prev pointer.
	 *	<li>Then set tailNode's next set to null, deleting the Node instance at the
	 *	end of the chain.
	 *	</ol><p>
	 */
	public void firstOut () {
		if (!this.isEmpty()) {
			if (headNode == tailNode){
				headNode = null;
				tailNode = null;
			}
			else {
				tailNode = tailNode.prev;
				tailNode.next = null;
			}
		}
	}
	
	/**
	 *	Removes Node instance located at the start of the chain.
	 *	<p>
	 *	If the chain is not empty, the following actions occur.
	 *	<p><ol>
	 *	<li>If headNode and tailNode are the same, both are set to null.
	 *	<li>Else the headNode is set to its prev pointer.
	 *	<li>Then tailNode's previous Node is set to null, deleting the Node
	 *	instance at the start of the chain.
	 *	</ol><p>
	 */
	public void lastOut () {
		if (!this.isEmpty()) {
			if (headNode == tailNode){
				headNode = null;
				tailNode = null;
			}
			else {
				headNode = headNode.next;
				headNode.prev = null;
			}
		}
	}
 
	//----------------------------------------------------------------------------
	/**
	 *	Checks to see if this class is managing a chain of Nodes.
	 *
	 *	@return true if chain of Nodes exists, false otherwise.
	 */
	private boolean isEmpty () {
		return (headNode == null);
	}
 
	//----------------------------------------------------------------------------
	/**
	 *	Converts the chain of Nodes, through itteration, into a String.
	 *	<p>
	 *	The order of the Node instances are printed from headNode to tailNode. 
	 *	Then again from tailNode to headNode for testing purposes.
	 *	<p>
	 *	Returns an emtpy string ("") if chain is empty.
	 *
	 *	@return String that contains all the values in the chain of Nodes.
	 */
	@Override
	public String toString() {
		Node currentNode = headNode;
		StringBuilder builder = new StringBuilder();
		while (currentNode != null) {
			builder.append(currentNode + " ");
			currentNode = currentNode.next;								
		}
		currentNode = tailNode;
		builder.append("\n");
		while (currentNode != null) {
			builder.append(currentNode + " ");
			currentNode = currentNode.prev;
		}
		return builder.toString();
	}

	//----------------------------------------------------------------------------
	/**
	 *	Tests this List class for possible errors.
	 *
	 *	@param args  command-line arguments in array form.
	 */
	public static void main (String... args){
		List<Integer> list = new List<Integer>();
		System.out.println (list);
		list.lastIn(5);
		list.lastIn(4);
		list.firstIn(3);
		list.firstIn(2);
		System.out.println (list);
		list.lastOut();
		list.lastOut();
		list.firstOut();
		list.firstOut();
		System.out.println (list);			
	}
}
