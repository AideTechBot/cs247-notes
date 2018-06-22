# June 22 2018

# IMAGE 1

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


