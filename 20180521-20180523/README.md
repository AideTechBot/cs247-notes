# Compilation and Linking

If we need to change the size of a class because we need a new variable, all clients must recompile.

## pImpl Idiom (*Pointer to Implementation*)

- Only the pointer class needs to recompile, the rest just need to relink.

```c++
// XWindow Impl.cc
#include <xll/xlib.h>

struct XWindowImpl {
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[10];
}
```
```c++
// XWindow.h

class XWindow {
    XWindowImpl * pImpl;
public:
    // Same as before.
}
```

```c++
// XWindow.cc

XWindow::XWindow(...) : pImpl(new XWindowImpl(...)) {}

// All other members, usages of d, w, s, ... become pImpl->d ...
```

# Namespaces and Directives

- **Never** place a using statement in a header file.
- **Never** place a using statement before an include.

Defining your own namespace may be used for subdividing global namespace into named space. Within a namespace, you can refer to other members by their local names.

- Namespaces can be defined at a global scope or within another class.

**Module**: A software component that encapsulates some design decision.

## Interface

> Abstraction public description of some module.

- Supports the hiding of information.
- Reduces information overload on the client programmers.

## Benefits of Modularity

- Simplifies development.
- Supports teamwork.
- Facilitates change because it consolidates all information required for a module in one place and allows for the implementation to change as long as the interface is identical.


Credit to Alexander Shah for this page: [Here](https://raw.githubusercontent.com/ZanderShah/notes/master/cs247.md)
