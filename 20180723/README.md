## Iterator Invalidation
```cpp
vector<int> v;
for(size_t i = 0; i < 10; ++i) {
  v.emplace_back(i);
}
auto it = v.begin()+5; // 5
int &ref = v.at(4); // 4
int *ptr = &v.at(3); // 3
cout << *it << " " << ref << " " << *ptr << endl;
for(size_t i=0; i < 10000; ++i) v.emplace_back(i);
cout << *it << " " << ref << " " << *ptr << endl; // undefined behaviour
```

Certain container operations may invalidate iterators/pointers/references.

## STL Algorithm Library
`#include <algorithm>`


A suite of template functions, many of which work over iterators. Some of these have particular requirements of the iterators you give them.

Input Iterators | Output Iterators
--- | ---
operator++ | operator++
operator!= | operator!=
operator* (RHS or rvalue) | operator* (LHS)

There is an iterator type that is both an input *and* output iterator. It is called a **Forward Iterator**, because in the case of a single linked list, it can only go forward.


But even then, there's a **Bidirectional Iterator** that implements `operator--` to go backwards.


And finally, encompassing the bidirectional iterator, is the **Random Access Iterator**, which implements `operator+=`, `operator-=`, `operator+`, `operator-`, `operator[]`, `operator<`, etc.


**Example 1**: finding something
```cpp
template<typename InIter, typename T>
InIter find(InIter first, InIter last, const T& val) {
  //Returns an Iter to the first occurence of val
  //in [first,last), or last if val not found.
}
```
**Example 2**: copy items
```cpp
template<typename InIter, typename OutIter>
OutIter copy(InIter first, InIter last, OutIter dest) {
  // copies items from [first, last) to the location
  // starting at dest
  // the container associated with dest much have enough space!!! copy doesn't allocate space.
}
```
**Example 3**: 
```cpp
template<typename InIter, typename OutIter, typename Func>
OutIter transform(InIter first, InIter last, OutIter result, Func f) {
  while(first != last) {
    *result = f(*first);
    ++first;
    ++result;
  }
}
```
```cpp
int add1(int n) { return n+1; }
vector<int> v{2,3,5,7,11];
vector<int> w(v.size()); // 0 0 0 0 0
transform(v.begin(), v.end(), w.begin(), add1); // w= 3, 4, 6, 8, 12
