#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Defining constants
#define MAX_NODES 1000
#define DAMPING_FACTOR 0.85
#define EPSILON 0.0001

// Defining global variables
int num_nodes;
int adj_list[MAX_NODES][MAX_NODES];
int out_degree[MAX_NODES];
double page_rank[MAX_NODES];

// Function prototypes
void read_input_file(char *filename);
void calculate_page_rank();
void output_page_rank(char *filename, struct tm *start_time, struct tm *end_time);
int compare(const void *a, const void *b);

// Read input file and initialize the graph
void read_input_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", &num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        out_degree[i] = 0;
        for (int j = 0; j < num_nodes; j++) {
            adj_list[i][j] = 0;
        }
    }

    int src, dst;
    while (fscanf(file, "%d %d", &src, &dst) != EOF) {
        if (src >= 0 && src < num_nodes && dst >= 0 && dst < num_nodes) {
            adj_list[src][dst] = 1;
            out_degree[src]++;
        }
    }

    fclose(file);
}

// Calculate PageRank for each node
void calculate_page_rank() {
    double new_page_rank[MAX_NODES];
    double damping_term = (1.0 - DAMPING_FACTOR) / num_nodes;

    int iterations = 0;
    double diff = 1.0;
    while (diff > EPSILON) {
        iterations++;
        double sum = 0.0;
        for (int i = 0; i < num_nodes; i++) {
            new_page_rank[i] = 0.0;
            for (int j = 0; j < num_nodes; j++) {
                if (adj_list[j][i]) {
                    new_page_rank[i] += page_rank[j] / out_degree[j];
                }
            }

            new_page_rank[i] *= DAMPING_FACTOR;
            new_page_rank[i] += damping_term;
            sum += new_page_rank[i];
        }
        diff = 0.0;

        for (int i = 0; i < num_nodes; i++) {
            new_page_rank[i] += (1.0 - sum) / num_nodes;
            diff += fabs(new_page_rank[i] - page_rank[i]);
            page_rank[i] = new_page_rank[i];
        }
    }
}

// Output PageRank to a file
void output_page_rank(char *filename, struct tm *start_time, struct tm *end_time) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        exit(1);
    }

    // Prepare for sorting
    typedef struct {
        int page;
        double rank;
        int out_deg;
    } Page;

    Page pages[MAX_NODES];
    for (int i = 0; i < num_nodes; i++) {
        pages[i].page = i;
        pages[i].rank = page_rank[i];
        pages[i].out_deg = out_degree[i];
    }

    qsort(pages, num_nodes, sizeof(Page), compare);

    fprintf(file, "Damping Factor: %f\n", DAMPING_FACTOR);
    fprintf(file, "Epsilon: %f\n", EPSILON);
    fprintf(file, "Number of nodes: %d\n\n", num_nodes);

    fprintf(file, "Page Rank of each page in descending order:\n");
    for (int i = 0; i < num_nodes; i++) {
        fprintf(file, "Page %d: Page Rank = %f\tOut Degree = %d\n",
                pages[i].page, pages[i].rank, pages[i].out_deg);
    }

    fprintf(file, "\nStart time: %d:%d:%d\n", start_time->tm_hour, start_time->tm_min, start_time->tm_sec);
    fprintf(file, "End time: %d:%d:%d\n", end_time->tm_hour, end_time->tm_min, end_time->tm_sec);

    // Time taken to calculate the page rank
    double time_taken = difftime(mktime(end_time), mktime(start_time));
    fprintf(file, "Time taken to calculate the page rank: %f seconds\n\n", time_taken);

    fprintf(file, "Time Complexity: O(n^2)\n");

    fclose(file);
}

// Comparator function for qsort
int compare(const void *a, const void *b) {
    Page *pageA = (Page *)a;
    Page *pageB = (Page *)b;
    return (pageB->rank > pageA->rank) - (pageB->rank < pageA->rank);
}

// Main function
int main(int argc, char *argv[]) {
    time_t start, end;
    struct tm *start_time, *end_time;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    read_input_file(argv[1]);

    start = time(NULL);
    start_time = localtime(&start);

    for (int i = 0; i < num_nodes; i++) {
        page_rank[i] = 1.0 / num_nodes;
    }

    calculate_page_rank();

    end = time(NULL);
    end_time = localtime(&end);

    for (int i = 0; i < num_nodes; i++) {
        printf("Page %d: Page Rank = %f\n", i, page_rank[i]);
    }

    printf("Output written to %s\n", argv[2]);
    output_page_rank(argv[2], start_time, end_time);

    return 0;
}


