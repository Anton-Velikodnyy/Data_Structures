//
//  main.cpp
//  CPP_List
//
//  Created by Anton Velikodnyy on 6/27/17.
//  Copyright © 2017 Anton Velikodnyy. All rights reserved.
//
#include "List.h"
#include <iostream>

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World2!\n";
	List<int>* list = new List<int>;									// create an instance of a List Object, calls the List constructor
	auto i = 5;
	list->first_in(4);
	list->first_in(std::forward<int>(5));
	list->last_in(6);
	std::cout<<list->to_string()<<std::endl;																//prints nothing, test to make sure it works
	list->last_out();
	std::cout<<list->to_string()<<std::endl;																//prints nothing, test to make sure it works
	list->first_out();
	std::cout<<list->to_string()<<std::endl;																//prints nothing, test to make sure it works
	list->first_out();
	std::cout<<list->to_string()<<std::endl;																//prints nothing, test to make sure it works

    return 0;
}
