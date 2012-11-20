#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "prototypes.h"
#include "test.h"

void test_print_cycle(event_ptr event) {
    printf("\nTesting Phase Beginning...\n");

    printf("\nPrinting Nodes...\n\n");
    test_nodes(event->node_head);

    printf("\nPrinting Tracks...\n\n");
    test_tracks(event->track_head);

    printf("\nPrinting Courses...\n\n");
    test_courses(event->course_head);

    printf("\nPrinting Competitors...\n\n");
    test_competitors(event->competitor_head);
}

void test_nodes(node* head_node) {
    node *current_node;
    current_node = head_node;

    printf("Head Node: Number: %d, Type: %d\n", current_node->number,
            current_node->type);
    current_node = current_node->next_node;

    while (current_node->next_node != NULL) {
        printf("Node: Number: %d, Type: %d, Previous: %d\n", current_node->number,
                current_node->type, current_node->previous_node->number);
        current_node = current_node->next_node;
    }
}

void test_tracks(track* head_track) {
    track *current_track;
    current_track = head_track;

    printf("Head Track: Number: %d, Start: %d, End: %d, Max Time: %d\n",
            current_track->number,
            current_track->track_start->number,
            current_track->track_end->number,
            current_track->max_time);
    current_track = current_track->next_track;

    while (current_track->next_track != NULL) {
        printf("Track: Number: %d, Start: %d, End: %d, Max Time: %d, Previous: %d\n",
                current_track->number,
                current_track->track_start->number,
                current_track->track_end->number,
                current_track->max_time,
                current_track->previous_track->number);
        current_track = current_track->next_track;
    }
}

void test_courses(course* head_course) {
    course *current_course;
    current_course = head_course;
    int counter = 0;

    printf("\nHead Course: ID: %c, Number of Nodes: %d,  Nodes: [",
            current_course->id,
            current_course->number_of_nodes);

    for (counter; counter < current_course->number_of_nodes; counter++) {
        if (counter != (current_course->number_of_nodes - 1)) {
            printf("%d,", current_course->course_nodes[counter]);
        } else {
            printf("%d]", current_course->course_nodes[counter]);
            printf("\n");
        }
    }
    current_course = current_course->next_course;

    while (current_course->next_course != NULL) {
        printf("\nCourse: ID: %c, Number of Nodes: %d, Nodes: [",
                current_course->id,
                current_course->number_of_nodes);

        counter = 0;

        for (counter; counter < current_course->number_of_nodes; counter++) {
            if (counter != (current_course->number_of_nodes - 1)) {
                printf("%d,", current_course->course_nodes[counter]);
            } else {
                printf("%d]", current_course->course_nodes[counter]);
                printf("\n");
                printf("Previous Course: %c\n", current_course->previous_course->id);
            }
        }
        current_course = current_course->next_course;
    }
}

void test_competitors(competitor* head_competitor) {
    competitor *current_competitor;
    current_competitor = head_competitor;

    printf("Head Competitor: Number: %d, Course: %c, Name: %s\n", current_competitor->number,
            current_competitor->course, current_competitor->name);
    current_competitor = current_competitor->next_competitor;

    while (current_competitor->next_competitor != NULL) {
        printf("Competitor: Number: %d, Course: %c, Name: %s, Previous: %d\n", current_competitor->number,
                current_competitor->course,
                current_competitor->name,
                current_competitor->previous_competitor->number);
        current_competitor = current_competitor->next_competitor;
    }

}