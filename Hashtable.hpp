// HashSet.hpp

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include <algorithm>
#include "Set.hpp"
#include "item.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    void resize();


private:
    HashFunction hashFunction;

    int items;
    int capacitySize;
    item<T>** table;

};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    capacitySize = DEFAULT_CAPACITY;
    items = 0;
    table = new item<T>*[capacitySize];
    for(int i = 0;i< capacitySize; i++){
        table[i] = NULL;
    }
}


template <typename T>
HashSet<T>::~HashSet()
{
    item<T>* temp;
    for(int i = 0; i <capacitySize;i++){
        if(table[i] == NULL){
            delete table[i];
        }
        else{
            while(table[i]!= NULL){
                temp = table[i];
                table[i] = table[i]->next;
                delete temp;
            }
        }
    }
    temp = NULL;// clean up random ptrs
    delete[] table;
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}
{
    capacitySize = s.capacitySize; //copy size,num of items, and hash function
    hashFunction = s.hashFunction;
    items = 0;
    table = new item<T>*[capacitySize];
    for(int i = 0;i< capacitySize; i++){
        while(s.table[i]){
            this->add(s.table[i]->data);
            s.table[i] = s.table[i]->next;
        }
    }
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        HashSet<T> temp(s);
        std::swap(temp.table, table);
        std::swap(temp.capacitySize, capacitySize);
    }

    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
    int newSize = items+1;
    double fraction = (float)newSize / (float) capacitySize;
    if(fraction >= 0.8){
        resize();
    }
    int index = hashFunction(element)%capacitySize; //make sure hashfunction makes an index that fits the table
    if(table[index] == NULL){
        table[index] = new item<T>(element);
        items++;
    }
    else{
        item<T>* currentItem = table[index];
        while(currentItem->next != nullptr){
            if(currentItem->data == element){ //no dupes
                return;
            }
            currentItem = currentItem->next;
        }
        currentItem->next = new item<T>(element);
        items++;
    }
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{   
    unsigned int index = (hashFunction(element))%capacitySize;
    item<T>* itemPtr = table[index];

    while(itemPtr != NULL){
        if(itemPtr->data == element){
            return true;
        }
        itemPtr = itemPtr->next;
    }

    return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return items;
}

template<typename T>
void HashSet<T>::resize(){
    int oldTableSize = capacitySize;
    capacitySize *= 2;
    item<T>** oldTable = table;
    table = new item<T>*[capacitySize];
    for(int i =0; i<capacitySize; i++){
        table[i] = NULL;
        items = 0; 
    }

    for(int k = 0; k< oldTableSize; k++){
        if(oldTable[k] != NULL){
            item<T>* oldEntry;
            item<T>* entry = oldTable[k];
            while(entry != nullptr){
                this->add(entry->data);
                oldEntry = entry;
                entry = entry->next;
                delete oldEntry;
            }
        }
    }
    delete[] oldTable;
}


#endif // HASHSET_HPP

