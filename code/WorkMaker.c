#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
  int i, char_amount;
  char alphabet = 'a';
  FILE *workload;

  printf("How many characters?: ");
  scanf(" %d", &char_amount);

  workload = fopen("Workload.txt", "w");
  check(workload);

  for (i = 1; i <= char_amount; i++){
    fputc(alphabet, workload);

    ++alphabet;

    if (alphabet == 'z' + 1){
      alphabet = 'a';
    }
  }

  return 0;
}

/* Checks if the file is opened correct */
void check(FILE *pointer) {
  if(pointer == NULL) {
    printf("Error opening the file!");             
  }
}