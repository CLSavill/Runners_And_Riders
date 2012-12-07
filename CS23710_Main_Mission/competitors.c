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

/* Function to load in all the competitors read from the file supplied (probably named "entrants.txt"). */
int competitors_file_load(event_ptr event, char* file_name) {
    FILE *competitors_file; /* File pointer. */
    int load_status;
    int number;
    char course;
    char name[MAX_NAME_LENGTH];
    competitor *new_competitor;
    event->competitor_head = NULL;

    if ((competitors_file = fopen(file_name, "r")) == NULL) { /* Open file with read permissions only and check file opened. */
        printf("Please enter in a valid file path and name.\n");
        return FAILURE;
    }

    while ((load_status = fscanf(competitors_file, " %d %c %[a-zA-Z ]", &number, &course, name)) != EOF && load_status == 3) {
        if (event->number_of_competitors == 0) {
            new_competitor = malloc(sizeof (struct competitor));
        } else {
            new_competitor->next_competitor = malloc(sizeof (struct competitor)); /* Allocates memory for the next competitor. */
            new_competitor = new_competitor->next_competitor;
        }

        /* Initialising the new competitor: */
        new_competitor->number = number;
        new_competitor->course = course;
        new_competitor->course_ptr = get_course_ptr(event, new_competitor);
        new_competitor->status = NS;
        new_competitor->location = -1;
        new_competitor->last_checkpoint_index = -1;
        strcpy(new_competitor->name, name);
        new_competitor->next_competitor = NULL;
        /*-----------------------------------------------------------------------*/

        /* Adding the new competitor to the linked list: */
        if (event->competitor_head == NULL) {
            event->competitor_head = new_competitor;
            printf("Head Competitor: Number: %d, Course: %c, Name: %s\n", new_competitor->number,
                    new_competitor->course, new_competitor->name);

        } else {
            printf("Competitor: Number: %d, Course: %c, Name: %s\n", new_competitor->number,
                    new_competitor->course,
                    new_competitor->name);
        }
        /*-----------------------------------------------------------------------*/

        event->number_of_competitors++;
    }

    if (load_status == EOF) {
        printf("\nCompetitors file loaded in successfully.\n");
        fclose(competitors_file); /* Closes file as no longer needed. */
        return SUCCESS;
    } else if (load_status != 3) { /* Expected 3 inputs. */
        printf("Error loading in file, possible pattern mismatch.\n");
        fclose(competitors_file); /* Closes file as no longer needed. */
        return FAILURE;
    }

}
/*-----------------------------------------------------------------------*/

/* Function to return a pointer to a competitor. */
competitor* get_competitor(event_ptr event, int number) {
    competitor *competitor;
    competitor = event->competitor_head;

    while (competitor != NULL) { /* Checks if no more competitors present in linked list. */
        if (competitor->number == number) {
            return competitor;
        } else {
            competitor = competitor->next_competitor;
        }
    }
}
/*-----------------------------------------------------------------------*/

/* Function to get query the location of a competitor. */
void query_location(event_ptr event) {
    competitor *competitor;
    int number;

    printf("\nPlease enter in the competitor number you wish to query the location of: ");
    scanf("%d", &number);

    while ((competitor = get_competitor(event, number)) == NULL) { /* Check to make sure a valid competitor is entered. */
        printf("\nPlease enter in a valid competitor number: ");
        scanf("%d", &number);
    }

    print_location(event, competitor);
}
/*-----------------------------------------------------------------------*/

/* Function to print out the status and location of the competitor passed in. */
void print_location(event_ptr event, competitor* competitor) {
    switch (competitor->status) {
        case NS:
            printf("\nCompetitor: %d, Name: %s, Location: Not Yet Started.\n",
                    competitor->number,
                    competitor->name);
            break;
        case TC:
            printf("\nCompetitor: %d, Name: %s, Location: At Time Checkpoint %d.\n",
                    competitor->number,
                    competitor->name,
                    competitor->location);
            break;
        case TN:
            printf("Last Recorded Location: Time Checkpoint %d.\n", competitor->last_checkpoint_index);
            printf("Assumed To Be On Track Number %d.\n", competitor->location);
            break;
        case CC:
            printf("\nCompetitor: %d, Name: %s, Completed Course.\n",
                    competitor->number,
                    competitor->name);
            break;
    }
}
/*-----------------------------------------------------------------------*/

/* Function to get a manual input for the updating of a competitor's arrival at a time checkpoint. */
void update_competitor(event_ptr event) {
    int hours;
    int minutes;
    competitor *competitor;
    int number;
    int checkpoint;

    printf("\nPlease enter in the competitor number you wish to update: ");
    scanf("%d", &number);

    while ((competitor = get_competitor(event, number)) == NULL) { /* Check to make sure a valid competitor is entered. */
        printf("\nPlease enter in a valid competitor number: ");
        scanf("%d", &number);
    }

    printf("\nPlease enter in the new checkpoint of the competitor: ");
    scanf("%d", &checkpoint);

    while (checkpoint > event->number_of_nodes || checkpoint < 1) { /* Check to make sure a valid status is entered. */
        printf("\nPlease enter in a valid checkpoint between 1 and %d: ", event->number_of_nodes);
        scanf("%d", &checkpoint);
    }

    printf("\nPlease enter in the hour at which the competitor arrived (between 00 and 23) for a 24-hour clock: ");
    scanf("%02d", &hours);

    while (hours > 23 || hours < 00) { /* Check to make sure a valid number of hours is entered. */
        printf("\nPlease enter in a valid hour between 00 and 23 for a 24-hour clock: ");
        scanf("%02d", &hours);
    }

    printf("\nPlease enter in the minutes at which the competitor arrived: ");
    scanf("%02d", &minutes);

    while (minutes > 60 || minutes < 00) { /* Check to make sure a valid number of minutes is entered. */
        printf("\nPlease enter in a valid number of minutes between (00 and 60): ");
        scanf("%02d", &minutes);
    }

    if ((chronological_check(event->current_time, hours, minutes)) == SUCCESS) {
        if (competitor->status == NS) {
            printf("\nCompetitor %d has now started\n", competitor->number);
        } else {
            checkpoint_update(event, competitor, checkpoint, hours, minutes); /* Call to function that does the updating. */
        }
    } else {
        printf("\n\nSorry but the manual update you are attempting is not in chronological order, updating process aborted.\n");
    }
}
/*-----------------------------------------------------------------------*/

/* Function to update a competitor's status and location. */
void checkpoint_update(event_ptr event, competitor* competitor, int checkpoint, int hours, int minutes) {
    char* status[] = {"NS", "TC", "TN", "CC"};

    if (competitor->status == NS) {
        competitor->start_time.hours = hours;
        competitor->start_time.minutes = minutes;
        competitor->status = TC;
        competitor->last_checkpoint_index = get_course_node_index(competitor->course_ptr, checkpoint, competitor->last_checkpoint_index);
        competitor->location = competitor->course_ptr->course_nodes[competitor->last_checkpoint_index]->number; /* Gets node number of the next node on the course. */
        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;
    } else if (competitor->status == TC || competitor->status == TN) {
        competitor->status = TC;
        competitor->last_checkpoint_index = get_course_node_index(competitor->course_ptr, checkpoint, competitor->last_checkpoint_index);
        competitor->location = competitor->course_ptr->course_nodes[competitor->last_checkpoint_index]->number; /* Gets node number of the next node on the course. */
        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;

        /* Checks if the competitor has reached the final checkpoint of the course/finished. */
        if (competitor->last_checkpoint_index == competitor->course_ptr->number_of_nodes - 1) {
            competitor->status = CC;
            competitor->end_time.hours = hours;
            competitor->end_time.minutes = minutes;
        }
        /*-----------------------------------------------------------------------*/
    }

    if (event->start_time.hours == NOT_SET) {
        event->start_time.hours = hours;
        event->start_time.minutes = minutes;
    }

    event->current_time.hours = hours;
    event->current_time.minutes = minutes;

    print_location(event, competitor);
    printf("Current event time updated to %02d:%02d.\n\n",
            event->current_time.hours,
            event->current_time.minutes);

    update_statuses(event); /* Call to function that updates all the competitors statuses. */
}
/*-----------------------------------------------------------------------*/

/* Function to return a time for a competitor. */
time get_result_time(time end_time, time start_time) {
    time time;

    time.hours = end_time.hours - start_time.hours;
    time.minutes = end_time.minutes - start_time.minutes;

    /* Checks if minutes are negative and if so then adjust time accordingly. */
    while (time.minutes < 0) {
        time.hours--;
        time.minutes = 60 + time.minutes;
    }
    /*-----------------------------------------------------------------------*/

    return time;
}
/*-----------------------------------------------------------------------*/

/* Function to update the statuses of all the competitors. */
void update_statuses(event_ptr event) {
    competitor *competitor;
    competitor = event->competitor_head;

    while (competitor != NULL) { /* Checks if no more competitors present in linked list. */
        if (competitor->status == TC || competitor->status == TN) { /* If competitor is on a course. */
            if ((competitor->last_time_recored.hours) < (event->current_time.hours)) {
                competitor->status = TN;
                competitor->location = estimate_location(event, competitor);
            } else if ((competitor->last_time_recored.hours) == (event->current_time.hours)) {
                if (competitor->last_time_recored.minutes < event->current_time.minutes) {
                    competitor->status = TN;
                    competitor->location = estimate_location(event, competitor);
                }
            }
        }
        competitor = competitor->next_competitor;
    }
}
/*-----------------------------------------------------------------------*/

/* Function to estimate the location of a competitor. */
int estimate_location(event_ptr event, competitor* competitor) {
    node* nodeA;
    node* nodeB;
    node* next_node;
    int next_node_number;
    int node_index;
    int est_arrival_time = 0;
    int current_competitor_time;
    int event_time;
    track* track;

    if (competitor->status == NS) {
        return NS;
    } else {
        node_index = competitor->last_checkpoint_index;
        nodeA = get_node(event->node_head, competitor->course_ptr->course_nodes[node_index]->number);
        node_index += 1;
        next_node_number = competitor->course_ptr->course_nodes[node_index]->number; /* Gets node number of the next node on the course. */
        nodeB = get_node(event->node_head, next_node_number);
        track = get_track(event->track_head, nodeA->number, nodeB->number); /* Retrieves track that lies between nodeA and nodeB. */

        current_competitor_time = (competitor->last_time_recored.hours * 60) + competitor->last_time_recored.minutes;
        event_time = (event->current_time.hours * 60) + event->current_time.minutes;
        est_arrival_time = current_competitor_time;

        if (nodeB->type == JN) { /* While the second node is a junction node. */
            track = track_estimation(event, competitor, nodeA, nodeB, node_index, next_node_number, event_time, est_arrival_time);
        }
        return track->number;
    }
}
/*-----------------------------------------------------------------------*/

/* Recursive function that estimates what track the competitor could currently be on.
 * Recursively calls if the next node is a junction node and the time difference allows for the next track to be considered. */
track* track_estimation(event_ptr event, competitor* competitor, node* nodeA, node* nodeB, int node_index, int next_node_number, int event_time, int est_arrival_time) {
    node* next_node;
    track* track;

    track = get_track(event->track_head, nodeA->number, nodeB->number); /* Obtain track. */
    est_arrival_time += track->max_time; /* Increase estimated arrival time for competitor at end of track. */

    if (event_time > est_arrival_time) {
        node_index += 1;
        next_node_number = competitor->course_ptr->course_nodes[node_index]->number; /* Gets node number of the next node on the course. */
        next_node = get_node(event->node_head, next_node_number);
        nodeA = nodeB;
        nodeB = next_node;

        if (nodeB->type == JN) {
            track = track_estimation(event, competitor, nodeA, nodeB, node_index, next_node_number, event_time, est_arrival_time);
        } else { /* If the new nodeB is not a junction node. */
            track = get_track(event->track_head, nodeA->number, nodeB->number);
        }
    }

    return track;
}
/*-----------------------------------------------------------------------*/
