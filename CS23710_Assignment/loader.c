/* 
 * File: loader.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling the loading of files.
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

int loader(event_ptr event) {
    int file_read;

    if (file_read = event_read_cycle(event) == SUCCESS) {
        printf("Event loading finished.\n");
        if (file_read = nodes_read_cycle(event) == SUCCESS) {
            printf("Node loading finished.\n");
            if (file_read = tracks_read_cycle(event) == SUCCESS) {
                printf("Track loading finished.\n");
                if (file_read = courses_read_cycle(event) == SUCCESS) {
                    printf("Course loading finished.\n");
                    if (file_read = competitors_read_cycle(event) == SUCCESS) {
                        printf("Competitor loading finished");
                        return SUCCESS;
                    }
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

int nodes_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;
    printf("\n\nPlease enter in the file path and name of the nodes file: ");
    scanf("%s", file_name);

    event->number_of_nodes = get_number_of_lines(file_name, event->number_of_nodes);

    if (event->number_of_nodes != 0) {
        printf("Number of Nodes: %d\n", event->number_of_nodes);

        if (file_read = nodes_file_load(event, file_name) == SUCCESS) {
            return SUCCESS;
        }
    }

    printf("\nError: File containing node details failed to load.\n");
    return FAILURE;
}

int tracks_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;

    printf("\n\nPlease enter in the file path and name of the tracks file: ");
    scanf("%s", file_name);

    event->number_of_tracks = get_number_of_lines(file_name, event->number_of_tracks);

    if (event->number_of_tracks != 0) {
        printf("Number of Tracks: %d\n", event->number_of_tracks);

        if (file_read = tracks_file_load(event, file_name) == SUCCESS) {
            return SUCCESS;
        }

        printf("\nError: File containing track details failed to load.\n");
        return FAILURE;
    }
}

int courses_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;

    printf("\n\nPlease enter in the file path and name of the courses file: ");
    scanf("%s", file_name);

    event->number_of_courses = get_number_of_lines(file_name, event->number_of_courses);

    if (event->number_of_courses != 0) {
        printf("Number of Courses: %d\n", event->number_of_courses);

        if (file_read = courses_file_load(event, file_name) == SUCCESS) {
            return SUCCESS;
        }

        printf("\nError: File containing course details failed to load.\n");
        return FAILURE;
    }
}

int competitors_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;

    printf("\n\nPlease enter in the file path and name of the competitors file: ");
    scanf("%s", file_name);

    event->number_of_competitors = get_number_of_lines(file_name, event->number_of_competitors);

    if (event->number_of_competitors != 0) {
        printf("Number of Courses: %d\n", event->number_of_competitors);

        if (file_read = competitors_file_load(event, file_name) == SUCCESS) {
            return SUCCESS;
        }

        printf("\nError: File containing competitor details failed to load.\n");
        return FAILURE;
    }
}

// Method to get the number of lines from a file supplied.

int get_number_of_lines(char* file_name, int number_of_lines) {
    FILE *number_file; // File pointer.
    char line_input[60]; // Size 60 to buffer the input.

    number_file = fopen(file_name, "r"); // Open file with read permissions only.

    while (fgets(line_input, sizeof (line_input), number_file)) { // While end of file has not been reached.
        number_of_lines++; // Counts the number of lines.
    }

    fclose(number_file); // Closes file as no longer needed.
    return number_of_lines;
}
///////////////////////////////////////////////////////////////////////////