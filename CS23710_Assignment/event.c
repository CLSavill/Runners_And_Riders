/* 
 * File: event.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to the handling of events.
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

// Method to load in the details of the event from the file supplied (probably named "name.txt").

int event_file_load(char* file_name, event_ptr event) {
    FILE *event_file = NULL; // File pointer.
    int load_status;
    event_file = fopen(file_name, "r");
    load_status = fscanf(event_file, "%[a-zA-Z -]", event->name);

    if (load_status == EOF) {
        printf("Error reading in Event Date.\n");
        fclose(event_file);
        return FAILURE;
    } else {
        load_status = fscanf(event_file, " %[a-zA-Z0-9 ]", event->date);
        if (load_status == EOF) {
            printf("Error reading in Event Start Time.\n");
            fclose(event_file);
            return FAILURE;
        } else {
            load_status = fscanf(event_file, " %d:%d",
                    &event->start_time.hours,
                    &event->start_time.minutes);
        }
    }

    printf("\nEvent file loaded in successfully.\n");
    fclose(event_file);
    return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////
