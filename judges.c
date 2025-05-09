
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum length for strings
#define MAX_LENGTH 100
#define MAX_JUDGES 5
#define REQUIRED_FIELDS 7  // Name, Gender, Affiliation, Title, Expertise, Email, Phone

// Function to get a line of input safely
void get_input(char *input, int length) {
    fgets(input, length, stdin);
    // Remove the newline character if present
    input[strcspn(input, "\n")] = '\0';
}

// Function to display judge information in a formatted way
void display_judges_info(char judges_array[MAX_JUDGES][MAX_LENGTH]) {
    for (int i = 0; i < MAX_JUDGES; i++) {
        printf("[Judge %d]\n", i + 1);
        printf("%s\n", judges_array[i]);
        printf("-----------------------------------\n");
    }
}

int main() {
    char project_name[MAX_LENGTH];
    int total_judges;
    char judges_array[MAX_JUDGES][MAX_LENGTH];
    char input[MAX_LENGTH];

    // Display project info entry
    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");
    printf("Participating Project: ");
    get_input(project_name, MAX_LENGTH);
    
    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    getchar();  // Consume the newline character left by scanf

    // Initialize the judges array
    for (int i = 0; i < total_judges; i++) {
        printf("++++++++++++++++++++++++++++++++++++\n");
        printf("Starting to input information for Judge %d.\n", i + 1);
        printf("++++++++++++++++++++++++++++++++++++\n");
        
        // Collect information for the judge
        while (1) {
            printf("Judge %d: Enter the following information in the format: Name, Gender, Affiliation, Title, Expertise, Email, Phone\n", i + 1);
            get_input(input, MAX_LENGTH);
            
            // Check if the input contains exactly 7 fields (name, gender, affiliation, title, expertise, email, phone)
            int field_count = 0;
            char *token = strtok(input, ",");
            while (token != NULL) {
                field_count++;
                token = strtok(NULL, ",");
            }
            
            if (field_count == REQUIRED_FIELDS) {
                // If the correct number of fields is entered, store the judge's information
                strcpy(judges_array[i], input);
                break;
            } else {
                printf("The input items are incorrect. Please enter them again.\n");
            }
        }
    }

    // Judge information entry complete
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    // Ask the user if they want to check the judge information
    printf("Should we check the judge information? (Y/N): ");
    char check_info;
    scanf(" %c", &check_info);  // Space before %c to consume any extra newline
    getchar();  // Consume the newline after entering the character
    
    if (check_info == 'Y' || check_info == 'y') {
        // Display the project and judge information
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        // Display the project name
        printf("[PROJECT]: %s\n\n", project_name);

        // Display all judges' information
        display_judges_info(judges_array);
    } else {
        printf("Exiting the program.\n");
    }

    return 0;
}
