/* 
 * File: tracks.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's tracks.
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

// Method to get the number of nodes from a file supplied (probably named "tracks.txt").

int get_number_of_tracks(char* file_name, int* number_of_tracks_ptr) {
    FILE *tracks_file; // File pointer.
    char line_input[18]; // Size 18 used just incase a large number of tracks are contained in a course.

    tracks_file = fopen(file_name, "r"); // Open file with read permissions only.

    while (fgets(line_input, sizeof (line_input), tracks_file)) { // While end of file has not been reached.
        (*number_of_tracks_ptr)++; // Counts the number of tracks.
    }

    fclose(tracks_file); // Closes file as no longer needed.
    return (*number_of_tracks_ptr);
}
///////////////////////////////////////////////////////////////////////////

// Method to get the number of tracks from a file supplied (probably named "tracks.txt").

int tracks_file_load(event_ptr event, char* file_name, int* number_of_tracks_ptr) {
    FILE *tracks_file; // File pointer.
    int load_status = 0;
    int counter = 0;
    int track_number;
    int track_start_number;
    int track_end_number;
    int track_max_time;
    track *current_track, *previous_track;
    current_track = event->track_head;
    event->track_head = NULL;

    tracks_file = fopen(file_name, "r"); // Open file with read permissions only. 

    for (counter; counter < (*number_of_tracks_ptr); counter++) {
        load_status = fscanf(tracks_file, " %d %d %d %d", &track_number,
                &track_start_number,
                &track_end_number,
                &track_max_time);

        if (counter == 0) {
            current_track = malloc(sizeof (struct track));
        }

        current_track->number = track_number;
        current_track->max_time = track_max_time;
        current_track->track_start = node_match(event->node_head, track_start_number); // Assigns the address of the start node.
        current_track->track_end = node_match(event->node_head, track_end_number); // Assigns the address of the end node.

        if (event->track_head == NULL) {
            event->track_head = current_track;
            printf("Head Track: Number: %d, Start: %d, End: %d, Max Time: %d\n",
                    current_track->number,
                    current_track->track_start->number,
                    current_track->track_end->number,
                    current_track->max_time);
            previous_track = current_track;
            current_track->next_track = malloc(sizeof (struct track));
            current_track = current_track->next_track;
        } else {
            current_track->previous_track = previous_track;
            previous_track = current_track;
            current_track->next_track = malloc(sizeof (struct track));
            printf("Track: Number: %d, Start: %d, End: %d, Max Time: %d, Previous: %d\n",
                    current_track->number,
                    current_track->track_start->number,
                    current_track->track_end->number,
                    current_track->max_time,
                    current_track->previous_track->number);
            current_track = current_track->next_track;
        }
    }

    printf("\nTracks file loaded in successfully.\n");
    fclose(tracks_file); // Closes file as no longer needed.
    return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

node* node_match(node* node, int node_number) {
    int node_found = 0;
    
    while (node_found == 0) {
        if (node_number == node->number) { // Evaluates if the two integer values match.               
            return node; // Returns the node pointer.
        }
        else {
            node = node->next_node;
        }
    }
}
