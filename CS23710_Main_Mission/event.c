/* 
 * File: event.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to the handling of events.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

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

void print_not_started(event_ptr event) {
    char* location[] = {"NS", "TC - ", "TN - " , "MC", "CC", "EI", "EM"};
    competitor *current_competitor;
    current_competitor = event->competitor_head;
    
    printf("\n Printing competitors that have not yet started...\n\n");
    printf("===================================================================================\n");
    printf("| Number |                        Name                        | Course | Location |\n");
    printf("===================================================================================\n");
    
    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->location == NS) {
            printf("|   %2d   | %-50s |   %c    |    %2s    |\n",
                    current_competitor->number,
                    current_competitor->name,
                    current_competitor->course,
                    location[current_competitor->location]);
        }
        
        current_competitor = current_competitor->next_competitor;
    }
    
    printf("===================================================================================\n");
}

void print_out_on_course(event_ptr event) {
    char* location[] = {"NS", "TC - ", "TN - " , "MC", "CC", "EI", "EM"};
    competitor *current_competitor;
    current_competitor = event->competitor_head;
    
    printf("\n Printing competitors that are out on a course...\n\n");
    printf("===================================================================================\n");
    printf("| Number |                        Name                        | Course | Location |\n");
    printf("===================================================================================\n");
    
    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->location == TC || current_competitor->location == TN || current_competitor->location == MC) {
            printf("|   %2d   | %-50s |   %c    |  %5s%d  |\n",
                    current_competitor->number,
                    current_competitor->name,
                    current_competitor->course,
                    location[current_competitor->location],
                    current_competitor->location);
        }
        
        current_competitor = current_competitor->next_competitor;
    }
    
    printf("===================================================================================\n");
}

void print_finished(event_ptr event) {
    char* location[] = {"NS", "TC", "TN" , "MC", "CC", "EI", "EM"};
    competitor *current_competitor;
    current_competitor = event->competitor_head;
    
    printf("\n Printing competitors that have finished...\n\n");
    printf("===================================================================================\n");
    printf("| Number |                        Name                        | Course | Location |\n");
    printf("===================================================================================\n");
    
    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->location == CC) {
            printf("|   %2d   | %-50s |   %c    |    %2s    |\n",
                    current_competitor->number,
                    current_competitor->name,
                    current_competitor->course,
                    location[current_competitor->location]);
        }
        
        current_competitor = current_competitor->next_competitor;
    }
    
    printf("===================================================================================\n");
}