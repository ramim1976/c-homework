#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 30
#define MAX_TESTS 7

// Store member names and nicknames
char milliways_members[MAX_MEMBERS][50] = {
    "Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Hank",
    "Ivy", "Jack", "Kelly", "Leo", "Mia", "Nina", "Oscar", "Paul", "Quinn",
    "Rachel", "Sam", "Tina", "Uma", "Victor", "Wendy", "Xander", "Yara",
    "Zane", "Aaron", "Betty", "Cathy", "Daniel"
};

char milliways_nicknames[MAX_MEMBERS][30] = {
    "Ali", "Bobby", "Chuck", "Davy", "Evie", "Frankie", "Gracie", "Hankie",
    "Ives", "Jackie", "Kel", "Lenny", "Mimi", "Nini", "Ozzy", "Pauly", "Quinny",
    "Rach", "Sammy", "Tee", "Umi", "Vic", "Wen", "Xan", "Yari",
    "Zan", "Ron", "Bet", "Cat", "Dan"
};

// Store fitness scores
float health_scores[MAX_MEMBERS][MAX_TESTS];

// Function to find a member by nickname
int findMemberByNickname(char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(milliways_nicknames[i], nickname) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

// Function to parse and set fitness data
void setHealth() {
    char input[100];
    char nickname[30];
    float scores[MAX_TESTS];

    printf("\nEnter nickname and %d fitness test values separated by commas: ", MAX_TESTS);
    scanf(" %[^\n]", input);

    char *token = strtok(input, ",");
    if (token == NULL) {
        printf("Invalid input format!\n");
        return;
    }

    strcpy(nickname, token);
    int member_index = findMemberByNickname(nickname);
    if (member_index == -1) {
        printf("Nickname not found!\n");
        return;
    }

    int i = 0;
    while ((token = strtok(NULL, ",")) != NULL && i < MAX_TESTS) {
        scores[i] = atof(token);
        i++;
    }

    if (i != MAX_TESTS) {
        printf("Error: Expected %d test scores!\n", MAX_TESTS);
        return;
    }

    for (int j = 0; j < MAX_TESTS; j++) {
        health_scores[member_index][j] = scores[j];
    }

    printf("Health data recorded for %s (%s)!\n", milliways_members[member_index], nickname);
}

// Function to get health data
void getHealth() {
    int choice;
    char nickname[30];

    printf("\nChoose an option:\n");
    printf("1. Display all fitness data\n");
    printf("2. Display specific member data\n");
    printf("3. Display a specific test result for a member\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nFitness Data:\n");
            for (int i = 0; i < MAX_MEMBERS; i++) {
                printf("%s (%s): ", milliways_members[i], milliways_nicknames[i]);
                for (int j = 0; j < MAX_TESTS; j++) {
                    printf("%.2f ", health_scores[i][j]);
                }
                printf("\n");
            }
            break;

        case 2:
            printf("Enter member nickname: ");
            scanf("%s", nickname);
            int member_index = findMemberByNickname(nickname);
            if (member_index == -1) {
                printf("Nickname not found!\n");
                return;
            }
            printf("\n%s (%s)'s fitness data: ", milliways_members[member_index], nickname);
            for (int j = 0; j < MAX_TESTS; j++) {
                printf("%.2f ", health_scores[member_index][j]);
            }
            printf("\n");
            break;

        case 3:
            printf("Enter member nickname: ");
            scanf("%s", nickname);
            int test_index;
            printf("Enter test index (0-%d): ", MAX_TESTS - 1);
            scanf("%d", &test_index);

            member_index = findMemberByNickname(nickname);
            if (member_index == -1 || test_index < 0 || test_index >= MAX_TESTS) {
                printf("Invalid input!\n");
                return;
            }
            printf("\n%s (%s)'s Test %d result: %.2f\n", milliways_members[member_index], nickname, test_index, health_scores[member_index][test_index]);
            break;

        default:
            printf("Invalid choice!\n");
    }
}

// Main function
int main() {
    int option;
    while (1) {
        printf("\n--- Fitness Tracker Menu ---\n");
        printf("1. Set Health Data\n");
        printf("2. Get Health Data\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                setHealth();
                break;
            case 2:
                getHealth();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option! Try again.\n");
        }
    }
}
