#include <stdlib.h>
#include <time.h>

#define MAX_PRIORITY 99
#define MAX_BURST 50
#define MAX_ARRIVAL 1000

int generate_burst() {
	return 1 + rand() % MAX_BURST; 
}

int generate_priority() {
	return 1 + rand() % MAX_PRIORITY; 
}

int generate_arrival() {
	return rand() % (MAX_ARRIVAL + 1);
}