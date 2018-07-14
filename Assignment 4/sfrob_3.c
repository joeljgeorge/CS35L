#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int frobcmp(const void* a, const void* b){

  char* a_1 = *(char**)a; 
  char* b_1 = *(char**)b;

  int i = 0;
  int j = 0;

  for(i, j; i < strlen(a_1) && j < strlen(b_1); i++, j++)
    {
      if(i == strlen(a_1))
	return -1;
      else if(j == strlen(b_1))
	return 1;
      else if((a_1[i] ^ 42) < (b_1[j]^42))
	return -1;
      else if((a_1[i]^42) > (b_1[j]^42))
	return 1;
    }

  return 0;
}
 
int main(){

  char c_character;
  int num_words = 10;
  int char_count = 0;
  int word_count = 0;
  int word_size = 10;
  int array_size = 10;
  char** input_array = malloc(array_size*sizeof(char*));

  while((c_character = getchar())!= EOF)
    {
      int string_size = 0;
      while(c_character!= ' ' && c_character != EOF)
	{
	  
	  if (input_array[word_count] == NULL)
	    {
	      input_array[word_count] = malloc(word_size*sizeof(char));
	      if(input_array[word_count] == NULL){
		fprintf(stderr, "An error occurred while allocating memory.");
		exit(1);
	      }
	      string_size = word_size;
	    }
	  if(char_count >= string_size){
	    char* dyn_ptr = realloc(input_array[word_count], 2*string_size*sizeof(char));
	    if(dyn_ptr == NULL){
	      fprintf(stderr, "An error occurred while reallocating memory.");
	      exit(1);
	    }
	    input_array[word_count] = dyn_ptr;
	    dyn_ptr = NULL;
	    string_size*=2;
	  }
	  input_array[word_count][char_count] = c_character;
	  c_character = getchar();
	  char_count++;
	}
      if(char_count+1 >= string_size){
      char* dyn_ptr = realloc(input_array[word_count], 2*string_size*sizeof(char));
      if(dyn_ptr == NULL){
	fprintf(stderr, "An error occurred while reallocating memory.");
	exit(1);
      }
      input_array[word_count] = dyn_ptr;
      dyn_ptr = NULL;
      }
      input_array[word_count][char_count + 1] = '\0';
      word_count++;
      char_count = 0;
      if(word_count >= array_size){
	array_size*=2; 
        char** dyn_ptr= realloc(input_array, array_size*sizeof(char*));
	if(dyn_ptr == NULL){
	  fprintf(stderr, "An error occurred while reallocating memory.");
	  exit(1);
	}
	input_array = dyn_ptr;
	dyn_ptr = NULL;
      }
      if(feof(stdin))
	{
          break;
	}
    }
  if(ferror(stdin)){
    fprintf(stderr, "An error occurred while reading the file");
    exit(1);
  }
  if(word_count+1 >= array_size){
    input_array = realloc(input_array, 1+array_size*sizeof(char*));
    array_size+=1;
  }
  input_array[word_count+1] = NULL;
  qsort(input_array, word_count, sizeof(char*), frobcmp);

  int x = 0;
  int y = 0;
  for(x; input_array[x] != NULL; x++){
    y=0;
    for(y; input_array[x][y] != '\0'; y++){
      putchar(input_array[x][y]);
      if(ferror(stdout)){
	fprintf(stderr, "An error occurred while outputting the sorted frobnicated text.");
	exit(1);
      }
    }
    putchar(' ');
    if(ferror(stdout)){
      fprintf(stderr, "An error occurred while outputting the sorted frobnicated text.");
      exit(1);
    }
  }
  x = 0;
  for(x; x < array_size; x++){
    free(input_array[x]);
  }
  free(input_array);
  exit(0);
}
