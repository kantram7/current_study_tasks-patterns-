#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

using namespace std;

class Encryptor {
public:
    Encryptor(int _key) : key(_key) {}

    // example
    string encryptPassword(const string& password) const {
        string enPas("");
        for (const char c : password) {
            enPas += (((int)c) * key);
        }
        return enPas;
    }

private:
    int key;
};


class User {
public:
    // password здесь уже зашифрован должен быть подающийся
    User(string _name, string _password) : name(_name), password(_password) {}

    string getName() const { return name; }

    string getPassword() const { return password; }

private:
    string name, password;
};


class DB {
public:
    void addNote(int key, const string& value) {
        db[key] = value;
    }

    string getNote(int key) {
        auto note = _getNote(key);
        if (note == db.end()) throw new exception(); // уточнить
        return (*note).second;
    }

    int key() const { return _key; }

    bool checkUser(const User& _user) const {
        for (const auto& user : users) {
            if (user->getName() == _user.getName()) return true; // example
        }
        return false;
    }

private:
    map<int, string>::const_iterator _getNote(int key) const {
        return db.find(key);
    }

    vector<User*> users;
    map<int, string> db;

    int _key = 101; // key for encriptor
};


class DBLoader {
public:
    DB* LoadDB(const string& path) const {
        /* тут загрузка бд из файла */
        return new DB();
    }

    /*и какие-то еще сложные большие возможности */
};

// упрощение доступа к БД
class Facade {
public:
    Facade(const string& path) {
        DBLoader load;
        db = load.LoadDB(path);
    }

    void setUser(string _name, string _pasword) {
        string encrPas = (new Encryptor(db->key()))->encryptPassword(_pasword);
        curUser = new User(_name, encrPas);
    }

    const string getNote(int DBkey) const {

        if (!checkUser(*curUser)) {
            printMes("нет доступа");
            return "";
        }

        printMes("доступ к просмотру записи");
        return db->getNote(DBkey);
    }

    void addNote(int key, const string& value) {

        if (!checkUser(*curUser)) {
            printMes("нет доступа");
            return;
        }

        db->addNote(key, value);
        printMes("запись успешно добавлена");
    }

    void printMes(const string& mes) const {
        cout << mes << endl;
    }


protected:

    bool checkUser(const User& user) const {
        return db->checkUser(user);
    }

    DB* db = nullptr;
    User* curUser = nullptr;
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Facade* dbWorker = new Facade("path");

    dbWorker->setUser("name", "password");


    dbWorker->addNote(1, "someNote");


    return 0;
}

/*
Вообще крайне синтетический пример программы
Но суть вроде показывает

Многие методы в более реальном примере были бы намного объемнее и сложнее
*/
