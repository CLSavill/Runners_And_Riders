/* 
 * File: file_reader.c
 * Author: Chris Savill - chsFILE_LOAD_SUCCESS7
 * Description: File that contains methods related to reading in the various data files.
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

int event_file_load(event * event_ptr) {
    FILE * event_file; // File pointer.
    char file_name[MAX_PATH_LENGTH];
    int load_status;    

    printf("\nPlease enter in the file path and name of the event file: ");
    scanf("%s", file_name);

    event_file = fopen(file_name, "r");

    if (load_status == EOF) {
        printf("\nError reading in Event Name.");
        fclose(event_file);
        return FILE_LOAD_FAILURE;

    } else {
        load_status = fscanf(event_file, "%50[a-zA-Z ]", event_ptr -> name);
        fgetc(event_file);

        if (load_status == EOF) {
            printf("\nError reading in Event Date.");
            fclose(event_file);
            return FILE_LOAD_FAILURE;
        } else {
            load_status = fscanf(event_file, "%19[a-zA-Z0-9]", event_ptr -> date);
            fgetc(event_file);

            if (load_status == EOF) {
                printf("\nError reading in Event Start Time.");
                fclose(event_file);
                return FILE_LOAD_FAILURE;
            } else {
                load_status = fscanf(event_file, "%d%d",
                        event_ptr -> start_time.hours,
                        event_ptr -> start_time.minutes);
            }
        }
    }

    printf("\nEvent file loaded in successfully.");
    fclose(event_file);
    return FILE_LOAD_SUCCESS;
}

/*int nodes_file_load() {
    printf("Please enter in the file path and name of the event file: ");
    scanf("%s", file_name);
}

int tracks_file_load() {
    printf("Please enter in the file path and name of the event file: ");
    scanf("%s", file_name);
}

int courses_file_load() {
    printf("Please enter in the file path and name of the event file: ");
    scanf("%s", file_name);
}

int entrants_file_load() {
    printf("Please enter in the file path and name of the event file: ");
    scanf("%s", file_name);
} */

