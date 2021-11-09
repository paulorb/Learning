//Simple Factory

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

class SimplePizzaStoreFactory {
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

class SimplePizzaStore {
public:
    SimplePizzaStoreFactory pizzaFactory;
    std::shared_ptr<Pizza> OrderPizza(SimplePizzaStoreFactory::Styles pizzaStyle) {
        std::shared_ptr<Pizza> p = pizzaFactory.createPizza(pizzaStyle);
        p->Prepare();
        p->Bake();
        p->Cut();
        p->Box();
        return p;
    }
};
