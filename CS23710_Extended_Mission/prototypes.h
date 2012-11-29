/* 
 * File: prototypes.h
 * Author: Chris Savill - chs17
 * Description: File that defines the method prototypes used in the event monitoring program.
 */

/* main.c Method Prototypes */
int loader(event_ptr event);
int menu(event_ptr event);
/*-----------------------------------------------------------------------*/

/* loader.c Method Prototypes */
int event_read_cycle(event_ptr event);
int nodes_read_cycle(event_ptr event);
int tracks_read_cycle(event_ptr event);
int courses_read_cycle(event_ptr event);
int competitors_read_cycle(event_ptr event);
int get_number_of_lines(char* file_name, int number_of_lines);
void read_times_file(event_ptr event);
/*-----------------------------------------------------------------------*/

/* event.c Method Prototypes */
int event_file_load(char* file_name, event_ptr event);
void print_not_started(event_ptr event);
void print_out_on_course(event_ptr event);
void print_finished(event_ptr event);
void print_results(event_ptr event);
/*-----------------------------------------------------------------------*/

/* nodes.c Method Prototypes */
int nodes_file_load(event_ptr event, char* file_name);
enum type determine_type(char* type_input);
node* get_node(node* node_head, int number);
/*-----------------------------------------------------------------------*/

/* tracks.c Method Prototypes */
int tracks_file_load(event_ptr event, char* file_name);
track* get_track(track* track_head, int node1, int node2);
/*-----------------------------------------------------------------------*/

/* courses.c Method Prototypes */
int courses_file_load(event_ptr event, char* file_name);
node** read_course_nodes(event_ptr event, node** course_nodes, FILE* courses_file, int number_of_course_nodes);
course* get_course_ptr(event_ptr event, competitor* competitor);
int get_course_node_number(course* course_ptr, int index);
int get_course_node_index(course* course_ptr, int node_number, int last_index);
int get_next_checkpoint_index(course* course_ptr, int last_index);
/*-----------------------------------------------------------------------*/

/* competitors.c Method Prototypes */
int competitors_file_load(event_ptr event, char* file_name);
competitor* get_competitor(event_ptr event, int number);
void query_location(event_ptr event);
void print_location(event_ptr event, competitor* competitor);
void update_competitor(event_ptr event);
void checkpoint_update(event_ptr event, competitor* competitor, int checkpoint, int hours, int minutes);
time get_time(competitor* competitor);
void update_statuses(event_ptr event);
int estimate_location(event_ptr event, competitor* competitor);
void evaluate_status(event_ptr event, competitor* competitor, int status, int checkpoint, int hours, int minutes);
/*-----------------------------------------------------------------------*/