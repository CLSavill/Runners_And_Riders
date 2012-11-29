/* 
 * File: loader.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling the loading of files.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

/* Method to cycle through the process of calling all the loading functions. */

int loader(event_ptr event) {
    int load_status;

    do {
        load_status = event_read_cycle(event);
    } while (load_status != SUCCESS);
    printf("Event loading finished.\n");
    load_status = FAILURE;

    do {
        load_status = nodes_read_cycle(event);
    } while (load_status != SUCCESS);
    printf("Node loading finished.\n");

    do {
        load_status = tracks_read_cycle(event);
    } while (load_status != SUCCESS);
    printf("Track loading finished.\n");

    do {
        load_status = courses_read_cycle(event);
    } while (load_status != SUCCESS);
    printf("Course loading finished.\n");

    do {
        load_status = competitors_read_cycle(event);
    } while (load_status != SUCCESS);
    
    printf("Competitor loading finished.\n");
    return SUCCESS;
}
/*-----------------------------------------------------------------------*/

/* Method to cycle through the process of reading in an event's details. */

int event_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];

    printf("\nPlease enter in the file path and name of the event file: ");
    scanf("%s", file_name);

    if (event_file_load(file_name, event) == SUCCESS) {
        printf("\n%s\n%s\n%02d:%d\n", event -> name, event -> date, event -> start_time.hours, event -> start_time.minutes);
        return SUCCESS;
    }

    return FAILURE;
}
/*-----------------------------------------------------------------------*/

/* Method to cycle through the process of reading in the event's nodes. */

int nodes_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];

    printf("\n\nPlease enter in the file path and name of the nodes file: ");
    scanf("%s", file_name);

    if ((event->number_of_nodes = get_number_of_lines(file_name, event->number_of_nodes)) != FAILURE) {
        printf("Number of Nodes: %d\n", event->number_of_nodes);

        if (nodes_file_load(event, file_name) == SUCCESS) {
            return SUCCESS;
        }
    }

    printf("\nError: File containing node details failed to load.\n");
    return FAILURE;
}
/*-----------------------------------------------------------------------*/

/* Method to cycle through the process of reading in the event's tracks. */

int tracks_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];

    printf("\n\nPlease enter in the file path and name of the tracks file: ");
    scanf("%s", file_name);

    if ((event->number_of_tracks = get_number_of_lines(file_name, event->number_of_tracks)) != FAILURE) {
        printf("Number of Tracks: %d\n", event->number_of_tracks);

        if (tracks_file_load(event, file_name) == SUCCESS) {
            return SUCCESS;
        }
    }

    printf("\nError: File containing track details failed to load.\n");
    return FAILURE;
}
/*-----------------------------------------------------------------------*/

/* Method to cycle through the process of reading in the event's courses. */

int courses_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];

    printf("\n\nPlease enter in the file path and name of the courses file: ");
    scanf("%s", file_name);

    if ((event->number_of_courses = get_number_of_lines(file_name, event->number_of_courses)) != FAILURE) {
        printf("Number of Courses: %d\n", event->number_of_courses);

        if (courses_file_load(event, file_name) == SUCCESS) {
            return SUCCESS;
        }
    }

    printf("\nError: File containing course details failed to load.\n");
    return FAILURE;
}
/*-----------------------------------------------------------------------*/

/* Method to cycle through the process of reading in the event's competitors. */

int competitors_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];

    printf("\n\nPlease enter in the file path and name of the competitors file: ");
    scanf("%s", file_name);

    if ((event->number_of_competitors = get_number_of_lines(file_name, event->number_of_competitors)) != FAILURE) {
        printf("Number of Competitors: %d\n", event->number_of_competitors);

        if (competitors_file_load(event, file_name) == SUCCESS) {
            return SUCCESS;
        }
    }

    printf("\nError: File containing competitor details failed to load.\n");
    return FAILURE;
}
/*-----------------------------------------------------------------------*/

/* Method to get the number of lines from a file supplied. */

int get_number_of_lines(char* file_name, int number_of_lines) {
    FILE *number_file; /* File pointer. */
    char line_input[60]; /* Size 60 to buffer the input. */

    if ((number_file = fopen(file_name, "r")) == NULL) { /* Open file with read permissions only and check file opened. */
        printf("Please enter in a valid file path and name.\n");
        return FAILURE;
    }

    while (fgets(line_input, sizeof (line_input), number_file)) { /* While end of file has not been reached. */
        number_of_lines++; /* Counts the number of lines. */
    }

    fclose(number_file); /* Closes file as no longer needed. */
    return number_of_lines;
}
/*-----------------------------------------------------------------------*/

/* Method to read in a file of times. */

void read_times_file(event_ptr event) {
    FILE *times_file; /* File pointer. */
    char file_name[MAX_PATH_LENGTH];
    int load_status;
    char status;
    int checkpoint;
    int competitor_number;
    int hours;
    int minutes;
    competitor *competitor;

    do {
        printf("\n\nPlease enter in the file path and name of the time file to be loaded: ");
        scanf("%s", file_name);

        if ((times_file = fopen(file_name, "r")) == NULL) { /* Open file with read permissions only and check file opened. */
            printf("Please enter in a valid file path and name.\n");
        }
    } while (times_file == NULL);

    do {
        if (load_status = fscanf(times_file, " %c %d %d %d:%d", &status, &checkpoint, &competitor_number, &hours, &minutes) == EOF) {
            load_status = EOF;
            printf("\nEnd of file reached.");
        } else {
            competitor = get_competitor(event, competitor_number);
            checkpoint_update(event, competitor, checkpoint, hours, minutes);
        }
    } while (load_status != EOF);

    fclose(times_file);
    printf("\nLoading of times files complete.\n");
}
/*-----------------------------------------------------------------------*/