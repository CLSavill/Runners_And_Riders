/* 
 * File: file_reader.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to reading in the various data files.
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

// Method to load in the details of the event from the file supplied (probably named "name.txt").

event_ptr event_file_load(event_ptr event) {
    FILE * event_file = NULL; // File pointer.
    char file_name[MAX_PATH_LENGTH];
    int load_status;

    printf("\nPlease enter in the file path and name of the event file: ");
    scanf("%s", file_name);
    ///////////////////////////////////////////////////////////////////////////
    event_file = fopen(file_name, "r");

    load_status = fscanf(event_file, "%[a-zA-Z -]", event -> name);
    if (load_status == EOF) {
        printf("\nError reading in Event Date.");
        fclose(event_file);
        return NULL;
    } else {
        load_status = fscanf(event_file, " %[a-zA-Z0-9 ]", event -> date);
        if (load_status == EOF) {
            printf("\nError reading in Event Start Time.");
            fclose(event_file);
            return NULL;
        } else {
            load_status = fscanf(event_file, " %d:%d",
                    &event -> start_time.hours,
                    &event -> start_time.minutes);
        }
    }

    printf("\nEvent file loaded in successfully.\n");
    fclose(event_file);
    return event;
}
///////////////////////////////////////////////////////////////////////////

// Method to load in all the nodes read from the file supplied (probably named "nodes.txt").

int nodes_file_load(node* node_array) {
    FILE * nodes_file; // File pointer.
    char file_name[MAX_PATH_LENGTH];
    int load_status = 0;
    int number_of_nodes = 0;
    int counter = 0;
    char line_input[7]; // Size 7 used just incase a large number of nodes are contained in a course.
    char type_input[3];

    printf("\n\nPlease enter in the file path and name of the nodes file: ");
    scanf("%s", file_name);

    nodes_file = fopen(file_name, "r"); // Open file with read permissions only.

    while (fgets(line_input, sizeof (line_input), nodes_file)) { // While end of file has not been reached.
        number_of_nodes++; // Counts the number of nodes.
    }

    node_array = (node*) malloc(number_of_nodes * sizeof (struct node)); // Allocates memory for the whole array of nodes.  
    rewind(nodes_file); // Rewinds file pointer to start of file.

    for (counter; counter < number_of_nodes; counter++) {
        load_status = fscanf(nodes_file, " %d %2s", &node_array[counter].number, type_input);
        if (strcmp(type_input, "CP") == 0) { // Evaluates input and assigns corresponding enum value.
            node_array[counter].type = CP;
        } else if (strcmp(type_input, "JN") == 0) { // Evaluates input and assigns corresponding enum value.
            node_array[counter].type = JN;
        } else if (strcmp(type_input, "MP") == 0) { // Evaluates input and assigns corresponding enum value.
            node_array[counter].type = MP;
        }
        printf("%d, %d = %2s\n", node_array[counter].number, node_array[counter].type, type_input);
    }

    printf("\nNodes file loaded in successfully.\n");
    fclose(nodes_file); // Closes file as no longer needed.
    return FILE_LOAD_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

/*int tracks_file_load() {
    printf("Please enter in the file path and name of the tracks file: ");
    scanf("%s", file_name);
}

int courses_file_load() {
    printf("Please enter in the file path and name of the course file: ");
    scanf("%s", file_name);
}

int entrants_file_load() {
    printf("Please enter in the file path and name of the entrants/competitors file: ");
    scanf("%s", file_name);
} */

