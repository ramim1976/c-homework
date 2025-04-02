#include <stdio.h>
#include <ctype.h>

#define NUM_MAIN_MENU 3
#define NUM_STAGES 8

// Function prototypes
void showMainMenu();
void manageAudition();
void manageTraining();
void manageDebut();
void handleTrainingStage(int stage);

// Main Menu and Training Menu as 2D arrays (Bonus Feature)
const char *menu[NUM_MAIN_MENU] = {
    "Audition Management",
    "Training",
    "Debut"
};

const char *stages[NUM_STAGES] = {
    "Physical Strength & Knowledge",
    "Self-Management & Teamwork",
    "Language & Pronunciation",
    "Vocal",
    "Dance",
    "Visual & Image",
    "Acting & Stage Performance",
    "Fan Communication"
};

// Training results (initialized to '-')
char trainingResults[NUM_STAGES] = {'-', '-', '-', '-', '-', '-', '-', '-'};

int main() {
    char choice;
    while (1) {
        showMainMenu();
        scanf(" %c", &choice);
        choice = toupper(choice);

        if (choice == '0' || choice == 'Q') {
            printf("Exiting program.\n");
            break;
        }
        switch (choice) {
            case '1': manageAudition(); break;
            case '2': manageTraining(); break;
            case '3': manageDebut(); break;
            default: printf("Invalid option! Please try again.\n");
        }
    }
    return 0;
}

void showMainMenu() {
    printf("\n=== Magrathea Training System ===\n");
    for (int i = 0; i < NUM_MAIN_MENU; i++) {
        printf("%d. %s\n", i + 1, menu[i]);
    }
    printf("Enter option (0/Q to exit): ");
}

void manageAudition() {
    printf("\nAudition Management: Feature to be implemented. Returning to main menu.\n");
}

void manageTraining() {
    int stage;
    while (1) {
        printf("\n=== Training Menu ===\n");
        for (int i = 0; i < NUM_STAGES; i++) {
            printf("%d. %s [%c]\n", i + 1, stages[i], trainingResults[i]);
        }
        printf("Enter stage number to train (0 to return): ");
        scanf(" %d", &stage);

        if (stage == 0) return;
        if (stage < 1 || stage > NUM_STAGES) {
            printf("Invalid stage number!\n");
            continue;
        }
        
        // Ensure sequential order for stage 1 and 2
        if (stage == 2 && trainingResults[0] != 'P') {
            printf("You must pass Stage 1 first!\n");
            continue;
        }
        if (stage > 2 && (trainingResults[0] != 'P' || trainingResults[1] != 'P')) {
            printf("You must pass Stages 1 and 2 first!\n");
            continue;
        }
        
        if (trainingResults[stage - 1] != '-') {
            printf("This stage is already completed.\n");
            continue;
        }
        
        handleTrainingStage(stage - 1);
    }
}

void handleTrainingStage(int stage) {
    char choice, result;
    printf("Would you like to enter the evaluation result? (Y/N): ");
    scanf(" %c", &choice);
    choice = toupper(choice);

    if (choice == 'Y') {
        printf("Did you complete the training and pass the certification? (P/F): ");
        scanf(" %c", &result);
        result = toupper(result);

        if (result == 'P' || result == 'F') {
            trainingResults[stage] = result;
        } else {
            printf("Invalid input!\n");
        }
    }
}

void manageDebut() {
    printf("\nDebut Management: Feature to be implemented. Returning to main menu.\n");
}
