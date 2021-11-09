//Observer Pattern

class Observer {
public:
    virtual void Update()=0;
    virtual ~Observer() {};
};

class Subject {
public:
    virtual void AddObserver(std::shared_ptr<Observer> ob) = 0;
    virtual void RemoveObserver(std::shared_ptr<Observer> ob) = 0;
    virtual void NotifyAll() = 0;
    virtual float GetTemp() = 0;
    virtual ~Subject() {};
};


class DataProvider : public Subject {
public:
    std::vector<std::shared_ptr<Observer>> _vectObserver;
    // Inherited via Subject
    virtual void AddObserver(std::shared_ptr<Observer> ob) override
    {
        _vectObserver.push_back(ob);
    }

    virtual void RemoveObserver(std::shared_ptr<Observer> ob) override
    {
        auto it = std::find_if(_vectObserver.begin(), _vectObserver.end(), [&](std::shared_ptr<Observer> const& p) {
            return p == ob;
            });

        if (it != _vectObserver.end()) {
            _vectObserver.erase(it);
        }
    }

    virtual void NotifyAll() override
    {
        for (auto i : _vectObserver) {
            i->Update();
        }
    }

    virtual float GetTemp() override
    {
        return 12.4;
    }

 
};


class ClientFirst : public Observer {
private:
    std::shared_ptr<Subject> _subject;
public:
    ClientFirst(std::shared_ptr<Subject> sb) : _subject(sb) {};
    // Inherited via Observer
    virtual void Update() override
    {
        float temp = _subject->GetTemp();
        std::cout << temp << std::endl;
    }

};

