# REVIEW
Right way to do things
```cpp
MyClass getThing() {
  MyClass T{...};
  return T;
}
```
Retuening an alias/pointer to an object that doesn't exist:
```cpp
MyClass & getThing() {
  MyClass T{...};
  return T; 
}

MyClass * getThing() {
  MyClass T{...};
  return &T; 
}
```
Returning a pointer/ref to something on the heap:
```cpp
MyClass * getThing() {
  MyClass * T = new MyClass{}; // the user needs to be aware they need to cleanup the pointer
  return T;
}

MyClass & getThing() {
  MyClass * T new MyClass{...};
  return *T;
}
```
To delete the obj you need to do:
```cpp
MyClass & x = getThing();
delete &x;
```
---
### Example with move constructor
```cpp
class Node {
  Node(int elem, Node * next);
  Node(const Node & n);
  Node & operator=(const Node & other);
  Node(Node && other);
  Node & operator=(Node && other);
};

Node plusOne(Node n) {
  for(Node * p = &n; p; p=p->next()) {
    p->dataIS(p->data()+1);
  }
  return n;
}

Node l = Node(1, new Node(2, new Node(...)));
Node q = plusOne(l);

Node::Node(Node && other): data_(other.data_), next_(other.next) {
  other.next_ = nullptr;
  // if we dont do this, other will go out of scope and call its destructor
}


Node::Node(Node && other): data_(other.data_), next_(other.next), name_(std::move(other.name_)) {
  other.next_ = nullptr;
}

Node & Node::operator=(Node && other) {
  swap(other);
  return *this;
}
```
### BY default, C++ gives you:
- A default ctor (disappears as soon as any other ctor is written)
- copy ctor (copies all the fields)
- dtor (does nothing)
- Copy assignment operator (copy assigns all fields)
- Move ctor (identical to built in copy ctor, disappears if you write a copy ctor)
- Move AO (samething but with CAO)

### When are the builtins insufficient?
- When you own a resource
- You have logical/semantic meaning to these operations/your objects

### Rules of thumb:
- BIG 5: (COPY CTOR, MOVE CTOR, CAO, MAO, DTOR)
- If you need one, you need all 5 (generally)

### Move and copy elision
- Compiler optimizes but just calling the basic ctor
- Don't have to know when it occurs but that it does
