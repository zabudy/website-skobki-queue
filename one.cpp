#include <iostream>
#include <fstream>
#include "cgi.h"
#include "stak.h"
using namespace std;
void show_content();
void show_menu();
bool stack(const char* s);

void main()
{
    cout << "Content-type: text/html; charset=Windows-1251\n\n";
    ifstream f("one.html");
    if (f.is_open()) {
        auto sz = 65536;
        auto buf = new char[sz];
        while (!f.eof()) {
            f.getline(buf, sz);
            if (!strcmp(buf, "<!--#CONTENT#-->")) {
                show_content();
            }
            else 
                if (!strcmp(buf, "<!--#MENU#-->")) {
                show_menu();

            }
            cout << buf;
        }
        delete[] buf;
        f.close();
    }
    else cout << "ФАЙЛ НЕ ОТКРЫЛСЯ( ";
}

void show_content() {
    cout << "<form method='get' action='one.cgi'>";
    cout << "Введите выражение из скобок: <input type='text' name='skobki' maxlength='50' size='50'><br>";
    cout << "<input type='submit' value='Отправить'>";
    cout << "</form>";
    char* data = nullptr;
    get_from_data(data);
    if (data && strlen(data) > 0) {
        char* value = nullptr;
        get_param_value(value, "skobki", data);
        if (stack(value))
            cout << "Выpажение верно";
        else
            cout << "Выpажение не верно";
    }
}
void show_menu() {
    cout << "<div><a href = 'index.cgi'>  Главная страница</a></div>";
    cout << "<div><a href = 'two.cgi'> Задание №2</a></div>";
}

bool	check(int c1, int c2)
{
    if (c1 == '(') {
        if (c2 == ')')
            return (true);
    }
    if (c1 == '{') {
        if (c2 == '}')
            return (true);
    }
    if (c1 == '[') {
        if (c2 == ']')
            return (true);
    }
    return(false);
}

bool stack(const char* s) {
    setlocale(LC_ALL, "Rus");
    char br1[4] = { '(', '[', '{' , '<' };
    char br2[4] = { ')', ']', '}', '>' };
    char upper;
    int flag;
    int c;
    elem* stack = nullptr;
    flag = 1;
    for (int i = 0; flag && (s[i] != '\0'); i++)
        for (int k = 0; k < 4; k++)
        {
            if (s[i] == br1[k]) {
                push(stack, s[i]); break;
            }
            if (s[i] == br2[k]) {
                upper = pop(stack, &c);
                if (upper || check(c, br2[k])) flag = 0;
                break;
            }
        }
    if (!flag && (stack == nullptr))
        return true;
    else
        return false;
}
