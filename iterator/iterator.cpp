#include <iostream>
#include <execution>
#include <initializer_list>

using namespace std;

template <class Y, class I>
class StackIterator;

template <class T>
class Stack {
public:

    struct StackItem {
        StackItem(T _item) : item(_item) {}
        T item;
        StackItem* next = nullptr;
    };

    friend class StackIterator<StackItem, T>;

    Stack() {}

    Stack(const initializer_list<T>& params) {
        for (const auto& item : params) {
            push(item);
        }
    }

    void push(const T& item) {
        if (isEmpty()) firstElement = new StackItem(item);
        else {
            StackItem* newFirstElement = new StackItem(item);
            newFirstElement->next = firstElement;
            firstElement = newFirstElement;
        }
        _size++;
    }

    T pop() {
        if (isEmpty()) throw new exception("Stack is empty");

        StackItem* popElement = firstElement;
        firstElement = firstElement->next;

        _size--;

        return popElement->item;
    }

    bool isEmpty() const {
        return (_size == 0);
    }

    size_t size() const {
        return _size;
    }

    StackIterator<StackItem, T>* iterator() const {
        return new StackIterator<StackItem, T>(this);
    }

    T operator[](const size_t& index) {
        if (index >= _size) throw new out_of_range("Index out of range");

        size_t i(0);
        StackItem* curItem = firstElement;

        while (i != index) {
            curItem = curItem->next;
            i += 1;
        }

        return curItem->item;
    }

private:
    size_t _size = 0;
    StackItem* firstElement = nullptr;
};


template <class Y, class I>
class StackIterator {
public:
    StackIterator(const Stack<I>* stack) : _stack(stack), _current(stack->firstElement) {}

    void first() {
        _current = _stack->firstElement;
    }

    void next() {
        _current = _current->next;
    }

    bool end() const {
        return (_current == nullptr);
    }

    I operator*() {
        return _current->item;
    }

private:
    Y* _current;
    const Stack<I>* _stack;
};




int main() {
    
    Stack<int>* st = new Stack({ 1, 2, 3, 6, 7, 0 });

    cout << "\nsize == " << st->size() << endl;
    cout << endl << (*st)[1] << "\n\n";

    cout << "stack top -> ";
    for (auto iter = st->iterator(); !iter->end(); iter->next()) {
        cout << **iter << " - ";
    }

    cout << endl;


    return 0;
}
