#include <stdio.h>

typedef struct process
{
	unsigned int left_time;
	unsigned int start_time;
	unsigned int waiting_time;
	unsigned int response_time;
	int priority;

} process;