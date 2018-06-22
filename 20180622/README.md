# IMAGE 1

- Favor composition over inheritance.
- Choose object adapter unless you absolutely need class adapter
  - **Ex:** need to override some behaviour provided to you by a virtual hook into template method realRequest (think drawShell)

### Facade Pattern
**Problem:** Complex interface


Client or subsystem interacts with multiple (complex?) classes.


**Solution:**
- Create a single, simplified **Interface class**.
- Restrict & simplify the client's (or subsystem's) interactions witht he complex subsystem's classes.


