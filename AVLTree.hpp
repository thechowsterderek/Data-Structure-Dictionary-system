// AVLSet.hpp


#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"

template <typename T>
class AVLSet : public Set<T>
{
private:
    struct tree_node{
        T data; //key of node
        tree_node* right;
        tree_node* left;
        int height =1; //height of node for balancing

        tree_node(const T& item):data(item),right(nullptr),left(nullptr),height(1){}//make node fastere
    };

    tree_node* root;
    int tSize = 0;//keep track of size

public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;



    int maxi(int x,int y);

    int findHeight(tree_node* Ptr);

    int balanceHeights(tree_node* Ptr);

    tree_node* rotateRight(tree_node* &Ptr);

    tree_node* rotateLeft(tree_node* &Ptr);

    void removeSubtree(tree_node* Ptr);

    void copyHelperFunc(tree_node* Ptr);

    tree_node* insertionHelper(tree_node* current, T element);
};


template <typename T>
AVLSet<T>::AVLSet()
{
    root = nullptr;//create the tree by making first node empty
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    removeSubtree(root);//helper function to help delete
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    root = nullptr;//make new node to empty
    tSize = s.tSize;//copy size of new tree
    copyHelperFunc(s.root);//helper function to help copy entirety of old tree
}

template <typename T>
void AVLSet<T>::copyHelperFunc(tree_node* tree){
    if(tree){
    this->add(tree->data); //add first node/root data into new root
    this->copyHelperFunc(tree->left);// go through entire tree
    this->copyHelperFunc(tree->right);
}

}

template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    if(this != &s){
        this->tSize = s.tSize; //copy size

        this->removeSubtree(root); //remove entire tree of the first variable(no mem leaks)
        root = nullptr;// make root to nullptr

        this->copyHelperFunc(s.root); //copy entire tree to new variable
    }
    return *this;
}


template <typename T> 
   
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    root = insertionHelper(root,element); //helper function to help recursively call itself
    tSize++; //increase size after element is added

}

template<typename T>
typename AVLSet<T>::tree_node* AVLSet<T>::insertionHelper(tree_node* current, T data){
    if (current == nullptr){
        tree_node* tn = new tree_node(data); // BST rotation
        return tn;//return the node
        
    }

    if (data < current->data){
        current->left = insertionHelper(current->left, data); 
    }

    else{//else its greater
        current->right = insertionHelper(current->right, data);
    }
    current->height = maxi(findHeight(current->left),findHeight(current->right)) + 1; //modify current height depending on newly added node
    int balance = balanceHeights(current);//calculate the balance to see if its balance

    if (balance > 1 && data < current->left->data){//LL
        return rotateRight(current);
    }
    if (balance < -1 && data > current->right->data){//RR
        return rotateLeft(current);
    }
    if (balance >1 && data > current->left->data){//LR
        current->left = rotateLeft(current->left);
        return rotateRight(current);
    }
    if(balance < -1 && data < current->right->data){//RL
        current->right = rotateRight(current->right);
        current = rotateLeft(current);
    }

    return current;//return the node after rebalancing is done

} 




template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    tree_node* current = root; //make 

    while (current != nullptr){
        if (current->data == element){ //if the current one its on data same as the element return true
            return true;
        }
        else if(element > current->data){ //if its not check if data is less or greater then transverse through it
            current = current->right;
        }
        else{
            current = current->left;
        }
    }
    return false;//if reached the end return false
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    if(root==nullptr){
        return 0;
    }
    else{
        return tSize; //return size of tree
    }

}

template<typename T>
int AVLSet<T>::maxi(int x,int y){ //max function returns max of two ints
    if (x>y){
        return x;
    }
    else{
        return y;
    }
}


template<typename T>
int AVLSet<T>::findHeight(tree_node* Ptr){
    if (Ptr == nullptr){//if the node given is empty height is 0
        return 0;
    }
    else{
        return Ptr->height; //retruns height
    }
}

template<typename T>
int AVLSet<T>::balanceHeights(tree_node* Ptr){
    if (Ptr ==nullptr){ //find the balance of the node
        return 0;
    }
    else{
        return (findHeight(Ptr->left)-findHeight(Ptr->right)); //calculates the balance
    
}
}

template<typename T>
typename AVLSet<T>::tree_node* AVLSet<T>::rotateRight(tree_node* &Ptr){
    tree_node* x; //make two temp nodes to rotate right correctly
    tree_node* y;
    x = Ptr->left;
    y = x->right;
    x->right = Ptr;
    Ptr->left = y;

    Ptr->height = maxi(findHeight(Ptr->left), findHeight(Ptr->right)) +1; //reconfigure the heights
    x->height = maxi(findHeight(x->left), findHeight(x->right)) +1;

    return x;
}

template<typename T>
typename AVLSet<T>::tree_node* AVLSet<T>::rotateLeft(tree_node* &Ptr){
    tree_node* x;//make two temp nodes to rotate left correctly
    tree_node* y;
    x = Ptr->right;
    y = x->left;
    x->left = Ptr;
    Ptr->right = y;

    Ptr->height = maxi(findHeight(Ptr->left), findHeight(Ptr->right)) +1;//reconfigure the heights
    x->height = maxi(findHeight(x->left), findHeight(x->right)) +1;

    return x;
}

template<typename T>
void AVLSet<T>::removeSubtree(tree_node* Ptr)
{
    if (Ptr != nullptr){
        if(Ptr->left != nullptr){
            removeSubtree(Ptr->left);
        }
        if(Ptr->right != nullptr){
            removeSubtree(Ptr->right);
        }
        delete Ptr;
    }
}


#endif // AVLSET_HPP

