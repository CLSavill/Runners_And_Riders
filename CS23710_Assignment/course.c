/* 
 * File: courses.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's courses.
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

// Method to get the number of nodes from a file supplied (probably named "courses.txt").

int get_number_of_courses(char* file_name, int number_of_courses) {
    FILE *courses_file; // File pointer.
    char line_input[40]; // Size 40 to buffer the input.

    courses_file = fopen(file_name, "r"); // Open file with read permissions only.

    while (fgets(line_input, sizeof (line_input), courses_file)) { // While end of file has not been reached.
        number_of_courses++; // Counts the number of courses.
    }

    fclose(courses_file); // Closes file as no longer needed.
    return number_of_courses;
}
///////////////////////////////////////////////////////////////////////////

// Method to get the number of courses from a file supplied (probably named "courses.txt").

int courses_file_load(event_ptr event, char* file_name) {
    FILE *courses_file; // File pointer.
    int load_status = 0;
    int counter = 0, counter2 = 0;
    char course_id;
    int number_of_course_nodes;
    course *current_course, *previous_course;
    current_course = event->course_head;
    event->course_head = NULL;

    courses_file = fopen(file_name, "r"); // Open file with read permissions only. 

    for (counter; counter < event->number_of_courses; counter++) {
        load_status = fscanf(courses_file, " %c %d", &course_id, &number_of_course_nodes);


        if (counter == 0) {
            current_course = malloc(sizeof (struct course));
        }

        current_course->course_nodes = malloc(number_of_course_nodes * (sizeof (int)));
        current_course->id = course_id;
        current_course->number_of_nodes = number_of_course_nodes;
        current_course->course_nodes = read_course_nodes(current_course->course_nodes, courses_file, number_of_course_nodes);

        if (event->course_head == NULL) {
            event->course_head = current_course;

            printf("\nHead Course: ID: %c, Number of Nodes: %d,  Nodes: [",
                    current_course->id,
                    current_course->number_of_nodes);

            counter2 = 0;

            for (counter2; counter2 < number_of_course_nodes; counter2++) {
                if (counter2 != (number_of_course_nodes - 1)) {
                    printf("%d,", current_course->course_nodes[counter2]);
                } else {
                    printf("%d]", current_course->course_nodes[counter2]);
                    printf("\n");
                }
            }

            previous_course = current_course;
            current_course->next_course = malloc(sizeof (struct course));
            current_course = current_course->next_course;
        } else {
            current_course->previous_course = previous_course;
            previous_course = current_course;
            current_course->next_course = malloc(sizeof (struct course));

            printf("\nCourse: ID: %c, Number of Nodes: %d, Nodes: [",
                    current_course->id,
                    current_course->number_of_nodes);

            counter2 = 0;

            for (counter2; counter2 < number_of_course_nodes; counter2++) {
                if (counter2 != (number_of_course_nodes - 1)) {
                    printf("%d,", current_course->course_nodes[counter2]);
                } else {
                    printf("%d]", current_course->course_nodes[counter2]);
                    printf("\n");
                    printf("Previous Course: %c\n", current_course->previous_course->id);
                }
            }

            current_course = current_course->next_course;
        }
    }

    printf("\nCourses file loaded in successfully.\n");
    fclose(courses_file); // Closes file as no longer needed.
    return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

int* read_course_nodes(int* course_nodes, FILE* courses_file, int number_of_course_nodes) {
    int counter = 0;
    int load_status;

    for (counter; counter < number_of_course_nodes; counter++) {
        load_status = fscanf(courses_file, " %d", &course_nodes[counter]);
        printf("%d", course_nodes[counter]);
    }

    return course_nodes;
}
