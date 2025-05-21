#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

#define MAX_DANCES 6
#define MAX_STEPS 6
#define MAX_MEMBERS 10
#define MAX_NAME 50

// Structures
typedef struct {
    char name_kr[MAX_NAME];
    char name_en[MAX_NAME];
    char steps[MAX_STEPS][MAX_NAME];
    int stepCount;
} Dance;

typedef struct {
    char name[MAX_NAME];
    char nickname[MAX_NAME];
    int score;
} Member;

// Globals
Dance dances[MAX_DANCES];
Member members[MAX_MEMBERS] = {
    {"Arthur", "artie", 0},
    {"Hye-kyung", "hyek", 0},
    {"Young-jin", "yj", 0},
    {"Ariel", "ariel", 0}
};
int memberCount = 4;

// Utility
void shuffle(char arr[][MAX_NAME], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[MAX_NAME];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

int loadDanceSteps(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;
    for (int i = 0; i < MAX_DANCES; i++) {
        if (fscanf(fp, "%s", dances[i].name_en) != 1) break;
        if (fscanf(fp, "%s", dances[i].name_kr) != 1) break;
        for (int j = 0; j < MAX_STEPS; j++) {
            if (fscanf(fp, "%s", dances[i].steps[j]) != 1) break;
        }
        dances[i].stepCount = MAX_STEPS;
    }
    fclose(fp);
    return 1;
}

Member *findMemberByNickname(const char *nickname) {
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].nickname, nickname) == 0)
            return &members[i];
    }
    return NULL;
}

void delaySeconds(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

void learnDanceStep() {
    char nickname[MAX_NAME];
    int attempts = 0;
    Member *learner = NULL;

    while (attempts < 3) {
        printf("Enter your nickname: ");
        scanf("%s", nickname);
        learner = findMemberByNickname(nickname);
        if (learner) break;
        printf("Invalid nickname. Try again.\n");
        attempts++;
    }

    if (!learner) {
        printf("Too many failed attempts. Returning to menu.\n");
        return;
    }

    if (!loadDanceSteps("dance_step.txt")) {
        printf("Failed to load dance steps.\n");
        return;
    }

    srand(time(NULL));
    int d = rand() % MAX_DANCES;
    Dance selected = dances[d];

    printf("Dance: %s (%s)\n", selected.name_en, selected.name_kr);
    for (int i = 0; i < selected.stepCount; i++) {
        printf("Step %d: %s\n", i + 1, selected.steps[i]);
    }
    delaySeconds(10);
    system(CLEAR);

    // Shuffle steps
    char shuffled[MAX_STEPS][MAX_NAME];
    for (int i = 0; i < selected.stepCount; i++)
        strcpy(shuffled[i], selected.steps[i]);
    shuffle(shuffled, selected.stepCount);

    printf("Reorder the steps of the dance: %s\n", selected.name_en);
    char input[MAX_STEPS][MAX_NAME];
    for (int i = 0; i < selected.stepCount; i++) {
        printf("Step %d: ", i + 1);
        scanf("%s", input[i]);
    }

    int correctOrder = 1, allPresent = 1, anyCorrect = 0;
    for (int i = 0; i < selected.stepCount; i++) {
        if (strcmp(input[i], selected.steps[i]) != 0)
            correctOrder = 0;
        int found = 0;
        for (int j = 0; j < selected.stepCount; j++) {
            if (strcmp(input[i], selected.steps[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) allPresent = 0;
        else anyCorrect = 1;
    }

    int score = 0;
    if (correctOrder) score = 100;
    else if (allPresent) score = 50;
    else if (anyCorrect) score = 20;

    learner->score = score;
    printf("\nCorrect Steps:\n");
    for (int i = 0; i < selected.stepCount; i++)
        printf("%s ", selected.steps[i]);
    printf("\nYour Input:\n");
    for (int i = 0; i < selected.stepCount; i++)
        printf("%s ", input[i]);
    printf("\nScore: %d\n", score);
}

// Main function for testing
int main() {
    learnDanceStep();
    return 0;
}
