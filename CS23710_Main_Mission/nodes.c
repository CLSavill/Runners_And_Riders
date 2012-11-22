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
    int load_status = 0;
    int counter = 0;
    char type_input[3];
    int number;
    node *current_node;
    event->node_head = NULL;

    nodes_file = fopen(file_name, "r"); // Open file with read permissions only.

    for (counter; counter < event->number_of_nodes; counter++) {
        load_status = fscanf(nodes_file, " %d %2s", &number, type_input);

        if (counter == 0) {
            current_node = malloc(sizeof (struct node));
        }

        current_node->number = number;
        current_node->type = determine_type(type_input);
        current_node->next_node = NULL;

        if (event->node_head == NULL) {
            event->node_head = current_node;
            printf("Head Node: Number: %d, Type: %d = %2s\n", current_node->number,
                    current_node->type, type_input);
            current_node->next_node = malloc(sizeof (struct node));
            current_node = current_node->next_node;
        } else {
            current_node->next_node = malloc(sizeof (struct node));
            printf("Node: Number: %d, Type: %d = %2s\n", current_node->number,
                    current_node->type, type_input);
            current_node = current_node->next_node;
        }
    }

    printf("\nNodes file loaded in successfully.\n");
    fclose(nodes_file); // Closes file as no longer needed.
    return SUCCESS;
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

node* node_match(node* node, int number) {
    int node_found = 0;

    while (node_found == 0) {
        if (number == node->number) { // Evaluates if the two integer values match.               
            return node; // Returns the node pointer.
        } else {
            node = node->next_node;
        }
    }
}

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
