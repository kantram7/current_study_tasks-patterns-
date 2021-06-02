#include <iostream>
#include <string>

using namespace std;

class Unit {
public:
    Unit(int h, int a, int d, string n) : _health(h), _curHealth(h), _attack(a), _defence(d), _name(n) {}

    double Health() const {
        return _curHealth;
    }

    int Attack() const {
        return _attack;
    }

    int Defence() const {
        return _defence;
    }

    string Name() const {
        return _name;
    }

    virtual void takeDamage(int damageSum) = 0; // получение урона

    bool Alive() const { return (int)_curHealth > 0; }

    virtual int AttackPower(int mod = 1) const = 0; // 0 < n <= _attack
    virtual int DefencePower(int mod = 1) const = 0; // 0 < n <= _defence
    virtual double Motivation(int mod = 1) const = 0; // 0 < n < 1

    virtual void SomeUnitSpec(Unit* attackedUnit, int mod = 1) = 0;

    // атака переданного юнита
    void AttackUnit(Unit* attackedUnit, int mod = 1) {
        if (Motivation(mod) > attackedUnit->Motivation(mod)) {
            attackedUnit->takeDamage(AttackPower(mod) - attackedUnit->DefencePower(mod));
            SomeUnitSpec(attackedUnit, mod);
        }
        else {
            takeDamage(attackedUnit->AttackPower(mod) - DefencePower(mod));
        }
    }

protected:
    int _health, _attack, _defence;
    double _curHealth;
    string _name;
};


class Archer : public Unit {
public:
    Archer(int h, int a, int d) : Unit(h, a, d, "Archer") {}

    int AttackPower(int mod = 1) const override {
        return (Attack() * (_curHealth / Health())) * mod;
    }

    int DefencePower(int mod = 1) const override {
        return (Defence() * (_curHealth / Health()) * mod);
    }

    double Motivation(int mod = 1) const override {
        return ((_curHealth * mod) / (Health() / mod));
    }

    void takeDamage(int damageSum) override {
        if (Motivation() > damageSum) _curHealth -= (damageSum / 2);
        else _curHealth -= (damageSum);
    }

    void SomeUnitSpec(Unit* attackedUnit, int mod = 1) {
        // вторая атака
        attackedUnit->takeDamage(AttackPower(mod));
    }
};


class Monster : public Unit {
public:
    Monster(int h, int a, int d) : Unit(h, a, d, "Monster") {}

    int AttackPower(int mod = 1) const override {
        return Attack();
    }

    int DefencePower(int mod = 1) const override {
        return Defence();
    }

    double Motivation(int mod = 1) const override {
        return 1;
    }

    void takeDamage(int damageSum) override {
        _curHealth -= damageSum;
    }

    void SomeUnitSpec(Unit* attackedUnit, int mod = 1) {
        return;
    }

    bool Alive() const { return _health >= 0; } // можно переопределять и уже реализованные методы
};


// просто так
class HeroMonster : public Monster {
public:
    HeroMonster(int h, int a, int d, string n) : Monster(h, a, d) {
        _name = n;
    }

    int AttackPower(int mod = 1) const override {
        return Attack() * 10;
    }

    int DefencePower(int mod = 1) const override {
        return Defence() * 10;
    }

};

int main()
{
    // тут вроде ничего в main не нужно

    Archer* a = new Archer(1, 1, 1);

    Monster* m = new Monster(2, 2, 2);

    HeroMonster* h = new HeroMonster(3, 4, 5, "Hero");


    return 0;
}
