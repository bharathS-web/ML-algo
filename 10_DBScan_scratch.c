#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 100

// Distance function using Manhattan distance
double dist(double *x, double *y, int dim) {
    double d = 0.0;
    for (int i = 0; i < dim; i++) {
        d += fabs(x[i] - y[i]);
    }
    return d; 
}

// Function to calculate the distance matrix
void dist_mat(double points[][2], double dist_mat[MAX_POINTS][MAX_POINTS], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist_mat[i][j] = dist(points[i], points[j], 2);
        }
    }
}

// DBSCAN Scratch function
void DBscan_scratch(double points[][2], int n, double eps, int minpt) {
    double dist_matrix[MAX_POINTS][MAX_POINTS];
    dist_mat(points, dist_matrix, n);

    int core[MAX_POINTS], core_count = 0;
    int border[MAX_POINTS], border_count = 0;
    int outlier[MAX_POINTS], outlier_count = 0;

    // Table to store information about core, border, and outliers
    int table[MAX_POINTS][3];  // [ [neighbors, count, status] ]

    // Initialize the table
    for (int i = 0; i < n; i++) {
        table[i][1] = 1;  // Start with 1 (the point itself)
        table[i][2] = -1; // Initially mark all points as noise
    }

    // Find core points
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist_matrix[i][j] <= eps) {
                table[i][1]++;  // Count the neighbors
            }
        }
        if (table[i][1] >= minpt) {
            table[i][2] = 1;  // Mark as core point
            core[core_count++] = i;
        }
    }

    // Identify border and outlier points
    for (int i = 0; i < n; i++) {
        if (table[i][2] != 1) {  // If not a core point
            for (int j = 0; j < n; j++) {
                if (dist_matrix[i][j] <= eps && table[j][2] == 1) {
                    table[i][2] = 0;  // Mark as border
                    border[border_count++] = i;
                    break;
                }
            }
            if (table[i][2] == -1) {  // If still noise
                outlier[outlier_count++] = i;
            }
        }
    }

    // Print the result
    printf("Core Points: ");
    for (int i = 0; i < core_count; i++) {
        printf("%d ", core[i]);
    }
    printf("\nBorder Points: ");
    for (int i = 0; i < border_count; i++) {
        printf("%d ", border[i]);
    }
    printf("\nOutliers: ");
    for (int i = 0; i < outlier_count; i++) {
        printf("%d ", outlier[i]);
    }
    printf("\n");
}

int main() {
    double datapoints[][2] = {
        {1, 1}, {1, 2}, {5, 7},
        {3, 1}, {3, 3}, {6, 6},
        {18, 4}, {18, 3}, {7, 6},
        {4, 3}, {4, 7}, {2, 2},
        {8, 6}, {8, 7}, {9, 6}
    };
    int n = sizeof(datapoints) / sizeof(datapoints[0]);

    double eps = 2.0;
    int minpt = 3;

    DBscan_scratch(datapoints, n, eps, minpt);

    return 0;
}
