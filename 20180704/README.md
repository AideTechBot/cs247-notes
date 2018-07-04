## Refactoring
- Changing your existing code to clean it up.
- In theory, not changing behaviour, just design.
- Tests should be reusable.
- In practice that rarely happens, usually happens along side bug fixes, feature patches, etc.

"*Refactoring Improving the design of existing code*" - Martin Fowler

### Why refactor?
- Even if you wrote perfectly clean code first time around(you didn't) better solutions may become apparent.
- That doesn't happen, in reality "quick and dirty" solution are used all the time to meet deadlines.
- After a while these Q&D solutions add up and build what is called "Technical Debt"
- Incur debt by using Q&D, repay it with refactoring.

### When to refactor?
- When you recognize a "bad smell"?
- When you add a function:
  - Likely not an island unto itself, may need to refactor interacting components
- When you fix a big:
  - May have been caused by bad design
- When you code review.

### When not to refactor?
- When a deadline is approaching.
- Invasive changes that will break other engineers mental model of the code
- When prohibitively expensive or time consuming.
- Generally, earlier = less expensive to refactor.

### What to refactor?
- Bad smells (indication of bad design)
  - There are *many* (look at the big list in the slides on the cs247 website)
- Here's a few:

#### Duplicated code:
- Same expressions in two (or more) methods in the same class.
- Same expressions in two (or more) "sibling" sub classes.
- Similar expressions in two "sibling" subclasses.
- Methods do same thing with different algorithms.

#### Long Method
- Best to think carefully about major tasks & how they inter-relate.
  - Often a sign of trying to do too much.
  - Often indicative of poorly thought out abstractions and boundaries.
- *Fowler's Heuristic*: when you see a comment, make a method.

#### Large Class
- Too many member variables, may be trying to do too many things.
- Too much, try to eliminate redundancy.
  - Gather codependant pieces separate into aggregate subparts, compose yourself of those.
- Delegate relevant methods to those aggregate types.

#### Long Param List
- Trying to do too much?
  - Too far from home.
  - With too many disprate subparts.

#### Divergent Changes
- One classs comonly changed in different ways for different reasons
  - Trying to do too much
  - Containing too many unrelated subparts
- Classic sign of poor cohesion and poor boundaries

#### Shotgun Surgery
- Opposite of divergant change
- Often when making a seemingly coherent change you must make many little changes to many classes
- Poor cohesion, maybe high coupling.

#### Primitive Obsession
- Many member variables, all primitive types. (int, bool, etc.)
  - Probably have constraints and invariants that apply to these (May be related)
  - Perhaps should be pulled out and wrapped up in a value ADT? (Or some other type)

#### Feature Envy
- Method `A::m()` uses other classes methods, features and data, much more than it's own.
  - Consider moving `m()` to class B
  - Some patterns are deliberate exceptions: Strategy, Iterator, Visitor (later)

#### Lazy Class
- A class that doesn't do much different from other classes (maybe sibling subclasses)
  - Could be vestigial and should be deprecated then removed
  - Could be a relic from ambitious design hopes
  - Could have been gutted from previous refactoring.

---

A note on automated testing
- For every new feature you add you should a test case.
- Should also retest all your old tests.
  - List of automated tests, which one fails and maybe auxillary info.
