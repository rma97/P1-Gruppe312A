#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(FILE *pointer);

void generate_workload(void){
  int i, char_amount;
  char alphabet = 'a';
  FILE *workload;

  printf("What should the size of the workload be?: ");
  scanf(" %d", &char_amount);

  workload = fopen("workloads.txt", "w");
  check(workload);

  for (i = 1; i <= char_amount; i++){
    fputc(alphabet, workload);

    ++alphabet;

    if (alphabet == 'z' + 1){
      alphabet = 'a';
    }
  }
  fclose(workload);
}

/* Checks if the file is opened correct */
void check(FILE *pointer) {
  if(pointer == NULL) {
    printf("Error opening the file!");             
  }
}
