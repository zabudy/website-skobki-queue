#pragma once
struct man{
    char name[50];
    char name1[50];
    char sex[50];
    int age;
    char job[50];
    int salary;
    char purpose[50];
};

struct elem{
    man m;
    elem* next = nullptr;
};

struct queue{
    elem* head = nullptr;
    elem* tail = nullptr;
    size_t size = 0;
};

void enqueue(queue& queue, const char* name, const char* name1, const char* sex, int age, const char* job, int salary, const char* purpose);
inline man create_elem(const char* name, const char* name1, const char* sex, int age, const char* job, int salary, const char* purpose);
bool dequeue(queue& queue, man& m);
void clear(queue& queue);