/* 
 * File: competitors.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's competitors.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "prototypes.h"

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
        current_competitor->course_ptr = get_course_ptr(event, current_competitor);
        current_competitor->status = NS;
        current_competitor->location = 0;
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

competitor* get_competitor(event_ptr event, int number) {
    competitor *current_competitor;
    current_competitor = event->competitor_head;

    while (current_competitor->next_competitor != NULL) {
        if (current_competitor->number == number) {
            return current_competitor;
        } else {
            current_competitor = current_competitor->next_competitor;
        }
    }
}

void query_location(event_ptr event) {
    competitor *current_competitor;
    int number;

    printf("\n Please enter in the competitor number you wish to query the location of (between 1 and %d): ",
            event->number_of_competitors);
    scanf("%d", &number);

    while (number < 1 || number > event->number_of_competitors) {
        ("\nPlease enter in a valid competitor number between 1 and %d", event->number_of_competitors);
        scanf("%d", &number);
    }

    current_competitor = get_competitor(event, number);

    printf("\nCompetitor: %d, Name: %s, Location: ",
            current_competitor->number,
            current_competitor->name);
    print_location(event, current_competitor);
}

void print_location(event_ptr event, competitor* competitor) {
    switch (competitor->status) {
        case NS:
            printf("Not Yet Started.\n");
            break;
        case TC:
            printf("At Time Checkpoint %d.\n", competitor->location);
            break;
        case TN:
            printf("On Track Number %d.\n", competitor->location);
            break;
        case MC:
            printf("At Medical Checkpoint %d.\n", competitor->location);
            break;
        case CC:
            printf("Completed Course.\n");
            break;
        case EI:
            printf("Excluded for taking an Incorrect Route.\n");
            break;
        case EM:
            printf("Excluded for Medical Safety Reasons.\n");
            break;
    }
}

void update_competitor(event_ptr event) {
    int checkpoint;
    int hours;
    int minutes;
    competitor *competitor;
    int number;

    printf("\n Please enter in the competitor number you wish to update (between 1 and %d): ",
            event->number_of_competitors);
    scanf("%d", &number);

    while (number < 1 || number > event->number_of_competitors) {
        ("\nPlease enter in a valid competitor number between 1 and %d", event->number_of_competitors);
        scanf("%d", &number);
    }

    competitor = get_competitor(event, number);

    printf("\nPlease enter in the checkpoint number (between 1 and %d): ",
            competitor->course_ptr->number_of_nodes);
    scanf("%d", &checkpoint);

    while (checkpoint > competitor->course_ptr->number_of_nodes || checkpoint < 1) {
        printf("\nPlease enter in a valid checkpoint number between 1 and %d: ",
                competitor->course_ptr->number_of_nodes);
        scanf("%d", &checkpoint);
    }

    printf("\nPlease enter in the hour at which the competitor arrived (between 00 and 23) for a 24-hour clock: ");
    scanf("%d", &hours);

    while (hours > 23 || hours < 00) {
        printf("\nPlease enter in a valid hour between 00 and 23 for a 24-hour clock: ");
        scanf("%2d", &hours);
    }

    printf("\nPlease enter in the minutes at which the competitor arrived: ");
    scanf("%2d", &minutes);

    while (minutes > 60 || minutes < 00) {
        printf("\nPlease enter in a valid number of minutes between (00 and 60): ");
        scanf("%2d", &minutes);
    }

    checkpoint_update(competitor, checkpoint, hours, minutes);
}

void checkpoint_update(competitor* competitor, int checkpoint, int hours, int minutes) {
    char* status[] = {"NS", "TC", "TN", "MC", "CC", "EI", "EM"};

    if (competitor->status == NS) {
        competitor->start_time.hours = hours;
        competitor->start_time.minutes = minutes;
        competitor->status = TC;
        competitor->location = checkpoint;
        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;
    } else {
        competitor->status = TC;
        competitor->location = checkpoint;
        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;

        if (checkpoint == competitor->course_ptr->course_nodes[competitor->course_ptr->number_of_nodes-1]) {
            competitor->status = CC;
            competitor->end_time.hours = hours;
            competitor->end_time.minutes = minutes;
        }
    }

    printf("Competitor %d- %s at %s %d updated with time %2d:%2d.\n",
            competitor->number,
            competitor->name,
            status[competitor->status],
            competitor->location,
            competitor->last_time_recored.hours = hours,
            competitor->last_time_recored.minutes = minutes);
}

time get_time(competitor* competitor) {
    time time;
    
    time.hours = competitor->end_time.hours - competitor->start_time.hours;
    time.minutes = competitor->end_time.minutes - competitor->start_time.minutes;
    
    if (time.minutes < 0) {
        time.hours--;
        time.minutes = 60 + time.minutes;
    }
    
    return time;    
}