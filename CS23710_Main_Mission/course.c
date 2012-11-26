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
    int counter = 0, counter2 = 0;
    char course_id;
    int number_of_course_nodes;
    course *new_course;
    new_course = event->course_head;
    event->course_head = NULL;

    courses_file = fopen(file_name, "r"); // Open file with read permissions only. 

    for (counter; counter < event->number_of_courses; counter++) {
        fscanf(courses_file, " %c %d", &course_id, &number_of_course_nodes);


        if (counter == 0) {
            new_course = malloc(sizeof (struct course)); // Allocates memory for a course struct.
        }

        // Initialises the new course:
        new_course->course_nodes = malloc(number_of_course_nodes * (sizeof (node*))); // Allocation memory for an array of node pointers.
        new_course->id = course_id;
        new_course->number_of_nodes = number_of_course_nodes;
        new_course->course_nodes = read_course_nodes(event, new_course->course_nodes, courses_file, number_of_course_nodes);
        ///////////////////////////////////////////////////////////////////////////

        // Adding the new course to the linked list:
        if (event->course_head == NULL) {
            event->course_head = new_course;

            printf("\nHead Course: ID: %c, Number of Nodes: %d,  Nodes: [",
                    new_course->id,
                    new_course->number_of_nodes);

            counter2 = 0;

            for (counter2; counter2 < number_of_course_nodes; counter2++) {
                if (counter2 != (number_of_course_nodes - 1)) {
                    printf("%d,", new_course->course_nodes[counter2]->number);
                } else {
                    printf("%d]", new_course->course_nodes[counter2]->number);
                    printf("\n");
                }
            }

        } else {
            printf("\nCourse: ID: %c, Number of Nodes: %d, Nodes: [",
                    new_course->id,
                    new_course->number_of_nodes);

            counter2 = 0;

            for (counter2; counter2 < number_of_course_nodes; counter2++) {
                if (counter2 != (number_of_course_nodes - 1)) {
                    printf("%d,", new_course->course_nodes[counter2]->number);
                } else {
                    printf("%d]\n", new_course->course_nodes[counter2]->number);
                }
            }
        }
        ///////////////////////////////////////////////////////////////////////////

        if (counter != event->number_of_courses) {
            new_course->next_course = malloc(sizeof (struct course)); // Allocates memory for the next course.
            new_course = new_course->next_course;
        }
    }

    printf("\nCourses file loaded in successfully.\n");
    fclose(courses_file); // Closes file as no longer needed.
    return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

// Method to read the nodes of a course and assign pointers to the nodes.

node** read_course_nodes(event_ptr event, node** course_nodes, FILE* courses_file, int number_of_course_nodes) {
    int counter = 0;
    int node_number;

    for (counter; counter < number_of_course_nodes; counter++) {
        fscanf(courses_file, " %d", &node_number);
        course_nodes[counter] = get_node(event->node_head, node_number);
    }

    return course_nodes;
}
///////////////////////////////////////////////////////////////////////////

// Method to return a pointer to the relevant course for a competitor.

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
///////////////////////////////////////////////////////////////////////////

// Method to return the node number of the next node in the course.

int get_course_node_number(course* course_ptr, int index) {
    return course_ptr->course_nodes[index]->number; // Returns the course node index.
}
///////////////////////////////////////////////////////////////////////////

// Method to return the node index of a node within the array of course_nodes.

int get_course_node_index(course* course_ptr, int node_number, int last_index) {
    int counter = 0;

    for (counter; counter < course_ptr->number_of_nodes; counter++) {
        if (course_ptr->course_nodes[counter]->number == node_number && counter > last_index) {
            return counter;
        }
    }
}
///////////////////////////////////////////////////////////////////////////
