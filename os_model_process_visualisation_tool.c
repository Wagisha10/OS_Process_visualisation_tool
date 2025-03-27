#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For sleep() function (Linux/Unix); use <windows.h> for Windows

#define MAX_PROCESSES 5
#define TIME_QUANTUM 1 // Simulated time unit

// Process states
typedef enum { READY, RUNNING, WAITING, TERMINATED } State;

// Process structure
typedef struct {
    int pid;           // Process ID
    State state;       // Current state
    int arrival_time;  // Time when process arrives
    int burst_time;    // Total execution time required
    int remaining_time;// Remaining time to complete
} Process;

// Function to initialize a process
void init_process(Process *p, int pid, int arrival, int burst) {
    p->pid = pid;
    p->state = READY;
    p->arrival_time = arrival;
    p->burst_time = burst;
    p->remaining_time = burst;
}

// Function to display process states
void display_processes(Process *processes, int num_processes, int current_time) {
    system("clear"); // Use "cls" for Windows
    printf("\nTime: %d\n", current_time);
    printf("PID\tState\t\tArrival\tBurst\tRemaining\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t", processes[i].pid);
        switch (processes[i].state) {
            case READY: printf("Ready\t\t"); break;
            case RUNNING: printf("Running\t\t"); break;
            case WAITING: printf("Waiting\t\t"); break;
            case TERMINATED: printf("Terminated\t"); break;
        }
        printf("%d\t%d\t%d\n", processes[i].arrival_time, processes[i].burst_time, processes[i].remaining_time);
    }
    printf("\n");
}

// Simulate process execution
void simulate_processes(Process *processes, int num_processes) {
    int current_time = 0;
    int completed = 0;

    while (completed < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].state != TERMINATED) {
                if (processes[i].state == READY) {
                    processes[i].state = RUNNING; // Move to Running
                }
                if (processes[i].state == RUNNING) {
                    processes[i].remaining_time -= TIME_QUANTUM;
                    if (processes[i].remaining_time <= 0) {
                        processes[i].state = TERMINATED; // Process completed
                        completed++;
                    } else if (rand() % 10 < 2) { // Randomly move to Waiting (20% chance)
                        processes[i].state = WAITING;
                    }
                } else if (processes[i].state == WAITING) {
                    if (rand() % 10 < 3) { // 30% chance to move back to Ready
                        processes[i].state = READY;
                    }
                }
            }
        }
        display_processes(processes, num_processes, current_time);
        sleep(1); // Pause for 1 second to simulate time (Linux/Unix)
        current_time += TIME_QUANTUM;
    }
}

int main() {
    srand(time(NULL)); // Seed random number generator
    Process processes[MAX_PROCESSES];

    // Initialize sample processes (PID, Arrival Time, Burst Time)
    init_process(&processes[0], 1, 0, 5);
    init_process(&processes[1], 2, 1, 3);
    init_process(&processes[2], 3, 2, 4);
    init_process(&processes[3], 4, 3, 2);
    init_process(&processes[4], 5, 4, 6);

    printf("Starting Process Visualization Tool...\n");
    sleep(2); // Pause before starting
    simulate_processes(processes, MAX_PROCESSES);

    printf("All processes completed!\n");
    return 0;
}