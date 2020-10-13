#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MEMORY_MODULE_NUM_MAX 2048
#define CYCLE_COUNT_MAX 1000000
#define TOLERANCE_VALUE 0.01

int cycle_count;
int num_of_processors;
char distribution_type;

void initialize_data_structures(int request[], int access_count[], int priority_of_connection[])
{
    // request = -1, access_count = 0, priority_of_connection [0, K-1]
    return;
}

void generate_requests(int request[], char distribution_type)
{
    // check distribution type
    // generate requests if not -1 
    return;
}

void process_requests()
{
    // for( int i to M-1) 
    //      find which processor requests this memory module
    //      compare the priority 
    //      update request[] to -1 if the processor's access is granted
    //      update priority_of_connection[K] and memory_module[M]
    //      updata access_count[K]
    return;
}

void compute_time_cumulative_average(int cycle_count, int access_count[], int time_cumulative_average[])
{
    for( int i=0; i<num_of_processors; i++)
       time_cumulative_average[i] = cycle_count / access_count[i];
}

double compute_arithmetic_average_of_all(int time_cumulative_average[])
{
    double sum=0;
    for(int i=0;i<num_of_processors;i++){
        sum += time_cumulative_average[i];
    }
    return sum/num_of_processors;
}

void write_result(int memory_module_num, double cur_arithmetic_average)
{
    FILE* fp;
    fp = fopen("output.csv", "a");

    // test
    memory_module_num = 1;
    cur_arithmetic_average = 2.5555555555;

    char cur_arithmetic_aver_string[sizeof(cur_arithmetic_average)];
    memcpy(cur_arithmetic_aver_string, &cur_arithmetic_average, sizeof(cur_arithmetic_average));
    
    // fprintf(fp, memory_module_num); 
    fprintf(fp, ","); 
    fprintf(fp, "jwuhaha");
    fprintf(fp, "\n");
    // fprintf(fp, cur_arithmetic_aver_string);
    // fprintf(fp, cur_arithmetic_aver_string);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    if(argc == 3) {
        num_of_processors = atoi(argv[1]);
        distribution_type = argv[2][0];
        int request[num_of_processors];
        int access_count[num_of_processors];
        int priority_of_connection[num_of_processors];

        printf("num of processors: %d\n", num_of_processors);
        printf("distribution type: %c\n", distribution_type);

        // Initialize data structures
        initialize_data_structures(&request, &access_count, &priority_of_connection);

        for(int i=1; i<=MEMORY_MODULE_NUM_MAX;i++) {   // run 2048 times simulation
            cycle_count = 0;
            double cur_arithmetic_average;
            double prev_arithmetic_average = cur_arithmetic_average;
            while(1) {      // for each simulation
                cycle_count = cycle_count+1;

                // 0. run a simulation algorithm:
                // - assign each processor a memory module num ( either by 'uniform' or 'normal' distribution )
                generate_requests(&request, distribution_type);
                process_requests();
                
                // 1. compute the time-cumulative average of the access-time for each processor
                //     ( The time-cumulative average of a processor’s memory access at cycle c
                //         = the total # of simulated memory cycles c / the total # of granted accesses so far )
                //     time-cumulative average of a processor's memory access at cycle c = c / access_count[ith_idx]
                int time_cumulative_average[num_of_processors];
                compute_time_cumulative_average(cycle_count, &access_count, &time_cumulative_average);
                    
                // 2. compute the arithmetic average W(Sc(p, m, d)) of all processors’ time-cumulative averages
                // W(Sc(p, m, d)) = sum of time-cumulative averages of all processors / K: {2, 4, 8, 16, 32, 64}
                cur_arithmetic_average = compute_arithmetic_average_of_all(&time_cumulative_average);
                
                // if( c == 10^6 OR abs( 1-W(Sc-1(p, mi, d)) /  W(Sc(p, mi, d)) < E (1%-3%)
                //     break;
                // }
                if( cycle_count == CYCLE_COUNT_MAX || abs(1 - prev_arithmetic_average / cur_arithmetic_average) < TOLERANCE_VALUE ) 
                    break;
            
            }
            write_result(i, cur_arithmetic_average);
        }
    }
    return 0;
}