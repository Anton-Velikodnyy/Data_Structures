//
//  main.cpp
//  Cpp_Stack
//
//  Created by Anton Velikodnyy on 7/18/17.
//  Copyright © 2017 Anton Velikodnyy. All rights reserved.
//

#include <iostream>
#include "Stack.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	Stack<int>* stack = new Stack<int>;									// create an instance of a List Object, calls the List constructor
	stack->last_in(6);
	stack->last_in(7);
	stack->last_in(8);
	stack->last_in(9);
	stack->first_out();
	stack->first_out();
	stack->first_out();
	stack->first_out();
	stack->first_out();
	std::cout<<stack->to_string()<<std::endl;
    return 0;
}
