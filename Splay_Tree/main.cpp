#include <iostream>
#include "splay.h"

int main(){
  auto i = { 7, 8, 19, 10, 15, 9, 14, 12, 11, 23};    //fill the tree with these numbers

  splay<int>* spl = new splay<int>;//create an object tree
  for (auto const& e : i)//itterative loop to fill treee
    spl->insert(e);

  std::cout<<"Splay Tree\n"<<spl->print()<<std::endl;
  auto number = 10;
  if (spl->find(number))//testing find function
    number = 14;
  else 
    std::cout<<"not found\n";
  std::cout<<"removing "<<number<<std::endl;
  spl->remove(number); // testing remove function
  std::cout<<spl->print()<<std::endl;//testing print after remove

return 0;
}

