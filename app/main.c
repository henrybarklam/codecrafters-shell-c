#include <stdio.h>
#include <string.h>

// Compiler will always look for this to determine where to start
int main(){
  //Flush after every printf
  // void setbuf( FILE *stream, char *buffer)
  // sets the internal buffer to use for stream operations
  // If buffer is null it turns off buffering

  char* EXIT_COMMAND = "exit";
  char* ECHO_COMMAND = "echo";
  setbuf(stdout, NULL);
  printf("$ ");

  char input[100];
  //char * fgets(char *string, int length, FILE * stream)
  fgets(input, 100, stdin); 
  input[strlen(input) -1] = '\0'; // \0 is the NULL character, end of a string
  const char delim[] = " ";

  char* token = strtok(input, delim); //This only gets the first word, need more 
  // String parsing here to get arguments

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
  else{
    printf("%s: command not found\n", token);
  }
  main();
  return 0;
}