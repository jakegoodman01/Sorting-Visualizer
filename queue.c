// This module provides the implementation of a FIFO queue of "struct pair"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 1024
#define PAIR 2

/* 						Defines struct pair 		 			  */
/* Used for animating sorts. If either value in arr is -1, it is  */
/* considered uninitialized. Otherwise, it indicates the array    */
/* index to color-fill during a sorting visualization			  */
struct pair {
	int arr[PAIR];
};

/* empty_pair() produces a pointer to the pair: [0, 0] */
struct pair *empty_pair(void) {
	struct pair *p = malloc(sizeof(struct pair));
	p->arr[0] = -1;
	p->arr[1] = -1;
	return p;
}

/* make_pair(a, b) produces a pointer to the pair: [a, b] */
struct pair *make_pair(int a, int b) {
	struct pair *p = malloc(sizeof(struct pair));
	p->arr[0] = a;
	p->arr[1] = b;
	return p;
}

/* prints a pair */
void print_pair(struct pair *p) {
	printf("[%d, %d]", p->arr[0], p->arr[1]);
}

/* defines struct queue */
struct queue {
	struct pair *pairp[MAX_LEN]; /* array of pair pointers */
	int first; 					 /* inclusive 			   */
	int last;  					 /* not inclusive 		   */
};

/* empty_queue() produces a new empty queue */
struct queue *empty_queue(void) {
	struct queue *q = malloc(sizeof(struct queue));
	for (int i = 0; i < MAX_LEN; i++) 
		q->pairp[i] = empty_pair();
	q->first = 0;
	q->last = 0;
	return q;
}

/* queue_is_empty(queue) produces true if queue is empty, false otherwise */
bool queue_is_empty(const struct queue *queue) {
	return queue->last == queue->first;
}

/* push(pair, queue) pushes pair onto the end of queue */
/* requires: queue is under maximum capacity           */
void push(struct pair *pair, struct queue *q) {
	assert(q->last - q->first + 1 < MAX_LEN);
	q->pairp[q->last++] = pair;
	if (q->last == MAX_LEN)
		for (int i = q->first; i < q->last; i++) 
			q->pairp[i - q->first] = q->pairp[i]; /* adjust everything to the start of pairp[] */
}

/* pop(queue) pops (and produces) the first element of queue */
/* requires: queue is not empty 							 */
struct pair *pop(struct queue *q) {
	assert(q->last - q->first);
	return q->pairp[q->first++];
}

/* print_queue(queue) prints the contents of queue */
void print_queue(const struct queue *q) {
	if (queue_is_empty(q)) {
		printf("[]\n");
	} else {
		printf("[");
		print_pair(q->pairp[q->first]);
		for (int i = q->first + 1; i < q->last; i++) {
			printf(", "); 
			print_pair(q->pairp[i]);
		}
		printf("]\n");
	}
}



