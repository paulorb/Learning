//Decorator Pattern
class Beverage {   //IPacketElement
public:
    virtual double cost()=0;
};

class CondimentDecorator : public Beverage{  //Packet
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
