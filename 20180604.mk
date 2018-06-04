# JUNE 4 2018
An invariant is some property that is held true for the entire execution of a program

Without invariants, it's hard to logic about a piece of software

A representation invariant applies to an entire class, so across objects of that class

An abstraction function that maps from legal representations of our data to the actual client facing representation

### CONSIDERING A LIST
* Array vs Linked List
* Depends entirely on how it's going to be used.
* Lots of inserts at the front, LL might be better O(1) insert at front
* lots of random access, array is probably better
we don't know necessarily which is better
want to be able to swap out representations easily/painlessly
so we want our spectADT to have REPRESENTATION INDEPENDANCE, changes to the representation don't affect how the ADT is used
we define some representaiton invariants R to help us reason about our class and write good code.
Defines what a legal/valid state for our representation invariants.
Similarly we come up with an abstraction function A, that map from valid states of representation, to our ADTs possible values
