#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    SYMBOL
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char *value;
} Token;

// Function to check if a character is a valid SQL symbol
int isSymbol(char c) {
    return strchr(",;()=*><+-/", c)!= NULL;
}

// Function to tokenize SQL query
Token* tokenizeSQL(char *query) {
    Token *tokens = malloc(sizeof(Token) * (strlen(query) + 1)); // Add one for the terminator token
    int tokenIndex = 0;
    int len = strlen(query);
    int i = 0;

    while (i < len) {
        // Skip whitespace
        while (isspace(query[i]))
            i++;

        // Check for end of query
        if (query[i] == '\0')
            break;

        // Check for symbols
        if (isSymbol(query[i])) {
            tokens[tokenIndex].type = SYMBOL;
            tokens[tokenIndex].value = malloc(2);
            tokens[tokenIndex].value[0] = query[i];
            tokens[tokenIndex].value[1] = '\0';
            tokenIndex++;
            i++;
            continue;
        }

        // Check for literals
        if (isdigit(query[i])) {
            int j = i;
            while (isdigit(query[j]))
                j++;
            tokens[tokenIndex].type = LITERAL;
            tokens[tokenIndex].value = malloc(j - i + 1);
            strncpy(tokens[tokenIndex].value, &query[i], j - i);
            tokens[tokenIndex].value[j - i] = '\0';
            tokenIndex++;
            i = j;
            continue;
        }

        // Check for identifiers or keywords
        if (isalpha(query[i])) {
            int j = i;
            while (isalnum(query[j]) || query[j] == '_')
                j++;
            char *temp = malloc(j - i + 1);
            strncpy(temp, &query[i], j - i);
            temp[j - i] = '\0';
            // Check if it's a keyword
            if (strcmp(temp, "SELECT") == 0 || strcmp(temp, "FROM") == 0 || strcmp(temp, "WHERE") == 0 || strcmp(temp, "AND") == 0 || strcmp(temp, "OR") == 0 || strcmp(temp, "NOT") == 0 || strcmp(temp, "IN") == 0 || strcmp(temp, "LIKE") == 0 || strcmp(temp, "BETWEEN") == 0 || strcmp(temp, "IS") == 0 || strcmp(temp, "NULL") == 0) {
                tokens[tokenIndex].type = KEYWORD;
            } else {
                tokens[tokenIndex].type = IDENTIFIER;
            }
            tokens[tokenIndex].value = temp;
            tokenIndex++;
            i = j;
            continue;
        }

        // Check for errors
        // For simplicity, we'll treat any unrecognized characters as symbols
        tokens[tokenIndex].type = SYMBOL;
        tokens[tokenIndex].value = malloc(2);
        tokens[tokenIndex].value[0] = query[i];
        tokens[tokenIndex].value[1] = '\0';
        tokenIndex++;
        i++;
    }

    // Add terminator token
    tokens[tokenIndex].type = SYMBOL;
    tokens[tokenIndex].value = strdup("");
    tokenIndex++;

    return tokens;
}

// Function to print tokens to file
void printTokensToFile(FILE *file, Token *tokens) {
    for (int i = 0; ; i++) {
        if (tokens[i].type == SYMBOL && strcmp(tokens[i].value, "") == 0)
            break; // Break loop when terminator token is encountered
        fprintf(file, "Token Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
    }
}

int main() {
    FILE *inputFile, *outputFile;
    char *inputFilename = "Query.txt";
    char *outputFilename = "lexical_analysis_output.txt";

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Determine the size of the file
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Allocate memory to store the SQL query
    char *query = malloc(fileSize + 1);
    if (query == NULL) {
        perror("Memory allocation error");
        fclose(inputFile);
        return 1;
    }

    // Read the SQL query from the file
    fread(query, 1, fileSize, inputFile);
    query[fileSize] = '\0'; // Null-terminate the string

    // Close the input file
    fclose(inputFile);

    // Tokenize the SQL query
    Token *tokens = tokenizeSQL(query);

    // Open the output file
    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        free(query);
        for (int i = 0; tokens[i].type != SYMBOL; i++) {
            free(tokens[i].value);
        }
        free(tokens);
        return 1;
    }

    // Print tokens to the output file
    printTokensToFile(outputFile, tokens);

    // Close the output file
    fclose(outputFile);

    // Free memory
    free(query);
    for (int i = 0; tokens[i].type != SYMBOL; i++) {
        free(tokens[i].value);
    }
    free(tokens);

    printf("\nLexical analysis output saved to %s\n", outputFilename);

    printf("You may now proceed with Syntax Analysis...\n");

    return 0;
}