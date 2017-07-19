//
//  main.cpp
//  CPP_AVL
//
//  Created by Anton Velikodnyy on 7/9/17.
//  Copyright © 2017 Anton Velikodnyy. All rights reserved.
//

#include <iostream>
#include "AVL.h"


int main(int argc, const char * argv[]) {
	std::unique_ptr<AVL<int>> tree = std::make_unique<AVL<int>>();
	auto i = 1;
	tree->insert(3);
	tree->insert(std::forward<decltype(i)> (i));
	tree->insert(2);
	tree->insert(6);
	std::cout<<tree->to_string();
	tree->remove(2);
	std::cout<<tree->to_string();
	tree->remove(6);
	if (tree->search_tree(3))
		std::cout<<"found 3\n";
	std::cout<<tree->to_string();
	return 0;
}
