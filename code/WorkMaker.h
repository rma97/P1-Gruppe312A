#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRIME_MAX 101
#define PRIME_MIN 20

void check(FILE *pointer);
int random_gen(void);

void generate_workload(void){
  int i, prime, random_number;
  FILE *workload;

  srand(time(NULL));

  printf("bla bla bla?: ");
  scanf(" %d", &prime);

  workload = fopen("workloads.txt", "w");
  check(workload);

  for (i = 0; i <= prime; i++){
    random_number = random_gen();
    fprintf(workload, "%d ", random_number);
  }
  fclose(workload);
}

void check(FILE *pointer){
  if (pointer == NULL) {
    printf("Error opening the file!");
  }
}

int random_gen(void){
    return (rand() % (PRIME_MAX - PRIME_MIN)) + 20;
}