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
