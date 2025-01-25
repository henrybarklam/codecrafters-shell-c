#include <stdio.h>
#include <string.h>

// Functions need to be declared before they're called
int contains_string(const char *str, const char *set[], size_t set_size){
  for (size_t i = 0; i < set_size; i++){
    if (strcmp(str, set[i]) == 0){
      return 1;
    }
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

  char *word_set[] = {TYPE_COMMAND, EXIT_COMMAND, ECHO_COMMAND};
  setbuf(stdout, NULL);
  printf("$ ");

  char input[100];
  //char * fgets(char *string, int length, FILE * stream)
  fgets(input, 100, stdin); 
  input[strlen(input) -1] = '\0'; // \0 is the NULL character, end of a string
  const char delim[] = " ";

  char* token = strtok(input, delim); //This only gets the first word, need more 

  // Should probably start separating these things into different functions

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
  else if (strcmp(TYPE_COMMAND, token) == 0){
    token = strtok(NULL," ");
    if(contains_string(token, word_set, sizeof(word_set)/sizeof(word_set[0]))){
      printf("%s is a shell builtin\n", token);
    }
    else{
      printf("%s: not found\n", token);  
    }

  }
  else{
    printf("%s: command not found\n", token);
  }
  main();
  return 0;
}

