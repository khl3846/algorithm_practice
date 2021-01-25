#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef int element;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

void enqueue(StackType* s1, StackType* s2, element item) {
	int i = -1;
	int tmp;
	if (is_full(s1)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	} 
	if (!is_empty(s2)) {
		tmp = s2->top;
		while (i < tmp) {
			push(s1, pop(s2));
			i++;
		}
		s1->data[++(s1->top)] = item;
	}
	else s1->data[++(s1->top)] = item;
}

element dequeue(StackType* s1, StackType* s2) {
	int i = -1;
	int tmp;
	/*if (is_empty(s2)) {
		fprintf(stderr, "스택 공백 에러\n");
		return;
	}*/
	if (!is_empty(s1)) {
		tmp = s1->top;
		while (i < tmp) {
			push(s2, pop(s1));
			i++;
		}
		return s2->data[(s2->top)--];
	}
	else return s2->data[(s2->top)--];
}

int main(void) {
	StackType s1, s2;
	char ch;

	init_stack(&s1);
	init_stack(&s2);

	enqueue(&s1, &s2, 1);
	enqueue(&s1, &s2, 2);
	enqueue(&s1, &s2, 3);
	int a = dequeue(&s1, &s2);
	printf("%d\n", a);
	int b = dequeue(&s1, &s2);
	printf("%d\n", b);
	enqueue(&s1, &s2, 4);
	int c = dequeue(&s1, &s2);
	printf("%d\n", c);
	int d = dequeue(&s1, &s2);
	printf("%d\n", d);
}
