Wednesday May 16
 
Entity vs Value Objects
 
Entity Objects:
-       Computer embodiement of a real world entity
-       Each object has a distinct entity
-       Objects with same attribute values does not imply they are the same entity
-       Examples:
o       physical objects, people, records (customer info, transactions, etc)
   
  Value Objects:
  -       Simply represents a value in our ADT
  -       value objects with same attribute values are considered to be identical (equal)
   
  Consider a video blackjack game – choose which of the following should be implemented as entity of value objects.
  -       card  entity
  -       deck entity
  -       hand entity
  -       player  entity
  -       score  value
   
  Distinction between entity and value objects is important as it defines how these objects are used.
   
  Design of entity based AOTs
  An operation on an entity object should represent a real life event
  -       prohibit ctor
  -       prohibit assignment
  -       prohibit type conversions
  -       avoid equality (except of attributes)
  -       clone operation may be useful
  Compuations on entities are generally not meaningful
  -       think twice about overloading operators for your entity classes other than new and delete
  -       operator< may be useful if it operates  on name or some unique ID
  -       refer to entity object through ptr or reference (can’t be copied)
  -       may allow moves…
  o       moves are allowed since not cloning or creating new entities
  -       construction of a new object should reflect a new object in real life
  -       comparison of entity objects is not meaningful, but comparison of attributes is. Forces client to consider what values they are interested in and write code explicity as such.
  if (a1.cost() << a2.cost()) { ….
    - only conversions that make sense are up/down casts or explicit down cast (dynamic/static)
      - wise to use smartPoints (more later)
       
       
      Preventing copy ctor/CAO
      -       previous to c++11, declare private and don ‘ implement
      -       Now, from c++11 onwards, delete it
       
      class X  {
                public:
                   X(const &X)=delete;
                   X& operator=(const&x) = delete();
      }}
 
Design of value based AOTs
-       equality is important the value types
-       equality ad other comparison ops
-       copy ctcopy
-       assignment operator
-       computation involvling value types do often make sense.        
o       may want to overload some operators
-       virtual methods/inheritance is uncommon
-       equality may be nontrivial (ex matrix)
   
  Mutable vs Immutable
  - Mutable objects can cause problems when they can be reference by two variables
   
  Person person(“george eisa”, new Date(19, “June”, 1998));
  Date * myDate = person.DOB();
  myDate -> MonthIS(myDate -> month() +1);
   
   
  Entity objects are usually mutable
  -       their attributes can change via mutators and other functions that may change state
  -       referred to by pointers and references
  Value objects SHOULD be immutable
  -       objects cannot change value
  -       instead, variables of the ADT are assigned to different objects
   
  Implications on value class design
  -       No mutators
  -       All field types should be primitive or immutable types
  -       If not
  o       when passed a parameter of a mutable type, make a copy of it rather then use any reference given to you
  -       make a copy when returning your immutable field
   
  How to make an immutable ADT
  -       obviously NO mutators
  -       fields should be private
  -       make sure methods don’t get overridden or class at all
  -       declare class final , declare methods final (strong immutability)
   
  To clarify, assignment is still allowed in immutable types, its just that new objects are created in assignment
   
