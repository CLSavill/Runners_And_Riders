/* 
 * File: nodes.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's nodes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"

// Method to load in all the nodes read from the file supplied (probably named "nodes.txt").

int nodes_file_load(event_ptr event, char* file_name) {
    FILE *nodes_file; // File pointer.
    int counter = 0;
    char type_input[3];
    int number;
    node *new_node;
    event->node_head = NULL;

    nodes_file = fopen(file_name, "r"); // Open file with read permissions only.

    for (counter; counter < event->number_of_nodes; counter++) {
        fscanf(nodes_file, " %d %2s", &number, type_input);

        if (counter == 0) {
            new_node = malloc(sizeof (struct node)); // Allocates memory for a new node.
        }

        // Initialises new node:
        new_node->number = number;
        new_node->type = determine_type(type_input);
        new_node->next_node = NULL;
        ///////////////////////////////////////////////////////////////////////////

        // Adds new node to linked list:
        if (event->node_head == NULL) {
            event->node_head = new_node;
            printf("Head Node: Number: %d, Type: %d = %2s\n", new_node->number,
                    new_node->type, type_input);
        } else {
            printf("Node: Number: %d, Type: %d = %2s\n", new_node->number,
                    new_node->type, type_input);
        }
        ///////////////////////////////////////////////////////////////////////////

        if (counter != event->number_of_nodes) {
            new_node->next_node = malloc(sizeof (struct node)); // Allocates memory for the next node.
            new_node = new_node->next_node;
        }
    }

    printf("\nNodes file loaded in successfully.\n");
    fclose(nodes_file); // Closes file as no longer needed.
    return SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

// Method to determine the enum type of a node.

enum type determine_type(char* type_input) {
    if (strcmp(type_input, "CP") == 0) { // Evaluates input and assigns corresponding enum value.
        return CP;
    } else if (strcmp(type_input, "JN") == 0) { // Evaluates input and assigns corresponding enum value.
        return JN;
    } else if (strcmp(type_input, "MP") == 0) { // Evaluates input and assigns corresponding enum value.
        return MP;
    }
}
///////////////////////////////////////////////////////////////////////////

// Method that finds a node that matches a number passed in an returns the corresponding node pointer.

node* get_node(node* node_head, int number) {
    node* current_node;
    current_node = node_head;

    while (current_node->next_node != NULL) {
        if (current_node->number == number) {
            return current_node;
        } else {
            current_node = current_node->next_node;
        }
    }
}
///////////////////////////////////////////////////////////////////////////
