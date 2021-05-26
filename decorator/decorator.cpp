#include <iostream>
#include <string>
#include <sstream>

using namespace std;


class SomeBase {
public:
    virtual ~SomeBase() {}
    virtual string SomeAct() const = 0;
    virtual bool AnotherAct(int _num) const = 0;
};

class Some : public SomeBase {
public:
    Some(const string& _str) : str(_str) {}

    string SomeAct() const override {
        return "String example - " + str;
    }

    bool AnotherAct(int _num) const override {
        if (str.size() >= _num) return true;
        return false;
    }

private:
    string str;
};

class Decorator : public SomeBase {
public:
    Decorator(SomeBase* _some) : some(_some) {}

    ~Decorator() { delete some; }

    string SomeAct() const override {
        return some->SomeAct();
    }

    bool AnotherAct(int _num) const override {
        return some->AnotherAct(_num);
    }

protected:
    SomeBase* some;
};

class CurDecorator : public Decorator {
public:
    CurDecorator(SomeBase* _some) : Decorator(_some) {}

    string SomeAct() const override {
        return "CurDecorator: catch [" + Decorator::SomeAct() + "]";
    }
};

class AnotherCurDecorator : public Decorator {
public:
    AnotherCurDecorator(SomeBase* _some) : Decorator(_some) {}

    string SomeAct() const override {
        return "AnotherCurDecorator: catch [" + Decorator::SomeAct() + "]";
    }
};

class ErrDecorator : public Decorator {
public:
    ErrDecorator(SomeBase* _some) : Decorator(_some) {}

    string SomeAct() const override {
        string mes = Decorator::SomeAct();
        cerr << "Message: `" + mes + "`" << endl;
        return mes;
    }
};


int main()
{
    SomeBase* s = new Some("some string 123");
    cout << s->SomeAct() << endl;

    cout << endl << endl;

    SomeBase* decorator = new CurDecorator(s);
    cout << decorator->SomeAct() << endl;

    cout << endl << endl;

    SomeBase* decorator_2 = new AnotherCurDecorator(decorator);
    cout << decorator_2->SomeAct() << endl;

    cout << endl << endl;

    SomeBase* decorator_err = new ErrDecorator(s);
    cout << decorator_err->SomeAct() << endl;

    return 0;
}
