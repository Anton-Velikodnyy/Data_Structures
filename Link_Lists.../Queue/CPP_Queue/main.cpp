//
//  main.cpp
//  CPP_Queue
//
//  Created by Anton Velikodnyy on 7/15/17.
//  Copyright © 2017 Anton Velikodnyy. All rights reserved.
//

#include <iostream>
#include <String>
#include "queue.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	Queue<int>* queue = new Queue<int>;									// create an instance of a Queue Object, calls the Queue constructor
	auto i = 9;
/*
	std::unique_ptr<int> temp = std::make_unique<int>(5);
	auto* raw = std::make_unique<int>(6).get();
	std::cout<<*raw;
	*/
	queue->first_in(1);
	queue->first_in(2);
	queue->first_in(3);
	queue->first_in(4);
	queue->first_in(5);
	queue->first_in(6);
	queue->first_in(7);
	queue->first_in(8);
	queue->first_in(std::forward<int>(i));
	std::cout<<queue->to_string()<<std::endl;																//prints nothing, test to make sure it works
	queue->first_out();
	std::cout<<queue->to_string()<<std::endl;																//prints nothing, test to make sure it works
	queue->first_out();
	std::cout<<queue->to_string()<<std::endl;																//prints nothing, test to make sure it works
	queue->first_out();
	std::cout<<queue->to_string()<<std::endl;																//prints nothing, test to make sure it works
	queue->first_out();
	queue->first_out();
	queue->first_out();
	queue->first_out();
	queue->first_out();
	queue->first_out();
	queue->first_out();
	queue->first_out();
	queue->first_out();
	std::cout<<queue->to_string()<<std::endl;			
	return 0;
}
