// Sequence.cpp

// Linked List = LL

#include "Sequence.h"
#include <iostream>

using namespace std;

Sequence::Sequence()              // Constructor
 : head(nullptr), tail (nullptr), m_size(0)  // Member initialization list
{
    if (head == nullptr) cerr << "head fr fr" << endl;
    if (tail == nullptr) cerr << "tail fr fr" << endl;
}

bool Sequence::empty() const
{
    return (m_size == 0);
    
    // Print statements to test if list is empty
//    if (m_size == 0)
//    {
//        cerr << "Empty list lol" << endl;
//        return true;
//    }
//    else
//    {
//        cerr << "List isn't empty..." << endl;
//        return false;
//    }
}

int Sequence::size() const
{
//    if (head == nullptr)        // Empty list case
//    {
//        cerr << "Empty list lol" << endl;
//        return 0;
//    }
//
//    // Iterate through LL
//    for (Node* p {head}; p != nullptr; p = p->next)
//    {
//        m_size++;
//    }
//    cerr << "LL has " << m_size << " elements" << endl;
//    return m_size;
    
//    cerr << "List has size " << m_size << endl;
    return m_size;
}

Sequence::~Sequence()    // Destructor
{
    Node* temp {head};
    
    while(head != nullptr)
    {
        temp = head->next;
        delete head;
        head = temp;
    }
    
    // Iterate through LL and delete each Node
//    cerr << "Calling destructor..." << endl;
//    for(Node* p {head}; p != nullptr; p = p->next)
//    {
//        // head = head->next;
//        // delete p->Node;
//        // delete Node; // INCORRECT?
//
//
//        cerr << "Deleted node with value: " << p->storedVal << endl;
//        delete p;
//    }
}

int Sequence::insert(int pos, const ItemType &value)
{
    
    // Return -1 if accessing a position out of bounds
    if (pos < 0 || pos > size())
    {
        cerr << "You attempted to insert an item at a position out of bounds, " << size() << endl;
        return -1;
    }
    
    // Dynamically allocate space for a new Node
    Node* newGuy = new Node;
    newGuy->storedVal = value;
    
    // Empty list case
    if(empty())
    {
        // No need to account for position since it's the only element
        // pos = 0;
        
        // Both pointers in 1 element list should be set to nullptr
        newGuy->next = nullptr;
        newGuy->prev = nullptr;
        
        cerr << "Inserting item into empty list: " << newGuy->storedVal << endl;
        
        // Reassign head and tail pointers to point to new node
        head = newGuy;
        tail = newGuy;
        
        if (head->next == nullptr) cerr << "Head is correct" << endl;
        if (tail->next == nullptr) cerr << "Tail is correct" << endl;
        
        // Increment size of LL by 1
        m_size++;
        cerr << "List now has " << size() << " elements" << endl;
        return 0;
    }
    
//    // Single element list
//    if (size() == 1)
//    {
//        if (pos == 0)
//        {
//            cerr << "Inserting item at position " << pos << endl;
//            newGuy->storedVal = value;
//            
//            // Assigning pointers to node that will be inserted
//            newGuy->next = head;
//            newGuy->prev = nullptr;  // End of list from tail's POV
//            
//            // Rearranging pointers of nodes surrounding node to be inserted
//            head = newGuy;
//            head->next->prev = newGuy;
//        }
//    
//    }
    
    // Case where position is 0 (aka insert element after head)
    if (pos == 0)
    {
        cerr << "Inserting item at position " << pos << endl;
//        newGuy->storedVal = value;
        
        // Assigning pointers to node that will be inserted
        newGuy->next = head;
        newGuy->prev = nullptr;  // End of list from tail's POV
        
        // Rearranging pointers of nodes surrounding node to be inserted
        head = newGuy;
        head->next->prev = newGuy;
        
        if (head->storedVal == value) cerr << "Successfully inserted " << newGuy->storedVal << " at beginning of LL!" << endl;
        
        m_size++;
        cerr << "List now has " << size() << " elements" << endl;
        return 0;
    }
    
    // Inserting item at end of LL
    if (pos == size())
    {
        // Assigning pointers to node that will be inserted
        newGuy->next = nullptr;  // End of list from head's POV
        newGuy->prev = tail;
        
        // Rearranging pointers of nodes surrounding node to be inserted
        tail = newGuy;
        tail->prev->next = newGuy;
        
        if (tail->storedVal == value) cerr << "Successfully inserted " << newGuy->storedVal << " at end of LL!" << endl;
        
        m_size++;
        cerr << "List now has " << size() << " elements" << endl;
        return pos;
    }
    
    // Case where position is size() (last element in list)
//    if (pos == m_size)
//    {
//        newGuy->storedVal = value;
//        newGuy->next = nullptr;
//        tail = newGuy;
//    }

    // General case
    
    // Initialize counter to track which element of LL we are at
    int counter {0};
    
    // Iterate through LL
    for (Node* p {head}; p!= nullptr; p = p->next)
    {
        if(counter == pos-1)
        {
//            newGuy->storedVal = value;
            cerr << "Inserting " << value << " at position " << pos << endl;
            
            // Assigning pointers to node that will be inserted
            newGuy->next = p->next;
            newGuy->prev = p; // This works!
            
            // Rearranging pointers of nodes surrounding node to be inserted
            //p->next = newGuy;
            //p = newGuy->next;
            //p->prev = newGuy;
            p->next->prev = newGuy;
            p->next = newGuy;
            
            // Case where position is size() (last element in list)
            if(pos == size())
            {
                newGuy->next = nullptr;
                if(p->next->next == nullptr) cerr << "Last element " << newGuy->storedVal << " points to nullptr" << endl;
//                tail = newGuy;
            }
//            break;
        }
        counter++;
    }
    m_size++;
    cerr << "List now has " << size() << " elements" << endl;
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    // Dynamically allocate space for a new Node
    Node* newGuy = new Node;
    newGuy->storedVal = value;
    
    // Empty list case
    if(empty())
    {
        // No need to account for position since it's the only element
        // pos = 0;
        
        // Both pointers in single element list should be set to nullptr
        newGuy->next = nullptr;
        newGuy->prev = nullptr;
        
        cerr << "Inserting item into empty list: " << newGuy->storedVal << endl;
        
        // Reassign head and tail pointers to point to new node
        head = newGuy;
        tail = newGuy;
        
        if (head->next == nullptr) cerr << "Head is correct" << endl;
        if (tail->next == nullptr) cerr << "Tail is correct" << endl;
        
        // Increment size of LL by 1
        m_size++;
        cerr << "List now has " << size() << " elements" << endl;
        return 0;
    }
    
    // Initialize counter to track which element of LL we are at
    int counter {0};
    
    // Position of where item is inserted in LL
    int pos {counter + 1};
    
    // Case where position is 0 (aka insert element after head)
    if (counter == 0 && newGuy->storedVal <= head->storedVal)
    {
//            cerr << "Inserting item at position " << pos << endl;
//            newGuy->storedVal = value;
        
        // This implementation works only for singly linked lists
//        newGuy->next = head;
//        head = newGuy;
        
        // Assigning pointers to node that will be inserted
        newGuy->next = head;
        newGuy->prev = nullptr;  // End of list from tail's POV
        
        // Rearranging pointers of nodes surrounding node to be inserted
        head = newGuy;
        head->next->prev = newGuy;
        
        if (head->storedVal == value) cerr << "Successfully inserted " << newGuy->storedVal << " at beginning of LL!" << endl;
        m_size++;
        cerr << "List now has " << size() << " elements" << endl;
        return 0;
    }
    
    // Iterate through LL
    for (Node* p {head}; p != nullptr; p = p->next)
    {
//        // Case where position is 0 (aka insert element after head)
//        if (counter == 0 && newGuy->storedVal <= p->storedVal)
//        {
////            cerr << "Inserting item at position " << pos << endl;
////            newGuy->storedVal = value;
//            newGuy->next = head;
//            head = newGuy;
//            if (head->storedVal == value) cerr << "Successfully inserted " << newGuy->storedVal << " at beginning of LL!" << endl;
//            m_size++;
//            cerr << "List now has " << size() << " elements" << endl;
//            return 0;
//        }
        
        // Case where position is size() (last element in list)
        if(newGuy->storedVal > p->storedVal && p->next == nullptr)
        {
            // This implementation works for singlt linked list only
//            newGuy->next = nullptr;
//            p->next = newGuy;
            
            // Assigning pointers to node that will be inserted
            newGuy->next = nullptr;  // End of list from head's POV
            newGuy->prev = tail;
            
            // Rearranging pointers of nodes surrounding node to be inserted
            tail = newGuy;
            tail->prev->next = newGuy;
            
            if(p->next->next == nullptr) cerr << "Last element " << newGuy->storedVal << " points to nullptr" << endl;
//                tail = newGuy;
            cerr << "Returning position: " << pos << endl;
            m_size++;
            cerr << "List now has " << size() << " elements" << endl;
            return pos;
        }
        
        if (newGuy->storedVal > p->storedVal && newGuy->storedVal <= p->next->storedVal)
        {
            cerr << "Inserting " << newGuy->storedVal << " at position " << pos << endl;
            
            // This implementation works for singly linked list
//            newGuy->next = p->next;
//            p->next = newGuy;
            
            // Assigning pointers to node that will be inserted
            newGuy->next = p->next;
            newGuy->prev = p; //lfgggggggggggg it works
            
            // Rearranging pointers of nodes surrounding node to be inserted
            //p->next = newGuy;
            //p = newGuy->next;
            //p->prev = newGuy;
            p->next->prev = newGuy;
            p->next = newGuy;
            
            cerr << "Successfully inserted " << newGuy->storedVal << " in LL!" << endl;
            m_size++;
            cerr << "List now has " << size() << " elements" << endl;

//            // Case where position is size() (last element in list)
//            if(p->next == nullptr && newGuy->storedVal > p->storedVal)
//            {
//                newGuy->next = nullptr;
//                if(p->next->next == nullptr) cerr << "Last element head points to nullptr" << endl;
//    //                tail = newGuy;
//            }
//             cerr << "Returning position: " << pos << endl;
//             return pos;
            cerr << "Returning position: " << pos << endl;
            return pos;
        }
        counter++;
        pos = counter + 1;
    }
    cerr << "Returning position: " << pos << endl;
    return pos;
}

bool Sequence::erase(int pos)
{
    // Initialize counter to track which element of LL we are at
//    int counter {0};
    
    // Return false if attempting to delete at a position out of bounds
    if (pos < 0 || pos >= size())
    {
        cerr << "Your position " << pos << " is out of range, try again..." << endl;
        return false;
    }
    
    // Single element case
    if (pos == 0 && size() == 1)
    {
        cerr << "Removing element " << head->storedVal << " from LL!" << endl;
        
        // Declare pointer to point to first elemnt in LL
        Node* temp = head;
        
        head = head->next;
        tail = tail->next;
        
        if (head == nullptr) cerr << "Head points to nullptr after erasing single element LL!" << endl;
        if (tail == nullptr) cerr << "Tail points to nullptr after erasing single element LL!" << endl;
        
        m_size--;
        cerr << "List now has " << size() << " elements" << endl;
        
        // Delete pointer removed node points to and get rid of dangling pointer
        //delete temp->next;
        //delete temp->prev;
        
        // Delete node
        delete temp;
        return true;
    }
    
    // Case where first item in LL is erased
    if (pos == 0)
    {
        // Declare pointer to point to first element in LL
        Node* temp = head;
        
        // Reassign pointer to point to next element/nullptr
        head->next->prev = nullptr;
        head = head->next;
        
        m_size--;
        cerr << "List now has " << size() << " elements" << endl;
        
        // Delete pointer removed node points to and get rid of dangling pointer
        //delete temp->next;
        
        // Delete node
        delete temp;
        return true;
    }
    
    // Case where last item in LL is erased
    if (pos == size() - 1)
    {
        // Declare pointer to point to first element in LL
        Node* temp = tail;
        
        // Reassign pointer to point to next element/nullptr
        tail->prev->next = nullptr;
        tail = tail->prev;
        
        m_size--;
        cerr << "List now has " << size() << " elements" << endl;
        
        // Delete node
        delete temp;
        return true;
    }
    
    // Initialize counter to track which element of LL we are at
    int counter {0};
    
    // General case
    for (Node* p {head}; p != nullptr; p = p->next)
    {
        if(counter == pos - 1)
        {
            cerr << "Deleting element with value: " << p->next->storedVal << endl;
            
            // Declare pointer to point to LL element to be removed.
            Node* temp = p->next;
            
            // Have element p is pointing to point to element after the one getting erased
            p->next = p->next->next;
            
            // Same for prev pointer of element after one to be erased
            p->next->prev = p->next->prev->prev;
            
            // Delete node
            delete temp;
            m_size--;
            
            cerr << "Succefully deleted element at position " << pos << endl;
            cerr << "List now has " << size() << " elements" << endl;
            return true;
        }
        counter++;
    }
    return false;
}

int Sequence::remove(const ItemType& value)
{
    int numItemsDeleted {0};
    int currentPos {0};
    
    for (Node* p {head}; p != nullptr; p = p->next)
    {
        if(p->storedVal == value)
        {
            cerr << "Erasing item of value: " << p->storedVal << endl;
            erase(currentPos);
            numItemsDeleted++;
            currentPos--;
        }
        currentPos++;
    }
    cerr << "Returning number of items deleted: " <<numItemsDeleted << endl;
    return numItemsDeleted;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= size())
    {
        cerr << "Attempting to get an element out of range, current size is " << size() << ", try again..." << endl;
        return false;
    }
    
    // Initialize a counter to track position in LL
    int counter {0};
    
    for (Node* p {head}; p != nullptr; p = p->next)
    {
        if (counter == pos)
        {
            value = p->storedVal;
//            cerr << "Copying item at pos " << pos << " which is " << p->storedVal << " into value which now has item: " << value << endl;
            return true;
        }
        counter++;
    }
    cerr << "idk what happened to your get function bro" << endl;
    return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= size())
    {
        cerr << "Attempting to get an element out of range, current size is " << size() << ", try again..." << endl;
        return false;
    }
    
    // Initialize a counter to track position in LL
    int counter {0};
    
    for (Node* p {head}; p != nullptr; p = p->next)
    {
        if (counter == pos)
        {
            cerr << "Inserting item " << value << " at " << pos << endl;
            insert(pos, value);
            cerr << "Node at pos " << pos << " now has value " << p->storedVal << endl;
            return true;
        }
        counter++;
    }
    cerr << "idk what happened to your set function bro" << endl;
    return false;
}

int Sequence::find(const ItemType& value) const
{
    // Initialize p
    int p {0};
    
    // Iterate through LL and find value
    for (Node* iter {head}; iter != nullptr; iter = iter->next)
    {
        if (iter->storedVal == value)
        {
            cerr << "Found " << value << " at position " << p << "!" << endl;
            return p;
        }
        p++;
    }
    cerr << "Couldn't find " << value << ", returning -1..." << endl;
    return -1;
}

void Sequence::swap(Sequence &other)
{
    // Declare temporary pointers to swap heads
    Node* temp_head = head;
    int temp_size = m_size;
    
    // Swap heads and pointer
    head = other.head;
    m_size = other.m_size;
    
    // Swap heads and pointers
    other.head = temp_head;
    other.m_size = temp_size;
}

Sequence::Sequence(const Sequence& other)         // Copy constructor
{
    // Declare a new head and tail pointer to copy
    head = nullptr;
    tail = nullptr;
    
    // Initialize size to zero
    m_size = 0;
    
    //
    for (int i {0}; i < other.size(); i++)
    {
        ItemType copyValue;
        other.get(i, copyValue);
        insert(i, copyValue);
    }
}

Sequence& Sequence::operator=(const Sequence& rhs)    // Assignment operator
{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    // Return -1 if both sequences are empty
    if(seq1.empty() || seq2.size() > seq1.size())
    {
        cerr << "Either your second sequence is greater than your first sequence or one of your sequences is empty, returning -1..." << endl;
        return -1;
    }

    // Initialize counter
    int counter {0};

    // Initialize common index position
    int pos {0};

    // Initialize variables to access ItemType in each sequence
    ItemType seq1counter;
    ItemType seq2counter;

    // Loop through seq1 and see if there is an element that matches first element of seq2
    {
        for (int i {0}; i < seq1.size(); i++)
        {
            
            // Find first element in seq2
            seq2.get(0, seq2counter);
            cerr << "Searching for first element of seq2: " << seq2counter << " in seq1..." << endl;
            
            seq1.get(i, seq1counter);

//            if (seq1.find(seq2counter) == -1)      // ISSUE IS HERE COS I ALWAY LOOK THROUGH ALL INDICES OF seq1 EVEN WHEN I DON'T WANNA
//            {
//                return -1;
//            }
            
            if (seq2counter == seq1counter)
            {
                pos = seq1.find(seq2counter);
                cerr << "Found item " << seq2counter << " in seq1, position index is set to " << pos << endl;
                
                counter++;
                cerr << "Counter = " << counter << endl;
                
                for(int j {1}; j <= seq2.size(); j++)
                {
                    
                    if (counter == seq2.size())
                    {
                        cerr << "Subseqeunce found, returning index of seq1: " << pos << endl;
                        return pos;
                    }
                    
                    seq1.get(i+j, seq1counter);
                    seq2.get(j, seq2counter);

                    if (seq2counter != seq1counter)
                    {
                        counter = 0;
                        cerr << "Item " << seq1counter << " in seq1 not matching with item " << seq2counter << " from seq2, resetting counter to " << counter << endl;
                        pos = 0;
                        cerr << "Position index is reset to " << pos << endl;
                        break;
                    }
                    else
                    {
                        cerr << "Matching item: " << seq2counter << endl;

                        counter++;
                        cerr << "Counter = " << counter << endl;
                
                    }
                }
            }
        }
    }
    cerr << "Subsequence not found, returning -1..." << endl;
    return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    // Initalize placeholder ItemType
    ItemType copyOver;
    
    // Iterate through seq1 in reverse
    for (int i {seq1.size() - 1}; i >= 0; i--)
    {
        seq1.get(i, copyOver);
        cerr << "Got item " << copyOver << " from seq1!" << endl;
        
        // Store into result
        result.insert(result.size() /*seq1.size() - 1 - i*/, copyOver);
        cerr << "Stored item " << copyOver << " into result at position " << result.size() << endl;
        
        // Increment total count by 1
        cerr << "Result now has size " << result.size() << endl;
//        if(result.size() == seq1.size()) cerr << "Successfully reversed seq1!";
    }
    if(result.size() == seq1.size()) cerr << "Successfully reversed seq1!" << endl;
    
    // Iterate through seq2 in reverse
    for (int i {seq2.size() - 1}; i >= 0; i--)
    {
        seq2.get(i, copyOver);
        cerr << "Got item " << copyOver << " from seq2!" << endl;

        // Store into result
        result.insert(result.size() /* - 1 + seq2.size() - 1*/, copyOver);
        cerr << "Stored item " << copyOver << " into result at position " << result.size() << endl;

        // Increment total count by 1
        cerr << "Result now has size " << result.size() << endl;
    }
    
    // Initalize placeholder ItemType
    ItemType resultItem;
    
    // Print result
    cerr << "Printing out result, which has " << result.size() << " elements:" << endl;
    for (int i {0}; i < result.size(); i++)
    {
        result.get(i, resultItem);
//        cerr << "Result has item " << resultItem << " at position " << i << endl;
        cerr << resultItem;
    }
    cerr << endl;
}

void Sequence::dump() const
{
    cerr << "Head to tail list :" << endl;
    for (Node* p {head}; p != nullptr; p = p->next) cerr << p->storedVal << " -> ";
    cerr << endl;
    
    cerr << "Tail to head list :" << endl;
    for (Node* p {tail}; p != nullptr; p = p->prev) cerr << p->storedVal << " -> ";
    cerr << endl;
}
