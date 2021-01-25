#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10
typedef char element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(DequeType* q) {
	q->front = q->rear = 0;
}

int is_empty(DequeType* q) {
	return (q->front == q->rear);
}

int is_full(DequeType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(DequeType* q) {
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void add_rear(DequeType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element delete_front(DequeType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element get_front(DequeType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val) {
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q) {
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[q->rear];
}

int palindrome(char exp[]) {
	int i = 0;
	int count;
	char ch, low;
	int len = strlen(exp);
	int t1, t2;

	DequeType q;
	init_queue(&q);

	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch >= 'A' && ch <= 'Z') {
			low = tolower(ch);
			add_rear(&q, low);
		}
		else if (ch >= 'a' && ch <= 'z') {
			add_rear(&q, ch);
		}
		else continue;
	}
	
	if (q.rear > q.front)
		count = q.rear - q.front;
	else count = q.front - q.rear;

	for (i = 0; i < count / 2; i++) {
		t1 = delete_front(&q);
		t2 = delete_rear(&q);
		if (t1 == t2)
			continue;
		else {
			printf("회문이 아닙니다.");
			return;
		}
	}
	printf("회문입니다.");
}

int main(void) {
	char* s = "maam";
	palindrome(s);
}