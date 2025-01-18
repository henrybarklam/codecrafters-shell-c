#include <stdio.h>
#include <string.h>

// Compiler will always look for this to determine where to start
int main(){
  //Flush after every printf
  // void setbuf( FILE *stream, char *buffer)
  // sets the internal buffer to use for stream operations
  // If buffer is null it turns off buffering

  setbuf(stdout, NULL);
  printf("$ ");

  //Wait for user input
  char input[100];
  //char * fgets(char *string, int length, FILE * stream)
  fgets(input, 100, stdin); 
  input[strlen(input) -1] = '\0'; // \0 is the NULL character, end of a string
  printf("%s: command not found\n", input); // Breaks for all rn
  char* s1 = "exit";
  if (strcmp(s1, input) == 0){
    return 0;
  }
  main();
  return 0;
}