/* 
 * File: courses.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's courses.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

// Method to get the number of courses from a file supplied (probably named "courses.txt").

int courses_file_load(event_ptr event, char* file_name) {
    FILE *courses_file; // File pointer.
    int load_status = 0;
    int counter = 0, counter2 = 0;
    char course_id;
    int number_of_course_nodes;
    course *current_course;
    current_course = event->course_head;
    event->course_head = NULL;

    courses_file = fopen(file_name, "r"); // Open file with read permissions only. 

    for (counter; counter < event->number_of_courses; counter++) {
        load_status = fscanf(courses_file, " %c %d", &course_id, &number_of_course_nodes);


        if (counter == 0) {
            current_course = malloc(sizeof (struct course));
        }

        current_course->course_nodes = malloc(number_of_course_nodes * (sizeof (node*)));
        current_course->id = course_id;
        current_course->number_of_nodes = number_of_course_nodes;
        current_course->course_nodes = read_course_nodes(event, current_course->course_nodes, courses_file, number_of_course_nodes);

        if (event->course_head == NULL) {
            event->course_head = current_course;

            printf("\nHead Course: ID: %c, Number of Nodes: %d,  Nodes: [",
                    current_course->id,
                    current_course->number_of_nodes);

            counter2 = 0;

            for (counter2; counter2 < number_of_course_nodes; counter2++) {
                if (counter2 != (number_of_course_nodes - 1)) {
                    printf("%d,", current_course->course_nodes[counter2]->number);
                } else {
                    printf("%d]", current_course->course_nodes[counter2]->number);
                    printf("\n");
                }
            }

            current_course->next_course = malloc(sizeof (struct course));
            current_course = current_course->next_course;
        } else {
            current_course->next_course = malloc(sizeof (struct course));

            printf("\nCourse: ID: %c, Number of Nodes: %d, Nodes: [",
                    current_course->id,
                    current_course->number_of_nodes);

            counter2 = 0;

            for (counter2; counter2 < number_of_course_nodes; counter2++) {
                if (counter2 != (number_of_course_nodes - 1)) {
                    printf("%d,", current_course->course_nodes[counter2]->number);
                } else {
                    printf("%d]\n", current_course->course_nodes[counter2]->number);
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

node** read_course_nodes(event_ptr event, node** course_nodes, FILE* courses_file, int number_of_course_nodes) {
    int counter = 0;
    int load_status;
    int node_number;

    for (counter; counter < number_of_course_nodes; counter++) {
        load_status = fscanf(courses_file, " %d", &node_number);       
        course_nodes[counter] = get_node(event->node_head, node_number);
        printf("%d", course_nodes[counter]->number);
    }

    return course_nodes;
}

course* get_course_ptr(event_ptr event, competitor* competitor) {
    course *current_course;
    current_course = event->course_head;

    while (current_course->next_course != NULL) {
        if (competitor->course == current_course->id) {
            return current_course;
        } else {
            current_course = current_course->next_course;
        }
    }
}

int get_next_course_node_number(course* course_ptr, int node_number) {
    int counter = 0;
    
    for (counter; counter < course_ptr->number_of_nodes; counter++) {
        if (course_ptr->course_nodes[counter]->number == node_number) {
            return course_ptr->course_nodes[counter+1]->number;
        }
    }
}
