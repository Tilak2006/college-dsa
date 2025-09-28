#include <stdio.h>

#define max_jobs 100

int getMaxDeadline(int deadlines[], int n) {
    int max = 0;
    for (int i = 0; i < n; ++i) {
        if (deadlines[i] > max) {
            max = deadlines[i];
        }
    }
    return max;
}

void sortJobs(int n, char ids[], int deadlines[], int profits[]) {
    for (int i = 0; i < n - 1; ++i) {
        int max_index = i;
        
        for (int j = i + 1; j < n; j++) {
            if (profits[j] > profits[max_index]) {
                max_index = j;
            }
        }
        
        if (max_index != i) {
            int temp_p = profits[i];
            profits[i] = profits[max_index];
            profits[max_index] = temp_p;

            int temp_d = deadlines[i];
            deadlines[i] = deadlines[max_index];
            deadlines[max_index] = temp_d;

            char temp_id = ids[i];
            ids[i] = ids[max_index];
            ids[max_index] = temp_id;
        }
    }
}

void job_sequencing(int n, char ids[], int deadlines[], int profits[]) {
    sortJobs(n, ids, deadlines, profits);

    int max_deadline = getMaxDeadline(deadlines, n); 
    
    int schedule[max_jobs];    
    for (int i = 0; i < max_deadline; ++i) {
        schedule[i] = -1;
    }

    int total_profit = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = deadlines[i] - 1; j >= 0; j--) {
            if (schedule[j] == -1) {
                schedule[j] = i; 
                total_profit += profits[i];
                break;
            }
        }
    }

    printf("\noptimal job sequence:\n");
    printf("time slot: ");
    for (int i = 0; i < max_deadline; ++i) {
        printf("%d | ", i + 1);
    }
    printf("\njob id:    ");
    for (int i = 0; i < max_deadline; ++i) {
        if (schedule[i] != -1) {
            printf("%c | ", ids[schedule[i]]);
        } else {
            printf("- | ");
        }
    }
    printf("\n\ntotal profit: %d\n", total_profit);
}

int main() {
    int n;
    
    char ids[max_jobs];
    int deadlines[max_jobs];
    int profits[max_jobs];

    printf("enter the number of jobs (max %d): ", max_jobs);
    scanf("%d", &n);

    if (n <= 0 || n > max_jobs) {
        printf("invalid number of jobs. exiting.\n");
        return 1;
    }

    printf("\nenter job details (id, deadline, profit):\n");
    for (int i = 0; i < n; ++i) {
        printf("job %d (id, deadline, profit): ", i + 1);
        scanf(" %c %d %d", &ids[i], &deadlines[i], &profits[i]);
    }

    job_sequencing(n, ids, deadlines, profits);

    return 0;
}