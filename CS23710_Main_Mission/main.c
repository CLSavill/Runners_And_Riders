/* 
 * File: main.c
 * Author: Chris Savill - chs17
 * Description: Main file for event monitoring program (menu).
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"
#include "test.h"

/*
 * 
 */
int main(int argc, char** argv) {
    event_ptr event;
    event = malloc(sizeof (struct event));
    int file_read;

    printf("Event Monitoring Program Launching...\n");

    if (file_read = loader(event) == SUCCESS) {
        printf("Loading Cycle Finished.");
        test_print_cycle(event);
        if(menu(event) == SUCCESS) {
            printf("\n\nExiting Program...\n");
        }
    }
    
    return EXIT_SUCCESS;
}

int menu(event_ptr event) {
    int option;
    
    do {
        printf("\nPress enter to continue.\n");
        getchar(); // Consumes \n.
        getchar(); // Pauses program until a new character is entered.
        printf("\n*************************************************************************************");
        printf("\n************************************* MAIN MENU *************************************");
        printf("\n*                                                                                   *");
        printf("\n* 1: Query competitor for current location/status.                                  *");
        printf("\n* 2: Display how many competitors have not started yet.                             *");
        printf("\n* 3: Display how many competitors are out on the courses.                           *");
        printf("\n* 4: Display how many competitors have finished.                                    *");
        printf("\n* 5: Manually supply time at which a competitor had reached a time checkpoint.      *");
        printf("\n* 6: Read in a file of times at which competitors have reached time checkpoints.    *");
        printf("\n* 7: Display how many competitors have not started yet.                             *");
        printf("\n* 8: Exit program.                                                                  *");
        printf("\n*                                                                                   *");
        printf("\n*************************************************************************************");
        printf("\n\nPlease select from one of the options above (number): ");
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                query_location(event);
                break;
            case 2: 
                print_not_started(event);
                break;
            case 3:
                print_out_on_course(event);
                break;
            case 4:
                print_finished(event);
                break;
            case 5:
                update_competitor(event);
                break;
            case 8:
                break;
            default:
                printf("\nPlease enter in a valid option.");
        }
        
    } while (option != 8);
    
    return SUCCESS;
}