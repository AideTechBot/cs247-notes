### How strict should a specification be?
> Exactly as strict as it needs to be

Specificand set is an element of set of accepted solutions

#### Comparing specifications
- **Strong**: tolerant on inputs, more demanding on outputs
- **Weak**: more demanding on inputs, more tolerant on outputs

Spec A is stronger than spec B (A >= B) iff:
1. A's preconditions are equal to or stronger than B's
> Requires A => Requires B
2. A's post conditions are stronger or equal to B's post conditions (promise more)
> Requires B => (Ensures A and Returns A) => (Ensures B and Returns B)
3. A modifies the same or more objects.
4. Throws same or fewer exceptions.

#### Preconditions:
- The client is responsible for holding preconditions before calling your code.
- Best practice: if precondition is easy to check, do so - throw exception if violated
- Example:
  - Find: finds item in list
    - requires list is sorted 
    - requires list is non-empty
  - Check if empty, throw exception if it is
  - Don't check if sorted

#### Vector example
- v[i] - returns ith element of vector, does not check if it's within bounds
- v.at(i) - is a checked version of v[i}

- vector<t> at raises the std::out_of_range exception when it fails
- how to handle?
```cpp
#include <stdexcept>
try {
  cout << v.at(i) << endl;
}
catch (out_of_range) {
  cerr << "Range Error" << endl;
}
```
Now consider:
```cpp
void f() {
  throw out_of_range("f"); // raises exception
}
void g() { f(); }
void h() { g(); }
int main() {
  try {
      h();
  }
  catch(out_of_range) {
    ...
  }
}
```
1. Main calls h calls g calls f
2. stack unwinds with exception until a matching try catch or termination
3. stack frames for functions are popped when they throw/propogate an exception
4. out_of_range is a class
  - out_of_range("f") is a ctor
  - string is auxillary info may want to examine

```cpp
try {
  ...
}
catch(out_of_range ex) {
  cout << ex.what() << endl;
}

try {...}
catch (someErrorType s) {
  ...
  throw someOtherError(...);
}

try {...}
catch (someErrorType s){
  ...
  throw;
}
```
- The exception s might actually belong to a subclass of someErrorType,  rather than someErrorType itself.
- The statement throw s; throws a new exception of type someErrorType.


Lastly a handler can be a catch-all:
```cpp
try {...}
catch(...) { // literally ... 
}
```
You can throw anything!!!!1


...but generally define your own meaningful exception classes or use a meaningful std exception


You can catch by reference, this avoids slicing the object, but static type thrown is what determines what gets caught.
