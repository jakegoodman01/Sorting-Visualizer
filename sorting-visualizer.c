// This program visualizes sorting algorithms

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sorts.c"

#define N 28
#define WINDOW_HEIGHT 25
#define ARRAY_HEIGHT 20
#define DELAY 15

void visualize_array(int *arr);
void delay(int ml);


int main(void) {	
	int arr[N];
	for (int i = 0; i < N; i++)
		arr[i] = rand() % ARRAY_HEIGHT;

	int arr_cpy[N];
	for (int i = 0; i < N; i++)
		arr_cpy[i] = arr[i];
	visualize_array(arr);
	delay(DELAY);

	struct queue *animations = insertion_sort_animations(arr_cpy, N);
	while (!queue_is_empty(animations)) {
		visualize_array(arr);
		struct pair *to_swap = pop(animations);
		int i = to_swap->arr[0];
		int j = to_swap->arr[1];
		if (j != -1)
			swap(&arr[i], &arr[j]);
		delay(DELAY);
	}
	visualize_array(arr);
	
}

void delay(int ml) {
	long pause;
	clock_t now, then;
	pause = ml * (CLOCKS_PER_SEC/1000);
	now = then = clock();
	while ((now - then) < pause)
		now = clock();
}

void visualize_array(int *arr) {
	for (int i = WINDOW_HEIGHT; i > 0; i--) {
		printf("\t\t");
		for (int j = 0; j < N; j++) 
			if (arr[j] >= i)
				printf("|*");
			else
				printf("  ");
		printf("\n");
	}
	printf("\t\t");
	for (int j = 0; j < N; j++) 
		printf("%2d", arr[j]);
	printf("\n");
}