#ifndef RB_Tree_H
#define RB_Tree_H
#include <memory>
#include <iostream>

template <class N, class... Args>
    std::unique_ptr<N> make_unique(Args&&... args) {
    return std::unique_ptr<N>(new N(std::forward<Args>(args)...));
} //c++11 specific code, not needed with c++14


template<class T>
class RB_Tree
{
  public:
    template<class K,class V>
    struct nodeRB_Tree;
    typedef std::unique_ptr<nodeRB_Tree<int,T>> node_ptr;
    typedef nodeRB_Tree<int,T> node;

    template<class K,class V>
    struct nodeRB_Tree
    {
      nodeRB_Tree(const K& key, const V& value):
           key_ (key), value_ (value)
          { left = nullptr;right=nullptr;parent=nullptr;
            red=false; }
      nodeRB_Tree()
          { red= false; }
      std::unique_ptr< nodeRB_Tree<K,V> > left, right;
      node*  parent;
      bool red;

      V value()
           { return value_; }
      K key()
           { return key_; }
      K key(const K& key)
           { key_ = key; }
      private:
        K key_;
        V value_;
    };


    RB_Tree()
        { head_=nullptr; };
    void insert (const T& value)
        { std::cout<<value<<" inserting\n";
          insertNode_ (head_, nullptr,value);
                        std::cout<<head_->value()<<" = head\n\n"; }
    std::string print() 
        { std::cout<<"print\n";
          return print_inOrder_(head_, ""); }

  private:
    node_ptr head_;

    
    void insertNode_( node_ptr& ,node* , const T& );
    std::string print_inOrder_(const node_ptr& current,std::string print);
};

template<class T>
void RB_Tree<T>::insertNode_( node_ptr& current,node* parent, const T& value)
    {
      if (current == nullptr){
        current = std::move(make_unique<node>(-1,value));
        
        std::cout<<current->value()<<" inserted\n";
        if (parent!= nullptr){
          current->parent = parent;
          std::cout<<parent->value()<<" parent\n";
        }
      }
      else {
        if ( current->value() > value ) 
          insertNode_(current->left, current.get(),value);
        else if ( current->value() < value )
          insertNode_(current->right, current.get(),value);
      }
    }


template<class T>
std::string RB_Tree<T>::print_inOrder_ (const node_ptr& current, std::string print)
    {
      if (current != nullptr) {
        print+= "[" + std::to_string(current->value())+"]";
        print = print_inOrder_(current->left,print);
        print = print_inOrder_(current->right,print);
      }
      return print;
    }
#endif

