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
int num_proc;

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

void add_response(process procs[]) {
    for (int i = start; i < end; ++i) {
        if(!(&procs[i])->runned){
            (&procs[i])->response_time +=1;
        }
    }
}

void add_wait(process procs[]) {
    for (int i = start; i < end; ++i) {
        (&procs[i])->waiting_time +=1;
    }
}


int main(int argc, char* argv[])
{

    RBNode *root = &nil_leaf;
    srand ( time(NULL) );

    if(argc > 1) {
    	num_proc = atoi(argv[1]);
    	// quantum = num_proc * MIN_GRAN;
    } else {
    	printf("Invalid number of processes.\n");
    	return 1;
    }

    gclock clock;
    process procs[num_proc];
    bool reinsert;

    printf("**************************************\n");
    printf("*           Processes list.          *\n");
    printf("**************************************\n\n");

    for (int i = 0; i < num_proc; i++) {
        // procs[i].priority = generate_priority();
        // procs[i].left_time = generate_burst();
        // procs[i].start_time = generate_arrival();
        procs[i].preempted = 0;
        procs[i].response_time = 0;
        procs[i].waiting_time = 0;
        procs[i].runned = false;
        procs[i].priority = 1;
        procs[i].left_time = 1;
        procs[i].start_time = 1;
    }

    qsort(&procs, num_proc, sizeof(process), compare);
    for (int i = 0; i < num_proc; ++i) {
        printf("Process #%d: %d (arrival), %d (burst), %d (prio)\n", i+1, procs[i].start_time, procs[i].left_time, procs[i].priority);
    }

    quantum = get_q(procs,num_proc);
    printf("q: %d\n",quantum );
    clock.ticks = 0;
    bool finished = false;

    // redBlackInsert(&root, &(procs[0]), 0);
    // end +=1;

    while(!finished) {
        while (end < num_proc && clock.ticks == procs[end].start_time) {
            RBNode* t = redBlackInsert(&root, &(procs[end]), 0);
            end +=1;
        }
        if(root == &nil_leaf)
            clock.ticks +=1;
        else {
        RBNode* temp = delete(&root);
        RBNode temp2 = *temp;
        int timeslice = get_timeslice(temp->process->priority, procs);
        int release;
        temp->process->runned = true;
        if (temp->process->left_time <= timeslice) {
            release = clock.ticks + temp->process->left_time;
            temp->vruntime += (temp->process->left_time*get_weight(temp->process->priority));
            temp->process->left_time = 0;
            start +=1;
            if(start == num_proc) {
                finished = true;
                break;
            }
            reinsert = false;

        } else {
            release = clock.ticks + timeslice;
            temp->process->left_time -= timeslice;
            temp->vruntime += (timeslice*get_weight(temp->process->priority));
            reinsert = true;
            temp->process->preempted +=1;
        }
        printf("%d %d\n",clock.ticks, release );
        while(clock.ticks != release) {
            add_response(procs);
            add_wait(procs);
            while (end < num_proc && clock.ticks == procs[end].start_time) {
                    redBlackInsert(&root, &(procs[end]), 0);
                    end +=1;
            }
            clock.ticks +=1;
        }
        if (reinsert){
            redBlackInsert(&root, (temp2.process), temp2.vruntime);
        }
    }
}



    for (int i = 0; i < num_proc; i++) {
        printf("%d(PR) %d(P) %d(S) %d(R)\n", procs[i].priority, procs[i].preempted, procs[i].start_time, procs[i].response_time);
    }
    return 0;
}
