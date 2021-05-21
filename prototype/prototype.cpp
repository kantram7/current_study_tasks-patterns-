#include <iostream>
#include <string>
#include <map>

using namespace std;

class Unit {
public:
	virtual ~Unit() {}
	virtual Unit* clone() const = 0;

	Unit(int _health, int _attack) : health(_health), attack(_attack) {}

	virtual int getHealth() const { return health; }
	virtual int geAttack() const { return attack; }

	virtual void PrintField() const = 0;

protected:
	int health;
	int attack;
};

class SomeUnit : public Unit {
public:
	SomeUnit(int _health, int _attack, int some) : Unit(_health, _attack), somethingElse(some) {}

	SomeUnit* clone() const override {
		return new SomeUnit(health, attack, somethingElse);
	}

	void PrintField() const {
		cout << somethingElse << endl;
	}

private:
	int somethingElse;
};

class SomeElseUnit : public Unit {
public:
	SomeElseUnit(int _health, int _attack, string _some) : Unit(_health, _attack), some(_some) {}

	SomeElseUnit* clone() const override {
		return new SomeElseUnit(health, attack, some);
	}

	void PrintField() const {
		cout << some << endl;
	}

private:
	string some;
};

enum class UnitClass {
	SomeUnit1,
	SomeUnit2
};

class PrototypeFactory {
public:
	PrototypeFactory() {
		prototypes[UnitClass::SomeUnit1] = new SomeUnit(10, 10, 10);
		prototypes[UnitClass::SomeUnit2] = new SomeElseUnit(10, 10, "10");
	}

	~PrototypeFactory() {
		delete prototypes[UnitClass::SomeUnit1];
		delete prototypes[UnitClass::SomeUnit2];
	}

	Unit* CreatePrototype(UnitClass class_) {
		return prototypes[class_]->clone();
	}

private:
	map< UnitClass, Unit* > prototypes;
};


int main()
{
	PrototypeFactory* factory = new PrototypeFactory();

	Unit* first = factory->CreatePrototype(UnitClass::SomeUnit1);

	Unit* second = factory->CreatePrototype(UnitClass::SomeUnit2);

	first->PrintField();

	second->PrintField();


	return 0;
}

