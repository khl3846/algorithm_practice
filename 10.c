#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType* q) {
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
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

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[q->front + 1] % MAX_QUEUE_SIZE;
}

void fib(QueueType* q, int n) {
	int t1, t2;
	if (n == 0)
		return printf("0");
	else if (n == 1)
		return printf("1");
	else {
		for (int i = 2; i <= n; i++) {
			t1 = dequeue(q);
			t2 = dequeue(q);
			enqueue(q, t2);
			enqueue(q, t1 + t2);
			printf("%d + %d = %d\n", t1, t2, t1 + t2);
		}
	}
}

int main(void) {
	QueueType q;
	init_queue(&q);

	enqueue(&q, 0);
	enqueue(&q, 1);

	fib(&q, 10);
}