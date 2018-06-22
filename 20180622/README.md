# June 22 2018

![asdf](https://drive.google.com/open?id=1X6Gbs8XnJfmPFZwkbD-qiZrDxiPX3MrL)

- Favor composition over inheritance.
- Choose object adapter unless you absolutely need class adapter
  - **Ex:** need to override some behaviour provided to you by a virtual hook into template method realRequest (think drawShell)

## Facade Pattern
**Problem:** Complex interface


Client or subsystem interacts with multiple (complex?) classes.


**Solution:**
- Create a single, simplified **Interface class**.
- Restrict & simplify the client's (or subsystem's) interactions witht he complex subsystem's classes.

# IMAGE 2

- When the subsystem interface changes, only need to update the Facade.
- Supports teamwork, not everyone needs to understand the complex subsystem.
- Reduce code complexity.
- Decoupling subsystems from the client code.

Important to note: original subsystem is still there, it is still available for the client code to use. That's the major difference between Facade and Adaptor.

## Strategy Pattern
**Problem:** Want to vary an algorithm (strategy) at runtime.


**Solution:**
- Encapsulate the algorithm decision.
- Define algorithm as a component objet of our class that uses.
- Have ABC for algorithm.
- Use inheritance to specialize.

# IMAGE 3

Quite similar to the Factory Pattern. The difference is that this is not strictly about creating objects, and you can swap strats at runtime.

- Goal is to allow objects to switch strategy at runtime.
- Can be done by simply swapping strat pointers.

**Example:** Card player changes strategies based on the context of game.

# IMAGE 4

# CODE 1 (uploaded by prof)
