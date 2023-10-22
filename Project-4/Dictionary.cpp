//  Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <utility>  // for swap

using namespace std;

const vector<int> MAXBUCKETS_CHOICES {2, 3, 97, 199, 569, 1097, 1553, 3001, 5107, 7919, 11057, 16111,
    26099, 30677, 35153, 40087, 47629, 54151, 60013, 65677, 70677, 75557, 80251, 86171, 90529, 95959, 9991};

const int ACSII_TO_LETTERS = 96;
const int LETTERS_IN_ALPHABET = 26;

void removeNonLetters(string& s);

  // This class does the real work of the implementation.

// Anagram Structure
struct Anagram
{
    string key;
    Anagram* nextPermutation;
};

// Bucket Structure
struct Bucket
{
    string key;
    Bucket* nextBucket;
    Anagram* nextAnagram;
};

class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets);
    ~DictionaryImpl();
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
    
    // My additions
    unsigned int hash_function(string str) const;
    void maxBucketsChoice(int maxBuckets);
    
  private:
    // Make array of pointers to buckets
    vector<Bucket*> ptrsToBuckets;
    
    // Number of buckets
    int m_numBuckets;
};

// Choose number of buckets as prime number for efficiency
void DictionaryImpl::maxBucketsChoice(int maxBuckets)
{
    for (int i {1}; i != MAXBUCKETS_CHOICES.size(); i++)
    {
        if (MAXBUCKETS_CHOICES.at(i) > maxBuckets)
        {
//            cerr << "Number of buckets is: " << MAXBUCKETS_CHOICES.at(i-1) << endl;
            m_numBuckets = MAXBUCKETS_CHOICES.at(i-1);
            return;
        }
    }
    m_numBuckets = maxBuckets;
}

DictionaryImpl::DictionaryImpl(int maxBuckets)
: m_numBuckets()
{
    maxBucketsChoice(maxBuckets);
    for (int i {0}; i < m_numBuckets; i++) ptrsToBuckets.push_back(nullptr);
}

// Hash Function
unsigned int DictionaryImpl::hash_function(string str) const
{
    unsigned int hash {0};
    
    for (int i {0}; i < str.length(); i++)
    {
        hash += str[i] - ACSII_TO_LETTERS;  // Map a->1, b->2, ..., z->26
//        cerr << val << endl;
    }
//    cerr << "Hash: " << hash << endl;
    int index = hash % m_numBuckets;
//    cerr << "Index: " << index << endl;
    return index;
}

// Anagram Checker
bool isAnagram(const string word, const string otherWord)
{
//    cerr << "Word: " << word << endl;
//    cerr << "Bucket Word: " << otherWord << endl;
    
    // Return false if words are not of equal length
    if (word.length() != otherWord.length()) return false;

    int numLetters[LETTERS_IN_ALPHABET] = {0};
    for (char c : word) numLetters[c-'a']++;

    // Print statement to check
//    for (int i {0}; i < LETTERS_IN_ALPHABET; i++) cerr << numLetters[i];
//    cerr << endl;

    int numLetters2[LETTERS_IN_ALPHABET] = {0};
    for (char c : otherWord) numLetters2[c-'a']++;

    // Print statement to check
//    for (int i {0}; i < LETTERS_IN_ALPHABET; i++) cerr << numLetters2[i];
//    cerr << endl;

    // Check usage count of each letter
    for (int i {0}; i < LETTERS_IN_ALPHABET; i++)
    {
        if (numLetters[i] != numLetters2[i])
        {
//            cerr << word << " is not an anagram of " << otherWord << ", returning false..." << endl;
            return false;
        }
    }
//    cerr << word << " is an anagram of " << otherWord << ", returning true!" << endl;
    return true;
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if ( ! word.empty())
    {
        int putInBucket = hash_function(word);
        
        // Insert node at bucket insertWord
        if (ptrsToBuckets[putInBucket] == nullptr) // Edge case for no buckets
        {
            // Create new bucket
            Bucket* insertWord = new Bucket;
            Anagram* insertAnagram = new Anagram;
//            cerr << "Creating new bucket...\n";
            
            insertAnagram->key = word;
            insertAnagram->nextPermutation = nullptr;
//            cerr << "Successfully inserted " << word << " at head of anagram LL!" << endl;
            
            insertWord->key = word;
            insertWord->nextBucket = nullptr;
            insertWord->nextAnagram = insertAnagram;
            
            ptrsToBuckets[putInBucket] = insertWord;
//            cerr << "Successfully inserted " << word << " into bucket " << putInBucket << endl;
            
            return;
        }
        else  // Insert item into first position of linked list
        {
                
            // Iterate through all buckets and check if word is an anagram of any of these
            for (Bucket* p = ptrsToBuckets[putInBucket]; p != nullptr; p = p->nextBucket)
            {
                // If word is an anagram, insert it into anagram linked list
                if(isAnagram(word, p->key))
                {
                    Anagram* insertAnagram = new Anagram;
                    insertAnagram->key = word;
                    insertAnagram->nextPermutation = p->nextAnagram;
//                    cerr << "Successfully inserted " << word << " into anagram LL!" << endl;
                    
                    // Have bucket point to newly inserted anagram
                    p->nextAnagram = insertAnagram;
                    return;
                }
            }
            
            // Word is not an anagram of any preexisting buckets, so we create a new bucket
            Bucket* insertWord = new Bucket;
            Anagram* insertAnagram = new Anagram; 
//            cerr << "Creating new bucket...\n";
            
            insertAnagram->key = word;
            insertAnagram->nextPermutation = nullptr;
//            cerr << "Successfully inserted " << word << " at head of anagram LL!" << endl;
            
            insertWord->key = word;
            insertWord->nextBucket = ptrsToBuckets[putInBucket];
            insertWord->nextAnagram = insertAnagram;
            
            ptrsToBuckets[putInBucket] = insertWord;
//            cerr << "Successfully inserted " << word << " into bucket " << putInBucket << endl;
            
            return;
        }
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;
    
    // Compute hash of letters
    int hashValue = hash_function(letters);

    // Go to hashValue in vector and iterate through buckets
    for (Bucket* p = ptrsToBuckets[hashValue]; p != nullptr; p = p->nextBucket)
    {
        if (isAnagram(letters, p->key)) // If we find an anagram in the bucket, use callback on corresponding anagram linked list
        {
            for (Anagram* q = p->nextAnagram; q != nullptr; q = q->nextPermutation)
            {
                callback(q->key);
            }
            return;
        }
    }
//    cerr << "No anagrams found :(\n";
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Destructor
DictionaryImpl::~DictionaryImpl()
{
    for(int i {0}; i < ptrsToBuckets.size(); i++)
    {
        Bucket* tempBucket {nullptr};
        Anagram* tempAnagram {nullptr};
        
        // Iterate through buckets and delete anagram linked lists
        for (Bucket* p = ptrsToBuckets[i]; p != nullptr; p = p->nextBucket)
        {
            for (Anagram* q = p->nextAnagram; q!= nullptr;)
            {
//                cerr << "Deleting word in anagram LL: " << q->key << endl;
                tempAnagram = q;
                q = q->nextPermutation;
                delete tempAnagram;
            }
        }
        // Delete buckets
        for (Bucket* p = ptrsToBuckets[i]; p != nullptr;)
        {
//            cerr << "Deleting word in bucket LL: " << p->key << endl;
            tempBucket = p;
            p = p->nextBucket;
            delete tempBucket;
        }
    }
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
