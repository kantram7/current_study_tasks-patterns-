#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum class Format { Markdown, Html };

class ListStrategy {
public:
    virtual ~ListStrategy() = default;
    virtual void addListItem(ostringstream& oss, const string& item) {};
    virtual void start(ostringstream& oss) {};
    virtual void end(ostringstream& oss) {};
};

class MarkdownListStrategy : public ListStrategy {
public:
    void addListItem(ostringstream& oss, const string& item) override { oss << " - " << item << endl; }
};


class HtmlListStrategy : public ListStrategy {
public:
    void start(ostringstream& oss) override { oss << "<ul>" << endl; }
    void end(ostringstream& oss) override { oss << "</ul>" << endl; }
    void addListItem(ostringstream& oss, const string& item) override { oss << "\t<li>" << item << "</li>" << endl; }
};

class Context {
public:

    Context(const Format& format) {
        clear();
        changeOutputFormat(format);
    }

    void clear() {
        m_oss.str("");
        m_oss.clear();
    }


    void appendList(const vector<string>& items) {
        list_strategy->start(m_oss);
        for (auto& item : items)
            list_strategy->addListItem(m_oss, item);
        list_strategy->end(m_oss);
    }


    void changeOutputFormat(const Format& format) {
        clear();

        switch (format) {

        case Format::Markdown:
            list_strategy = new MarkdownListStrategy();
            break;

        case Format::Html:
            list_strategy = new HtmlListStrategy();
            break;

        default:
            throw exception("");
        }
    }


    string toStr() const { return m_oss.str(); }


private:
    ostringstream m_oss;
    ListStrategy* list_strategy;
};


int main()
{
    Context* context = new Context(Format::Markdown);
    context->appendList({ "foo", "bar", "baz" });
    cout << context->toStr() << endl << endl;

    context->changeOutputFormat(Format::Html);
    context->appendList({ "foo", "bar", "baz" });
    cout << context->toStr() << endl << endl;


    return 0;
}
