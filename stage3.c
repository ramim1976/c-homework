#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct to store the Korean quiz question
typedef struct {
    int id;
    char content[256];
    char correctAnswer[256];
} KoreanQuestion;

// Struct to store trainee information
typedef struct {
    char name[100];
    char nickname[100];
    char nationality[50];
    int quizScore;
    char passStatus[10];
} Trainee;

// Struct to store quiz answer (correctness)
typedef struct {
    int questionId;
    char correctness;  // 'O' for correct, 'X' for incorrect
} QuizAnswer;

// Define the global quiz question bank (for simplicity, initializing directly)
KoreanQuestion questionBank[10] = {
    {1, "What is 'hello' in Korean?", "안녕하세요"},
    {2, "How do you say 'thank you' in Korean?", "감사합니다"},
    {3, "How do you say 'goodbye' (if you're leaving) in Korean?", "안녕히 계세요"},
    {4, "What is 'I love you' in Korean?", "사랑해요"},
    {5, "What is 'good morning' in Korean?", "좋은 아침"},
    {6, "How do you say 'yes' in Korean?", "네"},
    {7, "How do you say 'no' in Korean?", "아니요"},
    {8, "How do you say 'excuse me' in Korean?", "실례합니다"},
    {9, "How do you say 'good night' in Korean?", "잘 자요"},
    {10, "What is 'please' in Korean?", "제발"}
};

// Define Millieways trainees
Trainee trainees[4] = {
    {"Park Ji-yeon", "Ji-yeon", "Korean", 0, "Not Passed"},
    {"Lisa", "Lisa", "Thai", 0, "Not Passed"},
    {"John", "Johnny", "American", 0, "Not Passed"},
    {"Sana", "Sana", "Japanese", 0, "Not Passed"}
};

// Function to select a random trainee for the quiz (only non-Korean trainees)
void selectRandomTakers() {
    int validTrainees[3];  // Array to store non-Korean trainees
    int count = 0;

    // Collect non-Korean trainees' indexes
    for (int i = 0; i < 4; i++) {
        if (strcmp(trainees[i].nationality, "Korean") != 0) {
            validTrainees[count++] = i;
        }
    }

    // Select a random trainee from validTrainees
    srand(time(NULL));  // Seed random number generator
    int selectedIndex = validTrainees[rand() % count];
    printf("Welcome, %s, to the Korean quiz session!\n", trainees[selectedIndex].name);
    // Start the quiz for this trainee
    serveRandomQuiz(&trainees[selectedIndex]);
}

// Function to serve 5 random questions to the selected trainee
void serveRandomQuiz(Trainee *trainee) {
    QuizAnswer answers[5];  // Store the trainee's answers
    int totalScore = 0;

    printf("The quiz will begin in 30 seconds...\n");
    sleep(30);  // Wait for 30 seconds

    // Randomly select 5 unique questions from the question bank
    int questionIndexes[5];
    for (int i = 0; i < 5; i++) {
        int randomIndex;
        int isUnique;

        // Ensure unique questions are selected
        do {
            isUnique = 1;
            randomIndex = rand() % 10;
            for (int j = 0; j < i; j++) {
                if (questionIndexes[j] == randomIndex) {
                    isUnique = 0;
                    break;
                }
            }
        } while (!isUnique);
        
        questionIndexes[i] = randomIndex;
    }

    // Ask the 5 selected questions
    for (int i = 0; i < 5; i++) {
        KoreanQuestion q = questionBank[questionIndexes[i]];
        printf("Question %d: %s\n", q.id, q.content);

        char answer[256];
        printf("Your answer: ");
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';  // Remove trailing newline

        // Store the result in the quiz answer struct
        answers[i].questionId = q.id;
        answers[i].correctness = isAnswer(q.id, answer) ? 'O' : 'X';

        if (answers[i].correctness == 'O') {
            totalScore += 20;
        }
    }

    // Update trainee's quiz score and pass status
    trainee->quizScore = totalScore;
    if (totalScore >= 80) {
        strcpy(trainee->passStatus, "Passed");
    } else {
        strcpy(trainee->passStatus, "Failed");
    }

    // Display the result
    printf("Answer Sheet:\n");
    for (int i = 0; i < 5; i++) {
        printf("Question ID: %d, Correctness: %c\n", answers[i].questionId, answers[i].correctness);
    }
    printf("Total Score: %d\n", totalScore);
    printf("Pass Status: %s\n", trainee->passStatus);
}

// Function to check if the answer is correct
int isAnswer(int questionId, const char *answer) {
    for (int i = 0; i < 10; i++) {
        if (questionBank[i].id == questionId) {
            return strcmp(answer, questionBank[i].correctAnswer) == 0;
        }
    }
    return 0;  // If no match found, answer is incorrect
}

// Main function to trigger the quiz flow
int main() {
    selectRandomTakers();
    return 0;
}
