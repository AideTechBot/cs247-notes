## Recap:
### Strategy Pattern:
**Problem:** want to vary algorithm at runtime.


**Solution:** encapsulate the algorithm decision in an object hierarchy, specialize with overrides.

![diagram1](../20180622/diagram_3.jpg?raw=true)

- class hierarchy as shown
- class hierarchy of function objects 
- Non-OOP solution using function pointers

## Measures of Design Quality
### Coupling and Cohesion
**Coupling:** the degree to which distinct modules interact/depend on eachother.
- (*low*) Modules communicate via function calls with basic parameters/results
- Modules pass arrays/structs back and forth.
- Modules affect each other's control flow.
- Modules share global data.
- (*high*) Modules share/have access to each other's implementation (AKA they are friends)

### High Coupling
High coupling is bad because:
- Changes to one module require greater changes to another.
- Harder to reuse individual modules.

### Cohesion
**Cohesion:** How closely elements of a module are related to eachother.
- (*low*) arbitrary grouping of unrelated element. eg: `<utility>`
- Elements that share a common theme, otherwise unrelated. eg: `<algorithm>`
- Elements that manipulate the state over the lifetime of an entity. eg: opens/reads from/writes to/closes files
- (*high*) Elements cooperate to perform exactly one task.

### Low Cohesion
- Poorly organized code.
- More to understand/maintain.


### Goal:
Low coupling, High cohesion

## Decoupling the interface(MVC)
Your primary program should not be directly printing things.


Bad Example:
```cpp
class ChessBoard {
  //...
  ... cout << "your move" << ...
};
```
- This is bad design, inhibits code reuse.
- What if you want to reuse the chess board class, but not have it communicate via std out.
```cpp
class ChessBoard {
    istream &in;
    ostream &out;
  public:
    ChessBoard(istream &, ostream&);
    ... out << "your move";
};
```
This is better, but what if we want a graphical interface?


Your chess board should not be communicating at all.
### Single Responsibility Principle
- A class should have only one reason to change.


Game state and communication are two things, so we are not respecting this.

### Model - View - Controller (MVC)
- Seperate the distinct notions of data(state), the presentation of the data, and the control of the data(or system).

