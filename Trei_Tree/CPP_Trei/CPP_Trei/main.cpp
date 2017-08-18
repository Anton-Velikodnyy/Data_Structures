//
//  main.cpp
//  CPP_Trei
//
//  Created by Anton Velikodnyy on 7/27/17.
//  Copyright © 2017 Anton Velikodnyy. All rights reserved.
//

#include <iostream>
#include "trei.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	std::cout << "Hello, World!\n";
	my_vector<int> vec = my_vector<int>();
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	vec.push_bac(5);
	//vec.pop_bac();
	//vec.pop_bac();
	std::unique_ptr<node_radix> x = std::make_unique<node_radix>("Anton");
	std::unique_ptr<node_radix> y = std::make_unique<node_radix>("Bob");
	std::unique_ptr<node_radix> z = std::make_unique<node_radix>("Bob");
	x->insert(std::forward<std::unique_ptr<node_radix>>(z));
	std::cout<<x->vector[0]->data<<std::endl;
	std::cout<<x->to_string()<<std::endl;
	x->insert("Jacob");
	x->insert("Chandice");
	x->insert(std::forward<std::unique_ptr<node_radix>>(y));
	std::string temp =x->to_string();
	std::cout<<std::endl<<"!\n"<<temp<<"!"<<std::endl;
	
	std::unique_ptr<radix> rad = std::make_unique<radix>();
	rad->insert("#Antonpokemon");
	rad->insert("#A_ntoniswee");
	rad->insert("#Bob");
	rad->insert("#Bob");
	rad->insert("#Bobob1");
	rad->insert("#Bobob2");
	rad->insert("#Bobob3");
	rad->insert("#Bobob4");
	rad->insert("#Bobob5");
	rad->insert("#Bobob6");
	rad->insert("#Bobob7");
	rad->insert("#Chadice");
	rad->insert("#Chad");
	std::cout<<"\n\nradix_NEW =\n"<<rad->to_string()<<"\nEND (v.v)\n";
	rad->remove("#Bobob1");
	rad->remove("#Bobob2");
	rad->remove("#Bobob3");
	rad->remove("#Bobob4");
	rad->remove("#Bobob5");
	std::cout<<"\n\nradix_NEW =\n"<<rad->to_string()<<"\nEND (v.v)\n";
	rad->remove("#Bobob6");
	std::cout<<"\n\nradix_NEW =\n"<<rad->to_string()<<"\nEND (v.v)\n";
	rad->remove("#Bob");
	std::cout<<"\n\nradix_NEW =\n"<<rad->to_string()<<"\nEND (v.v)\n";
	rad->remove("#Bobob7");
	std::cout<<"\n\nradix_NEW =\n"<<rad->to_string()<<"\nEND (v.v)\n";
	
    return 0;
}
