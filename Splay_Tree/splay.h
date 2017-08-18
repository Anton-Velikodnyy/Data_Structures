#ifndef SPLAY_H
#define SPLAY_H
#include <memory>
#include <iostream>

template <class T>
class splay
{
  public:
    template < class V>
    struct nodeSplay{
      public:
        nodeSplay(V const& value):
              value_ (value) 
            { left = right =  nullptr; }
        std::shared_ptr< nodeSplay<V> > left, right;
        std::weak_ptr< nodeSplay<V> > parent;
        V value()
          {return value_;}
      private:
        V value_;
    };   
    typedef nodeSplay<T> node;
    splay()
        { null_ = std::make_shared<node>(NULL);
          null_->parent = null_;
          null_->right = null_->left = null_;
          head_  = null_; };
    void insert (const T& value) 
        { insertNode_ (head_, null_, value); };
    void remove (const T& value)
        { removeNode_ ( searchNode_(head_, value)); };
    bool find (const T& value)
        { std::shared_ptr<node> temp = searchNode_ (head_, value);
          if (temp)
            return true;
          else 
            return false; };
    std::string print ()
        { return print_inOrder_ (head_, ""); };

  private:
    std::shared_ptr<node> head_; 
    std::shared_ptr<node> null_;

    void insertNode_ (std::shared_ptr<node>& current,  //recursive insert
        const std::shared_ptr<node>& parent,const T& value)
    {
      if ( current == null_ ){ 
        current = std::make_shared<node> (value);
        current->parent = parent;
        current->left = current->right = null_;
        if (current->parent.lock()!= null_)
      if (current != head_) 
         splayNode(current);
      }
      else if (current->value() < value)
        insertNode_ (current->right, current, value);
      else if (current->value() > value)
        insertNode_ (current->left , current, value);
    }

    void removeNode_ (std::shared_ptr<node>& current) //deletes node
    {
      std::shared_ptr<node> parent = current->parent.lock();
      if (current != null_){
        if (current->right == null_) {
          if (current->left != null_)   {
            current->left->parent = current->parent;
            current = std::move(current->left);
          }
          else  
            current = null_;
        }
        else if (current->left == null_)  {
          current->right->parent = current->parent;
          current = std::move(current->right);
        }
        else  {                                       //worst case scenario
          std::shared_ptr<node> temp = current->right;
          while (temp->left != null_)
            temp = temp->left;
          current->left->parent = temp;
          temp->left = current->left;
          temp = current;
          current->right->parent=current->parent;
          current=current->right;
        }   
        if (current == null_ )
          splayNode(parent);
        else
          splayNode(current);
      }
    }
      

    std::shared_ptr<node> & searchNode_ (std::shared_ptr<node>& current, const T& value) 
    { //searches for node.
      if (current != null_) {
        if (current->value() < value)
          return searchNode_ (current->right, value);
        else if (current->value() > value)
          return searchNode_ (current->left , value);
        else  {
          return current;
        }
      }
      return null_;
    }

    void splayNode (const std::shared_ptr<node> current) {
      while (current != head_){
        if (head_ == current->parent.lock())  {
          if (head_->left == current)
            RR(current);
          else
            LR(current);
        }
        else  {
          if (current->parent.lock()->parent.lock()->left == 
              current->parent.lock())  {
            if (current->parent.lock()->left == current)  {
              RR(current->parent.lock());
              RR(current);
            }
            else  {
              LR(current);
              RR(current);
            }
          }
          else  {
            if (current->parent.lock()->right == current)  {
              LR(current->parent.lock());
              LR(current);
            }
            else  {
              RR(current);
              LR(current);
            }
          }
        }
      }
    }

    void LR(const std::shared_ptr<node> current)
    {
      if (current->left != null_)
        current->left->parent = current->parent.lock();
      current->parent.lock()->right = current->left;
      current->left = current->parent.lock();
      current->parent = current->left->parent;
      if (current->left->parent.lock() == null_)
        head_ = current;
      else if (current->left == current->left->parent.lock()->left)
        current->left->parent.lock()->left = current;
      else
        current->left->parent.lock()->right= current;
      current->left->parent = current; 
    };

    void RR(const std::shared_ptr<node> current)
    {
      current->parent.lock()->left = current->right;
      if (current->parent.lock()->left != null_)
        current->parent.lock()->left->parent = current->parent.lock();
      current->right = current->parent.lock();
      current->parent = current->right->parent;
      if (current->right->parent.lock() == null_)
        head_ = current;
      else if (current->right == current->right->parent.lock()->left)
        current->right->parent.lock()->left = current;
      else 
        current->right->parent.lock()->right= current;
      current->right->parent = current;
    };

    std::string print_inOrder_ (const std::shared_ptr<node>& current, 
        std::string print)
    {
      if (current != null_) {
        print+= "[" + std::to_string(current->value()) 
              + "," + std::to_string(current->parent.lock()->value()) + "]";
        print = print_inOrder_ (current->left, print);
        print = print_inOrder_ (current->right, print);
      }
      return print;
    }
};

#endif
