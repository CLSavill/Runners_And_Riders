/* 
 * File: competitors.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's competitors.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

// Method to load in all the competitors read from the file supplied (probably named "competitors.txt").

int competitors_file_load(event_ptr event, char* file_name) {
    FILE *competitors_file; // File pointer.
    int load_status = 0;
    int counter = 0;
    int number;
    char course;
    char name[MAX_NAME_LENGTH];
    competitor *current_competitor, *previous_competitor;
    event->competitor_head = NULL;

    competitors_file = fopen(file_name, "r"); // Open file with read permissions only.

    for (counter; counter < event->number_of_competitors; counter++) {
        load_status = fscanf(competitors_file, " %d %c %[a-zA-Z ]", &number, &course, name);

        if (counter == 0) {
            current_competitor = malloc(sizeof (struct competitor));
        }

        current_competitor->number = number;
        current_competitor->course = course;
        current_competitor->location = NS;
        strcpy(current_competitor->name, name);
        current_competitor->next_competitor = NULL;
        current_competitor->previous_competitor = NULL;

        if (event->competitor_head == NULL) {
            event->competitor_head = current_competitor;
            printf("Head Competitor: Number: %d, Course: %c, Name: %s\n", current_competitor->number,
                    current_competitor->course, current_competitor->name);
            previous_competitor = current_competitor;
            current_competitor->next_competitor = malloc(sizeof (struct competitor));
            current_competitor = current_competitor->next_competitor;
        } else {
            current_competitor->previous_competitor = previous_competitor;
            previous_competitor = current_competitor;
            current_competitor->next_competitor = malloc(sizeof (struct competitor));
            printf("Competitor: Number: %d, Course: %c, Name: %s, Previous: %d\n", current_competitor->number,
                    current_competitor->course,
                    current_competitor->name,
                    current_competitor->previous_competitor->number);
            current_competitor = current_competitor->next_competitor;
        }
    }

    printf("\nCompetitors file loaded in successfully.\n");
    fclose(competitors_file); // Closes file as no longer needed.
    return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

void print_not_started(event_ptr event) {
    competitor *current_competitor;
    current_competitor = event->competitor_head;
    
    printf("\n Printing competitors that have not yet started...\n\n");
    printf("=================================================================================\n");
    printf("| Number |                        Name                        | Course | Status |\n");
    printf("=================================================================================\n");
    
    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->location == NS) {
            printf("|   %2d   | %-50s |   %c    |  NS    |\n",
                    current_competitor->number,
                    current_competitor->name,
                    current_competitor->course);
        }
        
        current_competitor = current_competitor->next_competitor;
    }
    
    printf("=================================================================================\n");
}
