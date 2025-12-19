#include <stdio.h>
#include <string.h>

#define maxNoOfQuestions 15
#define passPercent 35

struct Question {
    char question[200];
    char optionA[50], optionB[50], optionC[50], optionD[50];
    char correct;
};

//Globally declared as used in multiple functions
struct Question q[maxNoOfQuestions]; 
int qnCount = 0; 

void login() {
    char user[20], pass[20];

    printf("\n Admin Login \n");
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin") == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid login!\n");
        login();
    }
}


void addQuestions() {
    int n;
    printf("\nHow many questions to add? ");
    scanf("%d", &n);

    if (qnCount + n > maxNoOfQuestions) {
        printf("You can add only 10 questions.\n");
    }

    //%[^\n] : Read everything until newline (including spaces)
    //number after '%' is its size limit
    for (int i = 0; i < n ; i++) {
        printf("\nQuestion %d:\n", qnCount + 1);

        printf("Enter question: ");
        scanf(" %199[^\n]", q[qnCount].question);

        printf("Option A: ");
        scanf(" %49[^\n]", q[qnCount].optionA);

        printf("Option B: ");
        scanf(" %49[^\n]", q[qnCount].optionB);

        printf("Option C: ");
        scanf(" %49[^\n]", q[qnCount].optionC);

        printf("Option D: ");
        scanf(" %49[^\n]", q[qnCount].optionD);

        printf("Correct option (A/B/C/D): ");
        scanf(" %c", &q[qnCount].correct);

        qnCount++;
    }
}


void startTest() {
    char name[50];
    int roll;
    int score = 0;
    char ans;

    if (qnCount == 0) {
        printf("No questions available!\n");
        return;
    }

    printf("\nStudent Details\n");
    printf("Name: ");
    scanf(" %49[^\n]", name);
    printf("Roll No: ");
    scanf("%d", &roll);

    for (int i = 0; i < qnCount; i++) {
        printf("\nQ%d. %s\n", i + 1, q[i].question);
        printf("A. %s\n", q[i].optionA);
        printf("B. %s\n", q[i].optionB);
        printf("C. %s\n", q[i].optionC);
        printf("D. %s\n", q[i].optionD);

        printf("Your answer: ");
        scanf(" %c", &ans);

        //"+32" because  'A' + 32 = 'a'
        if (ans == q[i].correct || ans == q[i].correct + 32) {
            score++;
        }
    }

    printf("\n Result \n");
    printf("Score: %d / %d\n", score, qnCount);

    int passMark = (passPercent * qnCount) / 100;

    if (score >= passMark)
        printf("Status: PASS\n");
    else
        printf("Status: FAIL\n");

    // Saving result in file:"result.txt"(appending)
    FILE *fp;
    fp= fopen("results.txt", "a");
    fprintf(fp, "Name: %s | Roll: %d | Score: %d/%d\n", name, roll, score, qnCount);
    fclose(fp);
}

// View saved results
void results() {
    char ch;
    FILE *fp ;
    fp= fopen("results.txt", "r");

    if (fp == NULL) {
        printf("No results found!\n");
    }

    printf("\n Previous Results\n");
    while ((ch = getc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}

int main() {
    int choice=0;

    while (choice!=4) {
        printf("\n ONLINE EXAMINATION SYSTEM \n");
        printf("1. Add Questions[Only for Admin]\n");
        printf("2. Start Test\n");
        printf("3. View Results\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        
        //Stopping infinite loop
        if (scanf("%d", &choice) != 1) {
        printf("Invalid input! Please enter a number.\n");
        while (getchar() != '\n'); // clear buffer
        continue;
        }

        switch (choice) {
            case 1:
                login();
                addQuestions();
                break;
            case 2:
                startTest();
                break;
            case 3:
                results();
                break;
            case 4:
                printf("Thank you!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}