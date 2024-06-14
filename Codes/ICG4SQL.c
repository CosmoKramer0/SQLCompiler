#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for SQL query components
typedef struct {
    char* table;
    char* column;
} Scan;

typedef struct {
    char* column;
    char* op;
    int value;
} Filter;

typedef struct {
    char* column1;
    char* column2;
} Project;

// Function to generate intermediate code
void generateIntermediateCode(Scan scan, Filter filter, Project project, FILE *outputFile) {
    // Scan operation
    fprintf(outputFile, "Scan (%s)\n", scan.table);

    // Filter operation
    fprintf(outputFile, "\tFilter (WHERE %s %s %d)\n", filter.column, filter.op, filter.value);

    // Project operation
    fprintf(outputFile, "\t\tProject (%s, %s)\n", project.column1, project.column2);
}

int main() {
    FILE *fp, *outputFile;
    char query[255];

    // Open input file for reading
    fp = fopen("Query.txt", "r");
    if (fp == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read SQL query from file
    fgets(query, sizeof(query), fp);
    fclose(fp);

    // Open output file for writing
    outputFile = fopen("intermediate_code_output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        return 1;
    }

    // Parse SQL query
    char *token;
    char *delimiters = " ";
    char *columns[2];

    // Skip SELECT keyword
    strtok(query, delimiters);

    // Read columns
    for (int i = 0; i < 2; i++) {
        token = strtok(NULL, delimiters);
        columns[i] = strdup(token);
    }

    // Skip FROM keyword and table name
    strtok(NULL, delimiters);
    strtok(NULL, delimiters);

    // Skip WHERE keyword
    strtok(NULL, delimiters);

    // Read column for filter
    token = strtok(NULL, delimiters);
    char* filterColumn = strdup(token);

    // Read operator
    token = strtok(NULL, delimiters);
    char* op = strdup(token);

    // Read value
    token = strtok(NULL, delimiters);
    int value = atoi(token);

    // Create query components
    Scan scan = {"employees", NULL};
    Filter filter = {filterColumn, op, value};
    Project project = {columns[0], columns[1]};

    // Generate intermediate code and write to output file
    generateIntermediateCode(scan, filter, project, outputFile);

    // Close output file
    fclose(outputFile);

    // Free allocated memory
    free(filterColumn);
    free(op);
    for (int i = 0; i < 2; i++) {
        free(columns[i]);
    }

    printf("\nIntermediate Code Generated Successfully!\n");
    return 0;
}
