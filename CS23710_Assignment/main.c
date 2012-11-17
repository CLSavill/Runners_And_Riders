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

    printf("Event Monitoring Program Launching...\n");
    event = loader(event);

    node *current_node;
    current_node = event->node_head;

    int counter = 0;
    printf("Testing phase...\n\n");
    printf("Node Number: %d, Node Type: %d\n", current_node->number,
            current_node->type);
    current_node = current_node->next_node;
    for (counter; counter < 12; counter++) {
        printf("Node Number: %d, Node Type: %d, Previous Node: %d\n", current_node->number,
                current_node->type, current_node->previous_node->number);
        current_node = current_node->next_node;
    }
    return (EXIT_SUCCESS);
}

event_ptr loader(event_ptr event) {
    int number_of_nodes = 0;
    int *number_of_nodes_ptr = &number_of_nodes;
    printf("%d\n", *number_of_nodes_ptr);
    int number_of_tracks = 0;
    int *number_of_tracks_ptr = &number_of_tracks;

    event = event_read_cycle(event);
    event = nodes_read_cycle(event, number_of_nodes_ptr);

    /*if (file_read == FILE_LOAD_SUCCESS) {
        file_read = tracks_read_cycle(event);
    }*/




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

    return event;
}

event_ptr event_read_cycle(event_ptr event) {
    char file_name[MAX_PATH_LENGTH];
    printf("\nPlease enter in the file path and name of the event file: ");
    scanf("%s", file_name);

    event = event_file_load(file_name, event);

    printf("\n%s\n%s\n%02d:%d\n", event -> name, event -> date, event -> start_time.hours, event -> start_time.minutes);
    return event;
}

event_ptr nodes_read_cycle(event_ptr event, int* number_of_nodes_ptr) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;
    printf("\n\nPlease enter in the file path and name of the nodes file: ");
    scanf("%s", file_name);

    file_read = get_number_of_nodes(file_name, number_of_nodes_ptr);

    if ((*number_of_nodes_ptr) != 0) {
        printf("Number of Nodes: %d\n", *number_of_nodes_ptr);

        event = nodes_file_load(event, file_name, number_of_nodes_ptr);
    }

    return event;
}

/*int tracks_read_cycle(event_ptr event, int number_of_nodes) {
    char file_name[MAX_PATH_LENGTH];
    int file_read;
    int number_of_tracks;
    
    printf("\n\nPlease enter in the file path and name of the tracks file: ");
    scanf("%s", file_name);

    number_of_tracks = get_number_of_tracks(file_name);

    if (number_of_tracks != 0) {
        printf("Number of Tracks: %d\n", number_of_tracks);
        file_read = tracks_file_load(event, file_name, number_of_nodes, number_of_tracks);

        if (file_read == FILE_LOAD_SUCCESS) {
            return FILE_LOAD_SUCCESS;
        } else {
            printf("\nError: File containing track details failed to load.");
        }

        return FILE_LOAD_FAILURE;
    }
}*/