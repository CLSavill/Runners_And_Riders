/* 
 * File: updater.c
 * Author: Chris Savill - chs17
 * Description: File that contains functions related to updating competitors.
 */

#include "structs.h"
#include "prototypes.h"

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
    update_statuses(event); /* Call to function that updates all the competitors statuses. */
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
