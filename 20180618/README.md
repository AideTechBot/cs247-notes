## Decorator Pattern

Suppose you want to enhance an object (e.g. adding functionality or features).

**Example**: Windowing System. We start with a basic window, and then add a toolbar, scrollbar, and a menu. We want the user to be able to choose these at runtime.

![](https://i.imgur.com/0tFP1IZ.jpg?1)

- Every decorator is a component and every decorator has a component.
- For example a window with a scrollbar is a window, but it also has a pointer to the underlying plain window.
- A window with a menu + a scrollbar is a window, but it also has a ptr to the window with a scroll bar, which also has a ptr to the base window.
- Example: pizza
```
* pizza (pointer to decorator?)
|
+-- crust and sauce 
|
+-- * decorator
    +-- stuffed crust
    +-- topping
    +-- sauce
```
```cpp
class Pizza {
  public:
    virtual float price() const = 0;
    virtual string desc() const = 0;
    virtual ~Pizza();
};

class crustAndSauce : public Pizza {
  public:
    float price() const override { return 5.99; }
    string desc() const override { return "Pizza"; }
};

class Decorator : public Pizza {
  protected:
    pizza * component;
  public:
    Decorator(Pizza * p): component{p} {}
    virtual ~Decorator() { delete component; }
};

class StuffedCrust : public Decorator {
  public:
    StuffedCurst(Pizza * p): Decorator{p} {}
    float price() const override {
      return component->price() + 2.69;
    }
    string desc() const override {
      return component->desc() + " with stuffed crust";
    }
};

class Topping : public Decorator {
    string name_;
  public:
    Topping(string topping, Pizza * p): Decorator{p}, name_(name) {}
    float price() const override {
      return component->price() + 0.75;
    }
    string desc() const override {
      return component->desc() + " with " + name_;
    }
};
```
### Usage:
```cpp
Pizza * p1 = new crustAndSauce();
p1 = new Topping("cheese", p1);
p1 = new Topping("pineapple", p1);
cout << p1->desc() << endl;
```
# Factory Method Pattern
Problem: write a video game with two kinds of enemies. Turtles & Bullets. The system randomly sends turtles and bullets, bulletsbecome more frequent in later levels.

UML:
```
*enemy
|
+-- turtle
|
+-- bullet
```
```
*level
|
+-- normallevel
|
+-- castle
```
* Since we never know exactly which enemy is going to come next, we (the client) cant call the turtle/bullet ctors directly. Moreover we dont want to hard code the policy that decides what comes next. That should be customizable.
* So instead we put a factory method in Level that creates enemies
```cpp
class Level {
  public:
      virtual Enemy * createEnemy() = 0;
      //factory method
      //...
};

class NormalLevel : public Level {
  public:
    Enemy * createEnemy override {
      // create enemy, mostly turtle  
    }
};

class Castle : public Level {
  public:
    Enemy * createEnemy() override {
      //create enemies mostly bullet
    }
};
```
* This pattern could also be called the "virtual ctor pattern"
### Template Method Pattern
The template method pattern is use when we want subclasses to override some aspects of a superclasses methods behavior but other aspects stay the same.

Example: there are red shelled turtles and green shelled turtles.
```
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
```
