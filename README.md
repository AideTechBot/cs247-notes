# JUNE 4 2018
An invariant is some property that is held true for the entire execution of a program

Without invariants, it\'s hard to logic about a piece of software

A representation invariant applies to an entire class, so across objects of that class

An abstraction function that maps from legal representations of our data to the actual client facing representation

### CONSIDERING A LIST
* Array vs Linked List
* Depends entirely on how it\'s going to be used.
* Lots of inserts at the front, LL might be better O(1) insert at front
* lots of random access, array is probably better


We don\'t know necessarily which is better. We want to be able to swap out representations easily/painlessly. So we want our spectADT to have REPRESENTATION INDEPENDANCE, changes to the representation don\'t affect how the ADT is used. We define some representaiton invariants R to help us reason about our class and write good code. Defines what a legal/valid state for our representation invariants. Similarly we come up with an abstraction function A, that map from valid states of representation, to our ADTs possible values.

Consider a set of Ints ADTs

R(no duplicates)
Arrays(R) | Int Set
----------|--------
[] | []
[1] | [1]
[1,2], [2,1] | [1,2]

```
class Set {
        int * elements_;
        size_t capacity_;
        size_t size_;
    public:
        Set();
        ~Set();
        void insert(int d);
        void remove(int d);
        bool member(int d);
};
```

1. No duplicate elements
  	1. FORALL i,j {0, ..., size_-1} i:=j | elements_[i] != elements_[j]. 
  	1. 2 Choices for now to represent this as an array with doubling strategy.
  	1. All elements in our set are stored in indicies 0, ..., size_-1 of elements_.
  	1. Check that each method preserves invariants
    	1. Verify that ctor establishes invariants
    	1. For each method, assume it holds true, prove/verify method doesn\'t violate invariant at end, done.
    	1. If encapsulation isn\'t broken, representation invariants hold true.
	
