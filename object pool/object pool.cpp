#include <string>
#include <iostream>
#include <list>

using namespace std;

template <class R>
class ResCreator {
public:
    R* createObj() const {
        return new R();
    }
};

class ResObject {
public:
    virtual void reset() = 0;
};

class Resource : public ResObject {
public:
    Resource() : value(0) {}

    void reset() override {
        value = 0;
    }

    int getValue() const {
        return value;
    }

    void setValue(int _value) {
        value = _value;
    }
private:
    int value;
};


template <class T>
class ObjectPool {

public:
    static ObjectPool* getInstance(ResCreator<T>* _creator)
    {
        if (instance == nullptr) {

            instance = new ObjectPool<T>(_creator);
            return instance;
        }
        return nullptr;
    }

    T* getResource() {
        if (resources->empty()) {

            return creator->createObj();
        }
        else {

            T* resource = resources->front();
            resources->pop_front();
            return resource;
        }
    }

    void returnResource(T* object) {
        object->reset();
        resources->push_back(object);
    }

    ~ObjectPool() {
        for (auto ptr : resources) {
            delete ptr;
        }
        resources.clear();

        delete creator;
        delete instance;
    }

private:
    inline static ResCreator<T>* creator = nullptr;

    list<T*>* resources;

    inline static ObjectPool* instance = nullptr;

    ObjectPool(ResCreator<T>* _creator) {
        resources = new list<T*>;
        creator = _creator;
    }
};


int main()
{
    ResCreator<Resource>* creator = new ResCreator<Resource>();

    auto pool = ObjectPool<Resource>::getInstance(creator);


    Resource* one = pool->getResource();
    one->setValue(10);
   cout << "one = " << one->getValue() << " [" << one << "]" << endl;

   Resource* two = pool->getResource();
    two->setValue(20);
    cout << "two = " << two->getValue() << " [" << two << "]" << endl;

    pool->returnResource(one);
    pool->returnResource(two);

    cout << endl << "---------------------------------------" << endl << endl;

    one = pool->getResource();
    cout << "one = " << one->getValue() << " [" << one << "]" << endl;

    two = pool->getResource();
    cout << "two = " << two->getValue() << " [" << two << "]" << endl;



    return 0;
}