// This program visualizes sorting algorithms

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "sorts.c"

#define N 35
#define WINDOW_HEIGHT 30
#define ARRAY_HEIGHT 20
#define DELAY 10

void visualize_array(int *arr);
void delay(int ml);


/* Accepts exactly one command line argument which tells the program what sort to
   visualize. Can be one one: "insertion"..., */
int main(int argc, char *argv[]) {	
	assert(argc == 2);
	int arr[N];
	for (int i = 0; i < N; i++)
		arr[i] = rand() % ARRAY_HEIGHT;

	int arr_cpy[N];
	for (int i = 0; i < N; i++)
		arr_cpy[i] = arr[i];

	struct queue *animations = NULL;
	char *cmd = argv[1];
	if (strcmp(cmd, "insertion") == 0)
		animations = insertion_sort_animations(arr_cpy, N);
	else {
		printf("Invalid sort: %s\n", cmd);
		exit(EXIT_SUCCESS);
	}

	visualize_array(arr);
	delay(DELAY);
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