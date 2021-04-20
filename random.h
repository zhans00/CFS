#include <stdlib.h>
#include <time.h>

#define MAX_PRIORITY 99
#define MAX_BURST 50

int generate_burst() {
	srand ( time(NULL) );
	return 1 + rand() % MAX_BURST; 
}

int generate_priority() {
    srand ( time(NULL) );
	return 1 + rand() % MAX_PRIORITY; 
}

// int generate_arrival() {
// timeslice = scheduling period * (task's weight/total weight of tasks in the run queue');
// }