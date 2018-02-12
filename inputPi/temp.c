#include <stdio.h>
#include <string.h>

int set(char* s,char* key, int l);
int rem(char* s, char* key, int l);

int main(void) {
  char keys[7][3];
  for(int i = 0; i < 7; i++){
    strncpy(keys[i], "00", 3);
  }
  
}
int set(char* s[][],char* key, int l){
  for(int i = 0; i < l; i++){
    if(strcmp(s[i],"00") == 1){
      strncpy(s[i],key,3);
      return 0;
    }
  }
  return -1;
}
int rem(char* s, char* key, int l){
  for(int i = 0; i < l; i++){
    if(strcmp(s[i], key) == 1){
      strncpy(s[i], "00",3)
      return 0;
    }
  }
  return -1;
}
