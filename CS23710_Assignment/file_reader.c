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

int get_number_of_nodes(char* file_name) {
    FILE * nodes_file; // File pointer.
    int number_of_nodes = 0;
    char line_input[7]; // Size 7 used just incase a large number of nodes are contained in a course.

    nodes_file = fopen(file_name, "r"); // Open file with read permissions only.

    while (fgets(line_input, sizeof (line_input), nodes_file)) { // While end of file has not been reached.
        number_of_nodes++; // Counts the number of nodes.
    }
    
    fclose(nodes_file); // Closes file as no longer needed.
    return number_of_nodes;
}

int nodes_file_load(node* node_array, char* file_name, int number_of_nodes) {
    FILE * nodes_file; // File pointer.
    int load_status = 0;
    int counter = 0;
    char type_input[3];  
    
    nodes_file = fopen(file_name, "r"); // Open file with read permissions only.

    for (counter; counter < number_of_nodes; counter++) {
        load_status = fscanf(nodes_file, " %d %2s", &node_array[counter].number, type_input);
        if (strcmp(type_input, "CP") == 0) { // Evaluates input and assigns corresponding enum value.
            node_array[counter].type = CP;
        } else if (strcmp(type_input, "JN") == 0) { // Evaluates input and assigns corresponding enum value.
            node_array[counter].type = JN;
        } else if (strcmp(type_input, "MP") == 0) { // Evaluates input and assigns corresponding enum value.
            node_array[counter].type = MP;
        }
        printf("Node Number: %d, Node Type: %d = %2s\n", node_array[counter].number,
                node_array[counter].type, type_input);
    }

    printf("\nNodes file loaded in successfully.\n");
    fclose(nodes_file); // Closes file as no longer needed.
    return FILE_LOAD_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////

int tracks_file_load(track* track_array, int number_of_nodes, node* node_array) {
    FILE * tracks_file; // File pointer.
    char file_name[MAX_PATH_LENGTH];
    int load_status = 0;
    int number_of_tracks = 0;
    int counter1 = 0, counter2 = 0;
    char line_input[18]; // Size 18 used just incase a large number of nodes are contained in a course.
    int track_start_number;
    int track_end_number;
    int track_start_assigned = 0;
    int track_end_assigned = 0;

    printf("\n\nPlease enter in the file path and name of the tracks file: ");
    scanf("%s", file_name);

    tracks_file = fopen(file_name, "r"); // Open file with read permissions only.

    while (fgets(line_input, sizeof (line_input), tracks_file)) { // While end of file has not been reached.
        number_of_tracks++; // Counts the number of tracks.
    }
    
    track_array = (track*) malloc(number_of_tracks * sizeof (struct track)); // Allocates memory for the whole array of tracks.  
    rewind(tracks_file); // Rewinds file pointer to start of file.

    for (counter1; counter1 < number_of_tracks; counter1++) {
        load_status = fscanf(tracks_file, " %d %d %d %d", &track_array[counter1].number,
                &track_start_number,
                &track_end_number,
                &track_array[counter1].max_time);

        counter2 = 0;
        for (counter2; counter2 < number_of_nodes; counter2++ && track_start_assigned == 0) {
            if (track_start_number == node_array[counter2].number) { // Evaluates if the two integer values match.               
                track_array[counter1].track_start = &node_array[counter2]; // Assigns the address of the node in the node array to the track start node pointer within the current track.
                track_start_assigned = 1;
            }
        }

        counter2 = 0;
        for (counter2; counter2 < number_of_nodes; counter2++ && track_end_assigned == 0) {
            if (track_end_number == node_array[counter2].number) { // Evaluates if the two integer values match.               
                track_array[counter1].track_end = &node_array[counter2]; // Assigns the address of the node in the node array to the track end node pointer within the current track.
                track_end_assigned = 1;
            }
        }
        printf("%d, %d, %d, %d\n", track_array[counter1].number,
                track_array[counter1].track_start -> number,
                track_array[counter1].track_end -> number,
                track_array[counter1].max_time);
    }

    printf("\nTracks file loaded in successfully.\n");
    fclose(tracks_file); // Closes file as no longer needed.
    return number_of_tracks;
}

/*int courses_file_load() {
    printf("Please enter in the file path and name of the course file: ");
    scanf("%s", file_name);
}

int entrants_file_load() {
    printf("Please enter in the file path and name of the entrants/competitors file: ");
    scanf("%s", file_name);
} */

