/* 
 * File: prototypes.h
 * Author: Chris Savill - chs17
 * Description: File that defines the function prototypes used in the event monitoring program.
 */

/* main.c Function Prototypes */
int main(int argc, char** argv);
int menu(event_ptr event);
/*-----------------------------------------------------------------------*/

/* loader.c Function Prototypes */
int loader(event_ptr event);
int load_cycle(event_ptr event, int (*load_function_ptr) (event_ptr, char*));
void read_times_file(event_ptr event);
int chronological_check(time current_time, int hours, int minutes);
/*-----------------------------------------------------------------------*/

/* event.c Function Prototypes */
int event_file_load(event_ptr event, char* file_name);
void print_not_started(event_ptr event);
void print_out_on_course(event_ptr event);
void print_finished(event_ptr event);
void print_results(event_ptr event);
void print_excluded(event_ptr event);
/*-----------------------------------------------------------------------*/

/* nodes.c Function Prototypes */
int nodes_file_load(event_ptr event, char* file_name);
enum type determine_type(char* type_input);
node* get_node(node* node_head, int number);
/*-----------------------------------------------------------------------*/

/* tracks.c Function Prototypes */
int tracks_file_load(event_ptr event, char* file_name);
track* get_track(track* track_head, int node1, int node2);
/*-----------------------------------------------------------------------*/

/* courses.c Function Prototypes */
int courses_file_load(event_ptr event, char* file_name);
node** read_course_nodes(event_ptr event, node** course_nodes, FILE* courses_file, int* load_status, int number_of_course_nodes);
course* get_course_ptr(event_ptr event, competitor* competitor);
int get_course_node_index(course* course_ptr, int node_number, int last_index);
int get_next_checkpoint_index(course* course_ptr, int last_index);
/*-----------------------------------------------------------------------*/

/* competitors.c Function Prototypes */
int competitors_file_load(event_ptr event, char* file_name);
competitor* get_competitor(event_ptr event, int number);
void query_location(event_ptr event);
void print_location(event_ptr event, competitor* competitor);
void update_competitor(event_ptr event);
time get_result_time(time end_time, time start_time, int medical_minutes);
int get_medical_time(time departure_time, time arrival_time);

/*-----------------------------------------------------------------------*/

/* updater.c Function Prototypes */
void checkpoint_update(event_ptr event, competitor* competitor, int checkpoint, int hours, int minutes);
void update_statuses(event_ptr event);
int estimate_location(event_ptr event, competitor* competitor);
track* track_estimation(event_ptr event, competitor* competitor, node* nodeA, node* nodeB, int node_index, int next_node_number, int event_time, int est_arrival_time);
void evaluate_status(event_ptr event, competitor* competitor, int status, int checkpoint, int hours, int minutes);
/*-----------------------------------------------------------------------*/
