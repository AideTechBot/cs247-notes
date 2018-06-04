// does an ADT have to be a class?
// Not really:
struct s {
  int x;
  int f(){return x+1;}
};
// could also be written in c as
struct s {
  int x;
};
int s_f(struct s* this){return this->x+1;}

// what do classes give you?
// -guaranteed initializtion and cleanup (ctor, dtor)
// -access control
// so we will write a class
class Rational {
  public:
    Rational(); //default ctor (no args 0/1)
    Rational(int num, int denom); // num/denom
    Rational(int num); // num/1 (if you put explicit here, the compiler type checks)

    /*
     * Rational r{2}; 2/1
     * Rational s=2; 2/1  ---implicit conversion (illegal if flagged explicit)
     * void f(Rational)   |
     * f(Rational {2})    -
     */

  private:
    int numerator_;
    int denominator_;
};

Rational r; //invokes default ctor
// advice: always make sure your ctors create a legal value
// Potentially illegal/uninitialized objects lead to errors and complicated code

// trash code:
Rational::Rational(){
  numerator_ = 0;
  denominator_ = 1;
}

// better code:
// MIL: member initialization list
Rational::Rational: numerator_ {0}, denominator_ {1} {}

Rational::Rational(int num, int denom):
  numerator_ {num}, denominator_ {denom} {}

Rational::Rational(int num): Rational{num,1} {} // ctor delegation

/* WHY MIL
 * readability because field init is easy to locate
 * improve quality by preventing frogetting init
 * ctor delegation
 * 
 * OBJECT CONSTRUCTION SEQUENCE
 * when an obj is created, 4 things happen
 * 1. space is allocated (stack, heap, whatever)
 * 2. ctor for the superclass part (if any) runs (inheritance)
 * 3. constructors for fields (if they are objects) run
 * 4. constructor body runs
 */

// BEGIN ASIDE:
class Posn {
  int x,y;
  Posn(){} //default ctor
};
Posn p;
// default ctor runs
// are x,y initialized?
// NO, they will contain garbage if you dont take steps to initialize
// it would be the same if you didnt write the default ctor
// because every class comes with a default ctor that looks like that 
// unless you write any ctor

class Person {
  string name;
  Person (){}
};
Person p;
// is name initialized?
// YES, because name is a string and string is a class, therefor it has a ctor (step 3)
// it is initialized to ""

// END ASIDE

// THE MIL puts feild init in step 3
// ctor body puts feild init in step 4
class Person {
    string name_;
  public:
    Person(string name) {
      name_ = name;
    }
};
// name_ is set to "" in step 3
// then name_ is reassigned in step 4
// but if you use the MIL:
class Person {
    string name_;
  public:
    Person (string name): name_ {name} {}
};
// now name_ is initialized in step 3 and nothing happens in step 4

// Should every class have a default ctor?
// NO!
// only give a class a default ctor if theres a reasonable default value

// what about Person? what default name would you give them?
// if you put a default ctor, you allow the client to create an illegal person
// that creates invalid objects
// better: no default ctor for Person
Person p; // invalid and wont compile
Person p{"Brad"}; // OK
Person p{""}; // uh oh
// if its a class invariant that name_ is not empty 
// don't let this invalid obj be created!
Person::Person(string name): name_ {name} {
  if(name == "") throw "Bad Name";
}
