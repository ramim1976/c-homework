#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTISTS 100
#define MAX_LEN 100

// Encryption Types
#define XOR 1
#define OR 2
#define AND 3
#define SHIFT 4

// Artist structure
typedef struct {
    char name[MAX_LEN];
    char nickname[MAX_LEN];
    char dob[MAX_LEN];
    char gender[MAX_LEN];
    char education[MAX_LEN];
    char phone[MAX_LEN];
    char email[MAX_LEN];
    char nationality[MAX_LEN];
    char height[MAX_LEN];
    char weight[MAX_LEN];
    char blood[MAX_LEN];
    char allergies[MAX_LEN];
    char sns[MAX_LEN];
} Artist;

// External Variables
int encryption_type;
unsigned char encryption_key;

// Encryption Algorithms
void encrypt(char *data, unsigned char key, int type) {
    for (int i = 0; data[i]; i++) {
        switch (type) {
            case XOR: data[i] ^= key; break;
            case OR:  data[i] |= key; break;
            case AND: data[i] &= key; break;
            case SHIFT: data[i] = (data[i] << 1) | ((data[i] >> 7) & 1); break;
        }
    }
}

void decrypt(char *data, unsigned char key, int type) {
    for (int i = 0; data[i]; i++) {
        switch (type) {
            case XOR: data[i] ^= key; break;
            case OR:  /* Cannot decrypt reliably */ break;
            case AND: /* Cannot decrypt reliably */ break;
            case SHIFT: data[i] = (data[i] >> 1) | ((data[i] & 1) << 7); break;
        }
    }
}

// Save artist data to file
void saveArtistsToFile(Artist *artists, int count, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("File open failed");
        return;
    }
    for (int i = 0; i < count; i++) {
        Artist temp = artists[i];
        encrypt(temp.phone, encryption_key, encryption_type);
        encrypt(temp.email, encryption_key, encryption_type);
        encrypt(temp.allergies, encryption_key, encryption_type);
        fwrite(&temp, sizeof(Artist), 1, fp);
    }
    fclose(fp);
}

// Load artists from file
int loadArtistsFromFile(Artist *artists, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("File open failed");
        return 0;
    }
    int count = 0;
    while (fread(&artists[count], sizeof(Artist), 1, fp)) {
        count++;
    }
    fclose(fp);
    return count;
}

// Menu function
void protectMyData() {
    Artist artists[MAX_ARTISTS];
    int count;

    printf("Enter number of artists: ");
    scanf("%d", &count);
    getchar();

    printf("Select encryption algorithm:\n1. XOR\n2. OR\n3. AND\n4. Bit Shift\n> ");
    scanf("%d", &encryption_type);
    getchar();

    printf("Enter encryption key (0~255): ");
    scanf("%hhu", &encryption_key);
    getchar();

    for (int i = 0; i < count; i++) {
        printf("\n--- Artist #%d ---\n", i + 1);
        printf("Name: "); fgets(artists[i].name, MAX_LEN, stdin);
        printf("Nickname: "); fgets(artists[i].nickname, MAX_LEN, stdin);
        printf("DOB: "); fgets(artists[i].dob, MAX_LEN, stdin);
        printf("Gender: "); fgets(artists[i].gender, MAX_LEN, stdin);
        printf("Education: "); fgets(artists[i].education, MAX_LEN, stdin);
        printf("Phone: "); fgets(artists[i].phone, MAX_LEN, stdin);
        printf("Email: "); fgets(artists[i].email, MAX_LEN, stdin);
        printf("Nationality: "); fgets(artists[i].nationality, MAX_LEN, stdin);
        printf("Height: "); fgets(artists[i].height, MAX_LEN, stdin);
        printf("Weight: "); fgets(artists[i].weight, MAX_LEN, stdin);
        printf("Blood Type: "); fgets(artists[i].blood, MAX_LEN, stdin);
        printf("Allergies: "); fgets(artists[i].allergies, MAX_LEN, stdin);
        printf("SNS: "); fgets(artists[i].sns, MAX_LEN, stdin);
    }

    saveArtistsToFile(artists, count, "artists.dat");
    printf("\nArtist data saved with encryption.\n");

    // View Menu
    Artist loaded[MAX_ARTISTS];
    int loaded_count = loadArtistsFromFile(loaded, "artists.dat");

    printf("\nList of Artists:\n");
    for (int i = 0; i < loaded_count; i++) {
        printf("%d. %s (%s)", i + 1, loaded[i].name, loaded[i].nickname);
    }

    int choice;
    printf("\nSelect artist by number to view details: ");
    scanf("%d", &choice);
    getchar();

    if (choice >= 1 && choice <= loaded_count) {
        Artist *a = &loaded[choice - 1];
        printf("\nName: %sNickname: %sDOB: %sGender: %sEducation: %s", a->name, a->nickname, a->dob, a->gender, a->education);
        printf("Phone: %sEmail: %sAllergies: %sNationality: %sHeight: %sWeight: %sBlood Type: %sSNS: %s",
            a->phone, a->email, a->allergies, a->nationality, a->height, a->weight, a->blood, a->sns);

        printf("\nDo you want to decrypt sensitive data? (y/n): ");
        char confirm;
        scanf("%c", &confirm);
        getchar();
        if (confirm == 'y' || confirm == 'Y') {
            unsigned char key_check;
            printf("Enter encryption key to decrypt: ");
            scanf("%hhu", &key_check);
            if (key_check == encryption_key) {
                decrypt(a->phone, encryption_key, encryption_type);
                decrypt(a->email, encryption_key, encryption_type);
                decrypt(a->allergies, encryption_key, encryption_type);
                printf("\n[Decrypted Info]\nPhone: %sEmail: %sAllergies: %s\n", a->phone, a->email, a->allergies);
            } else {
                printf("Incorrect key. Cannot decrypt.\n");
            }
        }
    }
}
