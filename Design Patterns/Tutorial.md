# Design Patterns

## OO Principles
* Encapsulate what varies
* Favor composition over inheritance
* Program to an interface, not implementation
* Strive for loosely coupled designs between between objects that interact
* Classes should be open for extension but closed for modification
* Depend on abstractions. Do not depend on concrete classes

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

Complete code available at: [Strategy.cpp](Strategy.cpp)


## Observer
Defines a one-to-many  dependency between objects so that when one object changes state, all its dependents are notified and updated automatically

## Decorator
Attach additional responsabilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending funcitonality

Let's suppose we have a Coffee Shop and we are implementing a system to prepare beverages, calculte price. The company prepares many types of coffee beverages like: HouseBlend, Dark Roast, Decaf, Expresso each one have its own price. Also you can ask for different condiments like extra milk, soy and mocha. We need to design a ordering system for our company.

Let's use the OO Principles when thinking about a design solution, ask yourself **What varies?** in this case we know that the types of beverages can vary so we can apply some OO Principles like **Encapsulate what varies** and **Program to an interface, not implementation** this means our beverage will be implemented as an interface (all pure virtual methods) with a method called cost(). Then we will have each type of beverage like Expresso implementing this interface (defining the price for each beverage).

The second problem we have is how do we design the idea of the condiments, we know that they do not depend on the beverage type, they are an extra with a specific price depending on the condiment. 
<!---
@startuml
abstract Beverage {
 + cost()
}

class Expresso {
 + cost()
}

class Decaf {
 + cost()
}

class CondimentDecorator {
  + Beverage : bv
}

Beverage  <|.. Expresso : Implements
Beverage  <|.. Decaf : Implements
Beverage  <|.. CondimentDecorator : Implements
Beverage  *-- CondimentDecorator
CondimentDecorator  <|.. Milk

@enduml
--->


![alt text](https://plantuml.atug.com/svg/VT1D3e9030NWVPEvGvV-10v0N12LXGiFKOPgY0D3ffMOg7SNnE12SDlvvlMba8fIq6lb350k6iWgRhdbG6V6km5Se_MYYwM1fm43rf48PhSci8YV5tksT9f_tlcwA2kkjNC-aFhmjXqUboUOjvy_ummtZpZ-Ra_mK3ME-npvKKE3lsIYnPnVHT44Dp0HCMGVItVfkwTS5zrvuGK0)

The decorator implementation is simple we add a new derived class from Beverage (base class) which also has a member pointing to the base class (composition)

```
class Beverage {   
public:
    virtual double cost()=0;
};

class CondimentDecorator : public Beverage{ 
public:
    std::shared_ptr<Beverage> bv;
};


class Expresso : public Beverage {
    // Inherited via Beverage
    virtual double cost() override
    {
        return 10.5;
    }
};


class Milk :  public CondimentDecorator {

public:
    Milk(std::shared_ptr<Beverage> bev) {
        bv = bev;
    }
    // Inherited via CondimentDecorator
    virtual double cost() override
    {
        return bv->cost() + 0.2;
    }
};
```


Example on how to use the classes that we just created, in this example Milk is a decorator, see that we are using it two times (adding two times the Milk condiment)
```
std::shared_ptr<Expresso> dp = std::make_shared<Expresso>();

//Add two times the Milk
std::shared_ptr<Milk> milk_decorator = std::make_shared<Milk>(dp);
std::shared_ptr<Milk> milk_decorator_second = std::make_shared<Milk>(milk_decorator);

std::cout << milk_decorator_second->cost() << std::endl;
```

Complete code available at: [Decorator.cpp](Decorator.cpp)
  
## Simple Factory (not a real design pattern/more of a programming idiom)
It is not considered a real Design Pattern, it is more of a programming idiom, but it is commonly used.

Suppose  we have a pizza store that creates different type of pizzas, I want to be able to create different types of pizzas, we can achieve that by creating an abstract class Pizza and concrete classes related to each type of pizza like PizzaMarguerita, PizzaNapolitana, PizzaCalabresa inheriting from the base class and overriding the Prepare method, defining specific behavior required to create specific types of pizzas.

<!---
@startuml
abstract Pizza {
 + Prepare()
}


class SimplePizzaFactory {
+ createPizza()
}

Pizza  <|.. PizzaMarguerita : Implements
Pizza  <|.. PizzaNapolitana : Implements
Pizza  <|.. PizzaCalabresa : Implements

SimplePizzaStore --* SimplePizzaFactory

Pizza   -- SimplePizzaFactory
@enduml
--->

![alt text](http://www.plantuml.com/plantuml/png/XSv12i9038NXVKwHfLhQ0uYBWY2uK0ezGLg356RQacGMLhsxemCYMd2RV3p-Ket4WdT0ZPfGQrXrqqHu1Som4Xv9UB64Em2qZbInxlpe-8LsaGzoYJR3LfWidHDFCxYv5KMQF92S0qjdX6lSFqSyzwQ_y4ZZu2Bh_y4jEMg4zSl1Hs9jWp3c-Mgc-zqO_tFlaljJyEu1)

Time to code our simple factory, first create a base class Pizza, then create each specific concrete implementation of pizza types (PizzaMarguerita, PizzaCalabresa and PizzaNapolitana) all inheriting from base class (Pizza) overriding Prepare() default implementation, since each pizza must be prepared in a different way.

```
class Pizza {
public:
    virtual void Prepare() { std::cout << "Standard Prepare" << std::endl; };
    virtual void Bake() { std::cout << "Standard Bake" << std::endl; };
    virtual void Cut() { std::cout << "Standard Cut" << std::endl; };
    virtual void Box() { std::cout << "Standard Box" << std::endl; };
    virtual ~Pizza() {};
};

class PizzaMarguerita : public Pizza{
public:
    virtual void Prepare() override { std::cout << "add cheese" << std::endl; };
    virtual ~PizzaMarguerita() {};
};

class PizzaCalabresa : public Pizza {
public:
    virtual void Prepare() override { std::cout << "add calabresa" << std::endl; };
    virtual ~PizzaCalabresa() {};
};

class PizzaNapolitana : public Pizza {
public:
    virtual void Prepare() override { std::cout << "add x" << std::endl; };
    virtual ~PizzaNapolitana() {};
};
```

Then implement the factory class (SimplePizzaFactory) that will have a createPizza method that will build a specific pizza type based on the specified type.

```
class SimplePizzaFactory {
public:
    enum Styles { eMarguerita, eCalabresa, eNapolitana };
    std::shared_ptr<Pizza> createPizza(Styles type)
    {
        switch (type)
        {
        case SimplePizzaStoreFactory::Styles::eCalabresa:
            return std::make_shared<PizzaCalabresa>();
            break;
        case SimplePizzaStoreFactory::Styles::eMarguerita:
            return std::make_shared<PizzaMarguerita>();
            break;
        case SimplePizzaStoreFactory::Styles::eNapolitana:
            return std::make_shared<PizzaNapolitana>();
            break;
        default:
            break;
        }
    }
};
```
Complete code available at: [Simple Factory.cpp](Simple Factory.cpp)

## Factory

## Abstract Factory
