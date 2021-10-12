# CFS

A simple simulator of Completely Fair Scheduler (CFS). CFS is is the default scheduler of the Linux kernel tasks of the SCHED_NORMAL class (i.e., tasks that have no real-time execution constraints).

## How to run:
    1) to generate random values, provide the number of processes as argument. 
        For example, $ gcc main.c -o main.out
                     $ ./main.out 5
        Here, 5 is the number of processes.
    2) to run with specific values, provide two arguments: 
        "-file" and the name of the .txt file with processes.
        For example, $ gcc main.c -o main.out
                     $ ./main.out -file processes.txt
    Structure of the .txt file is the following:
    The first line: the number of processes
    Next n lines: priority, burst time, and arrival time. (they must be valid positive integers: 
        priority in range [1-99] )
    For example:
        3
        12 34 4 
        34 46 7 
        7 23 9
    Here, priorities - 12, 34, 7; burst times - 34, 46, 23; arrival times - 4, 7, 9 for the 1st, 2nd and 3rd processes respectively.
