### STATIC MEMBERS
- you can declare fields of a class, and methods static
- static shared across objects of that class, tied/global to the class scope
- if you add a static field to a class that field is shared across all instances of that class.
- if it's public you can access it without an object at all
```cpp
class Foo {
  public:
    static int x;
}

Foo::x = 5;
Foo y;
Foo x;
cout << y.x; // prints 5
cout << z.x; // prints 5
z.x=10;
cout << y.x; // prints 10
```
- static member functions, tied to the class, not to individual objects
- can be called through class without an object w/out an object to call them on
- static member functions can only access static fields:
```cpp
class Foo {
  static void DoThing();
}
Foo::DoThing();
class Foo {
  public:
    void fun() { zIs(5); }
    static void bar() { zIs(6); } // illegal because can't access zIs() or z_, they're not static 
    void zIs(int i) { z_ = i;}
  private:
    int z_;
};
```
---
### License Plate ADT
- valid license plate is a unique sequence of 2-8 chars
- here chars means uppercase alphabetical chars, digits, or spaces
VALUE OR ENTITY?
- value!
- immutable? YES




- Valid Range: hidden canonical method to ensure meets requirements 
- Default Value: ctor generates "next" unused 7-char value
- Constructed from provided val: vanity plates
- Operations: operator<, i/o operators, operator++ to gen next value, maybe !=, ==
- isVanity(): bool

### DEFFAULT CTOR:
- generates next value, updates last generated if its free; if not repeat, if it is mark it as no longer free
- PARAMETERIZED CTOR: check if free if not throw exn, else mark it not free, check length too
- DEFAULT VISIBILITY OF STRUCT: public CLASS: private
```cpp
class LicensePlate {
    static string next_free_;
    static unordered_set<string> used_;
    string plate_;
  public:
    LicensePlate();
    LicensePlate(string s);
    bool isVanity();
    string name();
};
```
---
## Singleton design (anti) pattern
- The singleton pattern is used when we have a class for which we only ever want one instance
  - E.G. settings class is an example of where someone might use this
How does it work?
```cpp
class Egg {
  static Egg e; // singleton obj
  int i;
  Egg(int ii) : i(ii) {} // private so client cant create objects
  public:
    static Egg & instance() { return e; }
    int val() const { return i; }
    Egg(const & Egg) = delete;
    Egg & operator=(const Egg &) = delete;
};

Egg Egg e(42); //how you init the singleton egg
// should be in the egg module implementation file
```
