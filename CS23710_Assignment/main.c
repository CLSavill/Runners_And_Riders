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
    int load_success;

    printf("Event Monitoring Program Launching...\n");
    load_success = loader();
    return (EXIT_SUCCESS);
}

int loader() {
    int file_read;
    event_ptr event;
    node *node_array; // Declares a pointer to a node array.
    int number_of_nodes;
    int *number_of_nodes_ptr = &number_of_nodes;
    *number_of_nodes_ptr = 0;
    track *track_array;
    int number_of_tracks = 0;
    int *number_of_tracks_ptr = &number_of_tracks;
    event = (event_ptr) malloc(sizeof (struct event));

    file_read = event_read_cycle(event);

    if (file_read == FILE_LOAD_SUCCESS) {
        file_read = nodes_read_cycle(node_array, number_of_nodes_ptr);
    }

    if (file_read == FILE_LOAD_SUCCESS) {
        file_read = tracks_read_cycle(node_array, number_of_nodes_ptr, track_array, number_of_tracks_ptr);
    }




    /* if (file_read == FILE_LOAD_SUCCESS) {
                        
     }

 /*if (file_read != NULL) {
     file_read = courses_file_load();
                
     if (file_read != NULL) {
         file_read = entrants_file_load();
                    
         if (file_read != NULL) {
             main_menu();
         }
         else {
             printf("\nError: File containing entrants details failed to load.");
         }
                    
     }
     else {
         printf("\nError: File containing course details failed to load.");
     }
 }*/

    return FILE_LOAD_SUCCESS;
}

int event_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];
    printf("\nPlease enter in the file path and name of the event file: ");
    scanf("%s", file_name);

    event = event_file_load(file_name, event);

    if (event != NULL) {
        printf("\n%s\n%s\n%02d:%d", event -> name, event -> date, event -> start_time.hours, event -> start_time.minutes);
        return FILE_LOAD_SUCCESS;
    } else {
        printf("\nError: File containing event details failed to load.");
        return FILE_LOAD_FAILURE;
    }
}

int nodes_read_cycle(node* node_array, int* number_of_nodes_ptr) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;

    printf("\n\nPlease enter in the file path and name of the nodes file: ");
    scanf("%s", file_name);

    *number_of_nodes_ptr = get_number_of_nodes(file_name, number_of_nodes_ptr);
   //node_array = (node*) calloc((*number_of_nodes_ptr), sizeof (struct node));
    node_array = (node*) malloc((*number_of_nodes_ptr) * sizeof (struct node));

    if ((*number_of_nodes_ptr) != 0) {
        printf("Number of Nodes: %d\n", (*number_of_nodes_ptr));
        file_read = nodes_file_load(file_name, node_array, number_of_nodes_ptr);
        printf("Node Number: %d, Node Type: %d", node_array[1].number, node_array[1].type);

        if (file_read == FILE_LOAD_SUCCESS) {
            return FILE_LOAD_SUCCESS;
        } else {
            printf("\nError: File containing node details failed to load.");
        }
    }

    return FILE_LOAD_FAILURE;
}

int tracks_read_cycle(node* node_array, int* number_of_nodes_ptr, track* track_array, int* number_of_tracks_ptr) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;
    
    printf("Node Number: %d, Node Type: %d", node_array[1].number, node_array[1].type);
    printf("\n\nPlease enter in the file path and name of the tracks file: ");
    scanf("%s", file_name);

    *number_of_tracks_ptr = get_number_of_tracks(file_name);
    //track_array = (track*) calloc((*number_of_tracks_ptr), sizeof (struct track));
    track_array = (track*) malloc((*number_of_tracks_ptr) * sizeof (struct track)); // Allocates memory for the whole array of tracks.

    if ((*number_of_tracks_ptr) != 0) {
        printf("Number of Tracks: %d\n", (*number_of_tracks_ptr));
        file_read = tracks_file_load(file_name, track_array, number_of_tracks_ptr, node_array, number_of_nodes_ptr);

        if (file_read == FILE_LOAD_SUCCESS) {
            return FILE_LOAD_SUCCESS;
        } else {
            printf("\nError: File containing track details failed to load.");
        }

        return FILE_LOAD_FAILURE;
    }
}