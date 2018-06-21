### Methods Need To Preserve Invariants

1. Verify that the constructor establishes invariants.
2. For each method, assume it holds true, prove / verify method does not violate invariant at end.
3. If encapsulation is not broken, representation invariants hold true.

### Representation Example

- If we give access to the representation to the client, they can violate our invariants.

```c++
class Node {
    int data_;
    Node *next_ = nullptr;

public:
    Node(int d, Node *next = nullptr) : data_(d), next_(next) {}
    ~Node() {
        delete next_;
    }

    Node *next() {
        return next_;
    }
};

int main() {
    Node my_list = Node(1, new Node(2, new Node(3)));
    Node my_list_2 = Node(0, &my_list);
}
```

We need $R$.

- next_ is either the nullptr or a valid pointer to a heap allocated Node.
- $\forall o, p \in Nodes, o \neq p \land o.next\_ \Rightarrow o.next\_ \neq p.next\_$.

# Iterator Pattern

> We want to be able to iterate over our collection efficiently without exposing the representation.

```c++
class List {
    struct Node;

    Node *list;

    Iterator begin() {
        return Iterator(list);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

public:
    class Iterator {
        friend class List;

        explicit Iterator(Node *p) : p(p) {}

        Node *p;

    public:
        Iterator &operator++() {
            p = p->next();
            return *this;
        }

        bool operator!=(const Iterator &other) {
            return p != other.p;
        }

        bool operator==(const Iterator &other) {
            return p == other.p;
        }

        int &operator*() {
            return p->data;
        }
    }
};
```

# Documenting Representation Invariants

- They do nothing if nobody knows about them.
- Write them as comments in top of your class.

## Determining Representation Invariants

1. Look for invalid values for your representation.
2. Think about what assumptions you make or want to make while writing your code.

## Checking Representation Invariants

- It can be useful for **debugging** purposes to programmatically check our invariants.
- Write a method **check_rep** that asserts all of our invariants hold.
    1. End of constructors.
    2. Before any const methods.
    3. Before and after non-const methods.
    - Generally this should only be used for **debugging** (finding your errors), so remove from production code (preprocessor, build script, etc.).

- **Never** ship code different from what you tested.
- Asserts can be used for check_rep.
    - **Benefits**: Exits the program directly from that location, so it keeps the stack frame / call stack intact.
    - **Negatives**: Exits the program directly from that location, so it does not free up resources and call destructors. The severity of this depends on what resources you are holding.

```c++
class MyClass {
    bool check_rep();

public:
    ...
    void foo() {
        #ifdef MYDEBUG_
        check_rep();
        #endif
    }
};
```

> g++-5 -std=c++14 -DMYDEBUG_ -c MyClass.cc

## Abstraction Function

The abstraction function is not guaranteed to be injective, but it is guaranteed to be surjective. Therefore, it may not have an inverse function.

Example: **Rational r**

> $AF(r) = \frac{r.numerator\_}{r.denominator\_}$     
> $AF(r) = \{elements\_[i] | 0 \le i \le r.size\_\}$    

There is no concrete language for talking about our abstract values.

- It can be defined with maths , if not then we might to define by example.

Example: A set $S$ over the integers in range $0, ..., 255$.

> Bit vector stored in a char $c$, integer $i$ is in set if and only iff c & (1 << i). $AF(r) = \{\forall i \in [0, 255] | c \& (1 << i) \}$

# Models (*UML*)

> An abstraction of something.

- Help to understand something before you build.
- Communicate to others.
- Answer questions about the thing being modelled.
- We are going to mainly focus on UML class diagrams.
- UML consists of ~13 different modelling notations.

## Legend

- +, public
- -, private
- #, protected
- underline, static
- *italics*, pure virtual

> **Note**: We do not use **"in"**. We also do not want to be too specific with types because UML are designed to be language agnostic.

## Associations

An association represents a relationship between two classes, share a physical or conceptual link.

- **Non-transient link**, not just one parameter of a classes member function.
- One class contains another.
- We can name our associations (*optional*).
- We can name the roles of associations.
- Arrows denote who refers to whom.
- Self-association can exist.
- **Multiplicity**, place them on the side of the relationship that they refer to. It can be just a number (0), a variable (p), a range (0..1), or an asterisk (*) to represent **many**.

> Consider marks a student has in a course. To which class should we attribtue marks? Marks should be associated with a pair of (student, course).

- We can create association classes that allow for a unique value for each link. The name of the class is the name of the association.
- Instances of the association class exists only when a link exists between the associated classes.
- Association classes can be used as other classes in your diagram and have associations themselves.

## Relationships

### Composition Relationship

> A specialization of association, where one class **owns** an object(s) of another class.

If A *owns* B, then typically ...

- B has no identity outside of A (no independent existence).
- If A is destroyed / copied, B is destroyed / copied.
- In code, usually represented by one class having an object field of another, or by an **owning** pointer.

Modelled in UML as a solid diamond on the owner connected to the owned.

### Aggregation Relationship

> A specialization of association, where one class **has** objects(s) of a class.

If A *has* B then ...

- B has an identity outside of its association with A.
- If A is destroyed, B is not necessarily destroyed. 
- If A is copied, B is not copied (**shallow copy**).
- In code, usually represented by **non-owning** pointers.

Modelled in UML as a hollow diamond on the owner connected to the owned.

### Generalization / Specialization Relationship

> One class **is** another class.

- Public inheritance.

Modelled in UML as a hollow triangle pointing to the base class.

![](https://i.imgur.com/Zm2Kwcj.jpg?1)

## UML Object Model

- An object model models a runtime instance of class model.
    - Every object in our object model is an instantiation of our particular class.
    - Every link is an instantiation of a specific association.

![](https://i.imgur.com/ypbv44Q.jpg?1)

## UML Sequence Diagram

- Graphical model of communication events between objets as exhibited in one execution.
- Boxes are the execution patterns.

![](https://i.imgur.com/q2TAAbt.jpg?1)

# Design Patterns

- If you have a problem $p$ which is a common problem or simliar to a common problem, then **maybe** design pattern $D$ is a good solution.

## Observer Pattern

> We want to abstract away change.

- Publish and subscribe model.
- You need to maintain / propogate updates from a source to those it affects.
- We have one class called the **publisher** or the **subject** which generates the data.
- One or more classes are our **subscribers** or **observers**. They receive updates and react to it.

Example: Publisher is spreadsheet cells and observers are our generated graphs.

- There can be many different kinds of observers, and the subject should not need to know details about them.

![](https://i.imgur.com/Mr3Seyk.jpg?1)

- The abstract class subject contains all the code common to all subjects, the abstract class observer defines an interface common to all observers for subject to use.

1. Subject's state is updated.
2. Subject::notifyObservers is called, it calls notify() on all its observers.
3. Each observer does their update, which likely involves calling concreteSubject::getState to query the state and react accordingly.

Example: Horse Races. The subject publishes the winning horse, the observers are individual betters who will declare victory if their horse wins.

```c++
class Subject {
    vector<Observer *> observers_;

public:
    void attach(Observer *ob) {
        observers_.emplace_back(ob);
    }
    void detach(Observer *ob);
    void notifyObservers() {
        for (auto &p : observers_) {
            p->notify();
        }
    }
    virtual ~Subject() = 0;
    Subject::Subject() {}
};

class Observer {
public:
    virtual void notify() = 0;
    virtual ~Observer();
};

class Horserace : public Subject {
    ifstream in_;
    string last_winner_;

public:
    Horserace(string source) : in{source} {}
    ~Horserace() {}
    bool runRace() {
        return in_ >> last_winner_;
    }
    string getState() const {
        return last_winner_;
    }
};

class Bettor : public Observer {
    Horserace *subject_;
    string name_, horse_;

public:
    Bettor(...) {
        subject_->attach(this);
    }
    void notify() {
        string winner = subject_->getState();
        cout << (winner == horse_ ? "Win!" : "Lose.") << endl;
    }
};
```

- If you only have one ConcreteSubject, you may consider merging Subject and ConcreteSubject. Don't do so lightly however, if you need to add another subject in the future you will have to refactor.
- If the state is trivial (i.e. getting notified is all the information you need), you may not need getState method.
- If the subject and the observer are the same (e.g. cells in a grid), you could merge these classes.


Thanks to Alexander Shah for this page: [Here](https://raw.githubusercontent.com/ZanderShah/notes/master/cs247.md)
