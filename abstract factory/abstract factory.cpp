#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Archer {
public:
    virtual int getHealth() const = 0;
    virtual string Name() const = 0;
    virtual ~Archer() {};
};

class Swordsman {
public:
    virtual int getHealth() const = 0;
    virtual string Name() const = 0;
    virtual ~Swordsman() {};
};

class ConcreteArcher1 : public Archer {
public:
    ConcreteArcher1() {}

    int getHealth() const override {
        return health;
    }
    string Name() const override {
        return "ConcreteArcher1";
    }
private:
    int health = 10;
};

class ConcreteArcher2 : public Archer {
public:
    ConcreteArcher2() {}

    int getHealth() const override {
        return health;
    }
    string Name() const override {
        return "ConcreteArcher2";
    }
private:
    int health = 100;
};

class ConcreteSwordsman1 : public Swordsman {
public:
    ConcreteSwordsman1() {}

    int getHealth() const override {
        return health;
    }
    string Name() const override {
        return "ConcreteSwordsman1";
    }
private:
    int health = 20;
};

class ConcreteSwordsman2 : public Swordsman {
public:
    ConcreteSwordsman2() {}

    int getHealth() const override {
        return health;
    }
    string Name() const override {
        return "ConcreteSwordsman2";
    }
private:
    int health = 200;
};

class AbstractFactory {
public:
    virtual Archer* createArcher() const = 0;
    virtual Swordsman* createSwordsman() const = 0;
    virtual ~AbstractFactory() {}
};

class AbstractFactory1 : public AbstractFactory {
public:
    Archer* createArcher() const override {
        return new ConcreteArcher1();
    }

    Swordsman* createSwordsman() const override {
        return new ConcreteSwordsman1();
    }
};

class AbstractFactory2 : public AbstractFactory {
public:
    Archer* createArcher() const override {
        return new ConcreteArcher2();
    }

    Swordsman* createSwordsman() const override {
        return new ConcreteSwordsman2();
    }
};


class UnitsCreator {
public:
    UnitsCreator(AbstractFactory* _factory) : factory(_factory) {}

    Archer* getArcher() const {
        return factory->createArcher();
    }

    Swordsman* getSwordsman() const {
        return factory->createSwordsman();
    }

    ~UnitsCreator() { delete factory; }

private:
    AbstractFactory* factory = nullptr;
};

int main()
{
    AbstractFactory1* fuck1 = new AbstractFactory1(); // фабрика для юнитов 1

    UnitsCreator* creator = new UnitsCreator(fuck1);
    Archer* archer1 = creator->getArcher();
    cout << archer1->Name() << endl;
    cout << creator->getSwordsman()->Name() << endl << endl;


    UnitsCreator* creator2 = new UnitsCreator(new AbstractFactory2()); // фабрика для юнитов 2
    Archer* archer2 = creator2->getArcher();
    cout << archer2->Name() << endl;
    cout << creator2->getSwordsman()->Name() << endl << endl;


    return 0;
}
