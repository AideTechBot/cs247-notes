## Design Patterns Continued...

### Visitor Pattern
- For implementing **double dispatch**. Virtual methods are chosen based on the actual runtime type of the object(virtual dispatch).
- What if we want to choose a method based on two objects?

**Example:** Striking an enemy with a weapon.

# IMAGE 1 and 2

We want something like 
```
virtual void Strike(Enemy & e, Weapon & w);
```
- If we put it in Enemy `Enemy::Strike(Weapong & w)` then you choose based on enemy... but not weapon.
- If we put it in Weapon `Weapon::Strike(Enemy & e)` then you choose based on weapon... but not enemy.
- The trick to getting dispatch on both types is using both overriding & overloading.

- Because of this, it means we have some coupling between the classes inherent to the visitor pattern.
```
class Enemy {
  public:
    virtual void beStruckBy(Weapon & w) = 0;
    ...
}

class Turtle : public Enemy {
  public:
    void beStruckBy(Weapon & w) override { w.strike(*this); }
};

class Bullet : public Enemy {
  public:
    void beStruckBy(Weapon & w) override { w.strike(*this); }
};

class Weapon {
  public:
    virtual void strike(Turtle & t) = 0;
    virtual void strike(Bullet & b) = 0;
};

class Stick : public Weapon {
  public:
    void Strike(Turtle & t) {//codeforwhatever}
    void Strike(Bullet & b) {//asdf}
};

// ROCK IS THE SAME AS STICK
```
```
Enemy *e = EnemyFactory(); //create a turtle
Weapon *w = WeaponFactory(); //creates a stick
e->beStruckBy(*w);
```
`e->beStruckBy(*this);`
- Turtle be struck by gets called (virtual dispatch)
- that calls `Weapon::Strike(Turtle &)` (overload)
- which is actually calling `Stick::Strike(Turtle &)` (virtual dispatch)

Visitor can be used to add functionality to existing classes, without having to change them or recompile them.

```
class MyClass {
  ...
  virtual void accept(MyClassVisitor & v) { v.visit(*this) }
};
class MyClassVisitor {
  virutal void visit(MyClass A &) = 0;
  virtual void knightling
  ...
```
``` Class
class Boom { Enemy
  public:
  ...
  virtal void accept(BookVisitor & v) { v.visit(*this))


class MyClass {
  ...
  virtual void accept(MyClassVisitor & v) { v.visit(*this) }
};
class MyClassVisitor {
  virutal void visit(MyClass A &) = 0;
  virtual void knightling
  ...
```
``` Class
class Boom { Enemy
  public:
    virtual void accept(BoomVisiter &) { v.visit(*ths))
};
d
class ComicBook : public Boom () {
  public:
    virutal void accept(BookVisitor & v) { v.visit(*this) }
};

`````
Application track how many of each type of Book if it e'i
have, Grump by Author for rrewar, Suject for text books, & heros from cm
- WE use a mapstring<string, int>, we could add a method void updateMap(Map<string>,int> & s)

```
class Catalogue : BookVisior {
    map<string, int> catalogue_;
  public:
    map<string, int> catalogue() { return catalogue_; }
    void visit(Book & b) { ++catalogue_[b.getAuthor()] }
# INCOMPLETE

### Composite Pattern
- When working with tree structures code must be written such that it spe

