# Design Patterns

## OO Principles
* Encapsulate what varies
* Favor composition over inheritance
* Program to an interface, not implementation
* Strive for loosely coupled designs between between objects that interact
* Classes should be open for extension but closed for modification

## Strategy
**Formal Definition: Defined a family of algorithms, encapsulate each one, and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.**

Supose we have a car manufactorer company that builds vehicles (cars, trucks, bus) in different manners manually or in a fully automated way, as a user I want to be able to dynamically change the assembly method of a specific car **(Dynamic change of behavior)**

Let's use the OO Principles when thinking about a design solution, ask yourself **What varies?** in this case we know that the **ways of assembling vehicles varies** in this case this is one of the ideas that needs to be encapsulated. To do that we can also use another OO Principle **Program to an interface, not implementation** . This means let's define our Assembly methodology as an interface in a way that our **Vehicle does not have knowledge about how it will be assembled** doing that we decoupled the Vehicle from the assembly method. 

Look at the UML below, it shows what we have just described using a pattern called Strategy, you can create an instance of a Car and dynamically define an assembly strategy to it.




![alt text](https://plantuml.atug.com/svg/TOxB2i8m44NtWVp3B7tGVe2ugOhGXIl5hQJfr0QJLF8GIks_snQhOCrkkEVScI5fOYsgJDP7PvZ3QmthPnp3tajP9zvLgWlpqO4LfEekKQ5sbf90zy2qPpBGsJBJML44Pom5bzXZNQ8HFJmPpszXlF4s3AVFBBuc9K8xD0NZ25EneGIWOPdj0kvQU5GYXz6QpIbfAHdfv_PGYlvikzZtr0jBs64XDFvQmrRo0W00)

<!---
IAssemblyStrategy <|.. FullyAutomatedAssembly : Implements
IAssemblyStrategy <|.. ManualAssembly : Implements
Car <|-- Vehicle : Inherits
Truck <|-- Vehicle : Inherits
Bus <|-- Vehicle : Inherits
IAssemblyStrategy *-- Vehicle
interface IAssemblyStrategy {
  {abstract} void Assembly()
}
abstract Vehicle {
  - IAssemblyStrategy _strategy
  + DefineAssemblyStrategy()
}
--->

Time to code this solution, first we create an interface (IAssemblyStrategy) and two classes that will implement this interface FullyAutomatedAssembly and ManualAssembly with a concrete implementation of the individual assembly method

```
class IAssemblyStrategy {
public:
    virtual void Assembly() = 0;
    virtual ~IAssemblyStrategy() {}
    IAssemblyStrategy() {}
};

class FullyAutomatedAssembly : public IAssemblyStrategy {
public:
    virtual void Assembly() {
        std::cout << "FullyAutomatedAssembly";
    }
    ~FullyAutomatedAssembly() {}
    FullyAutomatedAssembly() {}
};


class ManualAssembly : public IAssemblyStrategy {
public:
    void Assembly() {
        std::cout << "ManualAssembly";
    }
    ~ManualAssembly() {}
    ManualAssembly() {}
};

```

Now we create the Vehicle and each different type of vehicle that will be inheriting from this base class

```
class Vehicle {
public:
    std::shared_ptr<IAssemblyStrategy> assemblyStrategy;
    void DefineAssemblyStrategy(std::shared_ptr<IAssemblyStrategy> strategy) {
        assemblyStrategy = strategy;
    }

    void Assembly() {
        assemblyStrategy->Assembly();
    }
    Vehicle() {
        assemblyStrategy = nullptr;
    }
    virtual ~Vehicle() {
    };
};

class Car : public Vehicle {
public:
    Car(std::shared_ptr<IAssemblyStrategy> strategy) {
        this->DefineAssemblyStrategy(strategy);
    }
};

class Truck : public Vehicle {
public:
    Truck(std::shared_ptr<IAssemblyStrategy> strategy) {
        this->DefineAssemblyStrategy(strategy);
    }
};

class Bus : public Vehicle {
public:
    Bus(std::shared_ptr<IAssemblyStrategy> strategy) {
        this->DefineAssemblyStrategy(strategy);
    }
};
```

Let's instanciate a car defining an assembly method during runtime

```
Car c(std::make_shared<FullyAutomatedAssembly>());
c.Assembly();
```

We can also change it after instantiation since we made our DefineAssemblyStrategy public

```
Car c(std::make_shared<FullyAutomatedAssembly>());
c.DefineAssemblyStrategy(std::make_shared <ManualAssembly>()); //Change
c.Assembly();
```




## Observer
Defines a one-to-many  dependency between objects so that when one object changes state, all its dependents are notified and updated automatically

## Decorator
Attach additional responsabilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending funcitonality

## Simple Factory (not a real design pattern/more of a programming idiom)


## Factory
