#include <stdio.h>

// Compiler will always look for this to determine where to start
int main(){
  //Flush after every printf
  // void setbuf( FILE *stream, char *buffer)
  // sets the internal buffer to use for stream operations
  // If buffer is null it turns off buffering

  setbuf(stdout, NULL);
  printf("$ "); //This is what the terminal will use as its prompt

  //Wait for user input
  char input[100]; //Max len 100 characters
  //Reads limited number of characters from a file stream source into an array
  // of characters
  //char * fgets(char *string, int length, FILE * stream)
  fgets(input, 100, stdin); 
  return 0;
}