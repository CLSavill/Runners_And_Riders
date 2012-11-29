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

/* Method to load in all the competitors read from the file supplied (probably named "entrants.txt"). */

int competitors_file_load(event_ptr event, char* file_name) {
    FILE *competitors_file; /* File pointer. */
    int counter = 0;
    int number;
    char course;
    char name[MAX_NAME_LENGTH];
    competitor *new_competitor;
    event->competitor_head = NULL;

    if ((competitors_file = fopen(file_name, "r")) == NULL) { /* Open file with read permissions only and check file opened. */
        printf("Please enter in a valid file path and name.\n");
        return FAILURE;
    }

    for (counter; counter < event->number_of_competitors; counter++) {
        fscanf(competitors_file, " %d %c %[a-zA-Z ]", &number, &course, name);

        if (counter == 0) {
            new_competitor = malloc(sizeof (struct competitor));
        }

        /* Initialising the new competitor: */
        new_competitor->number = number;
        new_competitor->course = course;
        new_competitor->course_ptr = get_course_ptr(event, new_competitor);
        new_competitor->status = NS;
        new_competitor->location = -1;
        new_competitor->last_checkpoint_index = -1;
        strcpy(new_competitor->name, name);
        new_competitor->medical_passed = FALSE;
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

        if (counter != event->number_of_competitors) {
            new_competitor->next_competitor = malloc(sizeof (struct competitor)); /* Allocates memory for the next competitor. */
            new_competitor = new_competitor->next_competitor;
        }
        /*-----------------------------------------------------------------------*/
    }

    printf("\nCompetitors file loaded in successfully.\n");
    fclose(competitors_file); /* Closes file as no longer needed. */
    return SUCCESS;
}
/*-----------------------------------------------------------------------*/

/* Method to return a pointer to a competitor. */

competitor* get_competitor(event_ptr event, int number) {
    competitor *current_competitor;
    current_competitor = event->competitor_head;

    while (current_competitor->next_competitor != NULL) { /* Checks if no more competitors present in linked list. */
        if (current_competitor->number == number) {
            return current_competitor;
        } else {
            current_competitor = current_competitor->next_competitor;
        }
    }
}
/*-----------------------------------------------------------------------*/

/* Method to get query the location of a competitor. */

void query_location(event_ptr event) {
    competitor *current_competitor;
    int number;

    printf("\nPlease enter in the competitor number you wish to query the location of (between 1 and %d): ",
            event->number_of_competitors);
    scanf("%d", &number);

    while (number < 1 || number > event->number_of_competitors) {
        printf("\nPlease enter in a valid competitor number between 1 and %d: ", event->number_of_competitors);
        scanf("%d", &number);
    }

    current_competitor = get_competitor(event, number);
    print_location(event, current_competitor);
}
/*-----------------------------------------------------------------------*/

/* Method to print out the status and location of the competitor passed in. */

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
        case A:
            printf("\nCompetitor: %d, Name: %s, Location: Medical Checkpoint %d.\n",
                    competitor->number,
                    competitor->name,
                    competitor->location);
            break;
        case CC:
            printf("\nCompetitor: %d, Name: %s, Completed Course.\n",
                    competitor->number,
                    competitor->name);
            break;
        case EI:
            printf("\nCompetitor: %d, Name: %s, Excluded for taking an Incorrect Route.\n",
                    competitor->number,
                    competitor->name);
            break;
        case EM:
            printf("\nCompetitor: %d, Name: %s, Excluded for Medical Safety Reasons.\n",
                    competitor->number,
                    competitor->name);
            break;
    }
}
/*-----------------------------------------------------------------------*/

/* Method to get a manual input for the updating of a competitor's arrival at a time checkpoint. */

void update_competitor(event_ptr event) {
    int hours;
    int minutes;
    competitor *competitor;
    int number;
    int checkpoint;

    printf("\nPlease enter in the competitor number you wish to update (between 1 and %d): ",
            event->number_of_competitors);
    scanf("%d", &number);

    while (number < 1 || number > event->number_of_competitors) { /* Check to make sure a valid competitor is entered. */
        ("\nPlease enter in a valid competitor number between 1 and %d", event->number_of_competitors);
        scanf("%d", &number);
    }

    competitor = get_competitor(event, number);

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
    
    

    if (competitor->status == NS) {
        checkpoint = -1;
        printf("\nCompetitor %d has now started\n", competitor->number);
        checkpoint_update(event, competitor, checkpoint, hours, minutes); /* Call to function that does the updating. */
    } else if (competitor->status == TC || competitor->status == TN) {
        if (competitor->course_ptr->course_nodes[competitor->last_checkpoint_index]->type == MP) {
            evaluate_status(event, competitor, D, competitor->location, hours, minutes);checkpoint_update(event, competitor, checkpoint, hours, minutes);
        } else if (competitor->course_ptr->course_nodes[competitor->last_checkpoint_index +1]->type == MP) {
            checkpoint = get_course_node_number(competitor->course_ptr, competitor->last_checkpoint_index + 1);
            evaluate_status(event, competitor, A, checkpoint, hours, minutes);checkpoint_update(event, competitor, checkpoint, hours, minutes);
        } else {
            checkpoint = get_course_node_number(competitor->course_ptr, competitor->last_checkpoint_index + 1);
            evaluate_status(event, competitor, TC, checkpoint, hours, minutes);checkpoint_update(event, competitor, checkpoint, hours, minutes);
        }      
    } else {
        printf("\nCompetitor unable to to be updated, may of already completed course or been excluded.\n");
    }


}
/*-----------------------------------------------------------------------*/

/* Method to update a competitor's status and location. */

void checkpoint_update(event_ptr event, competitor* competitor, int checkpoint, int hours, int minutes) {
    char* status[] = {"NS", "TC", "TN", "A", "D", "CC", "EI", "EM"};

    if (competitor->status == NS) {
        competitor->start_time.hours = hours;
        competitor->start_time.minutes = minutes;
        competitor->status = TC;

        if (checkpoint == -1) {
            competitor->location = get_course_node_number(competitor->course_ptr, 0);
            competitor->last_checkpoint_index = 0;
        } else {
            competitor->location = checkpoint;
            competitor->last_checkpoint_index = get_course_node_index(competitor->course_ptr, checkpoint, competitor->last_checkpoint_index);
        }

        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;
    } else if (competitor->status == TC || competitor->status == TN) {
        competitor->status = TC;
        competitor->last_checkpoint_index = get_course_node_index(competitor->course_ptr, checkpoint, competitor->last_checkpoint_index);
        competitor->location = get_course_node_number(competitor->course_ptr, competitor->last_checkpoint_index);
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

    printf("Last Recording of Competitor %d- %s at %s %d with time %02d:%02d.\n",
            competitor->number,
            competitor->name,
            status[competitor->status],
            competitor->location,
            competitor->last_time_recored.hours = hours,
            competitor->last_time_recored.minutes = minutes);
    printf("Current event time updated to %02d:%02d.\n\n",
            event->current_time.hours,
            event->current_time.minutes);

    update_statuses(event); /* Call to function that updates all the competitors statuses. */
}
/*-----------------------------------------------------------------------*/

/* Method to return a time for a competitor. */

time get_time(competitor* competitor) {
    time time;

    time.hours = competitor->end_time.hours - competitor->start_time.hours;
    time.minutes = competitor->end_time.minutes - competitor->start_time.minutes;

    /* Checks if minutes are negative and if so then adjust time accordingly. */
    if (time.minutes < 0) {
        time.hours--;
        time.minutes = 60 + time.minutes;
    }
    /*-----------------------------------------------------------------------*/

    return time;
}
/*-----------------------------------------------------------------------*/

/* Method to update the statuses of all the competitors. */

void update_statuses(event_ptr event) {
    competitor *current_competitor;
    current_competitor = event->competitor_head;

    while (current_competitor->next_competitor != NULL) { /* Checks if no more competitors present in linked list. */
        if (current_competitor->status == TC || current_competitor->status == TN || current_competitor->status == D) { /* If competitor is on a course. */
            if ((current_competitor->last_time_recored.hours) < (event->current_time.hours)) {
                current_competitor->status = TN;
                current_competitor->location = estimate_location(event, current_competitor);
            } else if ((current_competitor->last_time_recored.hours) == (event->current_time.hours)) {
                if (current_competitor->last_time_recored.minutes < event->current_time.minutes) {
                    current_competitor->status = TN;
                    current_competitor->location = estimate_location(event, current_competitor);
                }
            }
        }
        current_competitor = current_competitor->next_competitor;
    }
}
/*-----------------------------------------------------------------------*/

/* Method to estimate the current location of a competitor. */

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
        nodeA = get_node(event->node_head, get_course_node_number(competitor->course_ptr, node_index));
        node_index += 1;
        next_node_number = get_course_node_number(competitor->course_ptr, node_index); /* Gets node number of the next node on the course. */
        nodeB = get_node(event->node_head, next_node_number);
        track = get_track(event->track_head, nodeA->number, nodeB->number); /* Retrieves track that lies between nodeA and nodeB. */

        current_competitor_time = (competitor->last_time_recored.hours * 60) + competitor->last_time_recored.minutes;
        event_time = (event->current_time.hours * 60) + event->current_time.minutes;
        est_arrival_time = current_competitor_time;

        while (nodeB->type == JN) { /* While the second node is a junction node. */
            track = get_track(event->track_head, nodeA->number, nodeB->number); /* Obtain track. */
            est_arrival_time += track->max_time; /* Increase estimated arrival time for competitor at end of track. */

            if (event_time > est_arrival_time) {
                node_index += 1;
                next_node_number = get_course_node_number(competitor->course_ptr, node_index);
                next_node = get_node(event->node_head, next_node_number);
                nodeA = nodeB;
                nodeB = next_node;

                if (nodeB->type != JN) { /* If the new nodeB is not a junction node. */
                    track = get_track(event->track_head, nodeA->number, nodeB->number);
                    return track->number;
                }
            } else {
                return track->number;
            }
        }
        return track->number;
    }
}

/*-----------------------------------------------------------------------*/

void evaluate_status(event_ptr event, competitor* competitor, int status, int checkpoint, int hours, int minutes) {
    if (status == 'I') {
        competitor->status = EI;
        competitor->location = checkpoint;
        competitor->last_checkpoint_index = get_course_node_index(competitor->course_ptr, checkpoint, competitor->last_checkpoint_index);
        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;
        printf("Competitor %d- %s, excluded for taking an incorrect route.\n", competitor->number, competitor->name);
        update_statuses(event);
    } else if (status == 'A') {
        competitor->status = A;
        competitor->location = checkpoint;
        competitor->last_checkpoint_index = get_course_node_index(competitor->course_ptr, checkpoint, competitor->last_checkpoint_index);
        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;
        competitor->medical_arrival_time.hours = hours;
        competitor->medical_arrival_time.minutes = minutes;
        printf("Competitor %d- %s, arrived at a medical checkpoint.\n", competitor->number, competitor->name);
        update_statuses(event);
    } else if (status == 'D') {
        competitor->status = D;
        competitor->location = checkpoint;
        competitor->last_checkpoint_index = get_course_node_index(competitor->course_ptr, checkpoint, competitor->last_checkpoint_index);
        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;
        competitor->medical_departure_time.hours = hours;
        competitor->medical_departure_time.minutes = minutes;
        competitor->medical_passed = TRUE;
        printf("Competitor %d- %s, passed medical exam and just departed medical checkpoint.\n", competitor->number, competitor->name);
        update_statuses(event);
    } else if (status == 'E') {
        competitor->status = EM;
        competitor->location = checkpoint;
        competitor->last_checkpoint_index = get_course_node_index(competitor->course_ptr, checkpoint, competitor->last_checkpoint_index);
        competitor->last_time_recored.hours = hours;
        competitor->last_time_recored.minutes = minutes;
        printf("Competitor %d- %s, excluded for medical safety reasons.\n", competitor->number, competitor->name);
        update_statuses(event);
    } else {
        checkpoint_update(event, competitor, checkpoint, hours, minutes);
    }
}


