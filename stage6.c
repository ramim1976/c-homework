#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SOCIALS 5

typedef struct {
    char **qualifications;
    int num_qualifications;
    int number_of_hires;
    char job_field[50];
} JobDetails;

typedef struct {
    int id;
    char title[100];
    char posting_date[11];
    char deadline[11];
    JobDetails details;
} JobAd;

typedef struct {
    char name[20];
    char api_key[50];
    char api_url[100];
} SocialNetwork;

SocialNetwork socials[MAX_SOCIALS] = {
    {"Facebook", "FB123", "https://api.facebook.com/post"},
    {"Instagram", "IG456", "https://api.instagram.com/post"},
    {"Thread", "TH789", "https://api.thread.com/post"},
    {"LinkedIn", "LI101", "https://api.linkedin.com/post"},
    {"X", "X202", "https://api.x.com/post"}
};

JobAd *job_ads = NULL;
int job_count = 0;
int next_id = 1;

int isExpired(const char *deadline) {
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    char current_date[11];
    strftime(current_date, sizeof(current_date), "%Y-%m-%d", now);
    return strcmp(deadline, current_date) < 0;
}

void createJobPosting() {
    JobAd new_job;
    new_job.id = next_id++;

    printf("Enter job title (max 100): ");
    fgets(new_job.title, sizeof(new_job.title), stdin);
    new_job.title[strcspn(new_job.title, "\n")] = 0;

    printf("Enter posting date (YYYY-MM-DD): ");
    scanf("%10s", new_job.posting_date);
    printf("Enter deadline (YYYY-MM-DD): ");
    scanf("%10s", new_job.deadline);

    printf("Enter number of hires: ");
    scanf("%d", &new_job.details.number_of_hires);
    getchar();

    printf("Enter job field (max 50): ");
    fgets(new_job.details.job_field, sizeof(new_job.details.job_field), stdin);
    new_job.details.job_field[strcspn(new_job.details.job_field, "\n")] = 0;

    printf("Enter number of qualifications: ");
    scanf("%d", &new_job.details.num_qualifications);
    getchar();

    new_job.details.qualifications = malloc(sizeof(char *) * new_job.details.num_qualifications);
    for (int i = 0; i < new_job.details.num_qualifications; i++) {
        char buffer[100];
        printf("Enter qualification #%d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        new_job.details.qualifications[i] = strdup(buffer);
    }

    job_ads = realloc(job_ads, sizeof(JobAd) * (job_count + 1));
    job_ads[job_count++] = new_job;
    printf("Job posting created successfully!\n");
}

void viewJobPostings() {
    if (job_count == 0) {
        printf("No job postings found. Redirecting to Create Job Posting...\n");
        createJobPosting();
        return;
    }

    printf("Active Job Postings:\n");
    for (int i = 0; i < job_count; i++) {
        if (!isExpired(job_ads[i].deadline)) {
            printf("ID: %d | Title: %s | Deadline: %s\n",
                job_ads[i].id, job_ads[i].title, job_ads[i].deadline);
        }
    }

    int selected_id;
    printf("Enter ID to view details (or -1 to skip): ");
    scanf("%d", &selected_id);
    getchar();

    for (int i = 0; i < job_count; i++) {
        if (job_ads[i].id == selected_id) {
            JobAd *j = &job_ads[i];
            printf("\nTitle: %s\nPosted on: %s\nDeadline: %s\nHires: %d\nField: %s\nQualifications:\n",
                j->title, j->posting_date, j->deadline, j->details.number_of_hires, j->details.job_field);
            for (int q = 0; q < j->details.num_qualifications; q++) {
                printf(" - %s\n", j->details.qualifications[q]);
            }
            break;
        }
    }
}

void postOnSocialNetwork() {
    int id;
    printf("Enter Job Posting ID to post: ");
    scanf("%d", &id);
    getchar();

    JobAd *selected = NULL;
    for (int i = 0; i < job_count; i++) {
        if (job_ads[i].id == id) {
            selected = &job_ads[i];
            break;
        }
    }

    if (!selected) {
        printf("Invalid ID.\n");
        return;
    }

    printf("Select social network:\n");
    for (int i = 0; i < MAX_SOCIALS; i++) {
        printf("%d. %s\n", i + 1, socials[i].name);
    }

    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice >= 1 && choice <= MAX_SOCIALS) {
        printf("Posting to %s...\n", socials[choice - 1].name);
        printf("API Key: %s | URL: %s\n", socials[choice - 1].api_key, socials[choice - 1].api_url);
        printf("Posted job: %s (ID: %d)\n", selected->title, selected->id);
        printf("\u2705 Post successful!\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void freeMemory() {
    for (int i = 0; i < job_count; i++) {
        for (int j = 0; j < job_ads[i].details.num_qualifications; j++) {
            free(job_ads[i].details.qualifications[j]);
        }
        free(job_ads[i].details.qualifications);
    }
    free(job_ads);
}

void findSpecialistMenu() {
    int choice;
    do {
        printf("\n[II. Training > 6. Visual & Image Training > A. Finding People]\n");
        printf("1. Create Job Posting\n");
        printf("2. View Job Postings\n");
        printf("3. Post on Social Networks\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: createJobPosting(); break;
            case 2: viewJobPostings(); break;
            case 3: postOnSocialNetwork(); break;
            case 4: printf("Exiting to previous menu...\n"); break;
            default: printf("Invalid option. Try again.\n"); break;
        }
    } while (choice != 4);

    freeMemory();
}

int main() {
    findSpecialistMenu();
    return 0;
}
