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

Node::Node Node & operator= (const Node & other) {
  if (this == &other) return *this;
  delete next_;
  data_ = other.data_;
  next_ = other.next ? new Node(*other.next_) : nullptr; // if new throws an error here everything goes fucky
  return *this;
}

Node & Node & operator= (const Node & other) {
  if(this == &other) return *this;
  Node * tmp = other.next_ ? ....;
  data_ = other.data_;
  delete next_;
  next_ = tmp;
  return *this;
}

// COPY AND SWAP IDIOM
class  Node {
  //...
  private:
    void swap(Node & n);
};

#include <utility>

void Node::swap(Node & n) {
  std::swap(data_, other.data_);
  std::swap(next_, other.next_);
}

Node & Node operator= (const Node & other) {
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
  Node j = plusOne(n);
  
// lvalue reference : Node & n
// -value is anything with a memory address

// rvalues are temporary objects
// to create a reference to an rvalue you use &&
// Now we have a new important ctor and assignment operator

// COMPILE USING C++ 14
