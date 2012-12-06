/* 
 * File: courses.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's courses.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

/* Function to get the number of courses from a file supplied (probably named "courses.txt"). */
int courses_file_load(event_ptr event, char* file_name) {
    FILE *courses_file; /* File pointer. */
    int load_status;
    int counter = 0;
    char course_id;
    int number_of_course_nodes;
    course *new_course;
    new_course = event->course_head;
    event->course_head = NULL;

    if ((courses_file = fopen(file_name, "r")) == NULL) { /* Open file with read permissions only and check file opened. */
        printf("Please enter in a valid file path and name.\n");
        return FAILURE;
    }

    while ((load_status = fscanf(courses_file, " %c %d", &course_id, &number_of_course_nodes)) != EOF && load_status == 2) {
        if (load_status != 2) {
            printf("Error reading in course, possible pattern mismatch.");
            fclose(courses_file); /* Closes file as no longer needed. */
            return FAILURE;
        }

        if (event->number_of_courses == 0) {
            new_course = malloc(sizeof (struct course)); /* Allocates memory for a course struct. */
        } else {
            new_course->next_course = malloc(sizeof (struct course)); /* Allocates memory for the next course. */
            new_course = new_course->next_course;
        }

        /* Initialises the new course: */
        new_course->course_nodes = malloc(number_of_course_nodes * (sizeof (node*))); /* Allocation memory for an array of node pointers. */
        new_course->id = course_id;
        new_course->number_of_nodes = number_of_course_nodes;

        if ((new_course->course_nodes = read_course_nodes(event, new_course->course_nodes, courses_file, &load_status, number_of_course_nodes)) == NULL) {
            printf("Error reading in course nodes, possible pattern mismatch.");
            fclose(courses_file); /* Closes file as no longer needed. */
            return FAILURE;
        }

        new_course->next_course = NULL;
        /*-----------------------------------------------------------------------*/

        /* Adding the new course to the linked list: */
        if (event->course_head == NULL) {
            event->course_head = new_course;
            printf("\nHead Course: ID: %c, Number of Nodes: %d,  Nodes: [",
                    new_course->id,
                    new_course->number_of_nodes);

            counter = 0;

            for (counter; counter < number_of_course_nodes; counter++) {
                if (counter != (number_of_course_nodes - 1)) {
                    printf("%d,", new_course->course_nodes[counter]->number);
                } else {
                    printf("%d]", new_course->course_nodes[counter]->number);
                    printf("\n");
                }
            }

        } else {
            printf("\nCourse: ID: %c, Number of Nodes: %d, Nodes: [",
                    new_course->id,
                    new_course->number_of_nodes);

            counter = 0;

            for (counter; counter < number_of_course_nodes; counter++) {
                if (counter != (number_of_course_nodes - 1)) {
                    printf("%d,", new_course->course_nodes[counter]->number);
                } else {
                    printf("%d]\n", new_course->course_nodes[counter]->number);
                }
            }
        }
        /*-----------------------------------------------------------------------*/

        event->number_of_courses++;
    }

    printf("\nCourses file loaded in successfully.\n");
    fclose(courses_file); /* Closes file as no longer needed. */
    return SUCCESS;
}
/*-----------------------------------------------------------------------*/

/* Function to read the nodes of a course and assign pointers to the nodes. */
node** read_course_nodes(event_ptr event, node** course_nodes, FILE* courses_file, int* load_status, int number_of_course_nodes) {
    int counter = 0;
    int node_number;

    for (counter; counter < number_of_course_nodes; counter++) {
        *load_status = fscanf(courses_file, " %d", &node_number);

        if (*load_status != 1) {
            return NULL;
        }

        course_nodes[counter] = get_node(event->node_head, node_number);
    }

    return course_nodes;
}
/*-----------------------------------------------------------------------*/

/* Function to return a pointer to the relevant course for a competitor. */
course* get_course_ptr(event_ptr event, competitor* competitor) {
    course *course;
    course = event->course_head;

    while (course != NULL) {
        if (competitor->course == course->id) {
            return course;
        } else {
            course = course->next_course;
        }
    }
}
/*-----------------------------------------------------------------------*/

/* Function to return the node index of a node within the array of course_nodes. */
int get_course_node_index(course* course_ptr, int node_number, int last_index) {
    if (last_index == -1) {
        return 0;
    } else {
        int counter = last_index;

        for (counter; counter < course_ptr->number_of_nodes; counter++) {
            if (course_ptr->course_nodes[counter]->type != JN && course_ptr->course_nodes[counter]->number == node_number && counter > last_index) {
                return counter;
            } else if (course_ptr->course_nodes[counter]->type == JN && course_ptr->course_nodes[counter]->number == node_number && counter > last_index) {
                counter = get_next_checkpoint_index(course_ptr, counter++);
                return counter;
            }
        }
    }
}
/*-----------------------------------------------------------------------*/

/* Function to return the node index of a checkpoint node within an array of course_nodes. */
int get_next_checkpoint_index(course* course_ptr, int counter) {
    for (counter; counter < course_ptr->number_of_nodes; counter++) {
        if (course_ptr->course_nodes[counter]->type != JN) {
            return counter;
        }
    }
}
/*-----------------------------------------------------------------------*/
