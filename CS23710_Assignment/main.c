/* 
 * File: main.c
 * Author: Chris Savill - chs17
 * Description: Main file for event monitoring program (menu).
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"
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
    }

    return (EXIT_SUCCESS);
}