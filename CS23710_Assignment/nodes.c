/* 
 * File: nodes.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's nodes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

// Method to get the number of nodes from a file supplied (probably named "nodes.txt").

int get_number_of_nodes(char* file_name, int* number_of_nodes_ptr) {
    FILE *nodes_file; // File pointer.
    char line_input[7]; // Size 7 used just incase a large number of nodes are contained in a course.

    nodes_file = fopen(file_name, "r"); // Open file with read permissions only.

    while (fgets(line_input, sizeof (line_input), nodes_file)) { // While end of file has not been reached.
        (*number_of_nodes_ptr)++; // Counts the number of nodes.
    }

    fclose(nodes_file); // Closes file as no longer needed.
    return (*number_of_nodes_ptr);
}
///////////////////////////////////////////////////////////////////////////

// Method to load in all the nodes read from the file supplied (probably named "nodes.txt").

int nodes_file_load(event_ptr event, char* file_name, int* number_of_nodes_ptr) {
    FILE *nodes_file; // File pointer.
    int load_status = 0;
    int counter = 0;
    char type_input[3];
    int number;
    node *current_node, *previous_node;
    event->node_head = NULL;

    nodes_file = fopen(file_name, "r"); // Open file with read permissions only.

    for (counter; counter < (*number_of_nodes_ptr); counter++) {
        load_status = fscanf(nodes_file, " %d %2s", &number, type_input);

        if (counter == 0) {
            current_node = malloc(sizeof (struct node));
        }

        current_node->number = number;
        current_node->type = determine_type(type_input);
        current_node->next_node = NULL;
        current_node->previous_node = NULL;

        if (event->node_head == NULL) {
            event->node_head = current_node;
            printf("Head Node: Number: %d, Type: %d = %2s\n", current_node->number,
                    current_node->type, type_input);
            previous_node = current_node;
            current_node->next_node = malloc(sizeof (struct node));
            current_node = current_node->next_node;
        } else {
            current_node->previous_node = previous_node;
            previous_node = current_node;
            current_node->next_node = malloc(sizeof (struct node));
            printf("Node: Number: %d, Type: %d = %2s, Previous: %d\n", current_node->number,
                    current_node->type, type_input, current_node->previous_node->number);
            current_node = current_node->next_node;
        }
    }

    printf("\nNodes file loaded in successfully.\n");
    fclose(nodes_file); // Closes file as no longer needed.
    return FILE_LOAD_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

enum type determine_type(char* type_input) {
    if (strcmp(type_input, "CP") == 0) { // Evaluates input and assigns corresponding enum value.
        return CP;
    } else if (strcmp(type_input, "JN") == 0) { // Evaluates input and assigns corresponding enum value.
        return JN;
    } else if (strcmp(type_input, "MP") == 0) { // Evaluates input and assigns corresponding enum value.
        return MP;
    }
}
