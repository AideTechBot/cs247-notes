### Template Method Pattern
* Allow derived classes to modify some behaviour of the superclass, but keep other aspects the same.
**Example**: drawing red & green turtles
```cpp
class Turtle {
  public:
    void draw() {
      drawHead();
      drawShell();
      drawFeet();
    }
  private:
    void drawHead() {...}
    void drawFeet() {...}
    virtual void drawShell() = 0;
};

class RedTurtle : public Turtle {
  void drawShell() override {
    // draw a red shell
  }
};

class GreenTurtle : public Turtle {
  void drawShell() override {
    // draw a green shell
  }
};
```
* Sublcasses can't change the way a turtle is drawn, nor can they change how feet or head are drawn, but they can change how the shell is drawn.
---
**Extension**: Non-virtual interface (NVI) Idiom
* A public virtual methid is really 2 things:
  * An interface to the client
    * Indicates provided behaviour and pre/post conditions; as well as promise representation invariants
  * An interface (hook) for subclasses.
    * A book for subclasses to insert specialized behaviour.
* Hard to seperate these 2 ideas if they're wrapped up in one function declaration
* What if you later want to seperate the customizable behaviour into two methods, with some non-customiable in between?
* How to make sure all derived classes conform to the pre/post condns that the parent class promises?


The **NVI** idiom says:
1. All public methods should be non-virtual
2. All virtual methods should be private or at the very least protected.
3. Except, obviously, the destructor.


**Example**: Digital Media
```cpp
class DigitalMedia {
  public:
    virtual void play() = 0;
    virtual ~DigitalMedia();
};


##### Translated to NVI:
```cpp
class DigitalMedia {
    virtual void doPlay() = 0;
  public:
    virtual ~DigitalMedia();
    void play() { 
      checkLicense();
      doPlay();
    }
};
```
* *Now* if we want to exert extra control over play, we just  put the behaviour we want in the superclass play() method.
* We can add more "nouns" simply by calling more virtual methods.
* It's much easier to keep control of our interface from the beginning then having to refactor after the fact.
* The NVI idiom extends template method by wrapping every virtual method in a non-virtual wrapper.
### Adapter Pattern
**Problem**: interface mismatch between two modules
* Want to reuse an existing subsystem (class or library) but it's interface doesn't match our needs.
* Or the interface of our modules changes and we don't want to make major changes to the existing working code(!!)
* An adapter class maps one interface (adapter) to another (target)
* Square peg/Round hole? Throw an adapter between them.
**Note**: the adapter can adapt more than one class, the main idea is it entirely encapsulates the interface.


**Example**: STL stacks, they are implemented as an adapter of a container class. (Usually a deque)


* Two forms to adapter pattern
  * Object adapter
    * Done through composition, the adapter owns an objet of adaptee type
    * Adaptee.realRequest() || adaptee->realRequest()
    * Generally, preferred and better and cleaner
  * Class adapter
    * Does the same thing, but does it through an inheritance
    * Adaptee::realRequest()
    * The only reason you want to use the class adapter if you want to slightly ajust the behaviour. (overriding hooks to change behavior)
