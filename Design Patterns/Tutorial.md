# Design Patterns

## OO Principles
* Encapsulate what varies
* Favor composition over inheritance
* Program to an interface, not implementation
* Strive for loosely coupled designs between between objects that interact
* Classes should be open for extension but closed for modification

## Strategy
Defined a family of algorithms, encapsulate each one, and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.
Supose we have a car manufactorer company that builds vehicles in different manners manually or in a fully automated way, as a user I want to be able to dynamically change the assembly method of a specific car **(Dynamic change of behavior)**

Let's use the OO Principles when thinking about a design solution, ask yourself **What varies?** in this case we know that the **ways of assembling vehicles varies** in this case this is one of the ideas that needs to be encapsulated. To do that we can also use another OO Principle **Program to an interface, not implementation** . This means let's define our Assembly methodology as an interface in a way that our **Vehicle does not have knowledge about how it will be assembled** doing that we decoupled the Vehicle from the assembly method. 

Look at the UML below, it shows what we have just described using a pattern called Strategy, you can create an instance of a Car and dynamically define an assembly strategy to it.




![alt text](https://plantuml.atug.com/svg/TOxB2i8m44NtWVp3B7sGVe28K1MX2rUAMqdZr0QJA7aiIjj_jm7hmfhTp9npXqkAt3dKfMfEtdAFzmRMNPR18IZLvC4_zN2yZGwieD0lXHgDTvGaiaTk0bU9p8vROApRm0LhAHH6R6gqCiAp3UAHnjlWqd1QPi7OQ58YZKTRSO4m5TkU4bwwOHN--xkb183ziQ_kCqLX2NkifC5VQpQdf2Tl)

<!---
IAssemblyStrategy <|.. FullyAutomatedAssembly : Implements
IAssemblyStrategy <|.. ManualAssembly : Implements
Car <|-- Vehicle : Inherits
Truck <|-- Vehicle : Inherits
Bus <|-- Vehicle : Inherits
IAssemblyStrategy *-- Vehicle
interface IAssemblyStrategy {}
abstract Vehicle {
  - IAssemblyStrategy _strategy
  + DefineAssemblyStrategy()
}
--->




## Observer
Defines a one-to-many  dependency between objects so that when one object changes state, all its dependents are notified and updated automatically

## Decorator
Attach additional responsabilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending funcitonality

## Simple Factory (not a real design pattern/more of a programming idiom)


## Factory