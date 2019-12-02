#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRIME_MAX 100
#define PRIME_MIN 20

void check(FILE *pointer);
int random_gen(void);

void generate_workload(void){
  int i, prime, random_number, num_input;
  FILE *workload;

  /* Seeds the rand() with time */
  srand(time(NULL));

  /* Runs until it's given a valid input */
  do{
    printf("How many characters?: ");
    num_input = scanf(" %d", &prime);
    /* Eats everyting after the first number, and if there is no number, everything. */
    scanf("%*[^\n]");
    printf("\n");
  }while((prime <= 0 || prime >= 1000000) && num_input < 1);

  workload = fopen("workloads.txt", "w");
  check(workload);

  for (i = 1; i <= prime; i++){
    random_number = random_gen();
    fprintf(workload, "%d ", random_number);
  }
  fclose(workload);
}

/* Checks if the file is opened properly */
void check(FILE *pointer){
  if (pointer == NULL) {
    printf("Error opening the file!");
  }
}

/* Gets a random number between PRIME_MIN and PRIME_MAX */
int random_gen(void){
    return (rand() % (PRIME_MAX - PRIME_MIN)) + 20;
}
