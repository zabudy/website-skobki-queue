#include <iostream>
#include <fstream>
using namespace std;
void show_content();
void show_menu();

void main()
{
    cout << "Content-type: text/html; charset=Windows-1251\n\n";
    ifstream f("index");
    if (f.is_open()) {
        auto sz = 65536;
        auto buf = new char[sz];
        while (!f.eof()) {
            f.getline(buf, sz);
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
    
}
void show_menu() {
    cout << "<div><a href = 'one.cgi'> Задание №1 </a></div>";

    cout << "<div><a href = 'two.cgi'> Задание №2 </a></div>";

}
