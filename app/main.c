#include <stdio.h>
#include <string.h>

// Compiler will always look for this to determine where to start
int main(){
  //Flush after every printf
  // void setbuf( FILE *stream, char *buffer)
  // sets the internal buffer to use for stream operations
  // If buffer is null it turns off buffering

  char* EXIT_COMMAND = "exit";
  setbuf(stdout, NULL);
  printf("$ ");

  char input[100];
  //char * fgets(char *string, int length, FILE * stream)
  fgets(input, 100, stdin); 
  input[strlen(input) -1] = '\0'; // \0 is the NULL character, end of a string
  char* first_command;
  const char delim[] = " ";

  first_command = strtok(input, delim);
  // String parsing here to get arguments
  if (strcmp(EXIT_COMMAND, first_command) == 0){
    return 0;
  }


  printf("%s: command not found\n", first_command);

  

  

  main();
  return 0;
}