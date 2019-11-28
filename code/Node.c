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
  int benchmark, temp;
  FILE *fp_reader, *fp_writer;
  int file_time_pos;
  char ch;
  time_t start_time = time(NULL);

  temp = 0;

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

  /*Write node number and benchmark to output file */
  fprintf(fp_writer, "Node: %c - Benchmark %s \n",argv[1][0], argv[2]);
  fprintf(fp_writer, "Time: ");

  /* Save file stream position for where run time is located */
  file_time_pos = ftell(fp_writer);
  /* "Allocate" 10 spaces for a number */
  fprintf(fp_writer, "          \n");
  
  /* Calculating the workload */
  while ((ch = getc(fp_reader)) != EOF){
    ungetc(ch, fp_reader);
    /* wait for arbitrary node speed */
    Sleep((int) (((double) 1/benchmark)*TIME_MULTIPLY));
    /* load and find current prime */
    fscanf(fp_reader," %d ",&temp);
    printf("finding prime %d: ",temp);
    temp = find_prime(temp);
    /* output the found prime to output and file */
    printf("%d\n",temp);
    fprintf(fp_writer, "%d ", temp);

    /*
    printf("%c", ch);
    fprintf(fp_writer, "%d ", (int)(ch));
    */
  }
  
  /* set file stream position to where time is written */
  fseek(fp_writer, file_time_pos, SEEK_SET);
  /* write run time to allocated space */
  fprintf(fp_writer, "%-10d\n", (int) difftime(time(NULL),start_time));

  /* Closes the file pointers */
  fclose(fp_reader);
  fclose(fp_writer);  

  return 0;
}

/* converts ascii char which represents a number to integer */
int find_number(char *string, int length_string){
  return (int)(string[0] - ASCII_0);
}

/* returns nth prime */
int find_prime(int n) {
  int i, j;
  int last = 0;
  for (i = 0; i < n; i++) {
    last++;
    while (!is_prime(last)) last++;
  }
  return last;
}

/* checks if number is a prime, returns 1 if it is */ 
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
