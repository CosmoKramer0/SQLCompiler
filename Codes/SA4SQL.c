#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to check if the input string matches the expected SQL syntax
bool checkSQLSyntax(char *query) {
    // Find positions of keywords
    char *selectPos = strstr(query, "SELECT");
    char *fromPos = strstr(query, "FROM");
    char *wherePos = strstr(query, "WHERE");

    // Check if all keywords are present
    if (selectPos == NULL || fromPos == NULL || wherePos == NULL) {
        printf("Syntax error: Missing required SQL keyword\n");
        return false;
    }

    // Check if keywords are in correct order
    if (selectPos > fromPos || fromPos > wherePos) {
        printf("Syntax error: Keywords are not in the correct order\n");
        return false;
    }

    // Check if there are columns specified between SELECT and FROM
    if (strstr(query, ",") == NULL || strstr(query, ",") > fromPos) {
        printf("Syntax error: No columns specified between SELECT and FROM\n");
        return false;
    }

    // Check if there's a condition specified after WHERE
    if (wherePos - fromPos <= strlen("FROM")) {
        printf("Syntax error: No condition specified after WHERE\n");
        return false;
    }

    // Check if the query ends with a semicolon
    int queryLength = strlen(query);
    if (query[queryLength - 1] != ';') {
        printf("\nSyntax error: Missing semicolon at the end of the query. Please add (;)\n");
        return false;
    }

    // Syntax appears to be valid
    return true;
}

int main() {
    // Open the file for reading
    FILE *file = fopen("Query.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read the query from the file
    char query[1000]; // Assuming maximum query length of 1000 characters
    fgets(query, sizeof(query), file);

    // Close the file
    fclose(file);

    // Check syntax
    bool syntaxValid = checkSQLSyntax(query);

    // Write syntax analysis output to a text file
    FILE *outputFile = fopen("syntax_analysis_output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    if (syntaxValid) {
        fprintf(outputFile, "Syntax Analysis Successful! \nYou may now proceed with Intermediate Code Generation...");
    } else {
        fprintf(outputFile, "Syntax Analysis Failed!");
    }

    // Close the output file
    fclose(outputFile);

    return 0;
}
