// Sequence.h

// Linked List = LL

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

using ItemType = std::string;
// using ItemType = unsigned long;

class Sequence
{
  public:
    
    // Implementations from CS 32 HW 1
    Sequence();
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
    
    // Housekeeping functions
    ~Sequence();                                // Destructor
    Sequence(const Sequence& other);            // Copy constructor
    Sequence& operator=(const Sequence& rhs);   // Assignment operator
    
  private:
    
    int m_size; // Track number of elements in LL
    
    // Declare Nodes here
    struct Node
    {
        ItemType storedVal;
        Node* next;     // Pointer to next element in linked list
        Node* prev;     // Pointer to previous element in linked list;
    };
    
    Node* head;         // Pointer to first element in linked list
    Node* tail;         // Pointer to last element in linked list
};

// New Sequence algorithms to implement
int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* SEQUENCE_H */
