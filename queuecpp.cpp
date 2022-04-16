#include "queue.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
inline man create_elem(const char* name, const char* name1, const char* sex, int age, const char* job, int salary, const char* purpose){
    man m;
    strcpy_s(m.name, name1);
    strcpy_s(m.name, name1);
    strcpy_s(m.sex, sex);
    m.age = age;
    strcpy_s(m.job, job);
    m.salary = salary;
    strcpy_s(m.purpose, purpose);
    return m;
}

void enqueue(queue& queue, const char* name, const char* name1, const char* sex, int age, const char* job, int salary, const char* purpose){
    man newm = create_elem(name, name1, sex, age, job, salary, purpose);
    elem* newel = new elem;
    newel->m = newm;
    if (!queue.tail){
        queue.head = queue.tail = newel;
    }
    else{
        queue.tail->next = newel;
        queue.tail = newel;
    }
    queue.size++;
}

bool dequeue(queue& queue, man& m){
    if (!queue.head)
        return false; 
    m = queue.head->m;
    elem* rem = queue.head;
    queue.head = queue.head->next;
    delete rem;
    if (!queue.head) queue.tail = nullptr;
    queue.size--;
    return true;
}

void clear(queue& queue){
    while (queue.head){
        elem* rem = queue.head; 
        queue.head = queue.head->next;
        delete rem; 
    }
    queue.size = 0; 
    queue.tail = nullptr; 
}