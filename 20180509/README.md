**Accessors (getters)**
- methods that return the value of a member field
**Mutators (setters)**
- methods that allow for the setting of member fields


Restricts usage of memebr fields to only those we give access to through the interface.
Only allows usage of memember fields under our ADT's conditions.

### Common naming conventions
- attribute, getAttribute(), setAttribute()
- attribute, attribute(), attributeIs()

### Should it be a member?
> Only it if has to be
- ctors, dtors, accessors, mutators
- virtual method
- Cannot be writted with only ADTs public interface (needs access to internals):
  - Could also be a friend (only if it cant be a member)
- Certain operators (as per c++ standard) must be members
  - operator=, operator[], operator(), operator->, operatorT (where T is a type, (type conversion))


Some functions can't (at least if we want them to work properly) be members.
```cpp
in >> x;
out << x;
```
If they where written as members :
```cpp
class Rational {
  istream & operator>>(istream & in) {
    ...
    return in;
  }
};
```
^This would make it:
```cpp
r >> cin;
```
Do not do that, it's god awful.


Another cool thing: always return the input stream to chain stuff like:
```cpp
cin >> x >> y >> z;
```
---
### Rationals
```cpp
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
```
Otherwise, prefer non friend/non member functions because:
- Better encapsulation
- Compier ensures accesses cannot be made to private components
- More flexible packaging of data
  - Declarations of standalone functions can be spread across files, client can include only subsets of functions.
---
### Best practices
- All data members are private
- Mutators/accessors for the fields that make sense
- If a non member function needs full acess and can't be a member function, then make it a friend.
**Also:**
- Classes can be friends!
  - Often used when we have nested classes.
  - Alternatively if a nested class is private, it could just be a struct.
```cpp
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
```
In the code above, Node could be (and probably should be) a private struct. There is no reason for client to use Node objects.
