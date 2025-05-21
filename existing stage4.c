#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 30
#define CHANCES 3

typedef enum { MALE, FEMALE } Gender;

typedef struct {
    char name[MAX_NAME];
    Gender gender;
    float frequency;     // Hz
    float amplitude;     // dB
    float jitter;        // %
    int grbas[5];        // Bonus: G, R, B, A, S values (0–3)
} VoiceProfile;

// Function Prototypes
void findMyVoice();
void getMyVoiceFromHeaven(VoiceProfile *v);
int guessMyFloat(float target, const char *label, float min, float max);
int guessMyInt(int target, const char *label, int min, int max);
void printGRBASLabels();

// Random float generator within range
float randFloat(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

int main() {
    srand((unsigned int)time(NULL));
    int choice;

    while (1) {
        printf("\n=== Magrathea Voice Discovery Menu ===\n");
        printf("1. Find My Voice\n");
        printf("0. Exit\n");
        printf("Select menu: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                findMyVoice();
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void findMyVoice() {
    VoiceProfile v;
    char genderChar;

    printf("Enter your nickname: ");
    fgets(v.name, MAX_NAME, stdin);
    v.name[strcspn(v.name, "\n")] = '\0';

    do {
        printf("Enter your gender (M/F): ");
        scanf(" %c", &genderChar);
        genderChar = toupper(genderChar);
        if (genderChar != 'M' && genderChar != 'F') {
            printf("Invalid input. Please enter M or F.\n");
        }
    } while (genderChar != 'M' && genderChar != 'F');
    v.gender = (genderChar == 'M') ? MALE : FEMALE;

    getMyVoiceFromHeaven(&v);

    int success = 1;
    printf("\n🎯 Guess your vocal profile (3 tries per metric):\n");

    float fMin = (v.gender == MALE) ? 85.0 : 165.0;
    float fMax = (v.gender == MALE) ? 180.0 : 255.0;
    float aMin = (v.gender == MALE) ? 2.5 : 3.5;
    float aMax = (v.gender == MALE) ? 3.6 : 4.7;
    float jMin = (v.gender == MALE) ? 0.2 : 0.3;
    float jMax = (v.gender == MALE) ? 0.6 : 1.0;

    success &= guessMyFloat(v.frequency, "Frequency (Hz)", fMin, fMax);
    success &= guessMyFloat(v.amplitude, "Amplitude (dB)", aMin, aMax);
    success &= guessMyFloat(v.jitter, "Voice Pulse (%%)", jMin, jMax);

    printf("\n🎵 Bonus: GRBAS Scale (values 0–3)\n");
    printGRBASLabels();
    const char *grbasNames[] = {"Grade", "Roughness", "Breathiness", "Asthenia", "Strain"};
    for (int i = 0; i < 5; i++) {
        success &= guessMyInt(v.grbas[i], grbasNames[i], 0, 3);
    }

    if (success) {
        printf("\n🎉 Congratulations %s, you've found your voice!\n", v.name);
    } else {
        printf("\n😅 Sorry %s, try again to discover your voice.\n", v.name);
    }
}

void getMyVoiceFromHeaven(VoiceProfile *v) {
    if (v->gender == MALE) {
        v->frequency = randFloat(85.0, 180.0);
        v->amplitude = randFloat(2.5, 3.6);
        v->jitter = randFloat(0.2, 0.6);
    } else {
        v->frequency = randFloat(165.0, 255.0);
        v->amplitude = randFloat(3.5, 4.7);
        v->jitter = randFloat(0.3, 1.0);
    }
    for (int i = 0; i < 5; i++) {
        v->grbas[i] = rand() % 4; // 0 to 3
    }
}

int guessMyFloat(float target, const char *label, float min, float max) {
    float guess;
    for (int i = 0; i < CHANCES; i++) {
        printf("%s (%.1f–%.1f): ", label, min, max);
        scanf("%f", &guess);
        if (fabs(guess - target) < 0.1) {
            printf("✅ Correct!\n");
            return 1;
        } else if (guess < target) {
            printf("🔼 Higher!\n");
        } else {
            printf("🔽 Lower!\n");
        }
    }
    printf("❌ The correct value was: %.2f\n", target);
    return 0;
}

int guessMyInt(int target, const char *label, int min, int max) {
    int guess;
    for (int i = 0; i < CHANCES; i++) {
        printf("%s (%d–%d): ", label, min, max);
        scanf("%d", &guess);
        if (guess == target) {
            printf("✅ Correct!\n");
            return 1;
        } else if (guess < target) {
            printf("🔼 Higher!\n");
        } else {
            printf("🔽 Lower!\n");
        }
    }
    printf("❌ The correct value was: %d\n", target);
    return 0;
}

void printGRBASLabels() {
    printf("Scale: 0 (normal), 1 (mild), 2 (moderate), 3 (severe)\n");
}
