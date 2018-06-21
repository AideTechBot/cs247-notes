## Interface Specification

> **Precondition**: Constraints that must hold before the function is called.  
> **Postconditions**: Constraints that hold after the function is called.  
> **Modifies**: The objects/variables this function may modify.  
> **Throws**: Exceptions your function may throw, and conditions under which they are thrown.  
> **Ensures**: Guaranteed side effects on modified objects.  
> **Returns**: Describes return value.  


**Example**:
```cpp
// sumVector.h
#include <vector>
int sumVector(const std::vector<int> & vect);
// Preconditions: vect is a valid vector whose content's sum does not overflow.
// Requires ...
// Modifies ...
// Ensures ...
// Returns ...

int sumVector(const std::vector<int> & vect) {
    int sum = 0;
    for (size_t i = 0; i < vect.size(); ++i) {
        sum += vect[i];
    }
    return sum;
}
```
```cpp
// example replace.cc
// requires: exists i such that vect@pre[i] == oldElem
// modifies: vect
// ensures: let i be the first index such that vect@pre[i] == oldElem, vect[i] == newElem and all other indicies are unchanged
// return: i : vect@pre[i] = ??????????????????
//
// substring.cc
// returns: true iff there exists strings A and B s.t. text = <A><word><B>
```

- If you find yourself writing on a very complicated spec, it is incentive to redesign/rethink your approach

- Spec will affect/shape the structure of your code

- Spec should focus on requirements NOT implementation (more in cs445)


For exceptions section of your spec:
1. the interface should declare a complete list of possible exceptions
2. the conditions under which each exception is thrown
3. the specs preconditions should NOT include the conditions that lead to a thrown exception


### Class example 
```cpp
class IntStack {
  // specification fields:
  // stack
  // top = top element of stack
  public:
    IntStack();
    // ensures: initializes stack to or empty stack
    
    ~InitStack();
    // modifies: stack
    // ensures: stack no longer exists memory is all freed
    
    void push(int elem);
    // modifies: stack, top
    // ensures stack is appended with elem, top = elem
    
    int top();
    // requires: stack is non-empty
    // returns: top
    
    void pop();
    // modifies: stack, top
    // ensures: if stack@pre is empty, then stack is empty
    //          else stack = stack@pre with elem removed
    //          top = remaining top or everything if stack is empty
};
```    
"Stack" and "top" are *Abstract Specification Data Members*. They don't define the actual structure/fields of our class but rather a way to describe the clients view of the object state that we can write our expression over.


### Terminology
- An "interface specification" describes the behaviour of some software unit (fn or class).
- A implementation "satisfies" a spec if it conforms to the defined behaviour.
// - The "specification set" of a specification is the set of all conforming implementations.


