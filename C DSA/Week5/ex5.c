/**
 * Exercise 5 - Structures and its members
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256

typedef struct Course {
    char name[MAX_STR_LEN];        // Introduction to Computer Science II
    char department[MAX_STR_LEN];  // Computer Science
    int year;                      // 1
} Course;

typedef struct Offering {
    char section[MAX_STR_LEN];    // LEC01
    char professor[MAX_STR_LEN];  // Ponce Castro, M.
    Course* course;
} Offering;


typedef struct Node {
    char *prof;
    int offering_count;
    struct Node* next;

} Node;
/**
 * Function: courses_by_year
 * -------------------------
 * Determines the number of courses a student in a given year can take from an
 * array of courses.
 *
 * A student is eligible to enroll in a course only if the course's academic
 * year is less than or equal to the student's current academic year.
 *
 * Parameters:
 *   courses: An array of courses.
 *   length: The length of the courses array.
 *   year: The academic year of the student.
 *
 * Returns:
 *   The number of courses a student of the specified year can take.
 */
int courses_by_year(Course courses[], int length, int year) {
    int num_courses = 0;
    for (int i = 0; i< length; ++i){
        if (courses[i].year <= year){
            num_courses++;
        }

    }
    // TODO: Complete this function.
    return num_courses;
}

/**
 * Function: courses_by_dept
 * -------------------------
 * Counts the number of courses belonging to a specified department in the given
 * array.
 *
 * Parameters:
 *   courses: An array of courses.
 *   length: The length of the courses array.
 *   dept: The name of the department.
 *
 * Returns:
 *   The count of courses associated with the specified department.
 */
int courses_by_dept(Course courses[], int length, char* dept) {
    int num_courses_dept = 0;
    for (int i = 0; i < length; ++i){
        if (strcmp(courses[i].department, dept) == 0){
            num_courses_dept++;
        }
    }
    // TODO: Complete this function.
    return num_courses_dept;
}

/**
 * Function: number_of_offerings
 * -----------------------------
 * Counts the occurrences of a specific course name in the given array of
 * offerings.
 *
 * Parameters:
 *   offerings: An array of offerings.
 *   length: The length of the offerings array.
 *   course_name: The name of the course.
 *
 * Returns:
 *   The count of offerings for the specified course name.
 */
int number_of_offerings(Offering offerings[], int length, char* course_name) {
    int num_offerings = 0;
    

    
    for (int i = 0; i < length; ++i){
        if (strcmp(offerings[i].course->name, course_name) == 0){
            num_offerings++;
        }
    }
    // TODO: Complete this function.
    return num_offerings;
}

/**
 * Function: find_best_professor
 * -----------------------------
 * Determines the best professor based on the highest number of offerings
 * taught. Write the name of the best professor to the specified
 * 'output_professor' string.
 *
 * In case of a tie in the number of offerings, the professor with the
 * lexicographically smallest name (determined by ASCII values using strcmp())
 * is chosen.
 *
 * If there are no offerings, the output string is set to an empty string.
 *
 * Parameters:
 *   offerings: An array of offerings.
 *   length: The length of the offerings array.
 *   output_professor: The output string to write the professor's name to.
 */
void find_best_professor(Offering offerings[], int length, char* output_professor) {
    // TODO: Complete this function.



    //Create the head of the linked list

    
    struct Node *newNode;
    newNode = malloc(sizeof(struct Node));
    newNode->offering_count = 1;
    newNode->prof = offerings[0].professor;
    newNode->next = NULL;

    struct Node *ptr;
    ptr = malloc(sizeof(struct Node));

    bool inList = false;

    struct Node *Max;
    Max = malloc(sizeof(struct Node));
    Max = newNode;

    for (int i = 1; i < length; ++i){
        ptr = newNode;
        inList = false;
        while (ptr != NULL){
            if (strcmp(offerings[i].professor, ptr->prof) == 0){
                ptr->offering_count++;
                inList = true;
                
            }
           
            ptr = ptr->next;
            
        }

        if (inList == false){
            
            struct Node *Temp;
            Temp = malloc(sizeof(struct Node));
            Temp->prof = offerings[i].professor;
            Temp->offering_count = 1;
            Temp->next = NULL;

            ptr = newNode;

            while (ptr->next != NULL){
                ptr = ptr->next;
            }

            ptr->next = Temp;
            
        }
    }

    ptr = newNode;
    while (ptr != NULL){
        
        if (Max->offering_count < ptr->offering_count){
            Max->offering_count = ptr->offering_count;
            Max->prof =  ptr->prof;
        }
        ptr = ptr->next;
    }

    ptr = newNode;
    
    while (ptr != NULL){

        
        if (ptr->offering_count == Max->offering_count){
            if (strcmp(ptr->prof, Max->prof) < 0){
                Max->prof = ptr->prof;
            }
        }
        ptr = ptr->next;
    }

    if (length != 0){
        strcpy(output_professor, Max->prof);
    }

    


    /*
    STEPS:
    -> Loop through each offering and the get the name
    -> Create a linked list, where each node contains a profs name and the # of course offerings
    -> Check to see if offers[i].name is in the linked list, if they are in find their node and increment
    -> If they are not in create a new node for them
    -> Loop through to get the max offerings.
    -> Loop through to find the nodes with max offerings


    
    */
     
    return;
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main() {
    Course courses[20] = {
        {"Introduction to Computer Science I", "Computer Science", 1},
        {"Introduction to Programming", "Computer Science", 1},
        {"Discrete Mathematics", "Computer Science", 1},
        {"Software Design", "Computer Science", 2},
        {"Introduction to the Theory of Computation", "Computer Science", 2},
        {"Programming on the Web", "Computer Science", 3},
        {"Human-Computer Interaction", "Computer Science", 3},
        {"Introduction to Machine Learning and Data Mining", "Computer Science", 3},
        {"Introduction to Numerical Algorithms for Computational Mathematics", "Computer Science", 3},
        {"Introduction to Databases", "Computer Science", 3},
        {"Algorithm Design and Analysis", "Computer Science", 3},
        {"Engineering Large Software Systems", "Computer Science", 4},
        {"Social Impact of Information Technology", "Computer Science", 4},
        {"Advanced Data Analysis", "Computer Science", 4},
        {"Technology Innovation and Entrepreneurship", "Computer Science", 4},
        {"Computer Networks", "Computer Science", 4},
        {"Topics in Computer Science", "Computer Science", 4},
        {"The Startup Sandbox", "Computer Science", 4},
        {"Readings in Computer Science", "Computer Science", 4},
        {"Computer Science Project", "Computer Science", 4}
    };

    Offering offerings[33] = {
        {"LEC01", "Tafliovich, A.", &courses[0]},
        {"LEC02", "Gawde, P.", &courses[0]},
        {"LEC03", "Ponce Castro, M.", &courses[0]},
        {"LEC04", "Tafliovich, A.", &courses[0]},
        {"LEC05", "Cheng, N.", &courses[0]},
        {"LEC06", "Gawde, P.", &courses[0]},
        {"LEC01", "Harrington, B.", &courses[1]},
        {"LEC02", "Harrington, B.", &courses[1]},
        {"LEC01", "Bretscher, A.", &courses[2]},
        {"LEC02", "Bretscher, A.", &courses[2]},
        {"LEC03", "Bretscher, A.", &courses[2]},
        {"LEC01", "Abou Assi, R.", &courses[3]},
        {"LEC02", "Abou Assi, R.", &courses[3]},
        {"LEC01", "Abou Assi, R.", &courses[4]},
        {"LEC02", "Cheng, N.", &courses[4]},
        {"LEC01", "Sans, T.", &courses[5]},
        {"LEC02", "Sans, T.", &courses[5]},
        {"LEC01", "Nizam, N.", &courses[6]},
        {"LEC01", "Abou Assi, R.", &courses[7]},
        {"LEC01", "Pancer, R.", &courses[8]},
        {"LEC02", "Pancer, R.", &courses[8]},
        {"LEC01", "Agrawal, P.", &courses[9]},
        {"LEC01", "Hadzilacos, V.", &courses[10]},
        {"LEC01", "Bodurri, A./ Yong, C.", &courses[11]},
        {"LEC02", "Bodurri, A./ Yong, C.", &courses[11]},
        {"LEC01", "Harrington, B.", &courses[12]},
        {"LEC01", "Anderson, A.", &courses[13]},
        {"LEC01", "Kontozopoulos, H.", &courses[14]},
        {"LEC01", "Ponce Castro, M.", &courses[15]},
        {"LEC01", "Sans, T.", &courses[16]},
        {"LEC01", "Kontozopoulos, H.", &courses[17]},
        {"LEC01", "FACULTY", &courses[18]},
        {"LEC01", "FACULTY", &courses[19]}
    };

    int cby = courses_by_year(courses, 20, 2);
    if (cby != 5) {
        printf("Year 2 students have 5 course options. Got %d instead.\n", cby);
        exit(1);
    }

    int cbd = courses_by_dept(courses, 20, "Computer Science");
    if (cbd != 20) {
        printf("There are 20 Computer Science courses. Got %d instead.\n", cbd);
        exit(1);
    }

    int nof = number_of_offerings(offerings, 33, "Introduction to Computer Science I");
    if (nof != 6) {
        printf("There are 6 offerings for 'Introduction to Computer Science I'. Got %d instead.\n", nof);
        exit(1);
    }

    char best_professor[MAX_STR_LEN];
    find_best_professor(offerings, 33, best_professor);
    if (strcmp(best_professor, "Abou Assi, R.") != 0) {
        printf("'Abou Assi, R.' is the best professor. Got %s instead.\n", best_professor);
        exit(1);
    }

    printf("All test cases passed. Have you written any of your own?\n");
    return 0;
}

#endif
