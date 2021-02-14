
// This module provides sorting functions

#include <stdio.h>
#include <stdlib.h>
#include "queue.c"

#define MAIN 0

void insertion_sort(int *arr, int length);
struct queue *insertion_sort_animations(int *arr, int length);
void print_array(int *arr, int length);

#if MAIN
int main(void) {
	int arr[MAX_LEN];
	int length;
	printf("Enter a length: ");
	scanf("%d\n", &length);
	for (int i = 0; i < length; i++)
		scanf("%d", &arr[i]);
	struct queue *animations = insertion_sort_animations(arr, length);
	print_queue(animations);
	return 0;
}
#endif

// swap(p, q) swaps the values that p and q point to
// requires: p and q are valid pointers
void swap(int *p, int *q) {
	assert(p && q);
	int temp = *p;
	*p = *q;
	*q = temp;
}

// insertion_sort(arr, length) performs insertion sort on arr
// requires: length >= 0
void insertion_sort(int *arr, int length) {
	assert(length >= 0);
	for (int *p = arr; p < arr + length; p++) {
		while (p > arr && *(p - 1) > *p) {
			/* swap(--p, p + 1); */
			p--;						   
			swap(p, p + 1);			   
		}
	}
}

// insertion_sort_animations(arr, length) produces a pointer to a queue which contains
// requires: length >= 0
struct queue *insertion_sort_animations(int *arr, int length) {
	assert(length >= 0);
	struct queue *animations = empty_queue();
	/* i and j are the indices of arr */
	for (int i = 0; i < length; i++) {
		push(make_pair(i, -1), animations);
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) {
			push(make_pair(j, j + 1), animations);
			swap(&arr[j], &arr[j + 1]);
		}
	}
	return animations;
}

// print_array(arr) prints the contents of arr
void print_array(int *arr, int length) {
	int *p = arr;
	printf("[%d", *p);
	for (p++; p < arr + length; p++)
		printf(", %d", *p); 
	printf("]\n");
}










