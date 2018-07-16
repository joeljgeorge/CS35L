#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
int frobcmp(const void* a, const void* b){

  char* a_1 = *(char**)a; 
  char* b_1 = *(char**)b;

  int i = 0;
  int j = 0;

  int a_1_length = 0;
  int b_1_length = 0;
  for(i; a_1[i] != ' '; i++)
    a_1_length++;
  for(j; b_1[j] != ' '; j++)
    b_1_length++;
  i = 0;
  j = 0;
  //printf("%s\n", a);
  for(i, j; i <=a_1_length && j <=b_1_length; i++, j++)
    {
      if(i > a_1_length)
	return -1;
      else if(j > b_1_length)
	return 1;
      else if((a_1[i]^ 42) < (b_1[j]^42))
	return -1;
      else if((a_1[i]^42) > (b_1[j]^42))
	return 1;
    }

}
int frobcmp_case_insensitive(const void* a, const void* b){
  char* a_1 = *(char**)a;
  char* b_1 = *(char**)b;

  int i = 0;
  int j = 0;

  int a_1_length = 0;
  int b_1_length = 0;
  for(i; a_1[i] != ' '; i++)
    a_1_length++;
  for(j; b_1[j] != ' '; j++)
    b_1_length++;
  i = 0;
  j = 0;
  //printf("%s\n", a);
  for(i, j; i <=a_1_length && j <=b_1_length; i++, j++)
    {
      if(i > a_1_length)
        return -1;
      else if(j > b_1_length)
        return 1;
      else if(toupper((a_1[i] ^ 42)) < toupper((b_1[j]^42)))
        return -1;
      else if(toupper((a_1[i]^42)) > toupper((b_1[j]^42)))
        return 1;
    }

}
 
char** convert_to_two_d(char* c_array, int size, int* word_count_ptr, int* array_size)
{
  char** two_d_array = malloc(10*sizeof(char*));
  int a = 0;
  for(a; a < 10; a++)
    two_d_array[a] = NULL;
  //printf("%d\n", size);
  int j = 0;
  int two_d_size = 10;
  int word_count = 0;
  int word_size;
  int char_count = 0;

  while(char_count < size){
    if(word_count >= two_d_size){
      two_d_size*=2;
      two_d_array = realloc(two_d_array, two_d_size*sizeof(char*));
      if(two_d_array == NULL){
	fprintf(stderr, "Problem reallocating memory.");
	exit(1);
      }
      int a = word_count;
      for(a; a < two_d_size; a++)
	two_d_array[a] = NULL;
    }
    
    word_size = 10;
    int string_size = 0;
    char* new_word = malloc(word_size*sizeof(char));
    //printf("%d\n", char_count);
    while(char_count < size){
      if(c_array[char_count] == ' '){
	//printf("%s", "HEY!");
	char_count++;
	break;
      }
      if(string_size >= word_size){
	word_size*=2;
	new_word = realloc(new_word, word_size*sizeof(char));
	if(new_word == NULL){
	  fprintf(stderr, "Problem with reallocating memory.");
	  exit(1);
	}
      }
      //printf("%d\n", string_size);
      //printf("%d\n", word_size);
      new_word[string_size] = c_array[char_count];
      char_count++;
      string_size++;
    }
    if(string_size == 0)
      free(new_word);
    if(string_size != 0){
    //printf("%d\n", word_count);
    if(string_size+1 >= word_size){
      new_word = realloc(new_word, word_size*sizeof(char)+2);
      if(new_word == NULL){
	fprintf(stderr, "Problem with reallocating memory.");
	exit(1);
      }
    }
    //printf("%d\n", word_count);
    new_word[string_size] = ' ';
    new_word[string_size+1] = '\0';
    two_d_array[word_count] = new_word;
    word_count++;
    }
  } 
  *word_count_ptr = word_count;
  *array_size = two_d_size;
  return two_d_array;
}
int main(int argc, char *argv[]){
  //printf("%d\n", argc);
  if(argc > 2){
    fprintf(stderr, "Too many arguments.");
    exit(1);
  }
  int a = fileno(stdin);
  int case_sorted = 0;
  struct stat buffer;
  if(argc == 2 &&  strcmp(argv[1], "-f") != 0){
    fprintf(stderr, "Incorrect flag");
    exit(1);
  }
  case_sorted = (argc == 2 && strcmp(argv[1], "-f") == 0);
  char* read_file = NULL;
  int file_size = 0;
  int character_count = 0;
  int read_status;

  fstat(a, &buffer);
  file_size = buffer.st_size;
  if(!(S_ISREG(buffer.st_mode)))
    {
      //printf("%s", "NOT REG FILE!");
      file_size = 10;
    }
  read_file = malloc(file_size);
  if(read_file == NULL){
    fprintf(stderr, "Problem allocating memory.");
    exit(1);
  }

  int read_size = file_size;
  do{
    if(!(S_ISREG(buffer.st_mode))){
    read_status = read(STDIN_FILENO, read_file+character_count, 1);
    if(read_status < 0){
      fprintf(stderr, "Problem reading file.");
      exit(1);
    }
    character_count += 1;
    if(character_count >= file_size){
      file_size*=2;
      read_file = realloc(read_file, file_size);
      if(read_file == NULL){
	fprintf(stderr, "Problem reallocating memory.");
	exit(1);
      }
    }
    }
    else{
      //printf("%s\n", "HELLO");
      read_status = read(a, read_file+character_count, read_size);
      character_count+=read_status;
      if(read_status < 0){
      fprintf(stderr, "Problem with reading file.");
       exit(1);
      }
    }
  }while(read_status != 0);
  
  int word_count = 0;
  int arr_size = 0;
  char** array =  convert_to_two_d(read_file, character_count, &word_count, &arr_size);
  //printf("%d\n", word_count);
  if(!case_sorted)
    qsort(array, word_count, sizeof(char*), frobcmp);
  else
    qsort(array, word_count, sizeof(char*), frobcmp_case_insensitive);
 int i = 0;
 int j = 0;

 for(i; array[i] != NULL; i++){
   j = 0;
   for(j; array[i][j] != '\0'; j++){
     char current = array[i][j];
     write(1,&current, 1);
   }
  }
 int x = 0;
 for(x; x < arr_size; x++){
   free(array[x]);
 }
 free(array);
 free(read_file);
 exit(0);
}
