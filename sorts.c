
// This module provides sorting functions

#include <stdio.h>
#include <stdlib.h>
#include "queue.c"

#define MAIN 0
#define BOOL int /* either TRUE or FALSE */
#define TRUE 1
#define FALSE 0

void bubble_sort(int *arr, int length);
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
	bubble_sort(arr, length);
	print_array(arr, length);
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

// bubble_sort(arr, length) performs bubble sort on arr
// requires: length >= 0
void bubble_sort(int *arr, int length) {
	assert(length >= 0);
	BOOL sorted = FALSE;
	while (!sorted) {
		BOOL made_swap = FALSE;
		for (int i = 0; i < length - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(&arr[i], &arr[i + 1]);
				made_swap = TRUE;
			}
		}
		sorted = !made_swap;
	}
}

// bubble_sort_animations(arr, length) produces a pointer to a queue which contains
//  the indicies to be swapped for the animation of bubble sort
// requires: length >= 0
struct queue *bubble_sort_animations(int *arr, int length) {
	assert(length >= 0);
	struct queue *animations = empty_queue();
	BOOL sorted = FALSE;
	int num_passes = 0;
	while (!sorted) {
		BOOL made_swap = FALSE;
		for (int i = 0; i < length - 1 - num_passes; i++) {
			if (arr[i] > arr[i + 1]) {
				push(make_pair(i, i + 1), animations);
				swap(&arr[i], &arr[i + 1]);
				made_swap = TRUE;
			} else 
				push(make_pair(i, -1), animations);
		}
		num_passes++;
		sorted = !made_swap;
	}
	return animations;
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
//  the indicies to be swapped for the animation of insertion sort
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










