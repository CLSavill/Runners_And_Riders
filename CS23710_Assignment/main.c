/* 
 * File: main.c
 * Author: Chris Savill - chs17
 * Description: Main file for event monitoring program (menu).
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "test.h"

/*
 * 
 */
int main(int argc, char** argv) {
    event_ptr event;
    event = malloc(sizeof (struct event));
    int file_read;

    printf("Event Monitoring Program Launching...\n");

    if (file_read = loader(event) == SUCCESS) {
        printf("Loading Cycle Finished.");
        test_print_cycle(event);
    }

    return (EXIT_SUCCESS);
}

int loader(event_ptr event) {
    int file_read;
    int number_of_nodes = 0;
    int *number_of_nodes_ptr = &number_of_nodes;
    int number_of_tracks = 0;
    int *number_of_tracks_ptr = &number_of_tracks;
    int number_of_courses = 0;
    int *number_of_courses_ptr = &number_of_courses;

    if (file_read = event_read_cycle(event) == SUCCESS) {
        printf("Event loading finished.\n");
        if (file_read = nodes_read_cycle(event, number_of_nodes_ptr) == SUCCESS) {
            printf("Node loading finished.\n");
            if (file_read = tracks_read_cycle(event, number_of_tracks_ptr) == SUCCESS) {
                printf("Track loading finished.\n");
                if (file_read = courses_read_cycle(event, number_of_courses_ptr) == SUCCESS) {
                    printf("Course loading finished.\n");
                    return SUCCESS;
                }

            }
        }
    }

    printf("\nLoading Cycle Failed.\n");
    return FAILURE;
}

int event_read_cycle(event_ptr event) {
    int file_read;
    char file_name[MAX_PATH_LENGTH];
    printf("\nPlease enter in the file path and name of the event file: ");
    scanf("%s", file_name);

    if (file_read = event_file_load(file_name, event) == SUCCESS) {
        printf("\n%s\n%s\n%02d:%d\n", event -> name, event -> date, event -> start_time.hours, event -> start_time.minutes);
        return SUCCESS;
    }

    return FAILURE;
}

int nodes_read_cycle(event_ptr event, int* number_of_nodes_ptr) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;
    printf("\n\nPlease enter in the file path and name of the nodes file: ");
    scanf("%s", file_name);

    (*number_of_nodes_ptr) = get_number_of_nodes(file_name, number_of_nodes_ptr);

    if ((*number_of_nodes_ptr) != 0) {
        printf("Number of Nodes: %d\n", *number_of_nodes_ptr);

        if (file_read = nodes_file_load(event, file_name, number_of_nodes_ptr) == SUCCESS) {
            return SUCCESS;
        }
    }

    printf("\nError: File containing node details failed to load.\n");
    return FAILURE;
}

int tracks_read_cycle(event_ptr event, int* number_of_tracks_ptr) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;

    printf("\n\nPlease enter in the file path and name of the tracks file: ");
    scanf("%s", file_name);

    (*number_of_tracks_ptr) = get_number_of_tracks(file_name, number_of_tracks_ptr);

    if ((*number_of_tracks_ptr) != 0) {
        printf("Number of Tracks: %d\n", *number_of_tracks_ptr);

        if (file_read = tracks_file_load(event, file_name, number_of_tracks_ptr) == SUCCESS) {
            return SUCCESS;
        }

        printf("\nError: File containing track details failed to load.\n");
        return FAILURE;
    }
}

int courses_read_cycle(event_ptr event, int* number_of_courses_ptr) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;

    printf("\n\nPlease enter in the file path and name of the courses file: ");
    scanf("%s", file_name);

    (*number_of_courses_ptr) = get_number_of_courses(file_name, number_of_courses_ptr);

    if ((*number_of_courses_ptr) != 0) {
        printf("Number of Courses: %d\n", *number_of_courses_ptr);

        if (file_read = courses_file_load(event, file_name, number_of_courses_ptr) == SUCCESS) {
            return SUCCESS;
        }

        printf("\nError: File containing track details failed to load.\n");
        return FAILURE;
    }
}