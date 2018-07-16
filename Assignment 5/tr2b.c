#include <stdio.h>
#include <string.h>
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
  char current_char = getchar();
  char buffer[strlen(argv[1])];
  while(!feof(stdin)){
    if(current_char == argv[1][0]){
      buffer[0] = current_char;
      int i = 1;
      for(i; i < strlen(argv[1]); i++){
	char next_char = getchar();
	if(feof(stdin)){
	  int x = 0;
	  for(x; x < i; x++)
	    putchar(buffer[x]);
	  return;
	}
	buffer[i] = next_char;
	if(next_char != argv[1][i]){
	  //printf("%s\n", "YES");
	  int j = 0;
	  for(j; j < strlen(buffer); j++)
	    putchar(buffer[j]);
	  current_char = getchar();
	  break;
	}
      }
      if(i == (strlen(argv[1]))){
	i = 1;
	int j = 0;
	for(j; j < strlen(argv[1]); j++){
	  putchar(argv[2][j]);
	}
	current_char = getchar();
      }
    }
    else{
      putchar(current_char);
      current_char = getchar();
    }
  }
}
