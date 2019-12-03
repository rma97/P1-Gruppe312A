#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CHARS 10000
#define ASCII_A 48

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
  char file_string_w[] = "tasks000.txt";
  char file_string_workload[] = "workload000.txt";
  char file_string_output[] = "Output000.txt";
  char line_from_file[1000];
  char buffer[1000];
  char temp[50];
  char ch;
  node time[1000];
  FILE *ptr_non, *ptr_out, *ptr_task;

  ptr_non = fopen("number_of_nodes.txt", "r");
  for (i = 0; i < 1000; ++i){
    change_template(file_string_output, i);
    if(access(file_string_output, F_OK) == -1){
      change_template(file_string_output, i);
      break;
    }
  }
  ptr_out = fopen(file_string_output, "w");
  check(ptr_non);
  check(ptr_out);
  fgets(temp, 50, ptr_non);
  
  sscanf(temp, " %d", &number_of_nodes);

  fclose(ptr_non);

  printf("I found %d number of files", number_of_nodes);
  /* printf("Combines the following files to Output.txt\n"); */

  for(i = 1; i <= number_of_nodes; ++i) {
    change_template(file_string_w, i);
    /* printf("%s\n", file_string_w); */
    workload_individual = 0;

    ptr_task = fopen(file_string_w, "r");
    check(ptr_task); 

    /* while((ch = fgetc(ptr_task)) != EOF){
      ungetc(ch, ptr_task);
      restart_string(line_from_file, sizeof(line_from_file) / sizeof(char));
      fgets(line_from_file, 1000, ptr_task);
      fprintf(ptr_task, "%s ", line_from_file);
      sscanf(line_from_file, "Time: %d", &time[i]);
      printf("%d\n", time[i]);
    } */

    while((ch = fgetc(ptr_task)) != EOF){
      fputc(ch, ptr_out);
    }

    rewind(ptr_task);

    fgets(buffer, 1000, ptr_task);
    fgets(line_from_file, 1000, ptr_task);

    sscanf(line_from_file, "Time: %d", &time[i-1].time);
    time[i-1].node_ID = i;

    while((ch = fgetc(ptr_task)) != EOF){
      if (ch == ' '){
        ++workload_individual;
        ++workload_total;
      }
    } 

    fprintf(ptr_out, "\nIndividual workload amount: %d\n", workload_individual);

    fprintf(ptr_out, "\n"); 

    fclose(ptr_task); 

    if (remove(file_string_w) == 0){
      delete_count++;
    }
  }



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

int compare_time(const void *p1, const void *p2){
  node *c1 = (node *)p1,
       *c2 = (node *)p2;
  
  if(c1->time > c2->time){
    return -1;
  } else{
    return 1;
  }
}

void restart_string(char *string, int n){
  int i;
  for(i = 0; i < n; i++){
    string[i] = '\0';
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
  template[i]     = (char)((number / 100)                        + ASCII_A);
  /* This is the  10th spot, so that is the remaning of dividing with 100 minus the reaming divided by 10. divided with 10. */
  template[i + 1] = (char)((((number % 100) - number % 10) / 10) + ASCII_A);
  /* this is the   1th spot, and is just the remaning after dividing by 10. */
  template[i + 2] = (char)(number %  10                          + ASCII_A);
}

void check(FILE *pointer) {
  if(pointer == NULL) {
    printf("Error opening the file!");             
  }
}
