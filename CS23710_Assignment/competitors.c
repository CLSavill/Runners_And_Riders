/* 
 * File: competitors.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's competitors.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

// Method to get the number of competitors from a file supplied (probably named "entrants.txt").

int get_number_of_competitors(char* file_name, int number_of_competitors) {
    FILE *competitors_file; // File pointer.
    char line_input[60]; // Size 60 to buffer the input.

    competitors_file = fopen(file_name, "r"); // Open file with read permissions only.

    while (fgets(line_input, sizeof (line_input), competitors_file)) { // While end of file has not been reached.
        number_of_competitors++; // Counts the number of competitors.
    }

    fclose(competitors_file); // Closes file as no longer needed.
    return number_of_competitors;
}
///////////////////////////////////////////////////////////////////////////

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
