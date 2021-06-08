#include <iostream>
#include <list>
#include <string>
#include <fstream>

using namespace std;

class IObserver {
public:
    virtual void Update() = 0;

};

class Subject {
public:
    ~Subject() {
        for (IObserver* abs : _observers) {
            delete abs;
        }
        _observers.clear();
    };

    void Add(IObserver* observer) {
        _observers.push_back(observer);
    }

    void Remove(IObserver* observer) {
        _observers.remove(observer);
    }

    void Notify() const {
        for (IObserver* abs : _observers) {
            abs->Update();
        }
    }

    double getVal() const { return SubValue; }

    void setVal(double _v) {
        SubValue = _v;
        cout << "Subject update value, new = " << SubValue << endl;
        Notify();
    }

protected:
    list<IObserver*> _observers = list<IObserver*>();
    double SubValue = 0;
};


class FirstObserver : public IObserver {
public:
    FirstObserver(Subject* _s) : s(_s) {
        s->Add(this);
    }

    void Update() override {
        value = (int)s->getVal();
        cout << "FirstObserver update value" << endl;
    }

private:
    Subject* s;
    int value = 0;
};

class SecondObserver : public IObserver {
public:
    SecondObserver(Subject* _s) : s(_s) {
        s->Add(this);
    }

    void Update() override {
        value = to_string(s->getVal());
        cout << "SecondObserver update value" << endl;
    }

private:
    Subject* s;
    string value = "";
};

class LogObserver : public IObserver {
public:
    LogObserver(Subject* _s, string _file = "log.txt") : s(_s), fileName(_file) {
        s->Add(this);
        ofstream out(fileName);
        if (out.is_open())
        {
            out << "Value is " << s->getVal() << endl;
        }
        out.close();
    }

    void Update() override {
        ofstream out(fileName, ios::app);
        if (out.is_open())
        {
            out << "Update value to " << s->getVal() << endl;
        }
        out.close();
    }

private:
    Subject* s;
    string fileName;
};


int main()
{
    Subject* s = new Subject();
    
    IObserver* obs1 = new FirstObserver(s);
    IObserver* obs2 = new SecondObserver(s);
    IObserver* obs3 = new LogObserver(s);

    s->setVal(100.00);

    cout << "\n\n";

    s->setVal(300.00);

    return 0;
}
