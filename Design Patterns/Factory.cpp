#include <iostream>
#include <memory>
#include <vector>


//Factory
class Pizza {
public:
    virtual void Prepare() { std::cout << "Standard Prepare" << std::endl; };
    virtual void Bake() { std::cout << "Standard Bake" << std::endl; };
    virtual void Cut() { std::cout << "Standard Cut" << std::endl; };
    virtual void Box() { std::cout << "Standard Box" << std::endl; };
    virtual ~Pizza() {};
};


class PizzaStore {
public:
    enum Styles { eMarguerita, eCalabresa, eNapolitana };
  
    virtual std::shared_ptr<Pizza> orderPizza(Styles type) {
        std::shared_ptr<Pizza> pizza = createPizza(type);
        pizza->Prepare();
        pizza->Bake();
        pizza->Cut();
        pizza->Box();
        return pizza;
    }
    virtual ~PizzaStore() {};
protected:
    virtual std::shared_ptr<Pizza> createPizza(Styles type) = 0;
};

class BrazileiraCalabresa : public Pizza {
public:
    virtual void Prepare() override { std::cout << "Round style ... Prepare" << std::endl; };
    virtual ~BrazileiraCalabresa() {};
};

class BrazileiraMarguerita : public Pizza {
public:
    virtual void Prepare() override { std::cout << "Round style ... Prepare" << std::endl; };
    virtual ~BrazileiraMarguerita() {};
};

class BrazileiraNapolitana : public Pizza {
public:
    virtual void Prepare() override { std::cout << "Round style ... Prepare" << std::endl; };
    virtual ~BrazileiraNapolitana() {};
};


class PizzaBrasileiraStyle : public PizzaStore {
public:
   
    // Inherited via IPizzaStore
    virtual std::shared_ptr<Pizza> createPizza(Styles type) override
    {
        switch (type)
        {
        case PizzaStore::Styles::eCalabresa:
            return std::make_shared<BrazileiraCalabresa>();
            break;
        case PizzaStore::Styles::eMarguerita:
            return std::make_shared<BrazileiraMarguerita>();
            break;
        case PizzaStore::Styles::eNapolitana:
            return std::make_shared<BrazileiraNapolitana>();
            break;
        default:
            break;
        }

        return std::shared_ptr<Pizza>();
    }
};

class PizzaAmericanStyle : public PizzaStore {
    // Inherited via IPizzaStore
    virtual std::shared_ptr<Pizza> createPizza(Styles type) override
    {
        return std::shared_ptr<Pizza>();
    }
};


class PizzaItalianStyle : public PizzaStore {
    // Inherited via IPizzaStore
    virtual std::shared_ptr<Pizza> createPizza(Styles type) override
    {
        return std::shared_ptr<Pizza>();
    }
};
