#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>

#include "Programm.hpp"

std::vector<std::string> split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment &env);

private:
    void show();
    Wt::WLineEdit *nameEdit_;
    Wt::WText *greeting_;
    Wt::WTable *m_Table;
    Wt::WTable *table_;
    Wt::WTable *optable_;
};

void HelloApplication::show()
{
    table_->clear();
    optable_->clear();
    std::string input = nameEdit_->text().toUTF8();
    Programm pr(input);
    auto inputs = split(input, ",");
    pr.Execute();
    auto header = pr.Variables();
    unsigned int column = 0;
    for (auto &&i : header)
    {
        table_->elementAt(0, column++)->addWidget(std::make_unique<Wt::WText>(std::string(1, i)));
    }
    for (auto &&i : inputs)
    {
        table_->elementAt(0, column++)->addWidget(std::make_unique<Wt::WText>(i));
    }
    unsigned int row = 1;
    while (pr.availible())
    {
        auto result = pr.next();
        column = 0;
        for (auto &&i : result)
        {
            table_->elementAt(row, column++)->addWidget(std::make_unique<Wt::WText>(i ? "1" : "0"));
        }
        row++;
    }

    auto opcode = pr.GetOpCode();
    row = 1;
    optable_->elementAt(0, 0)->addWidget(std::make_unique<Wt::WText>("ID"));
    optable_->elementAt(0, 1)->addWidget(std::make_unique<Wt::WText>("OpCode"));
    for (unsigned int i = 0; i < opcode.size(); i++)
    {
        optable_->elementAt(row, 1)->addWidget(std::make_unique<Wt::WText>(std::to_string(opcode[i])));
        optable_->elementAt(row++, 0)->addWidget(std::make_unique<Wt::WText>(OpCodeStrings[opcode[i]]));
        if (opcode[i] == Programm::OP_Load)
        {
            i++;
            optable_->elementAt(row, 1)->addWidget(std::make_unique<Wt::WText>(std::to_string(opcode[i]) + " (" + header[opcode[i]] + ")"));
            optable_->elementAt(row++, 0)->addWidget(std::make_unique<Wt::WText>("Variable"));
        }
    }
    optable_->show();

    table_->show();
}
using namespace Wt;

HelloApplication::HelloApplication(const Wt::WEnvironment &env)
    : Wt::WApplication(env)
{
    setTheme(std::make_unique<Wt::WBootstrapTheme>());
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Aussage: "))->setMargin(10);
    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    nameEdit_->setMargin(10);
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Calculate"));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());

    button->clicked().connect(this, &HelloApplication::show);

    auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>();
    auto vbox = container->setLayout(Wt::cpp14::make_unique<Wt::WVBoxLayout>());
    auto hbox = vbox->addLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
    {
        auto table = std::make_unique<Wt::WTable>();
        table_ = table.get();
        table_->setHeaderCount(1);

        table_->addStyleClass("table form-inline");
        table_->hide();
        table_->toggleStyleClass("table-bordered", true);
        table_->toggleStyleClass("table-condensed", true);

        hbox->addWidget(std::move(table));
    }
    {
        auto table = cpp14::make_unique<WTable>();
        auto table_ = table.get();
        table_->setHeaderCount(1);

        table_->addStyleClass("table form-inline");
        table_->toggleStyleClass("table-bordered", true);
        table_->toggleStyleClass("table-condensed", true);

        table_->elementAt(0, 0)->addWidget(std::make_unique<WText>("Zeichen"));
        table_->elementAt(0, 1)->addWidget(std::make_unique<WText>("Erklaerung"));

        table_->elementAt(1, 0)->addWidget(std::make_unique<WText>("\"<=>\" oder \"=\""));
        table_->elementAt(1, 1)->addWidget(std::make_unique<WText>("Aequivalenz"));

        table_->elementAt(2, 0)->addWidget(std::make_unique<WText>("\"!=\""));
        table_->elementAt(2, 1)->addWidget(std::make_unique<WText>("Antivalenz"));

        table_->elementAt(3, 0)->addWidget(std::make_unique<WText>("\"->\""));
        table_->elementAt(3, 1)->addWidget(std::make_unique<WText>("Implikation"));

        table_->elementAt(4, 0)->addWidget(std::make_unique<WText>("\"<-\""));
        table_->elementAt(4, 1)->addWidget(std::make_unique<WText>("Implikation aber nach links"));

        table_->elementAt(5, 0)->addWidget(std::make_unique<WText>("\"|\""));
        table_->elementAt(5, 1)->addWidget(std::make_unique<WText>("Oder"));

        table_->elementAt(6, 0)->addWidget(std::make_unique<WText>("\"&\""));
        table_->elementAt(6, 1)->addWidget(std::make_unique<WText>("Und"));

        table_->elementAt(7, 0)->addWidget(std::make_unique<WText>("\"^\""));
        table_->elementAt(7, 1)->addWidget(std::make_unique<WText>("Xor (exclusives oder)"));

        table_->elementAt(8, 0)->addWidget(std::make_unique<WText>("\"!\""));
        table_->elementAt(8, 1)->addWidget(std::make_unique<WText>("Nicht"));

        table_->elementAt(9, 0)->addWidget(std::make_unique<WText>("\"0\""));
        table_->elementAt(9, 1)->addWidget(std::make_unique<WText>("Falsch"));

        table_->elementAt(10, 0)->addWidget(std::make_unique<WText>("\"1\""));
        table_->elementAt(10, 1)->addWidget(std::make_unique<WText>("Wahr"));

        table_->elementAt(10, 0)->addWidget(std::make_unique<WText>("\"(...)\""));
        table_->elementAt(10, 1)->addWidget(std::make_unique<WText>("Klammern"));

        table_->elementAt(11, 0)->addWidget(std::make_unique<WText>("\",\""));
        table_->elementAt(11, 1)->addWidget(std::make_unique<WText>("Komma trennt Aussagen. Man kann so viele Aussagen nacheinander haengen wie man will"));

        table_->elementAt(12, 0)->addWidget(std::make_unique<WText>("\"A...Z\""));
        table_->elementAt(12, 1)->addWidget(std::make_unique<WText>("Variablen"));

        table_->elementAt(13, 0)->addWidget(std::make_unique<WText>("Beispiel: A|B"));
        table_->elementAt(13, 1)->addWidget(std::make_unique<WText>("A oder B"));

        table_->elementAt(14, 0)->addWidget(std::make_unique<WText>("Beispiel: (A->B)&(B->C),A->C"));
        table_->elementAt(14, 1)->addWidget(std::make_unique<WText>("\"A impliziert B und B impliziert C\" und \"A impliziert C\""));

        table_->elementAt(15, 0)->addWidget(std::make_unique<WText>("Beispiel: !A&!B,!A,!B"));
        table_->elementAt(15, 1)->addWidget(std::make_unique<WText>("\"Nicht A und Nicht B\" und \"Nicht A\" und \"Nicht B\" "));

        hbox->addWidget(std::move(table));
    }
    {
        auto table = cpp14::make_unique<WTable>();
        optable_ = table.get();
        optable_->setHeaderCount(1);

        optable_->addStyleClass("table form-inline");
        optable_->hide();
        optable_->toggleStyleClass("table-bordered", true);
        optable_->toggleStyleClass("table-condensed", true);
        vbox->addWidget(std::move(table));
    }
    root()->addWidget(std::move(container));

}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<HelloApplication>(env);
    });
}