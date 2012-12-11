/* 
 * File: competitors.c
 * Author: Chris Savill - chs17
 * Description: File that contains methods related to handling an event's competitors.
 */

#include "structs.h"
#include "prototypes.h"

/* Function to load in all the competitors read from the file supplied (probably named "entrants.txt"). */
int competitors_file_load(event_ptr event, char* file_name) {
    FILE *competitors_file; /* File pointer. */
    int load_status;
    int number;
    char course;
    char name[MAX_NAME_LENGTH];
    competitor *new_competitor;
    event->competitor_head = NULL;

    if ((competitors_file = fopen(file_name, "r")) == NULL) { /* Open file with read permissions only and check file opened. */
        printf("Please enter in a valid file path and name.\n");
        return FAILURE;
    }

    while ((load_status = fscanf(competitors_file, " %d %c %[a-zA-Z ]", &number, &course, name)) != EOF && load_status == 3) {
        if (event->number_of_competitors == 0) {
            new_competitor = malloc(sizeof (struct competitor));
        } else {
            new_competitor->next_competitor = malloc(sizeof (struct competitor)); /* Allocates memory for the next competitor. */
            new_competitor = new_competitor->next_competitor;
        }

        /* Initialising the new competitor: */
        new_competitor->number = number;
        new_competitor->course = course;
        new_competitor->course_ptr = get_course_ptr(event, new_competitor);
        new_competitor->status = NS;
        new_competitor->location = -1;
        new_competitor->last_checkpoint_index = -1;
        new_competitor->medical_minutes = 0;
        strcpy(new_competitor->name, name);
        new_competitor->next_competitor = NULL;
        /*-----------------------------------------------------------------------*/

        /* Adding the new competitor to the linked list: */
        if (event->competitor_head == NULL) {
            event->competitor_head = new_competitor;
            printf("Head Competitor: Number: %d, Course: %c, Name: %s\n", new_competitor->number,
                    new_competitor->course, new_competitor->name);

        } else {
            printf("Competitor: Number: %d, Course: %c, Name: %s\n", new_competitor->number,
                    new_competitor->course,
                    new_competitor->name);
        }
        /*-----------------------------------------------------------------------*/

        event->number_of_competitors++;
    }

    if (load_status == EOF) {
        printf("\nCompetitors file loaded in successfully.\n");
        fclose(competitors_file); /* Closes file as no longer needed. */
        return SUCCESS;
    } else if (load_status != 3) { /* Expected 3 inputs. */
        printf("Error loading in file, possible pattern mismatch.\n");
        fclose(competitors_file); /* Closes file as no longer needed. */
        return FAILURE;
    }

}
/*-----------------------------------------------------------------------*/

/* Function to return a pointer to a competitor. */
competitor* get_competitor(event_ptr event, int number) {
    competitor *competitor;
    competitor = event->competitor_head;

    while (competitor != NULL) { /* Checks if no more competitors present in linked list. */
        if (competitor->number == number) {
            return competitor;
        } else {
            competitor = competitor->next_competitor;
        }
    }

    return NULL;
}
/*-----------------------------------------------------------------------*/

/* Function to get query the location of a competitor. */
void query_location(event_ptr event) {
    competitor *competitor;
    int number;

    printf("\nPlease enter in the competitor number you wish to query the location of: ");
    scanf("%d", &number);

    while ((competitor = get_competitor(event, number)) == NULL) {
        printf("\nPlease enter in a valid competitor number: ");
        scanf("%d", &number);
    }

    print_location(event, competitor);
}
/*-----------------------------------------------------------------------*/

/* Function to print out the status and location of the competitor passed in. */
void print_location(event_ptr event, competitor* competitor) {
    switch (competitor->status) {
        case NS:
            printf("\nCompetitor: %d, Name: %s, Location: Not Yet Started.\n",
                    competitor->number,
                    competitor->name);
            break;
        case TC:
            printf("\nCompetitor: %d, Name: %s, Location: At Time Checkpoint %d.\n",
                    competitor->number,
                    competitor->name,
                    competitor->location);
            break;
        case TN:
            printf("Last Recorded Location: Time Checkpoint %d.\n", competitor->last_checkpoint_index);
            printf("Assumed To Be On Track Number %d.\n", competitor->location);
            break;
        case A:
            printf("\nCompetitor: %d, Name: %s, Location: Medical Checkpoint %d.\n",
                    competitor->number,
                    competitor->name,
                    competitor->location);
            break;
        case D:
            printf("\nCompetitor: %d, Name: %s, Passed Medical Check and just departed Checkpoint %d.\n",
                    competitor->number,
                    competitor->name,
                    competitor->location);
            break;
        case CC:
            printf("\nCompetitor: %d, Name: %s, Completed Course.\n",
                    competitor->number,
                    competitor->name);
            break;
        case EI:
            printf("\nCompetitor: %d, Name: %s, Excluded for taking an Incorrect Route.\n",
                    competitor->number,
                    competitor->name);
            break;
        case EM:
            printf("\nCompetitor: %d, Name: %s, Excluded for Medical Safety Reasons.\n",
                    competitor->number,
                    competitor->name);
            break;
    }
}
/*-----------------------------------------------------------------------*/

/* Function to get a manual input for the updating of a competitor's arrival at a time checkpoint. */
void update_competitor(event_ptr event) {
    int hours;
    int minutes;
    competitor *competitor;
    int number;
    int checkpoint;
    char status;

    printf("\nPlease enter in the competitor number you wish to update: ");
    scanf("%d", &number);

    while ((competitor = get_competitor(event, number)) == NULL) { /* Check to make sure a valid competitor is entered. */
        printf("\nPlease enter in a valid competitor number: ");
        scanf("%d", &number);
    }

    getchar();
    printf("\nPlease enter in the new status of the competitor (T, I, A, D, E): ");
    scanf("%c", &status);

    while (status != 'T' && status != 'I' && status != 'A' && status != 'D' && status != 'E') { /* Check to make sure a valid status is entered. */
        printf("\nPlease enter in a valid status (T, I, A, D, E): ");
        scanf("%c", &status);
    }

    if (status == D) {
        checkpoint = competitor->location;
    } else {
        printf("\nPlease enter in the new checkpoint of the competitor: ");
        scanf("%d", &checkpoint);

        while (checkpoint > event->number_of_nodes || checkpoint < 1) { /* Check to make sure a valid status is entered. */
            printf("\nPlease enter in a valid checkpoint between 1 and %d: ", event->number_of_nodes);
            scanf("%d", &checkpoint);
        }
    }

    printf("\nPlease enter in the hour at which the competitor arrived (between 00 and 23) for a 24-hour clock: ");
    scanf("%02d", &hours);

    while (hours > 23 || hours < 00) { /* Check to make sure a valid number of hours is entered. */
        printf("\nPlease enter in a valid hour between 00 and 23 for a 24-hour clock: ");
        scanf("%02d", &hours);
    }

    printf("\nPlease enter in the minutes at which the competitor arrived: ");
    scanf("%02d", &minutes);

    while (minutes > 60 || minutes < 00) { /* Check to make sure a valid number of minutes is entered. */
        printf("\nPlease enter in a valid number of minutes between (00 and 60): ");
        scanf("%02d", &minutes);
    }

    if ((chronological_check(event->current_time, hours, minutes)) == SUCCESS) {
        evaluate_status(event, competitor, status, checkpoint, hours, minutes);
    } else {
        printf("\n\nSorry but the manual update you are attempting is not in chronological order, updating process aborted.\n");
    }
}
/*-----------------------------------------------------------------------*/

/* Function to return a time for a competitor. */
time get_result_time(time end_time, time start_time, int medical_minutes) {
    time time;

    time.hours = end_time.hours - start_time.hours;
    time.minutes = end_time.minutes - start_time.minutes - medical_minutes;

    /* Checks if minutes are negative and if so then adjust time accordingly. */
    while (time.minutes < 0) {
        time.hours--;
        time.minutes = 60 + time.minutes;
    }
    /*-----------------------------------------------------------------------*/

    return time;
}
/*-----------------------------------------------------------------------*/

/* Function to return the time spent at a medical checkpoint in minutes. */
int get_medical_time(time departure_time, time arrival_time) {
    int minutes;

    minutes = (departure_time.hours * 60) - (arrival_time.hours * 60);
    minutes += departure_time.minutes - arrival_time.minutes;
    return minutes;
}
/*-----------------------------------------------------------------------*/
