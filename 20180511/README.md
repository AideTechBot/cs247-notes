# Node Class Implementation
**Constructors:**
```cpp
class Node {
  public:
    Node(int data, Node * next);
    Node(const Node & other);
    Node & operator=(const Node & other);
  private:
    int data_;
    Node * next_;
};

Node::Node (int data, Node * next): data_{data}, next_{next} {}

Node::Node (const Node & other): data_{other.data_}, next_{other.next_ ? new Node(*other.next_) : nullptr} {}
```
Built in copy-constructor copies all values (byte-wise) of built in types and for any object fields, calls copy-constructor. For our case, it would only be a shallow copy (next node would be shared).


**Assignment Operators:**
```cpp
Node::Node Node & operator= (const Node & other) {
  if (this == &other) return *this;
  delete next_;
  data_ = other.data_;
  next_ = other.next ? new Node(*other.next_) : nullptr; // if new throws an error here everything goes fucky
  return *this;
}
```
So to prevent the program from crashsing when new throws an error:
```cpp
Node & Node & operator= (const Node & other) {
  if(this == &other) return *this;
  Node * tmp = other.next_ ? ....;
  data_ = other.data_;
  delete next_;
  next_ = tmp;
  return *this;
}
```
Or we can do:
### Copy and Swap Idiom
Header file:
```cpp
class  Node {
  //...
  private:
    void swap(Node & n);
};
```
CPP file:
```cpp
#include <utility>

void Node::swap(Node & n) {
  std::swap(data_, other.data_);
  std::swap(next_, other.next_);
}

Node & Node operator= (const Node & other) {
  // Destructor for tmp will get called which does the clean-up for us.
  Node tmp{other};
  swap(tmp);
  return *this;
}

Node::~Node () {
  delete next_;
}

Node plusOne(Node n) {
  for (Node * p=&n; p; p=p->next()) {
    p->dataIS(p->data() + 1);
  }
  return n;
}

int main () {
  Node n = new Node{o, new Node{1, new Node{1,nullptr}}};
  // j will have to be deep copied from plusOne(n).
  Node j = plusOne(n);
}
```
### lvalue References
- Node & n
- lvalue is anything with a memory address
### rvalue References
- rvalues are temporary objects
- To create a reference to an rvalue you use &&
- Now we have a new important ctor and assignment operator

# REMEMBER TO COMPILE USING C++ 14 FOR ASSIGNMENTS 
