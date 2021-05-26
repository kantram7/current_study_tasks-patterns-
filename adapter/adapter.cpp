#include <iostream>
#include <string>

using namespace std;

// целевой класс
class Target {
public:
    virtual void print(ostream& out = std::cout) const {
        out << "Target class print" << endl;
    }

    virtual string info() const {
        return "Target class";
    }

};

// адаптируемый класс
class Some {
public:
    Some(int _num) : num(_num) {}

    int count() const {
        return num;
    }
private:
    int num;
};


// адаптер адаптирует адаптируемый класс для совмещения его с целевым
class Adapter : public Target {
public:
    Adapter(Some* _one) : one(_one) {}

    void print(ostream& out = std::cout) const override {
        out << "Adapted Some " << one->count() << " print" << endl;
    }

    string info() const override {
        return "Adapted Some " + to_string(one->count());
    }

    ~Adapter() { delete one;  }

private:
    Some* one;
};


void Client(const Target* target) {
    cout << target->info() << endl;
}

void Print(const Target* target) {
    target->print();
}

int main()
{
    Target* t = new Target();
    Client(t);

    Some* s = new Some(13);
    // Client(s); // так работать не будет

    Adapter* ada = new Adapter(s);
    Client(ada); // а так будет

    Print(ada);
    Print(t);

    return 0;
}
