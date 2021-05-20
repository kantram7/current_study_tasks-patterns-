#include <iostream>

using namespace std;

class SimpleClass {
public:
    int get() const { return someValue; }
    void set(int value) { someValue = value; }

    static SimpleClass* Instance(int value = 13) {
        if (instance == nullptr) {
            instance = new SimpleClass(value);
            return instance;
        }
        else return nullptr;
    }

    ~SimpleClass() { delete instance; }

private:
    inline static SimpleClass* instance = nullptr;

    int someValue;

    // SimpleClass() : someValue(13) {}
    SimpleClass(int value) : someValue(value) {}
};

int main()
{
    SimpleClass* a = SimpleClass::Instance(22);

    cout << a->get() << endl;

    // SimpleClass* b = new SimpleClass(); нельзя
    SimpleClass* b = SimpleClass::Instance(22);

    if (b) cout << "b";
    else cout << "null";

    return 0;
}
