#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

// Functions need to be declared before they're called
int contains_string(const char *str, const char *set[], size_t set_size){
  for (size_t i = 0; i < set_size; i++){
    if (strcmp(str, set[i]) == 0){
      return 1;
    }
  }
  return 0;
}

int check_if_file_in_directory(char* directory, char* filename){
  char filepath[1024]; // Buffer for the full path
  snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename); 
  if (access(filepath, F_OK) == 0){ 
    return 1;
  }
  return 0;
  
}
// Compiler will always look for this to determine where to start
int main(){
  //Flush after every printf
  // void setbuf( FILE *stream, char *buffer)
  // sets the internal buffer to use for stream operations
  // If buffer is null it turns off buffering

  char* TYPE_COMMAND = "type";  
  char* EXIT_COMMAND = "exit";
  char* ECHO_COMMAND = "echo";
  char* PWD_COMMAND = "pwd";
  char* CHANGE_DIRECTORY = "cd";

  const char *word_set[] = {TYPE_COMMAND, EXIT_COMMAND, ECHO_COMMAND, PWD_COMMAND, CHANGE_DIRECTORY};
  setbuf(stdout, NULL);
  printf("$ ");

  char input[100];
  //char * fgets(char *string, int length, FILE * stream)
  fgets(input, 100, stdin); 
  input[strlen(input) -1] = '\0'; // \0 is the NULL character, end of a string
  const char delim[] = " ";
  

  char* token = strtok(input, delim); //This only gets the first word, need more 

  char * PATH_LOCATION = getenv("PATH");
  // strtok modifies the original string so need to make a copy first
  char * path_copy = strdup(PATH_LOCATION);
  if(path_copy == NULL){
    perror("strdup"); // Print error
  }
  // PATH contains a bunch of directories : separated so separate them first

  if (PATH_LOCATION == NULL){
    printf("PATH variable not found\n");
  }

  if (strcmp(EXIT_COMMAND, token) == 0){
    return 0;
  }
  else if (strcmp(ECHO_COMMAND, token) == 0){
    token = strtok(NULL, " ");
    char output[100];
    strcpy(output, "");
    while(token != NULL){
      strcat(output, token);
      token = strtok(NULL, " ");
      if(token != NULL ){
        strcat(output, " ");
      }
    }
    printf("%s\n", output);
  }

  else if (strcmp(CHANGE_DIRECTORY, token) == 0){
    char* new_directory = strtok(NULL, " ");
    if (access(new_directory, F_OK) == 0){ 
      setenv("PWD", new_directory,1);
  } else {
    printf("cd: %s: No such file or directory\n", new_directory);
  }

  }

  else if (strcmp(TYPE_COMMAND, token) == 0){
    char * command_to_check = strtok(NULL," ");
    if(command_to_check != NULL){
      bool is_built_in = false;
      bool file_found = false;
      if(contains_string(command_to_check, word_set, sizeof(word_set)/sizeof(word_set[0]))){
        printf("%s is a shell builtin\n", command_to_check);
        is_built_in = true;
      }
      char * path_directory = strtok(path_copy, ":");
      if(!is_built_in){
        while(path_directory != NULL){
          if(check_if_file_in_directory(path_directory,command_to_check)){
            printf("%s is %s/%s\n", command_to_check, path_directory,command_to_check);
            file_found = true;
      }
        path_directory = strtok(NULL, ":");
      }
      if (path_directory == NULL && !file_found){
        printf("%s: not found\n", command_to_check);  
      }
      }
      
  }
    }

  else if (strcmp(PWD_COMMAND, token) == 0){
    char * working_directory = getenv("PWD");
    printf("%s\n",working_directory);
  }

  else{
    if(token != NULL){
      char * second_argument = strtok(NULL," ");

      bool file_found = false;
      char * path_directory = strtok(path_copy, ":");

      while(path_directory != NULL && !file_found){
        if(check_if_file_in_directory(path_directory,token)){
          char full_command[1024]; // Buffer for the full path   
          if(second_argument != NULL){
            snprintf(full_command, sizeof(full_command), "%s %s", token, second_argument); 
          } 
          else{
            snprintf(full_command, sizeof(full_command), "%s", token); 
          }
          system(full_command);
          file_found = true;
      }
        path_directory = strtok(NULL, ":");
      }
      if (path_directory == NULL && !file_found){
        printf("%s: not found\n", token);  
      }
      
  
    }
  }
  main();
  return 0;
}

