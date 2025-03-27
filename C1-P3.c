#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define CURRENT_YEAR 2025

// Structure to store candidate information
typedef struct {
    char name[50];
    int dob_year, dob_month, dob_day;
    char gender;
    char email[50];
    char nationality[30];
    float bmi;
    char primary_skill[30];
    char secondary_skill[30];
    int topik;
    char mbti[5];
    char introduction[200];
} Candidate;

int main() {
    Candidate candidates[NUM_CANDIDATES];
    char group_name[50];
    int i = 0;
    
    printf("Enter audition group name: ");
    fgets(group_name, sizeof(group_name), stdin);
    group_name[strcspn(group_name, "\n")] = 0; // Remove newline
    
    // Data Entry
    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Entry\n", group_name);
    printf("####################################\n\n");
    
    while (i < NUM_CANDIDATES) {
        printf("Entering information for candidate %d.\n", i + 1);
        printf("1. Name: "); fgets(candidates[i].name, sizeof(candidates[i].name), stdin); candidates[i].name[strcspn(candidates[i].name, "\n")] = 0;
        printf("2. Date of Birth (YYYY/MM/DD): "); scanf("%d/%d/%d", &candidates[i].dob_year, &candidates[i].dob_month, &candidates[i].dob_day);
        printf("3. Gender (F/M): "); scanf(" %c", &candidates[i].gender);
        getchar(); // Clear newline
        printf("4. Email: "); fgets(candidates[i].email, sizeof(candidates[i].email), stdin); candidates[i].email[strcspn(candidates[i].email, "\n")] = 0;
        printf("5. Nationality: "); fgets(candidates[i].nationality, sizeof(candidates[i].nationality), stdin); candidates[i].nationality[strcspn(candidates[i].nationality, "\n")] = 0;
        printf("6. BMI: "); scanf("%f", &candidates[i].bmi);
        getchar();
        printf("7. Primary Skill: "); fgets(candidates[i].primary_skill, sizeof(candidates[i].primary_skill), stdin); candidates[i].primary_skill[strcspn(candidates[i].primary_skill, "\n")] = 0;
        printf("8. Secondary Skill: "); fgets(candidates[i].secondary_skill, sizeof(candidates[i].secondary_skill), stdin); candidates[i].secondary_skill[strcspn(candidates[i].secondary_skill, "\n")] = 0;
        printf("9. Korean Proficiency Level (TOPIK): "); scanf("%d", &candidates[i].topik);
        getchar();
        printf("10. MBTI: "); fgets(candidates[i].mbti, sizeof(candidates[i].mbti), stdin); candidates[i].mbti[strcspn(candidates[i].mbti, "\n")] = 0;
        printf("11. Introduction: "); fgets(candidates[i].introduction, sizeof(candidates[i].introduction), stdin); candidates[i].introduction[strcspn(candidates[i].introduction, "\n")] = 0;
        
        i++;
        printf("---------------------------------\n");
    }
    
    // Data Review
    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("Name (Age)       | DOB       | Gender | Email                 | Nationality | BMI  | Primary Skill | Secondary Skill | TOPIK | MBTI |\n");
    printf("=============================================================================================\n");
    
    for (i = 0; i < NUM_CANDIDATES; i++) {
        int age = CURRENT_YEAR - candidates[i].dob_year;
        printf("%-15s (%d) | %04d%02d%02d | %c      | %-20s | %-12s | %-4.1f | %-12s | %-15s | %-5s | %-4s |\n", 
            candidates[i].name, age, 
            candidates[i].dob_year, candidates[i].dob_month, candidates[i].dob_day, 
            candidates[i].gender, candidates[i].email, 
            candidates[i].nationality, candidates[i].bmi, 
            candidates[i].primary_skill, candidates[i].secondary_skill, 
            (candidates[i].topik == 0) ? "Native" : "Basic", candidates[i].mbti);
        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[i].introduction);
        printf("---------------------------------------------------------------------------------------------\n");
    }
    return 0;
}
