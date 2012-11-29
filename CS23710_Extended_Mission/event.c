/* 
 * File: event.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to the handling of events.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

/* Method to load in the details of the event from the file supplied (probably named "name.txt"). */

int event_file_load(char* file_name, event_ptr event) {
    FILE *event_file; /* File pointer. */
    int load_status;
    
    if ((event_file = fopen(file_name, "r")) == NULL) { /* Open file with read permissions only and check file opened. */
        printf("Please enter in a valid file path and name.\n");
        return FAILURE;
    }
    
    load_status = fscanf(event_file, "%[a-zA-Z -]", event->name);

    event->start_time.hours = NOT_SET;
    event->start_time.minutes = NOT_SET;

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
            event->current_time.hours = event->start_time.hours;
            event->current_time.minutes = event->start_time.minutes;
        }
    }

    printf("\nEvent file loaded in successfully.\n");
    fclose(event_file);
    return SUCCESS;
}
/*-----------------------------------------------------------------------*/

/* Method to display a table of the competitors who have not started and the number. */

void print_not_started(event_ptr event) {
    competitor *current_competitor;
    current_competitor = event->competitor_head;
    int counter = 0;

    printf("\n Printing competitors that have not yet started...\n\n");
    printf("===================================================================================\n");
    printf("| Number |                        Name                        | Course | Location |\n");
    printf("===================================================================================\n");

    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->status == NS) {
            printf("|   %02d   | %-50s |   %c    |    NS    |\n",
                    current_competitor->number,
                    current_competitor->name,
                    current_competitor->course);
            counter++;
        }

        current_competitor = current_competitor->next_competitor;
    }

    printf("===================================================================================\n");
    printf("\nNumber of Competitors not started yet: %d\n", counter);
}
/*-----------------------------------------------------------------------*/

/* Method to display a table of the competitors who are out on their course. */

void print_out_on_course(event_ptr event) {
    char* status[] = {"NS", "TC - ", "TN - ", "MC - ", "CC", "EI", "EM"};
    competitor *current_competitor;
    current_competitor = event->competitor_head;

    printf("\n Printing competitors that are out on a course...\n\n");
    printf("=======================================================================================================================\n");
    printf("| Number |                        Name                        | Course | Last Recorded Checkpoint | Presumed Location |\n");
    printf("=======================================================================================================================\n");

    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->status == TC || current_competitor->status == TN || current_competitor->status == MC) {
            printf("|   %02d   | %-50s |   %c    |          %02d              |     %5s%02d       |\n",
                    current_competitor->number,
                    current_competitor->name,
                    current_competitor->course,
                    get_course_node_number(current_competitor->course_ptr, current_competitor->last_checkpoint_index),
                    status[current_competitor->status],
                    current_competitor->location);
        }

        current_competitor = current_competitor->next_competitor;
    }

    printf("=======================================================================================================================\n");
}
/*-----------------------------------------------------------------------*/

/* Method to display a table of the competitors who have finished their course. */

void print_finished(event_ptr event) {
    char* status[] = {"NS", "TC", "TN", "MC", "CC", "EI", "EM"};
    competitor *current_competitor;
    current_competitor = event->competitor_head;

    printf("\n Printing competitors that have finished...\n\n");
    printf("===================================================================================\n");
    printf("| Number |                        Name                        | Course | Location |\n");
    printf("===================================================================================\n");

    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->status == CC) {
            printf("|   %02d   | %-50s |   %c    |    %2s    |\n",
                    current_competitor->number,
                    current_competitor->name,
                    current_competitor->course,
                    status[current_competitor->status]);
        }

        current_competitor = current_competitor->next_competitor;
    }

    printf("===================================================================================\n");
}
/*-----------------------------------------------------------------------*/

/* Method to display a table of the result times for the competitors. */

void print_results(event_ptr event) {
    char* status[] = {"NS", "TC", "TN", "MC", "CC", "EI", "EM"};
    competitor *current_competitor;
    current_competitor = event->competitor_head;
    time time;

    printf("\n Printing results...\n\n");
    printf("===================================================================================\n");
    printf("| Number |                        Name                        | Status |   Time   |\n");
    printf("===================================================================================\n");

    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->status == CC) {
            time = get_time(current_competitor);

            printf("|   %02d   | %-50s |   %2s   |   %02d:%02d  |\n",
                    current_competitor->number,
                    current_competitor->name,
                    status[current_competitor->status],
                    time.hours,
                    time.minutes);         
        }
        
        current_competitor = current_competitor->next_competitor;
    }

    printf("===================================================================================\n");
}
/*-----------------------------------------------------------------------*/