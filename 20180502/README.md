# SECTION 1
```cpp
#include <iostream>
using namespace std;
int main() {
  Rational r, s; // default ctor -other ctors?
  cout << "Enter a rational number (a/b);";
  cin >> r;
  cout << "Enter a rational number (a/b);";
  cin >> s;
  Rational t{r + s}; // or Rational t(r + s); // copy ctor
  cout << r << " + " << s << " = " << r + s << endl;
  cout << r << " * " << s << " = " << r * s << endl;
  cout << r << " = " << s << " is " << (r == s) << endl; // output, +, *, ==
}
```
