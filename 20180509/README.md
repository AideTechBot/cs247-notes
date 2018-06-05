// Accessors (getters)
// -methods that return the value of a member field
// Mutators (setters)
// -methods that allow for the setting of member fields

// Restricts usage of memebr fields to only those we 
// give access to through the interface

// only allows usage of memember fields under our ADT's conditions

// Common naming conventions:
// attribute, getAttribute(), setAttribute()
// attribute, attribute(), attributeIs()

// Should it be a member?
// - only it if has to be

// ctors, dtors, accessors, mutators
// virtual method
// cannot be writted with only ADTs public interface (needs access to internals):
//  -could also be a friend (only if it cant be a member)

// certain operators (as per c++ standard) must be members
// - operator=, operator[], operator(), operator->, operatorT (where T is a type, (type conversion))

// some functions cant (at least if we want them to work properly) be members
// in >> x;
// out << x;
// if they where written as members :
class Rational {
  istream & operator>>(istream & in) {
    ...
    return in;
  }
};

// this would make it
r >> cin;
// this is ugly

// another cool thing: always returns the input stream to chain stuff like
cin >> x >> y >> z;

// for rationals:
class Rational {
  public:
    ...
    int denominator() const { return denominator_; }
    int numerator() const { return numerator_; }
    void denominatorIs(int d) {
      if (!d) throw "divide by 0 attempt";
      denominator_ = d;
    }
    void numeratorIs(int n) { numerator_ = n; }
  private:
    int denominator_, numerator_;
}

istream & operator>> (istream & in, Rational & r) {
  char slash;
  int d, n;
  in >> d >> slash >> n;
  r.denominatorIs(d);
  r.numeratorIs(n);
  return in;
}

ostream & operator<< (ostream & out, const Rational & r) {
  out << r.numerator() << "/" << r.denominator();
  return out;
}

// otherwise prefer non friend, non member functions
// - better encapsulation
// - compier ensures accesses cannot be made to private components
// - more flexible packaging of data
//    (declarations of standalone functions can be spread across files, client can include only
//    subsets of functions)

// BEST PRACTICES
// - All data members are private
// - mutators/accessors for the fields that make sense
// - if a non member function needs full acess and can't be a member function;
//   then make it a friend

// Also:
// classes can be friends!
// often used when we have nested classes
// alternatively if a nested class is private, it could just be a struct

class Stack {
  public:
    Stack();
    ~Stack();
    void push(int n);
    int pop();
    int peek();
    class Node {
      friend class Stack;
      public:
        Node();
        ~Node();
      private:
        int elem_;
        Node * next;
    };
  private:
    Node * top_;
};

// here, Node could be (and probably should be) a private struct
// there is no reason for client to use Node objects
