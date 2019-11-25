#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void append_to_string(char *append_to, int number, int current_length);
void wait_for(unsigned int secs);
int find_number(char *string, int length_string);

int main(int argc, char *argv[]){
  int benchmark, node;
  FILE *fp_reader, *fp_writer;
  char ch, file_string_r[] = "workload000.txt", file_string_w[] = "tasks000.txt";

  node      = (argv[1][0] - 48);
  benchmark = find_number(argv[2], sizeof(argv[2])/sizeof(char);
  
  printf("This is node: %c it got %d parameters and the benchmark %s\n", argv[1][0], argc, argv[2]);
  
  append_to_string(file_string_r, node, 8);
  append_to_string(file_string_w, node, 5);
  fp_reader = fopen(file_string_r, "r");
  fp_writer = fopen(file_string_w, "w");
  if(fp_reader == NULL || fp_writer == NULL){
    printf("Couldn't open one of the files.");
    exit(EXIT_FAILURE);
  }

  while((ch = getc(fp_reader)) != EOF){
    wait_for((10 / benchmark));
    printf("%c", ch);
    fprintf(fp_writer, "%d ", (int)(ch));
  }

  fclose(fp_reader);
  fclose(fp_writer);  

  return 0;
}

int find_number(char *string, int length_string){
  int i, num = 0;
  for(i = 0; i < length_string; i++){
    num += string[i] * pow(10, (length_string - i - 2));
  }
  return num;
}

/* from stackoverflow */
void wait_for(unsigned int secs) {
  unsigned int retTime = time(0) + secs;
  while (time(0) < retTime);
}

void append_to_string(char *append_to, int number, int current_length){
  /*  printf("This is the number %d\n", number);*/
  number = number;
  append_to[current_length]     = (char)(number / 100 + 48);
  append_to[current_length + 1] = (char)(number /  10 + 48);
  append_to[current_length + 2] = (char)(number       + 48);
  
  /*  printf("%s\n", append_to); */
}
