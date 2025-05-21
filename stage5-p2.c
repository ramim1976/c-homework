#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define MAX_PATTERNS 6
#define MAX_SONGS 4
#define MAX_PATTERN_NAME_LEN 50
#define MAX_PATTERN_DESC_LEN 256
#define MAX_SONG_NAME_LEN 100

typedef struct {
    char name[MAX_PATTERN_NAME_LEN];
    char description[MAX_PATTERN_DESC_LEN];
} ChoreoPattern;

typedef struct PatternNode {
    char patternName[MAX_PATTERN_NAME_LEN];
    struct PatternNode *next;
} PatternNode;

typedef struct {
    char songName[MAX_SONG_NAME_LEN];
    PatternNode *head;
} SongChoreoTree;

ChoreoPattern patterns[MAX_PATTERNS];
int patternCount = 0;

SongChoreoTree songs[MAX_SONGS];
int songCount = 0;

void trimNewline(char *str) {
    char *p = str;
    while (*p) {
        if (*p == '\r' || *p == '\n') {
            *p = '\0';
            break;
        }
        p++;
    }
}

int loadChoreoPatterns(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening choreography pattern file: %s\n", filename);
        return 0;
    }
    char line[512];
    patternCount = 0;
    while (fgets(line, sizeof(line), fp) && patternCount < MAX_PATTERNS) {
        trimNewline(line);
        char *sep = strchr(line, '|');
        if (!sep) continue;
        *sep = '\0';
        strncpy(patterns[patternCount].name, line, MAX_PATTERN_NAME_LEN-1);
        patterns[patternCount].name[MAX_PATTERN_NAME_LEN-1] = '\0';
        strncpy(patterns[patternCount].description, sep+1, MAX_PATTERN_DESC_LEN-1);
        patterns[patternCount].description[MAX_PATTERN_DESC_LEN-1] = '\0';
        patternCount++;
    }
    fclose(fp);
    return 1;
}

int loadSongChoreoAnalysis(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening choreography analysis file: %s\n", filename);
        return 0;
    }
    char line[1024];
    songCount = 0;
    while (fgets(line, sizeof(line), fp) && songCount < MAX_SONGS) {
        trimNewline(line);
        char *token = strtok(line, ",");
        if (!token) continue;
        strncpy(songs[songCount].songName, token, MAX_SONG_NAME_LEN-1);
        songs[songCount].songName[MAX_SONG_NAME_LEN-1] = '\0';

        PatternNode *head = NULL;
        PatternNode *tail = NULL;

        while ((token = strtok(NULL, ",")) != NULL) {
            PatternNode *node = malloc(sizeof(PatternNode));
            if (!node) {
                printf("Memory allocation failed\n");
                fclose(fp);
                return 0;
            }
            strncpy(node->patternName, token, MAX_PATTERN_NAME_LEN-1);
            node->patternName[MAX_PATTERN_NAME_LEN-1] = '\0';
            node->next = NULL;

            if (!head) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
        songs[songCount].head = head;
        songCount++;
    }
    fclose(fp);
    return 1;
}

void generateRandomSnippet(const char *desc, char *snippet, int length) {
    int descLen = (int)strlen(desc);
    int validIndices[512], validCount = 0;
    for (int i=0; i<descLen; i++) {
        if (desc[i] != ' ') {
            validIndices[validCount++] = i;
        }
    }
    if (validCount < length) {
        strncpy(snippet, desc, length);
        snippet[length] = '\0';
        return;
    }
    int maxStart = validCount - length;
    int startIndex = rand() % (maxStart + 1);
    for (int i=0; i<length; i++) {
        snippet[i] = desc[validIndices[startIndex + i]];
    }
    snippet[length] = '\0';
}

int isAnswerCorrect(const char *userAnswer, const char *patternName) {
    char answerLower[64], patternLower[64];
    int i;
    for (i=0; i<(int)strlen(userAnswer) && i<63; i++) {
        char c = userAnswer[i];
        if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
        answerLower[i] = c;
    }
    answerLower[i] = '\0';
    for (i=0; i<(int)strlen(patternName) && i<63; i++) {
        char c = patternName[i];
        if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
        patternLower[i] = c;
    }
    patternLower[i] = '\0';
    return strcmp(answerLower, patternLower) == 0;
}

int runPatternQuiz() {
    int correctCount = 0;
    int askedIndices[MAX_PATTERNS] = {0};
    int askedCount = 0;
    for (int q=0; q<4; q++) {
        int idx;
        do {
            idx = rand() % patternCount;
            int unique = 1;
            for (int k=0; k<askedCount; k++) {
                if (askedIndices[k] == idx) unique = 0;
            }
            if (unique) break;
        } while (1);
        askedIndices[askedCount++] = idx;

        char snippet[11];
        generateRandomSnippet(patterns[idx].description, snippet, 10);

        printf("\nQuestion %d:\nDescription snippet: \"%s\"\n", q+1, snippet);
        printf("Enter the choreography pattern name: ");
        char userInput[64];
        if (!fgets(userInput, sizeof(userInput), stdin)) return correctCount;
        trimNewline(userInput);

        if (isAnswerCorrect(userInput, patterns[idx].name)) {
            printf("Correct!\n");
            correctCount++;
        } else {
            printf("Wrong! The correct answer was: %s\n", patterns[idx].name);
        }
    }
    return correctCount;
}

void printAllSongs() {
    for (int i=0; i<songCount; i++) {
        printf("\nSong: %s\nPatterns:\n", songs[i].songName);
        PatternNode *cur = songs[i].head;
        while (cur) {
            printf("  - %s\n", cur->patternName);
            cur = cur->next;
        }
    }
}

void freeSongTrees() {
    for (int i=0; i<songCount; i++) {
        PatternNode *cur = songs[i].head;
        while (cur) {
            PatternNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        songs[i].head = NULL;
    }
}

void interactiveSongQuiz() {
    printf("\nSelect a song by number:\n");
    for (int i=0; i<songCount; i++) {
        printf("  %d. %s\n", i+1, songs[i].songName);
    }
    printf("Enter your choice: ");
    char input[16];
    if (!fgets(input, sizeof(input), stdin)) return;
    int choice = atoi(input);
    if (choice < 1 || choice > songCount) {
        printf("Invalid choice.\n");
        return;
    }
    SongChoreoTree *song = &songs[choice - 1];
    PatternNode *cur = song->head;

    printf("\nStarting choreography pattern quiz for song: %s\n", song->songName);
    while (cur) {
        printf("Enter the next choreography pattern: ");
        char userInput[64];
        if (!fgets(userInput, sizeof(userInput), stdin)) return;
        trimNewline(userInput);
        if (!isAnswerCorrect(userInput, cur->patternName)) {
            printf("Wrong pattern! Exiting to menu.\n");
            return;
        }
        printf("Correct!\n");
        cur = cur->next;
    }
    printf("Congratulations! You completed the choreography pattern quiz for this song!\n");
}

void learnDancePattern() {
    srand((unsigned int)time(NULL));

    if (!loadChoreoPatterns("dance_pattern.txt")) {
        printf("Failed to load choreography patterns.\n");
        return;
    }
    if (!loadSongChoreoAnalysis("analyz_dance-pattern.csv")) {
        printf("Failed to load choreography analysis.\n");
        return;
    }

    printf("\n--- Choreography Pattern Quiz ---\n");
    int correct = runPatternQuiz();

    if (correct < 3) {
        printf("\nYou answered fewer than 3 correctly. Returning to menu.\n");
        freeSongTrees();
        return;
    }

    printf("\nQuiz passed! Displaying choreography patterns for sample songs...\n");
    printAllSongs();

    printf("\nBonus: Interactive choreography pattern quiz.\n");
    interactiveSongQuiz();

    freeSongTrees();

    system(CLEAR);
}

// Example simple main menu
void menu() {
    while (1) {
        printf("\n--- Dance Training Menu ---\n");
        printf("1. Learn Dance Pattern\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        char input[16];
        if (!fgets(input, sizeof(input), stdin)) break;
        int choice = atoi(input);
        if (choice == 0) break;
        else if (choice == 1) learnDancePattern();
        else printf("Invalid option.\n");
    }
}

int main() {
    menu();
    printf("Program exited.\n");
    return 0;
}
