#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"

int main()
{
    srand(time(NULL)); // Inicializa a seed para aleatoriedade

    int count = 5;
    double lambda_arrival = 3.0; // controla frequência de chegada (Poisson)
    double lambda_burst = 0.5;   // controla variação de burst time (Exponencial)
    int max_priority = 5;
    int quantum = 2;

    printf("=== Processos Estáticos ===\n");
    Process *static_list = generate_static_processes(count);
    print_processes(static_list, count);
    free_processes(static_list);

    printf("\n=== Processos Aleatórios ===\n");
    Process* random_list = generate_random_processes(count, lambda_arrival, lambda_burst, max_priority);
    print_processes(random_list, count);
    free_processes(random_list);


    printf("\n=== Escalonamento FCFS (First Come First Serve) ===\n");
    Process* fcfs_list = generate_static_processes(count); // ou generate_random_processes
    print_processes(fcfs_list, count);

    Stats fcfs_stats = simulate_fcfs(fcfs_list, count);
    printf("Tempo médio de espera: %.2f\n", fcfs_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", fcfs_stats.avg_turnaround_time);
    free_processes(fcfs_list);


    printf("\n=== Escalonamento SJF (Shortest Job First) ===\n");
    Process* sjf_list = generate_static_processes(count); 
    print_processes(sjf_list, count);

    Stats sjf_stats = simulate_sjf(sjf_list, count);
    printf("Tempo médio de espera: %.2f\n", sjf_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", sjf_stats.avg_turnaround_time);
    free_processes(sjf_list);


    printf("\n=== Escalonamento Round-Robin (RR) ===\n");
    Process* rr_list = generate_static_processes(count); 
    print_processes(rr_list, count);

    Stats rr_stats = simulate_rr(rr_list, count, quantum);
    printf("Tempo médio de espera: %.2f\n", rr_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", rr_stats.avg_turnaround_time);
    free_processes(rr_list);


    printf("\n=== Escalonamento Priority Não-Preemptivo ===\n");
    Process* priority_np_list = generate_static_processes(count);
    print_processes(priority_np_list, count);
    Stats priority_np_stats = simulate_priority_np(priority_np_list, count);
    printf("Tempo médio de espera: %.2f\n", priority_np_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", priority_np_stats.avg_turnaround_time);
    free_processes(priority_np_list);

    printf("\n=== Escalonamento Priority Preemptivo ===\n");
    Process* priority_p_list = generate_static_processes(count);
    print_processes(priority_p_list, count);
    Stats priority_p_stats = simulate_priority_p(priority_p_list, count);
    printf("Tempo médio de espera: %.2f\n", priority_p_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", priority_p_stats.avg_turnaround_time);
    free_processes(priority_p_list);


        printf("\n=== Escalonamento EDF (Earliest Deadline First) ===\n");
    Process* edf_list = generate_static_processes(count); 
    print_processes(edf_list, count);
    Stats edf_stats = simulate_edf(edf_list, count);
    printf("Tempo médio de espera: %.2f\n", edf_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", edf_stats.avg_turnaround_time);
    free_processes(edf_list);

    printf("\n=== Escalonamento Rate Monotonic (RMS) ===\n");

    // Define processos periódicos com período > 0
    Process periodic_list[] = {
        { .id = 0, .arrival_time = 0, .burst_time = 1, .remaining_time = 1, .priority = 1, .deadline = 4, .period = 4 },
        { .id = 1, .arrival_time = 0, .burst_time = 2, .remaining_time = 2, .priority = 2, .deadline = 5, .period = 5 },
        { .id = 2, .arrival_time = 0, .burst_time = 1, .remaining_time = 1, .priority = 3, .deadline = 8, .period = 8 }
    };

    int periodic_count = sizeof(periodic_list) / sizeof(Process);
    int simulation_time = 20;

    print_processes(periodic_list, periodic_count);

    RTStats rt_stats = simulate_rate_monotonic(periodic_list, periodic_count, simulation_time);
    printf("Total de processos periódicos: %d\n", rt_stats.total_processes);
    printf("Instâncias completadas: %d\n", rt_stats.completed);
    printf("Deadlines perdidos: %d\n", rt_stats.missed_deadlines);
    printf("Utilização da CPU: %.2f%%\n", rt_stats.cpu_utilization * 100);

    printf("\n=== Escalonamento Multilevel Queue (MLQ) ===\n");
    Process* mlq_list = generate_static_processes(count);
    print_processes(mlq_list, count);

    Stats mlq_stats = simulate_mlq(mlq_list, count, quantum);
    printf("Tempo médio de espera: %.2f\n", mlq_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", mlq_stats.avg_turnaround_time);
    free_processes(mlq_list);

    return 0; 
}


