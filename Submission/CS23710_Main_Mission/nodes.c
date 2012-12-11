/* 
 * File: nodes.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's nodes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "prototypes.h"

/* Function to load in all the nodes read from the file supplied (probably named "nodes.txt"). */
int nodes_file_load(event_ptr event, char* file_name) {
    FILE *nodes_file; /* File pointer. */
    int load_status;
    char type_input[3];
    int number;
    node *new_node;
    event->node_head = NULL;

    if ((nodes_file = fopen(file_name, "r")) == NULL) { /* Open file with read permissions only and check file opened. */
        printf("Please enter in a valid file path and name.\n");
        return FAILURE;
    }

    while ((load_status = fscanf(nodes_file, " %d %2s", &number, type_input)) != EOF && load_status == 2) {
        if (event->number_of_nodes == 0) {
            new_node = malloc(sizeof (struct node)); /* Allocates memory for a new node. */
        } else {
            new_node->next_node = malloc(sizeof (struct node)); /* Allocates memory for the next node. */
            new_node = new_node->next_node;
        }

        /* Initialises new node: */
        new_node->number = number;
        new_node->type = determine_type(type_input);
        new_node->next_node = NULL;
        /*-----------------------------------------------------------------------*/

        /* Adds new node to linked list: */
        if (event->node_head == NULL) {
            event->node_head = new_node;
            printf("Head Node: Number: %d, Type: %d = %2s\n", new_node->number,
                    new_node->type, type_input);
        } else {
            printf("Node: Number: %d, Type: %d = %2s\n", new_node->number,
                    new_node->type, type_input);
        }
        /*-----------------------------------------------------------------------*/

        event->number_of_nodes++;
    }

    if (load_status == EOF) {
        printf("\nNodes file loaded in successfully.\n");
        fclose(nodes_file); /* Closes file as no longer needed. */
        return SUCCESS;
    } else if (load_status != 2) { /* Expected 2 inputs. */
        printf("Error loading in file, possible pattern mismatch.\n");
        fclose(nodes_file); /* Closes file as no longer needed. */
        return FAILURE;
    }
}
/*-----------------------------------------------------------------------*/

/* Function to determine the enum type of a node. */
enum type determine_type(char* type_input) {
    if (strcmp(type_input, "CP") == 0) { /* Evaluates input and assigns corresponding enum value. */
        return CP;
    } else if (strcmp(type_input, "JN") == 0) { /* Evaluates input and assigns corresponding enum value. */
        return JN;
    }
}
/*-----------------------------------------------------------------------*/

/* Function that finds a node that matches a number passed in an returns the corresponding node pointer. */
node* get_node(node* node_head, int number) {
    node* node;
    node = node_head;

    while (node != NULL) {
        if (node->number == number) {
            return node;
        } else {
            node = node->next_node;
        }
    }
}
/*-----------------------------------------------------------------------*/
