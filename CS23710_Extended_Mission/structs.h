/* 
 * File: structs.h
 * Author: Chris Savill - chs17
 * Description: File that defines the structures used in the event monitoring program.
 */

/* Define integer constants */
#define MAX_PATH_LENGTH 51      /* Max length of file path. */
#define MAX_EVENT_LENGTH 51     /* Max length of event name string including /0. */
#define MAX_DATE_LENGTH 20      /* Max length of date string including /0. */
#define MAX_NAME_LENGTH 41      /* Max length of name string including /0. */
#define NOT_SET 100
#define SUCCESS 1
#define FAILURE 0
#define TRUE 1
#define FALSE 0
/*-----------------------------------------------------------------------*/

/* Enumeration Definition */
enum type {
    CP, /* Timed checkpoint */
    JN, /* Junction */
    MC /* Medical checkpoint */
};
/*-----------------------------------------------------------------------*/

/* Enumeration Definition */
enum status {
    NS, /* Not yet started */
    TC, /* Time checkpoint */
    TN, /* Track number */
    A, /* Medical checkpoint */
    D, /* Departed Medical checkpoint */
    CC, /* Course completed */
    EI, /* Excluded for taking an incorrect route */
    EM, /* Excluded for medical safety reasons */
};
/*-----------------------------------------------------------------------*/

/* Structure used to encapsulate attributes of a 24-hour clock. */
typedef struct time {
    int hours; /* int used to store the hours of the clock. */
    int minutes; /* int used to store the minutes of the clock. */
} time;
/*-----------------------------------------------------------------------*/

/* Structure used to encapsulate attributes for a node. */
typedef struct node {
    struct node *next_node;
    int number; /* int used to store the node number. */
    enum type type; /* enum used to represent node type. */
} node;
/*-----------------------------------------------------------------------*/

/* Structure used to encapsulate attributes for a track. */
typedef struct track {
    struct track *next_track;
    int number; /* int used to store the track number. */
    struct node *nodeA; /* Pointer to a node struct used to point to the node that the track leads from. */
    struct node *nodeB; /* Pointer to a node struct used to point to the node that the track leads to. */
    int max_time; /* int use to store the maximum time it should take for a competitor to get across the track. */
} track;
/*-----------------------------------------------------------------------*/

/* Structure used to encapsulate attributes for an entrant. */
typedef struct competitor {
    struct competitor *next_competitor;
    int number; /* int used to store the competitor's number. */
    char name[MAX_NAME_LENGTH]; /* char array used to store the entrants name. */
    char course; /* char used to store the course the entrant has entered. */
    struct course *course_ptr;
    time start_time; /* time struct used to store the time at which the competitor started on their course. */
    time end_time; /* time struct used to store the time at which the competitor finished their course. */
    time last_time_recored;
    int last_checkpoint_index;
    time medical_arrival_time; /* time struct used to store the time at which the competitor arrived at a medical checkpoint. */
    time medical_departure_time; /* time struct used to store the time at which the competitor departed the medical checkpoint. */
    int medical_minutes;
    enum status status; /* int used to store the current location of the competitor (#defined constant). */
    int location;
} competitor;
/*-----------------------------------------------------------------------*/

/* Structure used to encapsulate attributes for  a course. */
typedef struct course {
    char id;
    int number_of_nodes; /* int used to store the number of nodes in the course. */
    node **course_nodes;
    struct course *next_course;
} course;
/*-----------------------------------------------------------------------*/

/* Structure used to encapsulate attributes for an event. */
typedef struct event {
    char name[MAX_EVENT_LENGTH]; /* char array used to store the name of the event. */
    char date[MAX_DATE_LENGTH]; /* char array used to store the date of the event. */
    struct time start_time; /* time struct used to store the start time of the event. */
    struct time current_time;
    int number_of_nodes;
    struct node *node_head;
    int number_of_tracks;
    struct track *track_head;
    int number_of_courses;
    struct course *course_head;
    int number_of_competitors;
    struct competitor *competitor_head;
} event;
/*-----------------------------------------------------------------------*/

/* Type Definitions */
typedef event *event_ptr; /* Type definition for a pointer to an event struct. */
/*-----------------------------------------------------------------------*/
