#include <stdio.h>
#include <stdlib.h>

#define CANDIDATE_COUNT 6
#define PASS_COUNT 4

// Function to calculate weight from height and BMI
float calculate_weight(float height, float bmi) {
    return bmi * height * height; // weight = bmi * height^2
}

// Function to classify BMI
void print_bmi_status(float bmi) {
    int category;
    if (bmi < 18.5) category = 0;       // Underweight
    else if (bmi < 25.0) category = 1;  // Normal
    else if (bmi < 30.0) category = 2;  // Overweight
    else category = 3;                  // Obese

    switch (category) {
        case 0: printf("BMI Status: Underweight\n"); break;
        case 1: printf("BMI Status: Normal\n"); break;
        case 2: printf("BMI Status: Overweight\n"); break;
        case 3: printf("BMI Status: Obese\n"); break;
    }
}

int main() {
    // 1D arrays for candidate data (id, height, BMI, pass/fail)
    float candidate_arr[CANDIDATE_COUNT][4] = {
        {1001, 1.68, 20.2, 1},  // Passed
        {1002, 1.78, 24.1, 1},  // Passed
        {1003, 1.63, 21.5, 1},  // Passed
        {1004, 1.75, 19.0, 1},  // Passed
        {1005, 1.65, 22.0, 0},  // Failed
        {1006, 1.70, 23.5, 0}   // Failed
    };

    // Arrays to store interview data of passed candidates
    char* names[PASS_COUNT] = {"Park Ji-yeon", "Ethan Smith", "Helena Silva", "Liam Wilson"};
    char* nicknames[PASS_COUNT] = {"Ariel", "Lion", "Belle", "Aladdin"};
    char* education[PASS_COUNT] = {
        "Dropped out of high school", 
        "Dropped out of 3rd year of middle school", 
        "Middle school graduate", 
        "Dropped out of 2nd year of middle school"
    };
    char* blood[PASS_COUNT] = {"A", "THE", "B", "AB"};
    char* allergies[PASS_COUNT] = {"Dairy products", "peanut", "fish", "shellfish"};
    char* hobbies[PASS_COUNT] = {
        "dance practice, composition", 
        "Song writing, health training", 
        "Singing, drawing", 
        "Dancing, producing music"
    };
    char* sns[PASS_COUNT] = {
        "Instagram - @Ariel_Jiyeon", 
        "Twitter - @Simba_Ethan", 
        "Instagram - @Belle_Helena", 
        "Instagram - @Aladdin_Liam"
    };

    // Output Finalists
    printf("===== Milliways Finalist List =====\n");

    int idx = 0;
    for (int i = 0; i < CANDIDATE_COUNT; i++) {
        if ((int)candidate_arr[i][3] == 1) { // If candidate passed
            int id = (int)candidate_arr[i][0];
            float height = candidate_arr[i][1];
            float bmi = candidate_arr[i][2];
            float weight = calculate_weight(height, bmi);

            // Output the data for passed candidates
            printf("\nCandidate ID: %d\n", id);
            printf("Name: %s (%s)\n", names[idx], nicknames[idx]);
            printf("Education: %s\n", education[idx]);
            printf("Height: %.2f m\n", height);
            printf("BMI: %.1f\n", bmi);
            printf("Weight (calculated): %.1f kg\n", weight);
            print_bmi_status(bmi); // Print BMI status
            printf("Blood Type: %s\n", blood[idx]);
            printf("Allergy: %s\n", allergies[idx]);
            printf("Hobbies: %s\n", hobbies[idx]);
            printf("SNS: %s\n", sns[idx]);
            idx++;
        }
    }

    return 0;
}
