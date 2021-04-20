#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rbt.h"
#include "random.h"

#define MIN_GRAN 5
#define LIMIT 1000


int main(int argc, char* argv[])
{
	int num_proc;
	int quantum;
	bool updated = false;
	int start = 0;
	int end = 0;

    if(argc > 1) {
    	num_proc = atoi(argv[1]);
    	quantum = num_proc * MIN_GRAN;
    } else {
    	printf("Invalid number of processes.\n");
    	return 0;
    }

    gclock clock;
    clock.ticks = 0;
    process procs[num_proc];

    for (int i = 0; i < num_proc; i++) {
    	printf("Enter (in the corrrect order) priority, burst time, and arrival time for  process #%d:\n", i+1);
    	scanf("%d %d %d", &(procs[i].priority), &(procs[i].left_time), &(procs[i].start_time));
    }

    return(0);

}