/* 
 * File: main.c
 * Author: Chris Savill - chs17
 * Description: Main file for event monitoring program (menu).
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

/*
 * 
 */
int main(int argc, char** argv) {
    event_ptr event;
    event = malloc(sizeof (struct event));
    int file_read;

    printf("Event Monitoring Program Launching...\n");

    if (file_read = loader(event) == FILE_LOAD_SUCCESS) {
        printf("Loading Cycle Finished.");
    }

    printf("\nNode Memory Check Phase\n");
    node* current_node;
    current_node = event->node_head;

    printf("Head Node: Number: %d, Type: %d\n", current_node->number,
            current_node->type);
    current_node = current_node->next_node;

    while (current_node->next_node != NULL) {
        printf("Node: Number: %d, Type: %d, Previous: %d\n", current_node->number,
                current_node->type, current_node->previous_node->number);
        current_node = current_node->next_node;
    }
    
    printf("\nTrack Memory Check Phase\n");
    track* current_track;
    current_track = event->track_head;

    printf("Head Track: Number: %d, Start: %d, End: %d, Max Time: %d\n",
                    current_track->number,
                    current_track->track_start->number,
                    current_track->track_end->number,
                    current_track->max_time);
    current_track = current_track->next_track;

    while (current_track->next_track != NULL) {
        printf("Track: Number: %d, Start: %d, End: %d, Max Time: %d, Previous: %d\n",
                    current_track->number,
                    current_track->track_start->number,
                    current_track->track_end->number,
                    current_track->max_time,
                    current_track->previous_track->number);
        current_track = current_track->next_track;
    }

    return (EXIT_SUCCESS);
}

int loader(event_ptr event) {
    int file_read;
    int number_of_nodes = 0;
    int *number_of_nodes_ptr = &number_of_nodes;
    int number_of_tracks = 0;
    int *number_of_tracks_ptr = &number_of_tracks;

    if (file_read = event_read_cycle(event) == FILE_LOAD_SUCCESS) {
        printf("Event loading finished.\n");
        if (file_read = nodes_read_cycle(event, number_of_nodes_ptr) == FILE_LOAD_SUCCESS) {
            printf("Node loading finished.\n");
            if (file_read = tracks_read_cycle(event, number_of_nodes_ptr, number_of_tracks_ptr) == FILE_LOAD_SUCCESS) {
                printf("Track loading finished.\n");
                return FILE_LOAD_SUCCESS;
            }
        }
    }

    printf("\nLoading Cycle Failed.\n");
    return FILE_LOAD_FAILURE;
}

int event_read_cycle(event_ptr event) {
    int file_read;
    char file_name[MAX_PATH_LENGTH];
    printf("\nPlease enter in the file path and name of the event file: ");
    scanf("%s", file_name);

    if (file_read = event_file_load(file_name, event) == FILE_LOAD_SUCCESS) {
        printf("\n%s\n%s\n%02d:%d\n", event -> name, event -> date, event -> start_time.hours, event -> start_time.minutes);
        return FILE_LOAD_SUCCESS;
    }

    return FILE_LOAD_FAILURE;
}

int nodes_read_cycle(event_ptr event, int* number_of_nodes_ptr) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;
    printf("\n\nPlease enter in the file path and name of the nodes file: ");
    scanf("%s", file_name);

    (*number_of_nodes_ptr) = get_number_of_nodes(file_name, number_of_nodes_ptr);

    if ((*number_of_nodes_ptr) != 0) {
        printf("Number of Nodes: %d\n", *number_of_nodes_ptr);

        if (file_read = nodes_file_load(event, file_name, number_of_nodes_ptr) == FILE_LOAD_SUCCESS) {
            return FILE_LOAD_SUCCESS;
        }
    }

    printf("\nError: File containing node details failed to load.\n");
    return FILE_LOAD_FAILURE;
}

int tracks_read_cycle(event_ptr event, int* number_of_nodes_ptr, int* number_of_tracks_ptr) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;

    printf("\n\nPlease enter in the file path and name of the tracks file: ");
    scanf("%s", file_name);

    (*number_of_tracks_ptr) = get_number_of_tracks(file_name, number_of_tracks_ptr);

    if ((*number_of_tracks_ptr) != 0) {
        printf("Number of Tracks: %d\n", *number_of_tracks_ptr);

        if (file_read = tracks_file_load(event, file_name, number_of_tracks_ptr) == FILE_LOAD_SUCCESS) {
            return FILE_LOAD_SUCCESS;
        }

        printf("\nError: File containing track details failed to load.\n");
        return FILE_LOAD_FAILURE;
    }
}