#include <stdio.h>
<<<<<<< HEAD
=======
/* 
>>>>>>> load_balancer
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char* argv[]) {
<<<<<<< HEAD
    /* expects at least 1 argument node number*/
    if (argc > 1) {
        /* open file */
        /* part with benchmark?? */
        
        /* while not EOF */
        /* getc to get workload */

        /* sleep 1/benchmark */
    } else {
        printf("not enough program arguments");
    }
}
=======
    expects at least 1 argument node number
    if (argc > 1) {
         open file
        part with benchmark??
        
        while not EOF
        getc to get workload

        sleep 1/benchmark
    } else {
        printf("not enough program arguments");
    }
}
*/
#include <stdlib.h>
#include <time.h>
#include <string.h>

void append_to_string(char *append_to, int number, int current_length);
void wait_for(unsigned int secs);

int main(int argc, char *argv[]){
  int benchmark, node;
  FILE *fp_reader, *fp_writer;
  char ch, file_string_r[] = "workload000.txt", file_string_w[] = "tasks000.txt";

  node      = (argv[1][0] - 48);
  benchmark = (argv[2][0] - 48);
  
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
>>>>>>> load_balancer
