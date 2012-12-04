/* 
 * File: event.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to the handling of events.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

/* Function to load in the details of the event from the file supplied (probably named "name.txt"). */

int event_file_load(event_ptr event, char* file_name) {
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

    printf("\n%s\n%s\n%02d:%d\n", event -> name, event -> date, event -> start_time.hours, event -> start_time.minutes);
    printf("\nEvent file loaded in successfully.\n");
    fclose(event_file);
    return SUCCESS;
}
/*-----------------------------------------------------------------------*/

/* Function to display a table of the competitors who have not started and the number. */

void print_not_started(event_ptr event) {
    competitor *competitor;
    competitor = event->competitor_head;
    int counter = 0;

    printf("\n Printing competitors that have not yet started...\n\n");
    printf("====================================================================================\n");
    printf("| Number  |                        Name                        | Course | Location |\n");
    printf("====================================================================================\n");

    while (competitor != NULL) {
        if (competitor->status == NS) {
            printf("|   %03d   | %-50s |   %c    |    NS    |\n",
                    competitor->number,
                    competitor->name,
                    competitor->course);
            counter++;
        }

        competitor = competitor->next_competitor;
    }

    printf("====================================================================================\n");
    printf("\nKey: NS = Not Started.\n");
    printf("\nNumber of Competitors not started yet: %d\n", counter);
    printf("\nCurrent Event Time: %d:%d.\n", event->current_time.hours, event->current_time.minutes);
}
/*-----------------------------------------------------------------------*/

/* Function to display a table of the competitors who are out on their course. */

void print_out_on_course(event_ptr event) {
    char* status[] = {"NS", "TC - ", "TN - ", "A - ", "D - "};
    competitor *competitor;
    competitor = event->competitor_head;
    int counter = 0;

    printf("\n Printing competitors that are out on a course...\n\n");
    printf("========================================================================================================================\n");
    printf("| Number  |                        Name                        | Course | Last Recorded Checkpoint | Presumed Location |\n");
    printf("========================================================================================================================\n");

    while (competitor != NULL) {
        if (competitor->status == TC || competitor->status == TN || competitor->status == A) {
            printf("|   %03d   | %-50s |   %c    |          %02d              |     %5s%02d       |\n",
                    competitor->number,
                    competitor->name,
                    competitor->course,
                    competitor->course_ptr->course_nodes[competitor->last_checkpoint_index]->number,
                    status[competitor->status],
                    competitor->location);
            counter++;
        }

        competitor = competitor->next_competitor;
    }

    printf("========================================================================================================================\n");
    printf("\nKey: NS = Not Started, TC = Time Checkpoint, TN = Track Number,\n"
            "A = Medical Checkpoint, D = Departed Medical Checkpoint.\n");
    printf("\nNumber of Competitors out on course: %d\n", counter);
    printf("\nCurrent Event Time: %d:%d.\n", event->current_time.hours, event->current_time.minutes);
}
/*-----------------------------------------------------------------------*/

/* Function to display a table of the competitors who have finished their course. */

void print_finished(event_ptr event) {
    competitor *competitor;
    competitor = event->competitor_head;
    int counter = 0;

    printf("\n Printing competitors that have finished...\n\n");
    printf("====================================================================================\n");
    printf("| Number  |                        Name                        | Course | Location |\n");
    printf("====================================================================================\n");

    while (competitor != NULL) {
        if (competitor->status == CC) {
            printf("|   %03d   | %-50s |   %c    |    CC    |\n",
                    competitor->number,
                    competitor->name,
                    competitor->course);
            counter++;
        }

        competitor = competitor->next_competitor;
    }

    printf("====================================================================================\n");
    printf("\nNumber of Competitors completed course successfully: %d\n", counter);
    printf("\nCurrent Event Time: %d:%d.\n", event->current_time.hours, event->current_time.minutes);
}
/*-----------------------------------------------------------------------*/

/* Function to display a table of the result times for the competitors. */

void print_results(event_ptr event) {
    competitor *competitor;
    competitor = event->competitor_head;
    time time;
    int counter = 0;

    printf("\n Printing results...\n\n");
    printf("====================================================================================\n");
    printf("| Number  |                        Name                        | Status |   Time   |\n");
    printf("====================================================================================\n");

    while (competitor != NULL) {
        if (competitor->status == CC) {
            time = get_result_time(competitor->end_time, competitor->start_time, competitor->medical_minutes);

            printf("|   %03d   | %-50s |   CC   |   %02d:%02d  |\n",
                    competitor->number,
                    competitor->name,
                    time.hours,
                    time.minutes);
            counter++;
        }

        competitor = competitor->next_competitor;
    }

    printf("====================================================================================\n");
    printf("\nNumber of Competitors completed course successfully: %d\n", counter);
    printf("\nCurrent Event Time: %d:%d.\n", event->current_time.hours, event->current_time.minutes);
}
/*-----------------------------------------------------------------------*/

/* Function to display a table of the result times for the competitors. */

void print_excluded(event_ptr event) {
    char* status[] = {"NS", "TC - ", "TN - ", "A - ", "D - ", "CC", "EI", "EM"};
    competitor *competitor;
    competitor = event->competitor_head;
    time time;
    int counter = 0;

    printf("\n Printing results...\n\n");
    printf("====================================================================================\n");
    printf("| Number  |                        Name                        | Status |  At Time |\n");
    printf("====================================================================================\n");

    while (competitor != NULL) {
        if (competitor->status == EI || competitor->status == EM) {

            printf("|   %03d   | %-50s |   %2s   |   %02d:%02d  |\n",
                    competitor->number,
                    competitor->name,
                    status[competitor->status],
                    competitor->last_time_recored.hours,
                    competitor->last_time_recored.minutes);
            counter++;
        }

        competitor = competitor->next_competitor;
    }

    printf("====================================================================================\n");
    printf("\nNumber of Competitors excluded: %d\n", counter);
    printf("\nCurrent Event Time: %d:%d.\n", event->current_time.hours, event->current_time.minutes);
}
/*-----------------------------------------------------------------------*/