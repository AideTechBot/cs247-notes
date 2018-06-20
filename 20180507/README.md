What do we need for the code in 20180502.txt?
1. default ctor
2. copy ctor
3. + operator, * operator, == operator
4. input/outputoperator

### Rational Constructor
```
Rational::Rational(int num, int den):
  numerator_(num), denominator_(den) {
  if (!den) throw "Divide by zero";
}
```
### Rational 1 arg Constructor
```
Rational::Rational(int num): numerator_(num), denominator(1) {}
```

### Rational Default Constructor
```
Rational::Rational(): numerator_(0), denominator_(1) {}
```
^ This is an example of function overloading
* - It must differ in type or number of params.
* - It cant differ by only return type.

But... Those constructors are terrible and a waste of time! Let's use default arguments instead:
```cpp
class Rational {
  public:
    Rational(int num=0, int den=1): // remember to put "explicit" if u dont want implicit type conversion
      numerator_(num), denominator_(den) {
      if (!den) throw "Divide by Zero";
    }
};
```
The default values must only be last n params
```cpp
Rational(int num=0, int den); // NO
```
What about our other operators/functions ?
```cpp
class Rational {
  public:
    Rational operator+(const Rational & other) {
      // When overloading an operator as a member fn: the first parameter is always itself (*this)
      // We passed our operand as a const lvalue reference
      return Rational(.....);
    }
};
```
#### lValue reference
* A reference is like a pointer, but NOT A POINTER.
* It is exactly what it refers to be, it refers to an actual piece of data elsewhere (an alias)
* It behaves like "const pointers with automatic dereferencing"
* Auto dereferencing means you treat a reference exactly as you would the thing it refers (eg. X.fn() not X->fn())
* No such thing as a null reference, must be initialized when created
* Since its just an alias for actual data, you can mutate the actual data itself through the reference
* So if you don't want to change the data, declare as "const ref"
  * pass by const ref not for speed, but safety of not modifying data itself
```cpp
class Rational {
...
};

Rational operator+(const Rational & lhs, const Rational & rhs) {
...
}
```
When it was a member function, we could access the private data, now we can't. So lets go back
```cpp
class Rational {
  public:
    Rational operator+(const Rational & other) {
      return Rational(
          this->numerator_ * other.denominator_ + this->denominator_ * other.numerator_,
          this->denominator_ * other.denominator
      );
  private:
    int numerator_, int denominator_;
};
```
Going back to a non member function:
```cpp
Rational operator+(const Rational & lhs, const Rational & rhs) {
```
### Should it be a member?
- If its a mutators + accessors ?
- If its a friend or not a friend?
- to member or not to member?
- if it doesn't need to be a member function, it isn't (generally)
