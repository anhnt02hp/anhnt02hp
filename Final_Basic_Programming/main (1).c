#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Student {
    //Attribute
    char studentID[20];
    char fullName[50];
    char DoB[20];
    float AlgeScore;
    float CalScore;
    float BPScore;
    float GPA;
};

//2. Enter student information
void enterStudentInfor(struct Student ds[], int n){
    printf("Enter student information:\n");
    for(int i = 0; i <= n - 1; i++){
        printf("Student %d: \n", i + 1);
        printf("    ID: ");
        fgets(ds[i].studentID, sizeof(ds[i].studentID), stdin);
        ds[i].studentID[strcspn(ds[i].studentID, "\n")] = '\0';
        
        printf("    fullName: ");
        fgets(ds[i].fullName, sizeof(ds[i].fullName), stdin);
        ds[i].fullName[strcspn(ds[i].fullName, "\n")] = '\0';
        
        printf("    DoB: ");
        fgets(ds[i].DoB, sizeof(ds[i].DoB), stdin);
        ds[i].DoB[strcspn(ds[i].DoB, "\n")] = '\0';
        
        printf("    AlgeScore: ");
        scanf("%f", &ds[i].AlgeScore);
        
        printf("    CalScore: ");
        scanf("%f", &ds[i].CalScore);
        
        printf("    BPScore: ");
        scanf("%f", &ds[i].BPScore);
        
        while(getchar() != '\n');        
    }
}

//3. Show student information
void showStudentInfor(struct Student ds[], int n){
    //show header
    printf("===================================================STUDENT INFORMATION===================================================\n");
    printf("%-20s %-30s %-20s %-10s %-10s %-10s %-10s\n", 
       "studentID", "fullName", "DoB", "AlgeScore", "CalScore", "BPScore", "GPA");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    
    //show infor
    for(int i = 0; i <= n - 1; i++){
        ds[i].GPA = (ds[i].AlgeScore + ds[i].CalScore + ds[i].BPScore) / 3;
        printf("%-20s %-30s %-20s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
            ds[i].studentID,
            ds[i].fullName,
            ds[i].DoB,
            ds[i].AlgeScore,
            ds[i].CalScore,
            ds[i].BPScore,
            ds[i].GPA
        );    
    }
    printf("=========================================================================================================================\n");
}

//4. Save student information into text file
void saveStudentInforToFile(struct Student ds[], int n){
    //open file
    FILE *fp = fopen("students_infor.txt", "w");
    
    //save header
    fprintf(fp,"===================================================STUDENT INFORMATION===================================================\n");
    fprintf(fp,"%-20s %-30s %-20s %-10s %-10s %-10s %-10s\n", "studentID", "fullName", "DoB", "AlgeScore", "CalScore", "BPScore", "GPA");
    fprintf(fp,"-------------------------------------------------------------------------------------------------------------------------\n");
    
    //save file
    if(fp == false){
        printf("Can Not open file!\n");
    } else {
        for(int i = 0; i <= n - 1; i++){
            ds[i].GPA = (ds[i].AlgeScore + ds[i].CalScore + ds[i].BPScore) / 3;
            fprintf(fp, "%-20s %-30s %-20s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
                ds[i].studentID,
                ds[i].fullName,
                ds[i].DoB,
                ds[i].AlgeScore,
                ds[i].CalScore,
                ds[i].BPScore,
                ds[i].GPA
            );    
        }
    }
    fprintf(fp,"=========================================================================================================================\n");
    
    //close file
    fclose(fp);
    printf("Save file successful!\n");
}

//5. Find Student having highest GPA, lowest GPA, highest BPScore
//Find highest GPA
void showStudentMAXGPA(struct Student ds[], int n){
    int idxMaxGPA = 0;
    float MAX_GPA = ds[0].GPA;
    for(int i = 0; i <= n - 1; i++){
        if(ds[i].GPA > MAX_GPA){
            MAX_GPA = ds[i].GPA;
            idxMaxGPA = i;
        }
    }
    printf("Student %d has highest GPA!\n", idxMaxGPA + 1);
}

//Find lowest GPA
void showStudentMINGPA(struct Student ds[], int n){
    int idxMinGPA = 0;
    float MIN_GPA = ds[0].GPA;
    for(int i = 0; i <= n - 1; i++){
        if(ds[i].GPA < MIN_GPA){
            MIN_GPA = ds[i].GPA;
            idxMinGPA = i;
        }
    }
    printf("Student %d has lowest GPA!\n", idxMinGPA + 1);
}

//Find highest BPScore
void showStudentMAXBPScore(struct Student ds[], int n){
    int idxMaxBPScore = 0;
    float MAX_BPSCORE = ds[0].BPScore;
    for(int i = 0; i <= n - 1; i++){
        if(ds[i].BPScore > MAX_BPSCORE){
            MAX_BPSCORE = ds[i].BPScore;
            idxMaxBPScore = i;
        }
    }
    printf("Student %d has highest BPScore!\n", idxMaxBPScore + 1);
}

//6. Split fullName into First Name and Last Name
void splitFullName(struct Student ds[], int n){
    for(int i = 0; i <= n - 1; i++){
        char fullNameTemp[50];
        strcpy(fullNameTemp, ds[i].fullName);
        
        char *token_word[50]; //eg.token_word = [&fullName[0], &fullName[7],...] 
        char *token = strtok(fullNameTemp, " "); //token = &fullName[0]
        
        int count = 0;
        for(int j = 0; j <= 49; j++){
            count++;
            token_word[j] = token; 
            token = strtok('\0', " ");
            
            if(token == NULL){
                break;
            }
        }
        
        //printf
        printf("LastName of %d Student: %s\n", i + 1, token_word[count - 1]);
    }
    
}

//7. Find Oldest Student
int convertDoB(char *DoB) {
    int day, month, year;
    sscanf(DoB, "%d/%d/%d", &day, &month, &year);
    //Convert dd/mm/yyyy -> yyyymmdd
    int newDoB = year * 10000 + month * 100 + day;
    return newDoB;
}

void findOldestStudent(struct Student ds[], int n){
    int idx_oldest = 0;
    int oldest = convertDoB(ds[0].DoB);
    
    for(int i = 0; i <= n - 1; i++){
        if(convertDoB(ds[i].DoB) < oldest){
            oldest = convertDoB(ds[i].DoB);
            idx_oldest = i;
        }
    }
    
    printf("%s is the oldest student!\n", ds[idx_oldest].fullName);
}

//8. Find Youngest Student
void findYoungestStudent(struct Student ds[], int n){
    int idx_yougest = 0;
    int youngest = convertDoB(ds[0].DoB);
    
    for(int i = 0; i <= n - 1; i++){
        if(convertDoB(ds[i].DoB) > youngest){
            youngest = convertDoB(ds[i].DoB);
            idx_yougest = i;
        }
    }
    
    printf("%s is the youngest student!\n", ds[idx_yougest].fullName);
}

//9. Search Student by studentID
void searchStudentID(struct Student ds[], int n){
    printf("Search student by ID: ");
    char stdID[50];
    fgets(stdID, sizeof(stdID), stdin);
    stdID[strcspn(stdID, "\n")] = '\0';

    bool canFind = false;
    for(int i = 0; i <= n - 1; i++){
        if(strcmp(stdID,ds[i].studentID) == 0){
            canFind = true;
            printf("%-20s %-30s %-20s %-10.2f %-10.2f %-10.2f %-10.2f\n", 
                ds[i].studentID, ds[i].fullName, ds[i].DoB, ds[i].AlgeScore, ds[i].CalScore, ds[i].BPScore, ds[i].GPA);
            printf("DONE!\n");
            break;
        }
    }
    
    if(canFind == false){
        printf("NO MATCHED ID!\n");
    }
}

//10. Sort GPA with Descent order
void sortGPAStudent(struct Student ds[], int n){
    //sort
    for(int i = 0; i <= n - 1; i++){
        int idx_max = i;
        float MAX_GPA = ds[i].GPA;
        
        for(int j = i; j <= n - 1; j++){
            if(ds[j].GPA > MAX_GPA){
                MAX_GPA = ds[j].GPA;
                idx_max = j;
            }    
        }
        //swap
        struct Student tmp_GPA = ds[i];
        ds[i] = ds[idx_max];
        ds[idx_max] = tmp_GPA;
    }
    
    //print
    for(int i = 0; i <= n - 1; i++){
        printf("%d. %s\n", i + 1, ds[i].fullName);
    }
}

int main() {
    //1. Enter student number
    printf("Enter student number: \nn = ");
    int n; scanf("%d", &n);
    while(getchar() != '\n');        
    
    //2. Enter student information
    struct Student ds[n];
    enterStudentInfor(ds, n);
    
    //3. Show student information
    showStudentInfor(ds, n);
    
    //4. Save student information into text file
    saveStudentInforToFile(ds, n);
    
    //5. Find Student having highest GPA, lowest GPA, highest BPScore
    showStudentMAXGPA(ds, n);
    showStudentMINGPA(ds, n);
    showStudentMAXBPScore(ds, n);
    
    //6. Split Full Name into First Name and Last Name and Middle Name
    splitFullName(ds, n);

    //7. Find Oldest Student
    findOldestStudent(ds, n);

    //8. Find Youngest Student
    findYoungestStudent(ds, n);
    
    //9. Search Student by studentID
    searchStudentID(ds, n);
    
    //10.Sort student GPA Descent order
    sortGPAStudent(ds, n);
}