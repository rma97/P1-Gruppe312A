#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 10000

void append_to_string(char *append_to, int number, int current_length);
void check(FILE *pointer);

int main(void) {
  int number_of_nodes, i;
  char file_string_w[] = "tasks000.txt";
  
  char buffer[1000];
  FILE *ptr_non = fopen("number_of_nodes.txt", "r");
  FILE *ptr_out = fopen("Output.txt.txt", "w");  
  check(ptr_non);
  check(ptr_out);
  char temp = fgetc(ptr_non);

  sscanf(&temp, " %d", &number_of_nodes);

  fclose(ptr_non);
  
  printf("Combines the following files to Output.txt\n");

  for(i = 1; i <= number_of_nodes; ++i) {
 
    append_to_string(file_string_w, i, 5);
    printf("%s\n", file_string_w);

    FILE *ptr_task = fopen(file_string_w, "r");
    check(ptr_task);

    fprintf(ptr_out, "Node %d: \n", i);

    fgets(buffer, MAX_CHARS ,ptr_task);
    fputs(buffer, ptr_out);

    fprintf(ptr_out, "\n\n");

    fclose(ptr_task);   
  } 

  fclose(ptr_out);
  return 0;

}

void append_to_string(char *append_to, int number, int current_length){
  /*  printf("This is the number %d\n", number);*/
  append_to[current_length]     = (char)(number / 100 + 48);
  append_to[current_length + 1] = (char)(number /  10 + 48);
  append_to[current_length + 2] = (char)(number       + 48);
  
  /*  printf("%s\n", append_to); */
}

void check(FILE *pointer) {
  if(pointer == NULL) {
    printf("Error opening the file!");             
  }
}
