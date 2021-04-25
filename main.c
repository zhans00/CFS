// #include <stdio.h>
// #include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "lib.h"
#include "random.h"

#define MIN_GRAN 1
#define LIMIT 1000
    
int quantum;
int start = 0;
int end = 0;

int get_pr(process procs[], int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += procs[i].priority;
    }

    return sum;
}

int get_q(process procs[], int num_proc){
    return MIN_GRAN*(get_pr(procs, 0, num_proc));
}

int get_timeslice(int prior, process procs[]) {
    return (quantum * prior)/get_pr(procs, start, end);
}


double get_weight(int prior) {
    return 45.0/prior;
}


int main(int argc, char* argv[])
{
    // RBNode  T_Nil_Node;
    // RBNode* T_Nil = &T_Nil_Node;
    RBNode *root = &nil_leaf;
    srand ( time(NULL) );
	int num_proc;

    if(argc > 1) {
    	num_proc = atoi(argv[1]);
    	// quantum = num_proc * MIN_GRAN;
    } else {
    	printf("Invalid number of processes.\n");
    	return 1;
    }

    gclock clock;
    process procs[num_proc];

    printf("*************************************************************************\n");
    printf("Processes list in the following order: arrival time, burst time, priority.\n");
    printf("**************************************************************************\n\n");

    for (int i = 0; i < num_proc; i++) {
        procs[i].priority = generate_priority();
        procs[i].left_time = generate_burst();
        procs[i].start_time = generate_arrival();
    }

    qsort(&procs, num_proc, sizeof(process), compare);
    for (int i = 0; i < num_proc; ++i) {
        printf("Process #%d: %d %d %d\n", i+1, procs[i].start_time, procs[i].left_time, procs[i].priority);
    }

    quantum = get_q(procs,num_proc);
    printf("quantum: %d\n",quantum );
    redBlackInsert(&root, &(procs[0]), 0);
    end +=1;
    clock.ticks = procs[0].start_time;
    bool finished = false;
    int counter =0;

    while(!finished) {
        counter +=1;
        while (end < num_proc && clock.ticks == procs[end].start_time) {
            RBNode* t = redBlackInsert(&root, &(procs[end]), 0);
            end +=1;
        }
        clock.ticks +=1;
        if(root != &nil_leaf){
        RBNode* temp = delete(&root);
        RBNode temp2 = *temp;
        int timeslice = get_timeslice(temp->process->priority, procs);
        int release;
        bool reinsert = false;
        if (temp->process->left_time <= timeslice) {
            release = clock.ticks + temp->process->left_time - 1;
            temp->process->left_time = 0;
            start +=1;
            if(start == num_proc) {
                finished = true;
                break;
            }
            reinsert = false;

        } else {
            release = clock.ticks + timeslice - 1;
            temp->process->left_time -= timeslice;
            temp->vruntime += (timeslice*get_weight(temp->process->priority));
            reinsert = true;
        }
        while(clock.ticks != release) {
            while (end < num_proc && clock.ticks == procs[end].start_time) {
                RBNode *t = redBlackInsert(&root, &(procs[end]), 0);
                // printf("inserted: %d", t->process->start_time);
                end +=1;
            }
            clock.ticks +=1;
        }
        if (reinsert){
            redBlackInsert(&root, (temp2.process), temp2.vruntime);
        }
        // printTree(root);
        // printf("\n");
    }
}



    // for (int i = 0; i < num_proc; i++) {
    //     printf("%d %d %d\n", procs[i].priority, procs[i].left_time, procs[i].start_time);
    // }
    return 0;
}
