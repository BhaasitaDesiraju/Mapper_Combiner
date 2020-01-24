#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//tuple structure
struct tuple {
    char *userId;
    int score;
    char topic[15];
    struct node *next;
};

void printTuples(struct tuple *head, FILE *outputFile) {
    while (head) {
        printf("(%s,%s,%d)\n", head->userId, head->topic, head->score);
        fprintf(outputFile, "(%s,%s,%d)\n", head->userId, head->topic, head->score);
        fflush(outputFile);
        if (head->next == NULL)
            break;
        head = (struct tuple *) head->next;
    }
}

void removeTuples(struct tuple *head) {
    struct tuple *prev;
    while (head) {
        prev = (struct tuple *) head;
        head = (struct tuple *) head->next;
        free(prev->userId);
        free(prev);
    }
}

void insertTuple(const struct tuple *head, struct tuple *temp) {
    if (head == NULL) {
        return;
    }

    struct tuple *iterNode = (struct tuple *) head;
    struct tuple *lastNode;

    while (iterNode != NULL) {
        if ((strcmp(iterNode->userId, temp->userId) == 0) && (strcmp(iterNode->topic, temp->topic) == 0)) {
            iterNode->score += temp->score;
            return;
        }
        lastNode = iterNode;
        iterNode = (struct tuple *) iterNode->next;
    }
    lastNode->next = (struct node *) (struct tuple *) temp;
}

int main() {

    FILE *inputFile, *outputFile;
    char inputBuffer[100];
    char *tokens;
    struct tuple *head = NULL, *temp;

    //opening input and output files
    inputFile = fopen("output.txt", "r");
    outputFile = fopen("reducer_output.txt", "w");

    if (inputFile && outputFile) {
        while (fgets(inputBuffer, 100, inputFile) != NULL) {
            temp = (struct tuple *) malloc(sizeof(struct tuple));
            tokens = strtok(inputBuffer, ",");

            //gets the userId
            temp->userId = (char *) malloc((strlen(tokens) - 1) * sizeof(char));
            strcpy(temp->userId, &tokens[1]);

            //gets the topic
            tokens = strtok(NULL, ",");
            strcpy(temp->topic, tokens);

            //gets the score
            tokens = strtok(NULL, ")");
            temp->score = atoi(tokens);

            temp->next = NULL;

            //checking for similar userIds and topics
            if (head == NULL) {
                head = temp;
            }
            else {
                //checking for similar userIds
                if (strcmp(head->userId, temp->userId) != 0) {
                    printTuples(head, outputFile);
                    removeTuples(head);
                    head = temp;
                }
                else
                    insertTuple(head, temp);
            }
        }
        printTuples(head, outputFile);
        fclose(inputFile);
        fclose(outputFile);
    }
    else {
        fprintf(stderr, "Cannot open file.\n");
        exit(0);
    }
}