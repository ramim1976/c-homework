#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 20
#define MAX_MENTORS 8
#define NAME_LENGTH 50

typedef struct {
    char name[NAME_LENGTH];
    int asciiSum;
    int ability;
    int mentorID;
} Trainee;

typedef struct {
    int id;
    char name[NAME_LENGTH];
    int menteeIndex;  // -1 if none assigned
} Mentor;

// Converts nickname to ASCII sum
int parseIntMember(const char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++)
        sum += (int)name[i];
    return sum;
}

// Generates random ability
int getRandomAbility() {
    return (rand() % 901) + 100; // 100–1000
}

// Initialize trainees
void initTrainees(Trainee trainees[], int *count) {
    char *sampleNames[] = {
        "Arthur", "Lancelot", "Gwen", "Mordred", "Elyan",
        "Leon", "Percival", "Gwaine", "Tristan", "Isolde",
        "Kay", "Bors", "Bedivere", "Galahad", "Agravaine",
        "Uther", "Merlin", "Morgana", "Nimueh", "Taliesin"
    };

    *count = MAX_TRAINEES;
    for (int i = 0; i < *count; i++) {
        strcpy(trainees[i].name, sampleNames[i]);
        trainees[i].asciiSum = parseIntMember(trainees[i].name);
        trainees[i].ability = getRandomAbility();
        trainees[i].mentorID = -1;
    }
}

// Input mentors
void inputMentors(Mentor mentors[], int *count) {
    *count = MAX_MENTORS;
    for (int i = 0; i < *count; i++) {
        mentors[i].id = i + 1;
        snprintf(mentors[i].name, NAME_LENGTH, "Mentor%d", mentors[i].id);
        mentors[i].menteeIndex = -1;
    }
}

// Matching logic (bonus 1:1 matching)
void matchMentoring(Trainee trainees[], int traineeCount, Mentor mentors[], int mentorCount) {
    int usedMentors[MAX_MENTORS] = {0};
    int mentorAssigned = 0;

    for (int i = 0; i < traineeCount && mentorAssigned < mentorCount; i++) {
        int preferred = trainees[i].asciiSum % mentorCount;
        
        // Find next available mentor starting from preferred
        for (int j = 0; j < mentorCount; j++) {
            int idx = (preferred + j) % mentorCount;
            if (!usedMentors[idx]) {
                trainees[i].mentorID = mentors[idx].id;
                mentors[idx].menteeIndex = i;
                usedMentors[idx] = 1;
                mentorAssigned++;
                break;
            }
        }
    }
}

// Output trainees and matched mentors
void printMatches(Trainee trainees[], int traineeCount, Mentor mentors[], int mentorCount) {
    printf("\nTrainee-Mentor Matches:\n");
    for (int i = 0; i < traineeCount; i++) {
        printf("Trainee #%d: %s | Mentor ID: %d",
            i + 1, trainees[i].name,
            trainees[i].mentorID);
        
        // Find mentor name
        for (int j = 0; j < mentorCount; j++) {
            if (mentors[j].id == trainees[i].mentorID) {
                printf(" (%s)", mentors[j].name);
                break;
            }
        }
        printf("\n");
    }
}
