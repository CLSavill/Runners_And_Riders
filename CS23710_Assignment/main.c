/* 
 * File: main.c
 * Author: Chris Savill - chsFILE_LOAD_SUCCESS7
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
    event * event_ptr;
    event_ptr = calloc(1, sizeof (event)); // Allocates a single clock of memory for the event struct.
    
    printf("Event Monitoring Program Launching...\n");
    
    printf("\n%s\n%s\n%d:%d", event_ptr -> name, event_ptr -> date, event_ptr -> start_time.hours, event_ptr -> start_time.minutes);
    file_read = event_file_load(event_ptr);  
    
    if (file_read == FILE_LOAD_SUCCESS) {
        printf("\n%s\n%s\n%d:%d", event_ptr -> name, event_ptr -> date, event_ptr -> start_time.hours, event_ptr -> start_time.minutes);
        /*file_read =  nodes_file_load();
        
        if (file_read == FILE_LOAD_SUCCESS) {
            file_read = tracks_file_load();
            
            if (file_read == FILE_LOAD_SUCCESS) {
                file_read = courses_file_load();
                
                if (file_read == FILE_LOAD_SUCCESS) {
                    file_read = entrants_file_load();
                    
                    if (file_read == FILE_LOAD_SUCCESS) {
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
        } */
    }
    else {
        printf("\nError: File containing event details failed to load.");
    }  
    
    
    return (EXIT_SUCCESS);
}

