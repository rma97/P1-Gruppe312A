#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CHARS 10000
#define ASCII_0 48

struct node{
  int time;
  int node_ID;
};

typedef struct node node;

void change_template(char *template, int number);
void restart_string(char *string, int n);
void check(FILE *pointer);
int compare_time(const void *p1, const void *p2);

int main(void) {
  int number_of_nodes, i, delete_count = 0, workload_individual = 0, workload_total = 0;
  char file_string_tasks[] = "tasks000.txt";
  char file_string_workload[] = "workload000.txt";
  char file_string_output[] = "Output000.txt";
  char line_from_file[1000];
  char buffer[1000];
  char temp[50];
  char ch;
  node time[1000];
  FILE *ptr_non, *ptr_out, *ptr_task;

  ptr_non = fopen("number_of_nodes.txt", "r");
  /* Loop that creates multiple Output files */
  for (i = 0; i < 1000; ++i){
    change_template(file_string_output, i);
    /* access function checks if a file exists, from the library unistd.h. While there are Output files it keeps counting,
       if there isn't, it breaks. */
    if(access(file_string_output, F_OK) == -1){
      break;
    }
  }
  ptr_out = fopen(file_string_output, "w");
  check(ptr_non);
  check(ptr_out);

  /* reads the number_of_nodes.txt files to recieve the number of nodes */
  fgets(temp, 50, ptr_non);
  
  sscanf(temp, " %d", &number_of_nodes);

  fclose(ptr_non);

  printf("I found %d number of files", number_of_nodes);
  /* printf("Combines the following files to Output.txt\n"); */

  for(i = 1; i <= number_of_nodes; ++i) {
    change_template(file_string_tasks, i);
    workload_individual = 0;

    ptr_task = fopen(file_string_tasks, "r");
    check(ptr_task); 

    /* Loop that copies every char from the individual task file into the Output file */
    while((ch = fgetc(ptr_task)) != EOF){
      fputc(ch, ptr_out);
    }

    /* Rewind function from the string.h library, to go back to the beginning of the file */
    rewind(ptr_task);

    /* Use the fgets function, from string.h, to remove the first two lines of the file and put it into an array */
    fgets(buffer, 1000, ptr_task);
    /* Second line of the file is important, as the runtime of each node is important data so it is moved into a different array*/
    fgets(line_from_file, 1000, ptr_task);

    /* Scan for the runtime integer which is saved in the time array in the struct. */
    sscanf(line_from_file, "Time: %d", &time[i-1].time);
    time[i-1].node_ID = i;

    /* To avoid manually counting a large workload, a while loop goes through the third line of the task file and counts whitespace, 
       as the numbers in the file are separated by a whitespace */
    while((ch = fgetc(ptr_task)) != EOF){
      if (ch == ' '){
        ++workload_individual;
        ++workload_total;
      }
    } 

    fprintf(ptr_out, "\nIndividual workload amount: %d\n", workload_individual);

    fprintf(ptr_out, "\n"); 

    fclose(ptr_task); 

    /* After everything important from the file is retrieved, it is deleted. */
    remove(file_string_tasks);
  }

  /* After the runtime of each node is stored, it is sorted so they're ordered by speed */
  qsort(time, number_of_nodes, sizeof(node), compare_time);

  fprintf(ptr_out, "\nSlowest node(%d): %d\nFastest node(%d): %d\n", time[0].node_ID, time[0].time, time[number_of_nodes-1].node_ID, 
                                                                     time[number_of_nodes-1].time);
  
  for (i=0;i<number_of_nodes;++i){
    printf("Time: %d, Node: %d\n", time[i].time, time[i].node_ID);
  }

  fprintf(ptr_out, "Total workload amount: %d", workload_total);

  fclose(ptr_out);

  for(i = 1; i <= number_of_nodes; ++i){
    change_template(file_string_workload, i);
    remove(file_string_workload);
  }

  return 0;

}

/* Function that compares the node speeds */
int compare_time(const void *element1, const void *element2){
  node *node1 = (node *)element1,
       *node2 = (node *)element2;
  
  if(node1->time > node2->time){
    return -1;
  } else{
    return 1;
  }
}

void change_template(char *template, int number){
  int i = 0, infinite_loop_break = 1000;
  /* This goes until it find the first occurence of 0 in the template / string, and stop if i reaches 1000, so not to get stuck in an infinit loop. */
  while(template[i] != '0'){
    if(i >= infinite_loop_break){
      printf("Wrong use of the function change_template.");
      exit(EXIT_FAILURE);
    }
    i++;
  }
  /* This is the 100th spot, so for each time we can divide the number with 100. */
  template[i]     = (char)((number / 100)                        + ASCII_0);
  /* This is the  10th spot, so that is the remaning of dividing with 100 minus the reaming divided by 10. divided with 10. */
  template[i + 1] = (char)((((number % 100) - number % 10) / 10) + ASCII_0);
  /* this is the   1th spot, and is just the remaning after dividing by 10. */
  template[i + 2] = (char)(number %  10                          + ASCII_0);
}

/* Checks if the called file exists */
void check(FILE *pointer) {
  if(pointer == NULL) {
    printf("Error opening the file!");             
  }
}