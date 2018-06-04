// REVIEW
MyClass getThing() { // RIGHT
  MyClass T{...};
  return T;
}

MyClass & getThing() {
  MyClass T{...};
  return T; // returning an alias to an object that doesnt exist
}

MyClass * getThing() {
  MyClass T{...};
  return &T; // same as #2
}

MyClass * getThing() {
  MyClass * T = new MyClass{}; // the user needs to be aware they need to cleanup the pointer
  return T;
}

MyClass & getThing() {
  MyClass * T new MyClass{...};
  return *T;
}

// to delete the obj you need to do:
MyClass & x = getThing();
delete &x;


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

// BY default, C++ gives you:
// - a default ctor (disappears as soon as any other ctor is written)
// - copy ctor (copies all the fields)
// - dtor (does nothing)
// - Copy assignment operator (copy assigns all fields)
// - move ctor (identical to built in copy ctor, disappears if you write a copy ctor)
// - move AO (samething but with CAO)

// When are the builtins insufficient?
// - when you own a resource
// - you have logical/semantic meaning to these operations/your objects

// Rules of thumb:
// - BIG 5: (COPY CTOR, MOVE CTOR, CAO, MAO, DTOR)
// - if you need one, you need all 5

// move and copy illision
// - compiler optimizes but just calling the basic ctor
// - dont have to know when it occurs but that it does

// Entity vs value
//
// ENTITY:
// - computer embodiement of irl
// - each object has a unique entity
// - objects with the same attributes values does not imply they are the same
// example:
// - physical objects airplane, runway, taxiway
// - people, passengers, booking agent
// - records: customer info, boarding pass
// - transactions: reservations, cancellations, receipts
//
// VALUE:
