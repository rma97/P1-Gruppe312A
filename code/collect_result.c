#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 10000

void append_to_string(char *append_to, int number, int current_length);
void check(FILE *pointer);

int main(void) {
  int number_of_nodes, i, delete_count = 0, workload_individual = 0, workload_total = 0;
  char file_string_w[] = "tasks000.txt";
  char file_string_workload[] = "workload000.txt";
  char buffer[1000];
  char ch;

  FILE *ptr_non = fopen("number_of_nodes.txt", "r");
  FILE *ptr_out = fopen("Output.txt.txt", "w");  
  check(ptr_non);
  check(ptr_out);
  char temp[50];
  fgets(temp, 50, ptr_non);
  
  sscanf(temp, " %d", &number_of_nodes);

  fclose(ptr_non);

  printf("I found %d number of files", number_of_nodes);
  /* printf("Combines the following files to Output.txt\n"); */

  for(i = 1; i <= number_of_nodes; ++i) {
    append_to_string(file_string_w, i, 5);
    /* printf("%s\n", file_string_w); */
    workload_individual = 0;

    FILE *ptr_task = fopen(file_string_w, "r");
    check(ptr_task); 

    while((ch = fgetc(ptr_task)) != EOF){
      fputc(ch, ptr_out);
    }

    rewind(ptr_task);

    fgets(buffer, 1000, ptr_task);  
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

  fprintf(ptr_out, "Total workload amount: %d", workload_total);

  fclose(ptr_out);

  for(i = 1; i <= number_of_nodes; ++i){
    append_to_string(file_string_workload, i, 8);
    remove(file_string_workload);
  }

  return 0;

}

void append_to_string(char *append_to, int number, int current_length){
  append_to[current_length]     = (char)((number / 100)                        + 48);
  append_to[current_length + 1] = (char)((((number % 100) - number % 10) / 10) + 48);
  append_to[current_length + 2] = (char)(number %  10                          + 48);
}

void check(FILE *pointer) {
  if(pointer == NULL) {
    printf("Error opening the file!");             
  }
}
