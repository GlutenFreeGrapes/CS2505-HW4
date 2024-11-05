#include <string.h>
#include <stdlib.h>
#include "roster.h"

// adds new student to list - if full, don't add anything
int add_student(FILE* in, FILE* out, char* students[], int current_students, int const max_students)
{
    // check if class is already full or not
    if (current_students<max_students)
    {
        // allocate space at new index and insert new name
        students[current_students] = calloc(101, sizeof(char));
        fscanf(in, "%[^\n]\n",students[current_students]);
        // output result to file
        fprintf(out,"Command: add %s\n\t%s was added. %d spot(s) remain.\n",students[current_students],students[current_students],max_students-current_students-1);
        // return new number of students
        return current_students+1;
    }
    else
    {
        // store new name in a temp variable
        char* student_to_be_added = calloc(101, sizeof(char));
        fscanf(in, "%[^\n]\n",student_to_be_added);
        // output result to file
        fprintf(out,"Command: add %s\n\tStudent %s not added. The class is already at capacity.\n",student_to_be_added,student_to_be_added);
        // free up temp variable
        free(student_to_be_added);
        // return unchanged number of students
        return current_students;
    }
}
// remove given student - if not found, don't remove anything
int remove_student(FILE* in, FILE* out, char* students[], int current_students, int const max_students)
{
    // store new name in a temp variable
    char* student_to_be_removed = calloc(101, sizeof(char));
    fscanf(in, "%[^\n]\n",student_to_be_removed);
    // index for if the name is found
    int found = -1;
    // iterate through the list
    for (int i=0;i<current_students;i++)
    {
        // if name found, store the index
        if (strcmp(students[i],student_to_be_removed)==0)
        {
            found = i;
        }
    }
    // check if name was found
    if (found>-1)
    {
        // iterate through all the indices and shift the names ahead
        for (int i=found;i<current_students-1;i++)
        {
            students[i]=strcpy(students[i],students[i+1]);
        }
        // free up last slot
        free(students[current_students-1]);
        // output result to file
        fprintf(out, "Command: remove %s\n\tStudent %s removed. The course now has %d seats remaining.\n",student_to_be_removed,student_to_be_removed,max_students-current_students+1);
        // free up temp variable
        free(student_to_be_removed);
        // return new number of students
        return current_students-1;
    }
    else
    {
        // output result to file
        fprintf(out, "Command: remove %s\n\tNo student named %s was found to remove.\n",student_to_be_removed,student_to_be_removed);
        // free up temp variable
        free(student_to_be_removed);
        // return unchanged number of students
        return current_students;
    }
    
}
// delete all students from class and free up list
void delete_class(FILE* out, char* students[], int* current_students)
{
    fprintf(out,"Command: delete");
    // iterate through list
    for (int i=0;i<*current_students;i++)
    {
        // free every index
        fprintf(out,"\n\t%s removed in class delete.",students[i]);
        free(students[i]);
    }
    // 
    fprintf(out,"\n\tClass was restarted and reopened for enrollment.\n\n");
    // reset current_students
    *current_students=0;
}
// modify given student's name - if not found don't modify anything
void modify_name(FILE* in, FILE* out, char* students[], int current_students)
{
    // store old and new names in temp variables
    char* student_to_be_modified = calloc(101, sizeof(char));
    char* modified_student_name = calloc(101, sizeof(char));
    fscanf(in, "%[^:]:%[^\n]\n",student_to_be_modified,modified_student_name);
    // index for if the name is found
    int found = -1;
    // iterate through the list
    for (int i=0;i<current_students;i++)
    {
        // if name found, store the index and replace the name with the new name
        if (strcmp(students[i],student_to_be_modified)==0)
        {
            students[i]=strcpy(students[i],modified_student_name);
            found=i;
        }
    }
    // check if name was found
    if (found>-1)
    {
        // output result to file
        fprintf(out, "Command: modify %s:%s\n\tStudent %s name modified to %s.\n",student_to_be_modified, modified_student_name, student_to_be_modified, modified_student_name);
    }
    else
    {
        // output result to file
        fprintf(out, "Command: modify %s:%s\n\tNo student with name %s found.\n",student_to_be_modified, modified_student_name, student_to_be_modified);
    }
    // free up temp variables
    free(student_to_be_modified);
    free(modified_student_name);
}
// output list of students to file
void display_class(FILE* out, char* students[], int current_students)
{
    fprintf(out,"Command: display\n\tCurrently Enrolled:\n");
    // iterate through list
    for (int i=0;i<current_students;i++)
    {
        // output students names and indexes to file
        fprintf(out,"\t\tStudent %d: %s\n",i+1,students[i]);
    }
}