#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BIG_ENOUGH 200

void generate_benchmarks(int *benchmarks, int n);
void append_to_string(char *append_to, int number, int current_length);
int seach_string(char *desired, int length, char *fstring, int *pos_point, int look_for);
int not_number(char c);

int main(void){
  int *benchmarks, num_nodes, counter_bench = 0, counter_node = 0, i, ch_this_line, pos_point;
  char string_c[] = "workload000.txt", desired[BIG_ENOUGH], ch, fstring[19];
  FILE *fp_reader, *fp_writer;

  srand(time(NULL));
  
  printf("Hey, how many nodes, would you like to do the work for you? ");
  scanf(" %d", &num_nodes);

  /* Assign memory for benchmarks. */
  benchmarks = malloc(num_nodes * sizeof(int));
  if(benchmarks == NULL){
    printf("Memory not allocated.");
    exit(EXIT_FAILURE);
  }
  generate_benchmarks(benchmarks, num_nodes);
  
  /* Start by opening the FILE from which to read. */
  fp_reader = fopen("workloads.txt", "r");
  fp_writer = fopen("temp.txt", "w");
  if(fp_reader == NULL || fp_writer == NULL){
    printf("Couldn't open one of the files.");
    exit(EXIT_FAILURE);
  }

  for(i = 0; i < num_nodes; i++){
    printf("This is node nr. %2d it has the benchmark %d\n", i + 1, benchmarks[i]);
  }

  ch_this_line = 0;
  while((ch = getc(fp_reader)) != EOF){
    ch_this_line++;
    fprintf(fp_writer, "\\%d %c ", counter_node + 1, ch);
    counter_bench++;
    if(counter_bench == benchmarks[counter_node]){
      counter_bench = 0;
      counter_node = (counter_node + 1) % num_nodes;
    }
    if(ch_this_line > 15){
      ch_this_line = 0;
      fputc('\n', fp_writer);
    }
  }
  
  fclose(fp_reader);
  fclose(fp_writer);

  fp_reader = fopen("temp.txt", "r");
  if(fp_reader == NULL){
    printf("Couldn't open temp.txt");
    exit(EXIT_FAILURE);
  }
  
  for(i = 1; i <= num_nodes; ++i){
    rewind(fp_reader);
    append_to_string(string_c, i, 8);
    fp_writer = fopen(string_c, "w");
    if(fp_writer == NULL){
      printf("Couldn't open %s", string_c);
      exit(EXIT_FAILURE);
    }
    append_to_string(string_c, i, 8);
    while((ch = getc(fp_reader)) != EOF){
      ungetc(ch, fp_reader);
      fgets(desired, BIG_ENOUGH, fp_reader);
      /* printf("%s\n", desired); */
      pos_point = 0;
      while(seach_string(desired, sizeof(desired)/sizeof(char), fstring, &pos_point, i) == 1)
	fprintf(fp_writer, "%s", fstring);
    }
    fclose(fp_writer);
  }

  free(fp_reader);

  if(remove("temp.txt") == 0)
    printf("Deleted 'temp.txt' successfully.");
  else
    printf("Unable to delete 'temp.txt'.");

  free(benchmarks);

  return EXIT_SUCCESS;
}

int seach_string(char *desired, int length, char *fstring, int *pos_point, int look_for){
  int i, j;
  j = 0;
  for(i = *pos_point; i < length; i++){
    if(desired[i] == (char)(look_for + 48)){
      i++;
      while((desired[i] != '\n' && desired[i] != '\\' && not_number(desired[i])) && i < length){
	if(desired[i] == ' ')
	  i++;
	else{
	  fstring[j] = desired[i];
	  j++;
	  i++;
	}
      }
      i--;
      fstring[j] = '\0';
      *pos_point = i;
      return 1;
    }
  }
  
  return 0;
}

int not_number(char c){
  int i;
  for(i = 0; i < 10; i++){
    if(c == (char)(i + 48))
      return 0;
  }
  return 1;
}

void append_to_string(char *append_to, int number, int current_length){
  number = number;
  append_to[current_length]     = (char)(number / 100 + 48);
  append_to[current_length + 1] = (char)(number /  10 + 48);
  append_to[current_length + 2] = (char)(number       + 48);
  
  printf("%s\n", append_to);
}

void generate_benchmarks(int *benchmarks, int n){
  int i;
  for(i = 0; i < n; ++i){
    benchmarks[i] = (rand() % 5) + 1;
  }
}
