// #include <stdio.h>
// #include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "lib.h"
#include "random.h"

#define MIN_GRAN 5
#define LIMIT 1000
    
int quantum;
int start = 0;
int end = 0;
RBNode *root = &nil_leaf;

int get_pr(process procs[]) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += procs[i].priority;
    }

    return sum;
}

int get_timeslice(int prior, process procs[]) {
    return (quantum * prior)/get_pr(procs);
}


double get_weight(int prior) {
    return 45.0/prior;
}


int main(int argc, char* argv[])
{
    srand ( time(NULL) );
	int num_proc;

    if(argc > 1) {
    	num_proc = atoi(argv[1]);
    	quantum = num_proc * MIN_GRAN;
    } else {
    	printf("Invalid number of processes.\n");
    	return 1;
    }

    gclock clock;
    process procs[num_proc];

    for (int i = 0; i < num_proc; i++) {
        procs[i].priority = generate_priority();
        procs[i].left_time = generate_burst();
        procs[i].start_time = generate_arrival();
    	// printf("%d %d %d\n", procs[i].priority, procs[i].left_time, procs[i].start_time);
    }


    qsort(procs, num_proc, sizeof(process), compare);
    redBlackInsert(&root, &(procs[0]));
    root->vruntime = 4;
    clock.ticks = procs[0].start_time;
    RBNode *temp = redBlackInsert(&root, &(procs[1]));
    delete(&root);

    


    for (int i = 0; i < num_proc; i++) {
        printf("%d %d %d\n", procs[i].priority, procs[i].left_time, procs[i].start_time);
    }

    printf("%d %d\n",root->process->start_time, root->vruntime);
    return 0;
}