/* 
 * File: tracks.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's tracks.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

// Method to get the number of tracks from a file supplied (probably named "tracks.txt").

int tracks_file_load(event_ptr event, char* file_name) {
    FILE *tracks_file; // File pointer.
    int load_status = 0;
    int counter = 0;
    int track_number;
    int track_start_number;
    int track_end_number;
    int track_max_time;
    track *current_track;
    current_track = event->track_head;
    event->track_head = NULL;

    tracks_file = fopen(file_name, "r"); // Open file with read permissions only. 

    for (counter; counter < event->number_of_tracks; counter++) {
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
            current_track->next_track = malloc(sizeof (struct track));
            current_track = current_track->next_track;
        } else {
            current_track->next_track = malloc(sizeof (struct track));
            printf("Track: Number: %d, Start: %d, End: %d, Max Time: %d\n",
                    current_track->number,
                    current_track->track_start->number,
                    current_track->track_end->number,
                    current_track->max_time);
            current_track = current_track->next_track;
        }
    }

    printf("\nTracks file loaded in successfully.\n");
    fclose(tracks_file); // Closes file as no longer needed.
    return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

track* get_track(track* track_head, int node1, int node2) {
    track *current_track;
    current_track = track_head;

    while (current_track->next_track != NULL) {
        if (current_track->track_start->number == node1 && current_track->track_end->number == node2) {
            return current_track;
        } else {
            current_track = current_track->next_track;
        }
    }
}
