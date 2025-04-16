#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_CATEGORIES 5
#define MAX_NAME_LEN 50
#define ID_LEN 7
#define SCORE_FIELDS 7 // ID + 5 categories + total
#define MAX_TOTAL_SCORE 500
#define MIN_SCORE 10
#define MAX_SCORE 100

// Candidate data
char candidate_names[NUM_CANDIDATES][MAX_NAME_LEN] = {
    "Jiyeon Park", "Ethan Smith", "Helena Silva",
    "Liam Wilson", "Mina Choi", "Carlos Reyes"
};

int candidate_ids[NUM_CANDIDATES] = {
    123456, 234567, 345678, 456789, 567890, 678901
};

// Scoring sheet: flattened 1D array [candidate0_data(7), candidate1_data(7), ...]
int scoring_sheet[NUM_CANDIDATES * SCORE_FIELDS];

void initialize_scores() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int base = i * SCORE_FIELDS;
        scoring_sheet[base] = candidate_ids[i];
        for (int j = 1; j < SCORE_FIELDS; j++) scoring_sheet[base + j] = 0;
    }
}

int get_valid_score(const char *category) {
    int score;
    while (1) {
        printf("%s (%d-%d): ", category, MIN_SCORE, MAX_SCORE);
        scanf("%d", &score);
        if (score >= MIN_SCORE && score <= MAX_SCORE) break;
        printf("Invalid score. Try again.\n");
    }
    return score;
}

void enter_scores() {
    char judge_name[MAX_NAME_LEN];
    char expertise[MAX_NAME_LEN];

    printf("####################################\n");
    printf("#     Audition Evaluation Entry    #\n");
    printf("####################################\n");
    printf("> Judge Name: ");
    scanf(" %49[^\n]", judge_name);
    printf("> Expertise: ");
    scanf(" %49[^\n]", expertise);

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int base = i * SCORE_FIELDS;
        printf("++++++++++++++++++++++++++++++++++++\n");
        printf("Candidate: %s\n", candidate_names[i]);

        scoring_sheet[base + 1] = get_valid_score("Music Proficiency");
        scoring_sheet[base + 2] = get_valid_score("Dance");
        scoring_sheet[base + 3] = get_valid_score("Vocal");
        scoring_sheet[base + 4] = get_valid_score("Visual");
        scoring_sheet[base + 5] = get_valid_score("Expression");

        scoring_sheet[base + 6] = scoring_sheet[base + 1] + scoring_sheet[base + 2] +
                                 scoring_sheet[base + 3] + scoring_sheet[base + 4] +
                                 scoring_sheet[base + 5];
    }
}

void display_scores() {
    printf("\nSubmission completed. Please review your input!\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int base = i * SCORE_FIELDS;
        printf("%s: %d\n", candidate_names[i], scoring_sheet[base + 6]);
    }
}

void modify_scores() {
    char name[MAX_NAME_LEN];
    int id, found;
    while (1) {
        printf("\nEnter candidate name to modify (or 'exit' to finish): ");
        scanf(" %49[^\n]", name);
        if (strcmp(name, "exit") == 0) break;

        printf("Enter 6-digit candidate ID: ");
        scanf("%d", &id);

        found = 0;
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            int base = i * SCORE_FIELDS;
            if (strcmp(name, candidate_names[i]) == 0 && candidate_ids[i] == id) {
                printf("Modifying scores for %s\n", name);
                scoring_sheet[base + 1] = get_valid_score("Music Proficiency");
                scoring_sheet[base + 2] = get_valid_score("Dance");
                scoring_sheet[base + 3] = get_valid_score("Vocal");
                scoring_sheet[base + 4] = get_valid_score("Visual");
                scoring_sheet[base + 5] = get_valid_score("Expression");

                scoring_sheet[base + 6] = scoring_sheet[base + 1] + scoring_sheet[base + 2] +
                                          scoring_sheet[base + 3] + scoring_sheet[base + 4] +
                                          scoring_sheet[base + 5];
                found = 1;
                break;
            }
        }
        if (!found) printf("Candidate not found or ID mismatch.\n");
    }
}

void rank_candidates() {
    int indices[NUM_CANDIDATES];
    for (int i = 0; i < NUM_CANDIDATES; i++) indices[i] = i;

    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = i + 1; j < NUM_CANDIDATES; j++) {
            int total_i = scoring_sheet[indices[i] * SCORE_FIELDS + 6];
            int total_j = scoring_sheet[indices[j] * SCORE_FIELDS + 6];
            if (total_j > total_i) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    printf("\n=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[indices[i]]);
    }
}

int main() {
    char submit;
    initialize_scores();

    while (1) {
        enter_scores();
        display_scores();

        printf("\nWould you like to submit? (Y/N): ");
        scanf(" %c", &submit);

        if (submit == 'Y' || submit == 'y') {
            printf("***Final submission completed.***\n");
            break;
        } else {
            modify_scores();
        }
    }

    rank_candidates();
    return 0;
}
