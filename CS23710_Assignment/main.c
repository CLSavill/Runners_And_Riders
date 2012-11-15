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
    int file_read;
    event_ptr event;
    event = (event_ptr) malloc(sizeof (struct event));

    printf("Event Monitoring Program Launching...\n");
    event = event_file_load(event);

    if (event != NULL) {
        printf("\n%s\n%s\n%02d:%d", event -> name, event -> date, event -> start_time.hours, event -> start_time.minutes);
        node *node_array; // Declares an array of nodes of length 'number_of_nodes'.
        file_read = nodes_file_load(node_array);

        /*if (file_read == FILE_LOAD_SUCCESS) {
            file_read = tracks_file_load();
            
            if (file_read != NULL) {
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
            }
            else {
                printf("\nError: File containing track details failed to load.");
            }
        }
        else {
            printf("\nError: File containing node details failed to load.");
        }*/
    } else {
        printf("\nError: File containing event details failed to load.");
    }

    return (EXIT_SUCCESS);
}

