#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <windows.h>

#define ASCII_0 48
#define TIME_MULTIPLY 100

void append_to_string(char *append_to, int number, int current_length);
int find_number(char *string, int length_string);
int find_prime(int);
int is_prime(int);

int main(int argc, char *argv[]){
  int benchmark, result;
  FILE *fp_reader, *fp_writer;
  char ch;
  time_t start_time = time(NULL);

  /* Sets benchmark from the argument from Load_balancer.c */
  benchmark = find_number(argv[2], sizeof(argv[2])/sizeof(char));
  
  /* Prints the nodenumber, its parameters and its benchmark */
  printf("This is node: %c it got %d parameters and the benchmark %s\n", argv[1][0], argc, argv[2]);
  
  /* fp_reader opens the file with its workload inside and reads it */
  /* fp_writer creates a file to write its output to */
  fp_reader = fopen(argv[argc - 2], "r");
  fp_writer = fopen(argv[argc - 1], "w");

  /* Checks if fp_reader && fp_writer are opened properly */
  if(fp_reader == NULL || fp_writer == NULL){
    printf("Couldn't open one of the files.");
    exit(EXIT_FAILURE);
  }

  /*Writing node number and benchmark to output file */
  fprintf(fp_writer, "Node: %c - Benchmark %s \n",argv[1][0], argv[2]);
  
  /* Calculating the workload (DOVYDAS) */
  while ((ch = getc(fp_reader)) != EOF){
    Sleep((int) (((double) 1/benchmark)*TIME_MULTIPLY));


    /*
    printf("%c", ch);
    fprintf(fp_writer, "%d ", (int)(ch));
    */
  }
  

  /* Closes the file pointers */
  fclose(fp_reader);
  fclose(fp_writer);  

  return 0;
}

/* converts ascii char which represents a number to integer */
int find_number(char *string, int length_string){
  return (int)(string[0] - ASCII_0);
}

int find_prime(int prime_to_find) {
  int i, j;
  int last = 0;
  for (i = 0; i < prime_to_find; i++) {
    last++;
    while (!is_prime(last)) last++;
  }
  return last;
}

int is_prime(int number) {
  int i, bool;
  bool = 0;
  for (i = number/2; (i > 0) && (number % i != 0); i--);
  if (i == 1) bool = 1;
  return bool;
}

/* replaces charcters in a string with a number, this is usfull in the format 'workload000.txt', where the 000 is replaced with the number. */
void append_to_string(char *append_to, int number, int current_length){
  append_to[current_length]     = (char)((number / 100)                        + ASCII_0);
  append_to[current_length + 1] = (char)((((number % 100) - number % 10) / 10) + ASCII_0);
  append_to[current_length + 2] = (char)((number %  10)                        + ASCII_0);
}
