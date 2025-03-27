#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep() on Linux/macOS
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

void printSplashScreen(char *name, char *date) {
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    // Print right-angled and inverted right-angled triangles
    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < i; j++) printf("*"); // Left Triangle
        printf("      [Magrathea ver 0.1]      ");
        for (int j = 0; j < 6 - i; j++) printf("*"); // Right Triangle
        printf("\n");
    }

    printf("   Magrathea, where a shining planet is created in a wasteland with no grass,\n");
    printf("a place where unseen potential is discovered and gems are polished by experts,\n");
    printf("                         Welcome to Magrathea.\n");
    
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s                     [Execution Time]: %s\n", name, date);
    printf("===============================================================================\n");
}

int main() {
    char name[50];
    char date[11];

    // Take user input
    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%10s", date);
    printf("[Please enter your name]: ");
    scanf(" %49[^\n]", name); // Reads full name with spaces

    // Confirmation message
    printf("**The input has been processed successfully.**\n");

    // Wait for 3 seconds and clear the screen
    sleep(3);
    system(CLEAR_SCREEN);

    // Display the splash screen
    printSplashScreen(name, date);

    return 0;
}
