/* 
 * File: loader.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling the loading of files.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

/* Function to cycle through the process of calling all the loading functions. */
int loader(event_ptr event) {
    int load_status;

    do {
        printf("\nPlease enter in the file path and name of the event file: ");
        load_status = load_cycle(event, &event_file_load);
    } while (load_status != SUCCESS);
    printf("Event loading finished.\n");
    load_status = FAILURE;

    do {
        printf("\n\nPlease enter in the file path and name of the nodes file: ");
        load_status = load_cycle(event, &nodes_file_load);
    } while (load_status != SUCCESS);
    printf("Node loading finished.\n");

    do {
        printf("\n\nPlease enter in the file path and name of the tracks file: ");
        load_status = load_cycle(event, &tracks_file_load);
    } while (load_status != SUCCESS);
    printf("Track loading finished.\n");

    do {
        printf("\n\nPlease enter in the file path and name of the courses file: ");
        load_status = load_cycle(event, &courses_file_load);
    } while (load_status != SUCCESS);
    printf("Course loading finished.\n");

    do {
        printf("\n\nPlease enter in the file path and name of the competitors file: ");
        load_status = load_cycle(event, &competitors_file_load);
    } while (load_status != SUCCESS);

    printf("Competitor loading finished.\n");
    return SUCCESS;
}
/*-----------------------------------------------------------------------*/

/* Function to call the relevant loading/reading function using function pointer passed in. */
int load_cycle(event_ptr event, int (*load_function_ptr) (event_ptr, char*)) {
    char file_name[MAX_PATH_LENGTH];

    scanf("%s", file_name);

    if (load_function_ptr(event, file_name) == SUCCESS) {
        return SUCCESS;
    }

    printf("\nError: File failed to load.\n");
    return FAILURE;
}
/*-----------------------------------------------------------------------*/

/* Function to read in a file of times. */
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
        load_status = fscanf(times_file, " %c %d %d %d:%d", &status, &checkpoint, &competitor_number, &hours, &minutes);

        if (load_status == EOF) {
            printf("\nEnd of file reached.");
        } else if (load_status == 5) {
            if ((chronological_check(event->current_time, hours, minutes)) == SUCCESS) {
                competitor = get_competitor(event, competitor_number);
                evaluate_status(event, competitor, status, checkpoint, hours, minutes);
            } else {
                load_status = FAILURE;
            }
        } else {
            printf("Error reading in time file, possible pattern mismatch.\n");
        }
    } while (load_status != EOF && load_status == 5 && load_status != FAILURE);

    if (load_status == EOF) {
        fclose(times_file);
        printf("\nLoading of times files complete.\n");
    } else if (load_status == FAILURE) {
        printf("\nFile has not arrived in chronological order, permission to read in file denied.\n");
        fclose(times_file);
    } else if (load_status != 5) {
        printf("Error reading in time file, possible pattern mismatch.\n");
        fclose(times_file);
    }
}
/*-----------------------------------------------------------------------*/