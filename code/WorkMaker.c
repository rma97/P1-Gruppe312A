#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(FILE *pointer);

int main(void){
  int i, char_amount, num_input;
  char alphabet = 'a';
  FILE *workload;

  /* Runs until it's given a valid input */
  do{
    printf("How many characters?: ");
    num_input = scanf(" %d", &char_amount);
    /* Eats everyting after the first number, and if there is no number, everything. */
    scanf("%*[^\n]");
    printf("\n");
  }while((char_amount <= 0 || char_amount >= 1000000) && num_input > 0);

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
  return 0;
}

/* Checks if the file is opened correct */
void check(FILE *pointer) {
  if(pointer == NULL) {
    printf("Error opening the file!");             
  }
}
