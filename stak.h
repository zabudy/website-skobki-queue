#pragma once
#include <iostream>
using namespace std;

struct elem
{
	int value;
	elem* next = nullptr;
};

void push(elem*& stack, int value);

bool pop(elem*& stack, int* value);

const int* peek(const elem* stack);

void clear(elem*& stack);