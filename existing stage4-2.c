#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOTES 3

// Note structure
typedef struct {
    char note;     // A to G
    int octave;    // 1 to 8
} Note;

// Chord structure
typedef struct {
    Note notes[MAX_NOTES]; // root, third, fifth
} Chord;

typedef int (*CheckFunc)(Chord*);

// Convert note character to index (A=0, B=1, ..., G=6)
int noteToIndex(char note) {
    switch (toupper(note)) {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 6;
        default: return -1;
    }
}

// Calculate pitch difference between two notes
int pitchDifference(Note *a, Note *b) {
    return abs(noteToIndex(a->note) - noteToIndex(b->note));
}

// Check if all notes are in the same octave
int isSameOctave(Chord *chord) {
    int octave = chord->notes[0].octave;
    for (int i = 1; i < MAX_NOTES; ++i) {
        if (chord->notes[i].octave != octave)
            return 0;
    }
    return 1;
}

// Check for duplicate notes
int hasDuplicateNotes(Chord *chord) {
    for (int i = 0; i < MAX_NOTES; ++i) {
        for (int j = i + 1; j < MAX_NOTES; ++j) {
            if (toupper(chord->notes[i].note) == toupper(chord->notes[j].note))
                return 1;
        }
    }
    return 0;
}

// Check harmony of the chord
int isHarmonious(Chord *chord) {
    int rootToThird = pitchDifference(&chord->notes[0], &chord->notes[1]);
    int rootToFifth = pitchDifference(&chord->notes[0], &chord->notes[2]);

    if (rootToThird <= 2 && rootToFifth >= 4) {
        printf(">> The chord sounds harmonious.\n");
        return 1;
    } else {
        printf(">> The chord sounds dissonant.\n");
        return 0;
    }
}

// Print chord information
void printChord(Chord *chord) {
    const char *labels[] = {"Root", "Third", "Fifth"};
    printf("\nChord Notes:\n");
    for (int i = 0; i < MAX_NOTES; ++i) {
        printf("  %s: %c%d\n", labels[i], toupper(chord->notes[i].note), chord->notes[i].octave);
    }
}

// Main music theory function
void learnMusicTheory() {
    Chord chord;
    printf("\n[Music Theory] Enter a chord (Root, Third, Fifth):\n");

    for (int i = 0; i < MAX_NOTES; ++i) {
        char input[10];
        printf("  Enter note %d (A-G): ", i + 1);
        scanf(" %s", input);
        chord.notes[i].note = toupper(input[0]);

        if (noteToIndex(chord.notes[i].note) == -1) {
            printf("Invalid note.\n");
            return;
        }

        printf("  Enter octave for note %d (1-8): ", i + 1);
        scanf("%d", &chord.notes[i].octave);
        if (chord.notes[i].octave < 1 || chord.notes[i].octave > 8) {
            printf("Invalid octave.\n");
            return;
        }
    }

    printChord(&chord);

    CheckFunc checks[] = {isSameOctave, hasDuplicateNotes, isHarmonious};

    if (!checks[0](&chord)) {
        printf(">> Invalid chord: All notes must be in the same octave.\n");
        return;
    }

    if (checks[1](&chord)) {
        printf(">> Invalid chord: Duplicate notes are not allowed.\n");
        return;
    }

    checks[2](&chord); // Bonus: Harmony check
}

// Example menu call
void vocalTrainingMenu() {
    int choice;
    while (1) {
        printf("\n[II. Training > 4. Vocal Training]\n");
        printf("  A. Vocal Evaluation\n");
        printf("  B. My Voice\n");
        printf("  C. Music Theory\n");
        printf("  0. Back\n");
        printf("Select an option: ");
        char input[10];
        scanf(" %s", input);
        if (input[0] == '0') break;
        else if (toupper(input[0]) == 'A') evalVocal();
        else if (toupper(input[0]) == 'B') findMyVoice();
        else if (toupper(input[0]) == 'C') learnMusicTheory();
        else printf("Invalid option.\n");
    }
}
