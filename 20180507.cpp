// what do we need for the code in 20180502.txt?
// default ctor
// copy ctor
// + operator, * operator, == operator
// input/outputoperator

// Rational Constructor
Rational::Rational(int num, int den):
  numerator_(num), denominator_(den) {
  if (!den) throw "Divide by zero";
}

// Rational 1 arg Constructor
Rational::Rational(int num): numerator_(num), denominator(1) {}

// Rational Default Constructor
Rational::Rational(): numerator_(0), denominator_(1) {}

// ^ this is an example of function overloading
// - must differ in type or number of params
// - cant differ by only return type

// those constructors are terrible and a waste of time
// use default arguments instead

class Rational {
  public:
    Rational(int num=0, int den=1): // remember to put "explicit" if u dont want implicit type conversion
      numerator_(num), denominator_(den) {
      if (!den) throw "Divide by Zero";
    }
};

// with default values must only be last n params
Rational(int num=0, int den); // NO

// what about our other operators/functions
class Rational {
  public:
    Rational operator+(const Rational & other) {
      // wait what? when overloading an operator as a member fn: the first parameter is always itself (*this)
      // we passed our operand as a const lvalue reference
      return Rational(.....);
    }
};

// a reference is like a pointer, but NOT A POINTER AAAAAAAAA
// it is exactly what it refers to be, it refers to an actual piece of data elsewhere (an alias)
// behave like "const pointers with automatic dereferencing"
// auto dereferencing means you treat a reference exactly as you would the thing it refers (eg. X.fn() not X->fn())
// no such thing as a null reference, must be initialized when created
// since its just an alias for actual data, you can mutate the actual data itself through the reference
// so if you don't want to change the data, declare as "const ref"
// - pass by const ref for speed, but safety of not modifying data itself
class Rational {
...
};

Rational operator+(const Rational & lhs, const Rational & rhs) {
...
}

// when it was a member function, we could access the private data
// now we can't 
// so lets go back
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
//going back to a non member function:
Rational operator+(const Rational & lhs, const Rational & rhs) {
  // mutators + accessors ?
  // friend or not a friend?
  // to member or not to member?
  //  -if it doesn't need to be a member function, it isn't
