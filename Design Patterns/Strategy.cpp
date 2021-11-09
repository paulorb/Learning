//Strategy


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

};

class Bus : public Vehicle {

};
