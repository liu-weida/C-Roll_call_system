#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char ID[16];    // Student ID
    char Name[24];  // Name
    int  Status;    // Absentee status (1 for absent, 0 for present)
    int  AbsentCount; // Number of absences
    char AbsentCourses[256]; // Course names of absences
} Student;

typedef struct StudentList {
    Student StudentDatas[256]; // Student array
    int     Length;     // Used length of the student array
    int     Capacity;   // Maximum length of the student array
} StudentList;

const char *filepath = "file20.txt"; // File path

const char *courseFilepath = "course_number.txt";

// Function declarations
void StudentListInit(StudentList *List);
int StudentListFindByID(StudentList *List , const char *ID);
StudentList StudentListNewFromFilepath(const char *filepath);
void StudentListSaveToFile(StudentList *List , const char *filepath);
void CallTheRollItem(StudentList *List, int courseNum, char *courseName);
void CountStudentInfoItem(StudentList *List);
void StudentManagement(StudentList *List);
void CallTheRollMenu(int courseNum, const char *courseFilepath);
int LoadCourseNumberFromFile(const char *courseFilepath);
void SaveCourseNumberToFile(int courseNum, const char *courseFilepath);
void AddStudent(StudentList *List);
void DeleteStudent(StudentList *List);
void ModifyStudent(StudentList *List);
void SaveCourseNumberToFile(int courseNum, const char *filename);
int LoadCourseNumberFromFile(const char *filename);


void StudentListInit(StudentList *List) {
    List->Length = 0;
    List->Capacity = 256;
}

int StudentListFindByID(StudentList *List , const char *ID) {
    int Index;

    if (List == NULL || ID == NULL) {
        return -1;
    }

    for (Index = 0; Index < List->Length; ++Index) {
        if (strcmp(List->StudentDatas[Index].ID , ID) == 0) {
            return Index;
        }
    }
    return -1;
}

StudentList StudentListNewFromFilepath(const char *filepath) {
    FILE *fp;
    StudentList List;
    int Index;

    StudentListInit(&List);
    if (filepath == NULL) {
        return List;
    }
    fp = fopen(filepath, "rt");
    if (!fp) {
        return List;
    }

    Index = 0;
    char line[512];
    while (!feof(fp) && Index < List.Capacity) {
        if (fgets(line, sizeof(line), fp) == NULL) {
            break;
        }
        sscanf(line, "%s %s %d %d", List.StudentDatas[Index].ID, List.StudentDatas[Index].Name, &List.StudentDatas[Index].Status, &List.StudentDatas[Index].AbsentCount);

        // Find the starting position of the absent courses
        char *absentCoursesStart = strchr(line, '"');
        if (absentCoursesStart) {
            // Remove the leading quote
            absentCoursesStart++;
            // Find the ending position of the absent courses
            char *absentCoursesEnd = strchr(absentCoursesStart, '"');
            if (absentCoursesEnd) {
                // Remove the trailing quote
                *absentCoursesEnd = '\0';
                strcpy(List.StudentDatas[Index].AbsentCourses, absentCoursesStart);
            } else {
                strcpy(List.StudentDatas[Index].AbsentCourses, "");
            }
        } else {
            strcpy(List.StudentDatas[Index].AbsentCourses, "");
        }

        ++Index;
    }
    List.Length = Index;
    fclose(fp);
    return List;
}


void StudentListSaveToFile(StudentList *List , const char *filepath) {
    FILE *fp;
    int Index;
    if (filepath == NULL || List == NULL) {
        return;
    }
    fp = fopen(filepath , "wt");
    if (!fp) {
        return;
    }
    for (Index = 0; Index < List->Length; ++Index) {
        fprintf(fp, "%s %s %d %d \"%s\"\n",
                List->StudentDatas[Index].ID,
                List->StudentDatas[Index].Name,
                List->StudentDatas[Index].Status,
                List->StudentDatas[Index].AbsentCount,
                List->StudentDatas[Index].AbsentCourses);
    }
    fclose(fp);
}

void CallTheRollItem(StudentList *List, int courseNum, char *courseName) {
    int Index;
    if (List == NULL || List->Length == 0) {
        system("cls");
        printf("Teacher roll call\n");
        printf("The number of students is zero\n");
    } else {
        for (Index = 0; Index < List->Length; ++Index) {
            system("cls");
            printf("Teacher roll call(%d/%d)\n" , Index + 1 , List->Length);
            printf("Student number: %s\n" , List->StudentDatas[Index].ID);
            printf("Name: %s\n" , List->StudentDatas[Index].Name);
            printf("Absent or not(0.No,1.Yes):");
            int previousStatus = List->StudentDatas[Index].Status;
            scanf("%d" , &List->StudentDatas[Index].Status);
            if (List->StudentDatas[Index].Status == 1) {
                List->StudentDatas[Index].AbsentCount++;
                strcat(List->StudentDatas[Index].AbsentCourses, " ");
                strcat(List->StudentDatas[Index].AbsentCourses, courseName);
            }
        }
        system("cls");
        printf("Teacher roll call\n");
        printf("End of roll call\n");
        StudentListSaveToFile(List, filepath);
    }
    system("pause");
}

void CountStudentInfoItem(StudentList *List) {
    int Index;
    int Absent = 0;
    if (List == NULL) {
        return;
    }
    system("cls");
    printf("*****************Information Statistics*****************\n");
    for (Index = 0; Index < List->Length; ++Index) {
        if (List->StudentDatas[Index].Status == 1) {
            ++Absent;
        }
    }

    printf("The number of absentees is: %d\n" , Absent);
    printf("The number of non-absent persons is: %d\n" , List->Length - Absent);

    int choice;
    printf("Do you want to display the attendance of each student?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Please select:");
    scanf("%d", &choice);

    if (choice == 1) {
        for (Index = 0; Index < List->Length; ++Index) {
            printf("\nStudent number: %s\n", List->StudentDatas[Index].ID);
            printf("Name: %s\n", List->StudentDatas[Index].Name);
            printf("Absent count: %d\n", List->StudentDatas[Index].AbsentCount);
            printf("Absent courses:%s\n", List->StudentDatas[Index].AbsentCourses);
        }
    }

    system("pause");
}

void AddStudent(StudentList *List) {
    Student

    student;
    if (List == NULL) {
        return;
    }
    system("cls");
    printf("*****************Student information addition*****************\n");

    if (List->Length == List->Capacity) {
        printf("Failed to add,Student storage is full\n");
    } else {
        printf("Please enter your student number:");
        scanf("%s" , student.ID);

        printf("Please enter your name:");
        scanf("%s" , student.Name);

        student.Status = 0;
        student.AbsentCount = 0;
        strcpy(student.AbsentCourses, "");

        if (StudentListFindByID(List, student.ID) != -1) {
            printf("The student with the same student number already exists.\n");
        } else {
            List->StudentDatas[List->Length] = student;
            List->Length++;
            printf("The student was added successfully.\n");
            StudentListSaveToFile(List, filepath);
        }
    }
    system("pause");
}

void RemoveStudent(StudentList *List) {
    char studentID[16];
    int index;
    if (List == NULL) {
        return;
    }

    system("cls");
    printf("*****************Student information deletion*****************\n");
    printf("Please enter the student number to remove:");
    scanf("%s", studentID);

    index = StudentListFindByID(List, studentID);
    if (index == -1) {
        printf("Student not found.\n");
    } else {
        for (int i = index; i < List->Length - 1; i++) {
            List->StudentDatas[i] = List->StudentDatas[i + 1];
        }
        List->Length--;
        printf("The student has been removed successfully.\n");
        StudentListSaveToFile(List, filepath);
    }
    system("pause");

}

void ModifyStudent(StudentList *List) {
    char studentID[16];
    int index;
    if (List == NULL) {
        return;
    }

    system("cls");
    printf("*****************Student information modification*****************\n");
    printf("Please enter the student number to modify:");
    scanf("%s", studentID);

    index = StudentListFindByID(List, studentID);
    if (index == -1) {
        printf("Student not found.\n");
    } else {
        printf("Enter new student number:");
        scanf("%s", List->StudentDatas[index].ID);
        printf("Enter new student name:");
        scanf("%s", List->StudentDatas[index].Name);
        printf("The student information has been modified successfully.\n");
        StudentListSaveToFile(List, filepath);
    }
    system("pause");

}

void StudentManagement(StudentList *List) {
    int choice;
    while (1) {
        system("cls");
        printf("Student Management\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Modify Student\n");
        printf("4. Back to Main Menu\n");
        printf("Please select:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                AddStudent(List);
                break;
            case 2:
                RemoveStudent(List);
                break;
            case 3:
                ModifyStudent(List);
                break;
            case 4:
                return;
            default:
                printf("Invalid input\n");
                system("pause");
                break;
        }
    }

}

void CallTheRollMenu(int courseNum, const char *courseFilepath) {
    char course_Name[256];
    int choice;
    StudentList List = StudentListNewFromFilepath(filepath);
    while (1) {
        system("cls");
        printf("*****************Roll call system*****************\n");
        printf("1. Call The Roll\n");
        printf("2. Count Student Info\n");
        printf("3. Student Management\n");
        printf("4. Exit\n");
        printf("Please select:");

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Please enter the name of this course: ");
                scanf("%s", course_Name);
                CallTheRollItem(&List, courseNum, course_Name);
                break;
            case 2:
                CountStudentInfoItem(&List);
                break;
            case 3:
                StudentManagement(&List);
                break;
            case 4:
                courseNum++;
                SaveCourseNumberToFile(courseNum, courseFilepath);
                return;
            default:
                printf("Invalid input\n");
                system("pause");
                break;
        }
    }
}

void SaveCourseNumberToFile(int courseNum, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%d\n", courseNum);
    fclose(file);
}

int LoadCourseNumberFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int courseNum;
    fscanf(file, "%d", &courseNum);
    fclose(file);

    return courseNum;
}

int main() {
    int courseNum = LoadCourseNumberFromFile(courseFilepath);
    CallTheRollMenu(courseNum, courseFilepath);
    return 0;
}