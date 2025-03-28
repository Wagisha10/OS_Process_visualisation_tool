#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

#define MAX_PROCESSES 5
#define TIME_QUANTUM 1 // Simulated time unit


typedef enum { READY, RUNNING, WAITING, TERMINATED } State;


typedef struct {
    int pid;          
    State st;       
    int arrival_time;  
    int burst_time;    
    int remaining_time;
} Process;


void init_process(Process *p, int pid, int arrival, int burst) {
    p->pid = pid;
    p->st = READY;
    p->arrival_time = arrival;
    p->burst_time = burst;
    p->remaining_time = burst;
}


void display_processes(Process *processes, int num_processes, int current_time) {
    system("clear"); 
    printf("\nTime: %d\n", current_time);
    printf("PID\tState\t\tArrival\tBurst\tRemaining\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t", processes[i].pid);
        switch (processes[i].st) {
            case READY: printf("Ready\t\t"); break;
            case RUNNING: printf("Running\t\t"); break;
            case WAITING: printf("Waiting\t\t"); break;
            case TERMINATED: printf("Terminated\t"); break;
        }
        printf("%d\t%d\t%d\n", processes[i].arrival_time, processes[i].burst_time, processes[i].remaining_time);
    }
    printf("\n");
}


void simulate_processes(Process *processes, int num_processes) {
    int current_time = 0;
    int completed = 0;

    while (completed < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].st != TERMINATED) {
                if (processes[i].st == READY) {
                    processes[i].st = RUNNING; 
                }
                if (processes[i].st == RUNNING) {
                    processes[i].remaining_time -= TIME_QUANTUM;
                    if (processes[i].remaining_time <= 0) {
                        processes[i].st = TERMINATED; 
                        completed++;
                    } else if (rand() % 10 < 2) { // Randomly move to Waiting (20% chance)
                        processes[i].st = WAITING;
                    }
                } else if (processes[i].st == WAITING) {
                    if (rand() % 10 < 3) {
                        processes[i].st = READY;
                    }
                }
            }
        }
        display_processes(processes, num_processes, current_time);
        sleep(1);
        current_time += TIME_QUANTUM;
    }
}

int main() {
    srand(time(NULL)); 
    Process processes[MAX_PROCESSES];

    
    init_process(&processes[0], 1, 0, 5);
    init_process(&processes[1], 2, 1, 3);
    init_process(&processes[2], 3, 2, 4);
    init_process(&processes[3], 4, 3, 2);
    init_process(&processes[4], 5, 4, 6);

    printf("Starting Process Visualization Tool...\n");
    sleep(2); 
    simulate_processes(processes, MAX_PROCESSES);

    printf("All the processes are completed!\n");
    return 0;
}
