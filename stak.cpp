#include "stak.h"

void push(elem*& top, int value) {
	auto* newel = new elem;
	newel->value = value;
	if (top) newel->next = top;
	top = newel;
}

bool pop(elem*& top, int* value) {
	if (!top) return false;
	*value = top->value;
	auto* rem = top;
	top = top->next;
	delete rem;
	return true;
}

const int* peek(const elem* top) {
	if (!top) return nullptr;
	return &top->value;
}

void clear(elem*& top) {
	int val;
	while (pop(top, &val));
}