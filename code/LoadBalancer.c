#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "WorkMaker.h"

#define BIG_ENOUGH 1000
#define ASCII_A 48
#define CH_PER_LINE_IN_TEMP 30

void generate_benchmarks(int *benchmarks, int n);
void change_template(char *append_to, int number);
int search_string(char *desired, int length, char *fstring, int *pos_point, int look_for);
int not_number(char c);
void restart_string(char *string, int n);
void set_number_to_string(int number, char *string);
void weighted_round_robin(FILE *fp_reader, FILE *fp_writer, int *benchmarks, int num_nodes);
void round_robin(FILE *fp_reader, FILE *fp_writer, int num_nodes);
void extract_info_from_temp_to_node_file(int num_nodes);
void start_the_nodes(int num_nodes, int *benchmarks);

int main(void){
  int *benchmarks, num_nodes, i, virgin = 1, this_should_be_deleted_when_im_done_bet_whishes_from_the_one_and_only_Karl = 1;
  char users_choice[50], simulate_again, new_data, new_nodes;
  FILE *fp_reader, *fp_writer, *fp_non;
  
  srand(time(NULL));
  
  do{
    if(!virgin){
      printf("Do you want to change your nodes from the last time?(If you say yes(Y) you will get new benchmarks.)\n[Y/N] - ");
      scanf(" %c", &new_nodes);
    }
    if(virgin == 1 || new_nodes == 'Y' || new_nodes == 'y'){
      /* frees the space which is located in the heap. */
      if(!virgin)
        free(benchmarks);
      
      /* Prompts for number of nodes and writes it to number_of_nodes.txt */
      printf("How many nodes, would you like to do the work for you? ");
      scanf(" %d", &num_nodes);

      /* Assign memory for benchmarks. */
      benchmarks = malloc(num_nodes * sizeof(int));
      if(benchmarks == NULL){
        printf("Memory not allocated.");
        exit(EXIT_FAILURE);
      }

      /* Generates a random benchmark weight between 1-5 */
      generate_benchmarks(benchmarks, num_nodes);
      fp_non = fopen("number_of_nodes.txt", "w");
      fprintf(fp_non, "%d\n", num_nodes);
      for(i = 0; i < num_nodes; i++){
        fprintf(fp_non, "%d ", benchmarks[i]);
      }
      fclose(fp_non);
    }

    if(!virgin || this_should_be_deleted_when_im_done_bet_whishes_from_the_one_and_only_Karl){
      printf("Do you want a new workload from the last time?\n[Y/N] - ");
      scanf(" %c", &new_data);
    }
    /* Generates the workload. Look at WorkMaker.c file to see how it works */
    if(/*virgin == 1 || */(new_data == 'y' || new_data == 'Y'))
      generate_workload();

    /* fp_reader opens workloads.txt to read the workload from. */
    /* fp_writer opens tempt.txt to write the distributed workload to */
    fp_reader = fopen("workloads.txt", "r");
    fp_writer = fopen("temp.txt", "w");

    /* Checks if the file pointers are opnened properly */
    if(fp_reader == NULL || fp_writer == NULL){
      printf("Couldn't open one of the files.");
      exit(EXIT_FAILURE);
    }

    /* This just tells the user the specification on each node. */
    for(i = 0; i < num_nodes; i++){
      printf("This is node nr. %2d it has the benchmark %d\n", i + 1, benchmarks[i]);
    }

    while(1 == 1){
      printf("Which algorithm would you like to use? \nThe opstions is Weighted Round Robin(input 'wrr') or Round Robin(input 'rr') > ");
      scanf(" %s", users_choice);
      if(strcmp(users_choice, "wrr") == 0){
	weighted_round_robin(fp_reader, fp_writer, benchmarks, num_nodes);
	break;
      } else if(strcmp(users_choice, "rr") == 0){
	round_robin(fp_reader, fp_writer, num_nodes);
	break;
      }
    }

    /* closes the 2 files. */
    fclose(fp_reader);
    fclose(fp_writer);

    extract_info_from_temp_to_node_file(num_nodes);

    /* Start the nodes, such that they get their number and benchmark with in the arguments. */
    start_the_nodes(num_nodes, benchmarks);

    printf("Do you want to do another simulation, be warned this will reset your workload files?\n[Y/N] - ");
    scanf(" %c", &simulate_again);
    virgin = 0;
  }while(simulate_again == 'y' || simulate_again == 'Y');
  
  return EXIT_SUCCESS;
}

void start_the_nodes(int num_nodes, int *benchmarks){
  char tasks_template[] = "tasks000.txt", workload_template[] = "workload000.txt", command_for_system[50];
  int i;
  
  for(i = 1; i <= num_nodes; i++){
    change_template(tasks_template, i);
    change_template(workload_template, i);
    snprintf(command_for_system, 50, "START node.exe %d %d %s %s", i, benchmarks[i - 1], workload_template, tasks_template);
    system(command_for_system);
  }
}

void extract_info_from_temp_to_node_file(int num_nodes){
  FILE *fp_reader, *fp_writer;
  char ch, one_line_from_temp[BIG_ENOUGH], workload_template[] = "workload000.txt", one_work_load[BIG_ENOUGH], node_as_string[20];
  int i, pos_pointer, ch_per_file;
  
  /* opens 'temp.txt' in read mode. */
  fp_reader = fopen("temp.txt", "r");
  if(fp_reader == NULL){
    printf("Couldn't open temp.txt");
    exit(EXIT_FAILURE);
  }

  /* Runs once for each node. */
  for(i = 1; i <= num_nodes; ++i){
    /* Sets fp_reader to be in the beginning of the file. */
    rewind(fp_reader);
    /* Sets the num for character per file, to 0. mostly for debugging. */
    ch_per_file = 0;
    /* appends a number to the text file with the format 'workload[node nr.].txt'. */
    change_template(workload_template, i);
    /* opens the file workload[node nr.]. */
    fp_writer = fopen(workload_template, "w");
    rewind(fp_writer);
    /* Checks the file as indead been opened. */
    if(fp_writer == NULL){
      printf("Couldn't open %s", workload_template);
      exit(EXIT_FAILURE);
    }
    /* goes along while it hasn't reached the end of the file */
    while((ch = getc(fp_reader)) != EOF){
      ungetc(ch, fp_reader);
      /* set the string to only '\0's. */
      restart_string(one_line_from_temp, sizeof(one_line_from_temp)/sizeof(char));
      restart_string(one_work_load, sizeof(one_work_load)/sizeof(char));
      /* Skal forklares */
      fgets(one_line_from_temp, BIG_ENOUGH, fp_reader);
      pos_pointer = 0;
      /* converts a number into a string. With standard Math formating */
      set_number_to_string(i, node_as_string);
      while(search_string(one_line_from_temp, sizeof(one_line_from_temp)/sizeof(char), one_work_load, &pos_pointer, i)){
        fprintf(fp_writer, "%s ", one_work_load);
        ch_per_file++;
      }
    }
    /* closes the file, which we are writing in, in the format 'workload[node nr.].txt'. */
    fclose(fp_writer);
  }

  /* Closes the reading file, 'temp.txt'. */
  fclose(fp_reader);
}

void round_robin(FILE *fp_reader, FILE *fp_writer, int num_nodes){
  int ch_this_line = 0, counter_node = 0, i, virgin = 0;
  char ch, string_from_file[BIG_ENOUGH];
  
  while((ch = getc(fp_reader)) != EOF){
    ungetc(ch, fp_reader);
    restart_string(string_from_file, sizeof(string_from_file)/sizeof(char));
    fgets(string_from_file, BIG_ENOUGH, fp_reader);

    i = 0;
    while(string_from_file[i] != '\0'){
      if(string_from_file[i] != ' ' && string_from_file[i] != '\0' && string_from_file[i] != '\n'){
        fprintf(fp_writer, "\\%d ", counter_node + 1);
	virgin = 1;
      }
      while(string_from_file[i] != ' ' && string_from_file[i] != '\0' && string_from_file[i] != '\n'){
	fprintf(fp_writer, "%c", string_from_file[i]);
        ch_this_line++;
        /* makes it such that when a specific node has recived as many tasks as its bencmark it goes to the next node. */
	i++;
      }
      if(virgin == 1){
        counter_node = (counter_node + 1) % num_nodes;
	virgin = 0;
      }
      if(string_from_file[i] == ' ')
	fprintf(fp_writer, " ");
      i++;
      /* Makes sure the number of characters per line doesn't exceed 15. */
      if(ch_this_line > CH_PER_LINE_IN_TEMP){
        ch_this_line = 0;
        fputc('\n', fp_writer);
      }
    }
  }
}

void weighted_round_robin(FILE *fp_reader, FILE *fp_writer, int *benchmarks, int num_nodes){
  /* This prints to the file temp, with standard '\[node nr.] [character]' and making sure the charcters per line doesn't exceed 15. */
  int ch_this_line = 0, counter_bench = 0, counter_node = 0, i; 
  char ch, string_from_file[BIG_ENOUGH];
  while((ch = getc(fp_reader)) != EOF){
    ungetc(ch, fp_reader);
    restart_string(string_from_file, sizeof(string_from_file)/sizeof(char));
    fgets(string_from_file, BIG_ENOUGH, fp_reader);

    i = 0;
    while(string_from_file[i] != '\0'){
      if(string_from_file[i] != ' ' && string_from_file[i] != '\0' && string_from_file[i] != '\n')
        fprintf(fp_writer, "\\%d ", counter_node + 1);
      while(string_from_file[i] != ' ' && string_from_file[i] != '\0' && string_from_file[i] != '\n'){
	fprintf(fp_writer, "%c", string_from_file[i]);
        ch_this_line++;
        /* makes it such that when a specific node has recived as many tasks as its bencmark it goes to the next node. */
	i++;
      }
      counter_bench++;
      if(counter_bench >= benchmarks[counter_node]){
        counter_bench = 0;
        counter_node = (counter_node + 1) % num_nodes;
      }
      if(string_from_file[i] == ' ')
	fprintf(fp_writer, " ");
      i++;
      /* Makes sure the number of characters per line doesn't exceed 15. */
      if(ch_this_line > CH_PER_LINE_IN_TEMP){
        ch_this_line = 0;
        fputc('\n', fp_writer);
      }
    }
  }
}

/* Looks for a specific number in a string. */
int search_string(char *desired, int length, char *fstring, int *pos_point, int look_for){
  int i, j;
  char temp1[20], temp2[20];
  /* Set a whole string to '\0'. */
  restart_string(fstring, 20);
  /* Checks if the file_pointer points to the end of the file */
  if(*pos_point > length)
      return 0;

  /* Forklar string-magien her */
  for(i = *pos_point; i < length; i++){
    if(desired[i] == '\\'){
      restart_string(temp1, 20);
      j = 0;
      i++;

      while(desired[i] != ' '){
	    temp1[j++] = desired[i++];
      }
      set_number_to_string(look_for, temp2);
      if(strcmp(temp1, temp2) == 0){
	j = 0;

        while(desired[i] == ' ')
	  i++;
	
	while(desired[i] != ' ')
          fstring[j++] = desired[i++];
	
	*pos_point = ++i;
        return 1;
      }
    }
  }
  return 0;
}


/* Set a whole string to '\0'. */
void restart_string(char *string, int n){
  int i;
  for(i = 0; i < n; i++){
    string[i] = '\0';
  }
}

/* Checks that the charcter isn't a number. */
int not_number(char c){
  int i;
  for(i = 0; i < 10; i++){
    if(c == (char)(i + ASCII_A))
      return 0;
  }
  return 1;
}

/* replaces charcters in a string with a number, this is usfull in the format 'workload000.txt', where the 000 is replaced with the number. */
void change_template(char *template, int number){
  int i = 0, infinite_loop_break = 1000;
  while(template[i] != '0'){
    if(i >= infinite_loop_break){
      printf("Wrong use of the function change_template.");
      exit(EXIT_FAILURE);
    }
    i++;
  }
  template[i]     = (char)((number / 100)                        + ASCII_A);
  template[i + 1] = (char)((((number % 100) - number % 10) / 10) + ASCII_A);
  template[i + 2] = (char)(number %  10                          + ASCII_A);
}

/* This function changes a 3 decimales int to a string, with so weird math. */
void set_number_to_string(int number, char *string){
  int j = 0;
  /* The first if statemant checks if there is a value in the a hundred place. */
  if(number / 100 != 0)
    string[j++] = (char)(number / 100 + ASCII_A);
  
  /* This both check if there is a value greater than 0 in the 10th place, and if there hsa been an 100th. */
  if(((number / 10 - (number / 100) * 10)  != 0) && number / 100 == 0)
    string[j++] = (char)(number /  10 + ASCII_A);
  else if(((number / 10 - (number / 100) * 10) == 0) && (number / 100 != 0))
    string[j++] = (char)(ASCII_A);
  
  /* The last else statement could be left out, but it given a closer look into whats happening. 
   * Which is, that the number on the 1th place i printed no matter what. */
  if((number - number / 10) != 0)
    string[j++] = (char)(number % 10 + ASCII_A);
  else
    string[j++] = (char)(ASCII_A);
  string[j] = '\0';
}

/* This spits out random numbers between 1 and 5. */
void generate_benchmarks(int *benchmarks, int n){
  int i;
  for(i = 0; i < n; ++i){
    benchmarks[i] = (rand() % 5) + 1;
  }
}
