//
//  trei.h
//  CPP_Trei
//
//  Created by Anton Velikodnyy on 7/27/17.
//  Copyright © 2017 Anton Velikodnyy. All rights reserved.
//

#ifndef trei_h
#define trei_h

#define CASE ' '
#define CHARACTERS 96

/**
 *	Dynamically allocated array.
 */
template < class T >
class my_vector {
	
private:
	/**
	 *	Extends the size of arr to accomadate {@code push_bac}
	 *	<p>
	 *	If there is little to no space available, the array size is doubled.
	 *	Max, size, and empty are adjusted accordingly.
	 *	In order to double size, arr is moved to a temporary array, and a new array
	 *	is created at arr. 
	 *	Then, all the objects in temp are meticulously moved to the new array in arr.
	 *	<p>
	 *	Else, size is increased and empty is decreased.
	 */
	void extend(){
		if (empty <= 1) {
			max *= 2;
			++size ;
			empty = max - size;
			auto temp = std::move ( arr );
			arr = std::make_unique < T[] > ( max );
			
			for ( auto i = 0; i < size; ++i ) {
				arr[i] = std::move ( temp[i] );
			}
		}
		else {
			++size;
			--empty;
		}
	}
	
public:
	/**
	 *	Constructor, sets up array.
	 */
	my_vector()
	{ arr = std::make_unique < T[] > ( max ); };
	
	/**
	 *	array that this object manages
	 */
	std::unique_ptr < T[] > arr;
	
	/**
	 *	Size of the array's current object count.
	 */
	size_t size = 0;
	
	/**
	 *	How many more slots in the array are still available.
	 */
	size_t empty= 1;
	
	/**
	 *	Size of the allocated array.
	 */
	size_t max  = 1;
	
	/**
	 *	Overload operator, to accept [] operators.
	 *
	 *	@param i  index of of the array
	 *	@return T, returns object stored at index = i
	 */
	T& operator [] ( size_t i )
		{ return this -> arr[i]; }
	
	/**
	 *	Inserts given into array.
	 *	<p>
	 *	Calls extend, to enlarge array if neccessary.
	 *	Stores given at index = size, (note: -1 is used, because extend increments size)
	 *
	 *	@param given  object to be stored.
	 */
	void push_bac(T&& given){
		this -> extend();
		arr[ size - 1 ] = std::move ( given );
	}
	
	/**
	 *	Shrinks array, if there are a lot of empty spaces.
	 *	<p>
	 *	If there is to much space available, the array size is halfed twice.
	 *	Max, size, and empty are adjusted accordingly.
	 *	In order to shrink size, arr is moved to a temporary array, and a new array
	 *	is created at arr.
	 *	Then, all the objects in temp are meticulously moved to the new array in arr.
	 *	Nullptr are excluded in the new array.
	 *	<p>
	 *	Else, size is decreased and empty is increased.
	 */
	void shrink(){
		if ( size*4 <= max )  {
			max /= 4;
			--size;
			empty = max - size;
			
			auto temp = std::move ( arr );
			arr = std::make_unique < T[] > ( max );
			
			for ( int i = 0, index = 0; i < max*4; ++i )  {
				if ( temp[i] != nullptr) {
					arr[index] = std::move ( temp[i] );
					++index;
				}
			}
		}
		else  {
			--size;
			++empty;
		}
	}
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	node object for the trei tree.
 */
class node_radix
{
public:
	/**
	 *	Shorthand.
	 */
	typedef std::unique_ptr<node_radix> node_ptr;
	
	/**
	 *	Default constructor.
	 */
	node_radix()
	{}
	
	/**
	 *	Constructor.
	 *
	 *	@param given  string to store in data of this node.
	 */
	node_radix ( const std::string & given )
	{ data = given; }
	
	/**
	 *	Stores string given by user.
	 */
	std::string data;
	
	/**
	 *	Flag to show if this node contains children.
	 */
	bool leaf = true;
	
	/**
	 *	Dynamic array to store children.
	 */
	my_vector<node_ptr> vector = my_vector<node_ptr>();
	
	/**
	 *	A key to find where each object in vector is located.
	 *	<p>
	 *	Using  key[some_string->data[0] - CASE]-1 to access the appropriate location
	 *	in vector.
	 */
	std::unique_ptr < size_t [] > key = std::make_unique < size_t [] > ( CHARACTERS );

	/**
	 *	Gives a child to this node.
	 *	<p>
	 *	Sets this node's leaf as false.
	 *	Inserts node into the vector.
	 *	Maps the corresponding key.
	 *	
	 *	@param temp  node to be inserted
	 *	@return node_ptr to the inserted node
	 */
	node_ptr & insert (node_ptr &&  temp)
	{
		this -> leaf = false;
		vector.push_bac ( std::forward < node_ptr > ( temp ) );
		key[ vector [ vector.size - 1] -> data[0] - CASE ] = vector.size;
		return vector [ vector.size - 1 ];
	}
	
	/**
	 *	Gives freshly created child to this node.
	 *	<p>
	 *	Sets this node's leaf as false.
	 *	Inserts a fresh node (made using given string) into the vector.
	 *	Maps the corresponding key.
	 *
	 *	@param given  string to be inserted
	 *	@return node_ptr to the inserted node
	 */
	node_ptr & insert (std::string&& given)
	{
		this->leaf = false;
		vector.push_bac ( std::make_unique < node_radix > ( given ) );
		key[ vector [ vector.size - 1] -> data[0] - CASE ] = vector.size;
		return vector [ vector.size - 1 ];
	}
	
	/**
	 *	Prints the string of all nodes attached to this node including itself.
	 *	<p>
	 *	Searches through key, if a match is found, calls print with that node.
	 *
	 *	@return string that contains the string of all children
	 */
	std::string to_string ()
	{
		std::string print = "";
		for ( int i = 0; i < CHARACTERS; ++i )
			if ( this -> key[i] != 0 )
				print += this -> print( vector [ key[i] - 1 ], this -> data );
		return print;
	}
	
private:
	
	/**
	 *	Recursively goes through each node to return string of all children.
	 *	<p>
	 *	If leaf, returns data of this node.
	 *	Searches through key, if a match is found, calls print with that node.
	 *
	 *	@return string that contains the string of all children
	 */
	std::string print( const node_ptr & current,std::string stream){
		stream += current -> data;
		
		if ( !current -> leaf ) {
			std::string this_stream = "";
			
    	for ( int i = 0; i < CHARACTERS; ++i )
				if ( current -> key[i] != 0 && current->vector [ current->key[i] - 1 ] != nullptr)
  				this_stream += ( print ( current->vector[ current -> key[i] - 1 ], stream + ">" ) );
			
			return this_stream;
		}
		
		return stream + "\n";
	};
	
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

typedef std::unique_ptr<node_radix> node_ptr;
class radix
{
public:
	radix()
	{ head_=std::make_unique<node_radix>("");};
	radix(const std::string& given)
	{ head_=std::make_unique<node_radix>(given);};
	void insert(const std::string &);
	void remove(const std::string &);
	
	std::string to_string()
	{ return head_->to_string();}
	
	node_ptr head_;
private:
	void lookup ( node_ptr & , const std::string & , size_t );
	void case2( node_ptr &,const std::string & , size_t, size_t);
	void case1(const node_ptr &,const std::string & , size_t);
	bool lookdown ( node_ptr &, const std::string &, size_t);
	void remove_node (node_ptr& current);
	bool case3(const node_ptr &,const std::string & , size_t);
};

/**
 *	Inserts given string into this tree.
 */
void radix::insert( const std::string &  given)
{
	std::string given_new=given + ":";
	lookup(head_, given_new,0);
}

/**
 *	Matches given string with current node's string, character by character, and
 *	call function based on result.
 */
void radix::lookup(node_ptr & current, const std::string & given, size_t index)
{
	size_t i = 0;
	for (;i<current->data.size() && given[index] == current->data[i] ;++i) {
		if (given[index] != current->data[i])
			break;
		index++;
	}
	
	if (current->data[i-1] == ':' && given[index-1] == ':')
		;		//duplicate is found
	else if ( i == current->data.size())
		case1(current,given,index);
	else
		case2(current,given,i,index);
}

/*
 *	Goes through the vertex of given node, adds a new node if there is not one, 
 *	else calls lookup() with that node;
 */
void radix::case1(const node_ptr & current,const std::string & given, size_t index)
{
	const auto& child = current->key[given[index] - CASE];
	
	if (child != 0)
		lookup(current->vector[child - 1], given, index);
	else
		current->insert(given.substr(index));
}

/**
 *	Splits the node into two nodes at i and attaches new node with given
 *	substring from index to end.
 */
void radix::case2(node_ptr & current,const std::string & given, size_t i, size_t index)
{
	node_ptr temp;
	temp = std::move(current);
	current = std::make_unique<node_radix>(temp->data.substr(0,i));
	temp->data = temp->data.substr(i);
	
	current->insert(std::forward<node_ptr>(temp));
	current->insert(given.substr(index));
}

/**
 *	Removes given string from this tree.
 */
void radix::remove ( const std::string& given )
{
	std::string given_new = given + ":";
	lookdown ( head_, given_new, 0);
}

/**
 *	Matches given string with current node's string, character by character, and
 *	call function based on result.
 */
bool radix::lookdown ( node_ptr & current, const std::string & given, size_t index)
{
	size_t i = 0;
	
	for (;i<current->data.size() && given[index] == current->data[i] ;++i) {
		if (given[index] != current->data[i])
			break;
		index++;
	}
	
	if (current->data[i-1] == ':' && given[index-1] == ':')
		return true;//duplicate is found
	else if ( i == current->data.size()) 
		case3(current,given,index);
	
	return false;
}

/**
 *	Removes the node from the tree
 */


bool radix::case3 ( const node_ptr & current,const std::string & given, size_t index)
{
	auto& child = current->key[given[index] - CASE];
	if (child != 0) {
		if (lookdown(current->vector[child-1], given, index))  {
			current->vector[child-1].release();
			child = 0;
			current->vector.shrink();
			for ( int i = 0; i < current -> vector.size; i++ )  {
				if (current->vector[i] != nullptr)  {
					current -> key [current -> vector[i] ->data[0] - CASE] = i + 1;
				}
			}
			if ( current->vector.size == 1) {
				for (int z = 0; z < current->vector.max; ++z)  {
					if (current->vector[z] != nullptr) {
						
  				current->data = current->data + current->vector[z]->data;
  				current->leaf		= current->vector[z]->leaf;
  				current->key		= std::move (current->vector[z]->key);
  				current->vector = std::move (current->vector[z]->vector);
					}
				}
			}
		}
	}
	return false;
}
#endif /* trei_h */
