#include <stdio.h>

typedef struct process
{
	unsigned int left_time;
	unsigned int start_time;
	unsigned int waiting_time;
	unsigned int response_time;
	int priority;

} process;

typedef struct gclock
{
	unsigned int ticks;
} gclock;

int get_pr(int priors[], int start, int end) {
	int sum = 0;
	for (int i = start; i < end; i++) {
		sum += priors[i];
	}

	return sum;
}
