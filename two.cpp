#include <iostream>
#include <fstream>
#include "cgi.h"
#include "queue.h"
using namespace std;
void show_content();
void show_menu();
void show_data(queue& q);
void load_data(queue& credit, queue& deposit);
void credit_(queue& credit);
void deposit_(queue& deposit);

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
    cout << "<table>";
    cout << "<tr><th>ФИО</th><th>Пол</th><th>Возраст</th><th>Профессия</th><th>Зароботок</th><th>Тип</th></tr> ";
    cout << "<tr><td>Черникова Л.Д.</td><td>Ж</td><td>40</td><td>кассир</td><td>25000</td><td>кредит</td></tr> ";
    cout << "<tr><td>Лобиков А.В.</td><td>М</td><td>35</td><td>учитель</td><td>30000</td><td>кредит</td></tr> ";
    cout << "<tr><td>Довков В.Л.</td><td>М</td><td>73</td><td>пенсионер</td><td>26000</td><td>вклад</td></tr> ";
    cout << "<tr><td>Кузнецова Г.К</td><td>Ж</td><td>46</td><td>врач</td><td>34000</td><td>кредит</td></tr> ";
    cout << "<tr><td>Лерова К.П.</td><td>Ж</td><td>36</td><td>бухгалтер</td><td>32000</td><td>вклад</td></tr> ";
    cout << "<tr><td>Фролов Г.П.</td><td>М</td><td>20</td><td>студент</td><td>0</td><td>кредит</td></tr> ";
    cout<<"</table>";
    cout << "<form method='get' action='two.cgi'>";
    cout << "Введите тип: <input type='text' name='tip' maxlength='50' size='50'><br>";
    cout << "<input type='submit' value='Отправить'>";
    cout << "</form>";
    char* data = nullptr;
    get_from_data(data);
    if (data && strlen(data) > 0) {
        char* value = nullptr;
        get_param_value(value, "tip", data);
        queue credit;
        queue deposit;
        load_data(credit, deposit);
        if (!strcmp(value, "кредит")) {
            cout << "<div>Кредит</div>";
            credit_(credit);
        }
        else
            if (!strcmp(value, "вклад")) {
                cout << "<div>Вклад</div>";
                deposit_(deposit);
            }
            else cout << "<div>Неверный тип</div>";
    }
}
void show_menu() {
    cout << " <div><a href = 'index.cgi '> Главная страница </a></div>";
    cout << "<div><a href = 'one.cgi'> Задание №1 </a></div>";
}
void show_data(queue& q) {
    int i = 0;
    while (q.size > 0) {
        man m;
        if (dequeue(q, m)) {
            cout << ++i << ".\t" << m.name << ' ' << m.name1 << "\n" << "\tПол:" << m.sex << "\n" << "\tВозраст:" << m.age << "\n" << "\tРабота:" << m.job << "\n" << "\tЗарплата:" << m.salary << "\n" << "\tЦель обращения в банк:" << m.purpose << "\n";
        }
    }
}
void load_data(queue& credit, queue& deposit) {
    ifstream f("text.txt");
    if (f.is_open()){
        while (!f.eof()){
            char* man = new char[61];
            f.getline(man, 61);
            char* sex = new char[50];
            int age;
            char* job = new char[50];
            int salary;
            char* purpose = new char[50];
            char* name = new char[50];
            char* name1 = new char[50];
            char* context = nullptr;
            char* str = new char[strlen(man) + 1];
            strcpy_s(str, strlen(man) + 1, man);
            char* part = strtok_s(context, " ", &str);
            name = part;
            part = strtok_s(context, " ", &str);
            name1 = part;
            part = strtok_s(context, " ", &str);
            sex = part;
            part = strtok_s(context, " ", &str);
            age = atoi(part);
            part = strtok_s(context, " ", &str);
            job = part;
            part = strtok_s(context, " ", &str);
            salary = atoi(part);
            part = strtok_s(context, " ", &str);
            purpose = part;
            if (!strcmp(purpose, "кредит"))
                enqueue(credit, name, name1, sex, age, job, salary, purpose);
            else
                enqueue(deposit, name, name1, sex, age, job, salary, purpose);
        }
        f.close();
    }
}
void credit_(queue& credit){
    while (credit.size > 0){
        man m;
        if (dequeue(credit, m))
            cout <<"<div>" << m.name << ' ' << m.name1 << ' ' << m.sex << ' ' << m.age << ' ' << m.job << ' ' << m.salary << ' ' << m.purpose << "</div>" << "\n";
    }
}

void deposit_(queue& deposit){
    while (deposit.size > 0){
        man m;
        if (dequeue(deposit, m))
        cout << "<div>" << m.name << ' ' << m.name1 << ' ' << m.sex << ' ' << m.age << ' ' << m.job << ' ' << m.salary << ' ' << m.purpose << "</div>" << "\n";
    }
}
