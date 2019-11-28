#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRIME_MAX 100
#define PRIME_MIN 20

void check(FILE *pointer);
int random_gen(void);

void generate_workload(void){
  int i, prime, random_number;
  FILE *workload;

  /* Seeds the rand() with time */
  srand(time(NULL));

  printf("How many primes do you want to generate?: ");
  scanf(" %d", &prime);

  workload = fopen("workloads.txt", "w");
  check(workload);

  for (i = 0; i <= prime; i++){
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
