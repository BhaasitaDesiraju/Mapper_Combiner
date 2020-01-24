#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Maps the actions to a score
char *mapActionsToScores(char action) {
    char *actionPointer = NULL;
    char *P = ",50)";
    char *L = ",20)";
    char *D = ",-10)";
    char *C = ",30)";
    char *S = ",40)";

    switch (action) {
        case 'P':
            actionPointer = P;
            break;
        case 'L':
            actionPointer = L;
            break;
        case 'D':
            actionPointer = D;
            break;
        case 'C':
            actionPointer = C;
            break;
        case 'S':
            actionPointer = S;
            break;
        default:
            break;
    }
    return actionPointer;
}

//Generates tuples in the form: (userId, topic, score)
char* processTuples(char action, char arrayBuffer[]) {
    char *tempBuffer = arrayBuffer;
    char userId[6];
    char topic[17];
    char *rules;
    char *result = malloc (sizeof (char) * 26);
    rules = mapActionsToScores(action);

    //gets the userId
    memset(userId, '\0', sizeof(userId));
    strncpy(userId, tempBuffer, 5);

    //gets the topic
    memset(topic, '\0', sizeof(topic));
    strncpy(topic, tempBuffer + 7, 16);

    //concat
    strcpy(result, userId);
    strcat(result, topic);
    strcat(result, rules);
    strcat(result, "\0");
    strcat(result, "\n");

    return result;
}

int main() {
    FILE *inputFile, *outputFile;
    char input[26], output[26];
    char action;
    char *result;
    //Open input and output files
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");
    if (inputFile && outputFile) {
        while (fgets(input, 26, inputFile)) {
            int i = 0;
            for (; i < 26; i++) {
                output[i] = input[i];
            }
            //get action
            action = input[6];
            result = processTuples(action, output);
            printf("%s", result);
            fprintf(outputFile, "%s", result);
            fflush(outputFile);
        }
        fclose(inputFile);
        fclose(outputFile);
    } else {
        fprintf(stderr, "Cannot open file.\n");
        exit(0);
    }
}