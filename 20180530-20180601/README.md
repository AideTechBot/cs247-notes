### Exceptions
```c++
class BaseExn {};
class DerivedExn : public BaseExn {};

void f() {
    DerivedExn d;
    BaseExn &b = d;
    throw b;
}

void h() {
    DerivedExn d;
    throw d;
}

int main() {
    ...
    try {
        h();
    } catch (BaseExn &h) {
        // This handler will run.
        ...
    } catch (DerivedExn &d) {
        ...
    }
    ...
    try {
        f();
    } catch (DerivedExn &d) {
        ...
    } catch (BaseExn &h) {
        // This handler will run.
        ...
    }
}
```

You should **never** throw an exception in a destructor because exceptions will unwind the stack which will call the destructors for all stack allocated objects. This can cause multiple unhandled exceptions.

### Exception Safety

```c++
void f() {
    MyClass *p = new MyClass;
    MyClass mc;
    g();
    delete P;
}
```

No leaks in the code, but what if $g$ throws? During stack unwinding, $mc$ is popped off the stack and its destructor runs, freeing any resources associated with it. $p$ is a pointer, when it is popped off the stack, no fancy destructor is called, the object it points to is leaked.

Our only guarantee is that stack allocated data will be popped off (objects will have their destructors run).

**C++ Idiom**: Resource acquisition **is** intialization. (*RAII*). Every resource should be wrapped in a stack allocated object upon acquisition, whose destructor will free it.

```c++
#include <memory>
// unique_ptr<T> destructor will delete the pointer.
// std::make_unique<T>();
void f() {
    auto p = std::make_unique<MyClass>();
    MyClass mc;
    g();
}
```

Unique pointers are **unique** so copying is disabled. Moving is allowed. We also have shared pointers for when we want to copy.

```c++
void f() {
    auto p1 = std::make_shared<MyClass>();
    ...
    if (...) {
        auto p2 = p1;
    } // p2 is popped off, but it does not free the memory.
}
```

This can be implemented by having a pointer to a counter (*reference count*). We can increment when copying and decrement when the object no longer points at the same thing. If the reference count drops to 0, the destructor frees the memory.

```c++
MyClass *p = new MyClass;
shared_ptr<MyClass> sp1(p);
if (...) {
    shared_ptr<MyClass> sp2(p);
    ...
} // sp2 goes out of scope and the destructor frees p.
sp1->myFn(); // SegFault.
```

- Error handling itself is an intrinsically non-local problem.
- Consider vector::at, the vector class can detect the error but not decide what to do about it.
- The client knows what they want to do about an error, but may not be able to detect it.
- Throw exceptions when the current context can detect the problem but the problem can't be solved locally.

```c++
void fun_fib(int n) {
    if (n == 0) throw 0;
    if (n == 1) throw 1;

    try {
        fun_fib(n - 1);
    } catch (int a) {
        try {
            fun_fib(n - 2);
        } catch (int b) {
            throw (a + b);
        }
    }
}
```

> This is **very** slow. Orders of magnitude slower than the recursive solution.

In addition to unique and shared pointers, we also have **weak_ptrs**.

- Construct a weak pointer from a shared_ptr.
- Does not act like a regular pointer as shared an unique.
- weak_ptr<T>::lock() returns a shared_ptr to the data that the original shared_ptr pointed at.
- weak_ptr<T>::expired checks whether the reference is still valid.

Weak pointers are typically used to **break cycles in shared pointers**.

There are three levels of exception safety (no safety is not included) for a function $f$.

1. **Basic Guarantee**: Should $f$ terminate due to an exception, the program will be left in a valid but unspecified state.
    - "Valid" means that no resources are leaked and that any class invariants are not broken.
2. **Strong Guarantee**: Should $f$ terminate due to an exception, the program state will be as if $f$ were never called.
3. **No-Throw Guarantee**: $f$ will never throw an exception and always complete its task.

```c++
class A {...};
class B {...};

class C {
    A a;
    B b;

public:
    void f() {
        a.method1(); // Provides strong guarantee.
        b.method2(); // Provides strong guarantee.
    }
};
```

> Does C::f provide a strong guarantee? **No** because a.method1() could succeed and make changes but b.method2() could crash (we would not undo changes).

```c++
class C {
    A a;
    B b;

public:
    void f() {
        A temp_a = a;
        B temp_b = b;
        temp_a.method1();
        temp_b.method2();
        // Copy assignments cannot throw.
        a = temp_a;
        b = temp_b;
    }
}
```

How do we create our objects so copying can't throw?

- These are temp objects so we can treat them how we like.
- A non-copying swap is core to writing exception safe code.

How can we write swaps for objects so that they do not throw?

- Swapping pointers can't throw.
- **Solution**: pImpl idiom!

```c++
class CImpl {
    A a;
    B b;
    friend class C;
};

class C {
    unique_ptr<CImpl> pImpl;
public:
    void f() {
        auto temp = make_unique<CImpl>(*pImpl);
        temp->a.method1();
        temp->b.method2();
        std::swap(pImpl, temp); // No-throw guarantee.
    }
};
```

If a function offers the no-throw guarantee, you should mark it as such with "noexcept" keyword. At the very least, move operators should be noexcept. This allow the compiler to make optimizations (e.g. vector::emplace_back).
. All elements in our set are stored in indices $\{0 \to size\_ - 1\}$ of elements_.


Thanks to Alexander Shah for this page: [Here](https://raw.githubusercontent.com/ZanderShah/notes/master/cs247.md)
