#include <iostream>
#include <string>
#include <list>

using namespace std;

class Component {

public:
    Component(const string& _tag) : tag(_tag) {}

    virtual ~Component() {}

    void SetParent(Component* parent) {
        this->parent = parent;
    }
    Component* GetParent() const {
        return this->parent;
    }

    virtual void Add(Component* component) {}

    virtual void Remove(Component* component) {}

    virtual bool IsComposite() const {
        return false;
    }

    virtual string print() const = 0;

protected:
    Component* parent = nullptr;
    string tag = "";
};


class SimpleTag : public Component {
public:
    SimpleTag(const string& _tag, const string& _value) : Component(_tag), value(_value) {}

    string print() const override {
        return '<' + tag + '>' + value + "</" + tag + '>';
    }
private:
    string value;
};


class Composite : public Component {

public:

    Composite(const string& _tag) : Component(_tag) {}

    void Add(Component* component) override {
        this->childrens.push_back(component);
        component->SetParent(this);
    }

    void Remove(Component* component) override {
        childrens.remove(component);
        component->SetParent(nullptr);
    }

    bool IsComposite() const override {
        return true;
    }

    string print() const override {
        string result = "";

        for (const Component* c : childrens) {
            if (c == childrens.back()) {
                result += c->print();
            }
            else {
                result += c->print() + "\n";
            }
        }
        return  '<' + tag + '>' + "\n" + result + "\n" + "</" + tag + '>';
    }

private:
    list<Component*> childrens;
};


void printHTML(const Component* comp) {
    cout << comp->print() << endl;
}



int main()
{
    Component* tree = new Composite("html");

    Component* body = new Composite("body");

    Component* leaf1 = new SimpleTag("p", "text1");
    Component* leaf2 = new SimpleTag("i", "text1");
    Component* leaf3 = new SimpleTag("h1", "text1");


    body->Add(leaf1);
    body->Add(leaf2);


    Component* footer = new Composite("footer");

    footer->Add(leaf3);

    tree->Add(body);
    tree->Add(footer);


    printHTML(tree);
    cout << "\n\n";


    return 0;
}
