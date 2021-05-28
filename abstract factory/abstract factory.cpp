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

// здесь не нужно, но не удаляю
/*
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
*/

enum class UnitType
{
    FIRST,
    SECOND
};

AbstractFactory* GetFactory(const UnitType& type) {
    if(type == UnitType::FIRST) return new AbstractFactory1();
    else return new AbstractFactory2();
}

int main()
{
    AbstractFactory* fuck = GetFactory(UnitType::FIRST); // фабрика для юнитов 1

    Archer* archer1 = fuck->createArcher();
    cout << archer1->Name() << endl;
    cout << fuck->createSwordsman()->Name() << endl << endl;


    AbstractFactory* fuck2 = GetFactory(UnitType::SECOND); // фабрика для юнитов 2
    Archer* archer2 = fuck2->createArcher();
    cout << archer2->Name() << endl;
    cout << fuck2->createSwordsman()->Name() << endl << endl;


    return 0;
}
