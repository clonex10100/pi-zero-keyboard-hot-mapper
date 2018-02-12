
#include <stdio.h>
#include <string.h>

int set(char s[7][3],char key[], int l);
int rem(char s[7][3], char key[], int l);
void print(char s[7][3]);

int main(void) {
  char keys[7][3];
  for(int i = 0; i < 7; i++){
    strncpy(keys[i], "00", 3);
  }
  print(keys);
  printf("%i\n",set(keys,"45",7));
  print(keys);
  printf("%i\n",set(keys,"55",7));
  print(keys);
  printf("%i\n",rem(keys,"55",7));
  print(keys);
}
int set(char s[7][3],char key[], int l){
  for(int i = 0; i < l; i++){
    if(strcmp(s[i],"00") == 0){
      strncpy(s[i],key,3);
      return 0;
    }
  }
  return -1;
}
int rem(char s[7][3], char key[], int l){
  for(int i = 0; i < l; i++){
    if(strcmp(s[i], key) == 0){
      strncpy(s[i], "00",3);
      return 0;
    }
  }
  return -1;
}

void print(char s[7][3]){
  for(int i = 0; i < 7; i++){
    printf("%s\n",s[i]);
  }
}
