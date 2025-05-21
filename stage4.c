#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 100
#define MAX_NAME_LEN 30
#define MAX_FEEDBACK_LEN 51

typedef struct {
    char name[MAX_NAME_LEN];
    int vocalRange;              // Highest MIDI value
    int midiValues[12];          // Holds up to 12 random MIDI values
    int midiCount;               // Number of values used
    double stability;            // Calculated stability
    char feedback[MAX_FEEDBACK_LEN];
} VocalEvaluation;

VocalEvaluation trainees[MAX_TRAINEES];
int traineeCount = 0;

// Function Prototypes
void evalVocal();
void measure(VocalEvaluation *v);
void provideFeedback(VocalEvaluation *v);
void printVocalInfo();
int isDuplicate(int *arr, int size, int val);
int compareStability(const void *a, const void *b);

int main() {
    srand((unsigned int)time(NULL));
    int choice;

    while (1) {
        printf("\n===== Millieways Vocal Evaluation =====\n");
        printf("1. Evaluate Vocal\n");
        printf("2. Show Vocal Evaluations\n");
        printf("0. Exit\n");
        printf("Select menu: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                evalVocal();
                break;
            case 2:
                printVocalInfo();
                break;
            case 0:
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}

// Entry point for vocal evaluation
void evalVocal() {
    if (traineeCount >= MAX_TRAINEES) {
        printf("Max trainee limit reached.\n");
        return;
    }

    VocalEvaluation *v = &trainees[traineeCount];
    printf("Enter trainee name: ");
    fgets(v->name, MAX_NAME_LEN, stdin);
    v->name[strcspn(v->name, "\n")] = '\0'; // remove newline

    measure(v);
    provideFeedback(v);
    traineeCount++;
}

// Measures the vocal range and stability
void measure(VocalEvaluation *v) {
    int count;

    // Bonus: Allow specifying number of MIDI values
    do {
        printf("Enter vocal range (max MIDI value 0-127): ");
        scanf("%d", &v->vocalRange);
        if (v->vocalRange < 0 || v->vocalRange > 127) {
            printf("Invalid MIDI value. Must be between 0 and 127.\n");
        }
    } while (v->vocalRange < 0 || v->vocalRange > 127);

    do {
        printf("Enter number of MIDI values to generate (5–12): ");
        scanf("%d", &count);
        if (count < 5 || count > 12 || count > v->vocalRange) {
            printf("Invalid count. Must be between 5 and 12 and not exceed the vocal range.\n");
        }
    } while (count < 5 || count > 12 || count > v->vocalRange);

    v->midiCount = count;

    int i = 0;
    while (i < count) {
        int randVal = rand() % (v->vocalRange + 1);
        if (!isDuplicate(v->midiValues, i, randVal)) {
            v->midiValues[i++] = randVal;
        }
    }

    // Calculate stability
    int sum = 0;
    for (i = 1; i < count; i++) {
        sum += abs(v->midiValues[i] - v->midiValues[i - 1]);
    }
    v->stability = (double)sum / (count - 1);
}

// Check for duplicate MIDI values
int isDuplicate(int *arr, int size, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) return 1;
    }
    return 0;
}

// Get feedback input
void provideFeedback(VocalEvaluation *v) {
    getchar(); // clear input buffer
    printf("Enter feedback (max 50 characters): ");
    fgets(v->feedback, MAX_FEEDBACK_LEN, stdin);
    v->feedback[strcspn(v->feedback, "\n")] = '\0';
}

// Compare function for qsort
int compareStability(const void *a, const void *b) {
    VocalEvaluation *va = (VocalEvaluation *)a;
    VocalEvaluation *vb = (VocalEvaluation *)b;
    if (va->stability < vb->stability) return -1;
    else if (va->stability > vb->stability) return 1;
    return 0;
}

// Display all evaluations sorted by stability
void printVocalInfo() {
    if (traineeCount == 0) {
        printf("No evaluations available.\n");
        return;
    }

    qsort(trainees, traineeCount, sizeof(VocalEvaluation), compareStability);

    printf("\n--- Vocal Evaluation Results (Sorted by Stability) ---\n");
    for (int i = 0; i < traineeCount; i++) {
        printf("Name: %s\n", trainees[i].name);
        printf("Stability: %.2f\n", trainees[i].stability);
        printf("Feedback: %s\n", trainees[i].feedback);
        printf("----------------------------------------------------\n");
    }
}
