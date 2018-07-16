#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <unistd.h>

int main(int argc, char* argv[]){
  if(argc != 3){
    fprintf(stderr, "Wrong number of arguments.");
    exit(1);
  }
  if(strlen(argv[1])!=strlen(argv[2])){
    fprintf(stderr, "Arguments are not the same length.");
    exit(1);
  }
  int i = 0;
  int j = 1;
  for(i; i < strlen(argv[1]);i++){
    char a = argv[1][i];
    for(j; j < strlen(argv[2]); j++)
      {
	if(a == argv[1][j]){
	  fprintf(stderr, "Duplicate bytes in from parameter");
	  exit(1);
	}
      }
  }
  char current_char;
  int n = read(STDIN_FILENO, &current_char, 1);
  if(n < 0){
    fprintf(stderr, "There was an error reading your file.");
    exit(1);
  }
  char buffer[strlen(argv[1])];
  while(n != 0){
    if(current_char == argv[1][0]){
      buffer[0] = current_char;
      int i = 1;
      for(i; i < strlen(argv[1]); i++){
	char next_char;
	n = read(STDIN_FILENO, &next_char, 1);
	if(n < 0){
	  fprintf(stderr, "There was an error reading the file.");
	  exit(1);
	}
	if(n == 0){
	  int x = 0;
	  for(x; x < i; x++){
	    char print_char = buffer[j];
            write(1, &print_char, 1);
	  }
	  return;
	}
	buffer[i] = next_char;
	if(next_char != argv[1][i]){
	  //printf("%s\n", "YES");
	  int j = 0;
	  for(j; j < strlen(buffer); j++){
	    char print_char = buffer[j];
	    write(1, &print_char, 1);
	  }
	  n = read(STDIN_FILENO, &current_char, 1);
	  break;
	}
      }
      if(i == (strlen(argv[1]))){
	i = 1;
	int j = 0;
	for(j; j < strlen(argv[1]); j++){
	  char print_char = argv[2][j];
	  write(1, &print_char, 1);
	}
	n = read(STDIN_FILENO, &current_char, 1);
      }
    }
    else{
      write(1, &current_char, 1);
      n = read(STDIN_FILENO, &current_char, 1);
    }
  }
}
