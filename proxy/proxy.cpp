#include <iostream>
#include <string>

using namespace std;


class Object {
public:
    virtual void SomeAction() const = 0;
    virtual string getUrl() const = 0;
};

class RealObject : public Object {
public:
    RealObject(const string& _url) : url(_url) {}

    void SomeAction() const override {
        cout << "RealObject doing something : " + url << endl;
    }

    string getUrl() const override {
        return url;
    }

private:
    string url;
};

class Proxy : public Object {
public:

    ~Proxy() { delete realObj; }

    Proxy(const RealObject* _realObj, bool ava) : realObj(new RealObject(*_realObj)), isAvalible(ava) {} // const ?

    void SomeAction() const override {
        cout << "log: ";
        if (objAvalible()) {
            realObj->SomeAction();
            cout << "real obj successfully did smth " << endl; // example
        }
        else cout << "real obj isnt Avalible" << endl;
    }

    string getUrl() const override {
        if (objAvalible()) return realObj->getUrl();
        else return "obj isnt Avalible";
    }

private:
    RealObject* realObj;

    bool objAvalible() const {
        if (1 == 1 && 10 != 11 && isAvalible) return true; // example
        return false;
    }

    bool isAvalible;
};

int main()
{
    RealObject* real = new RealObject("string");
    real->SomeAction();

    cout << endl << endl;

    Proxy* proxy = new Proxy(real, true); // or false
    proxy->SomeAction();



    return 0;
}
