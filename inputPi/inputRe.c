#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

int set(char s[7][5],char key[]);
int rem(char s[7][5], char key[]);
void print(char s[7][5]);
char* cToSend(char c);
char inToC(int n);

int main(void) {
  char keys[7][5];
  char code[5];
  for(int i = 0; i < 7; i++){
    strncpy(keys[i], "00", 5);
  }
  struct input_event ev;
  ssize_t n;
  int file = open("/dev/input/event0", O_RDONLY);
  while(1){
      n = read(file, &ev, sizeof ev);
      if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
        printf("%i 0x%04x (%d)\n", (int)ev.value, (int)ev.code, (int)ev.code);
	//if it's a mod key do somthing else
	if(0){
	
	}
	else{
	    if(ev.value == 1){
	        //sprintf(code,"%x",(int)ev.code);
		set(keys,cToSend(inToC((int)ev.code)));
        	}
	    else if(ev.value == 0){
			//sprintf(code, "%x",(int)ev.code);
			rem(keys,cToSend(inToC((int)ev.code)));
		}
	}
	print(keys);
	//output
      }
    }
}

int set(char s[7][5],char key[]){
  for(int i = 0; i < 7; i++){
    if(strcmp(s[i],"00") == 0){
      strncpy(s[i],key,5);
      return 0;
    }
  }
  return -1;
}
int rem(char s[7][5], char key[]){
  for(int i = 0; i < 7; i++){
    if(strcmp(s[i], key) == 0){
      strncpy(s[i], "00",3);
      return 0;
    }
  }
  return -1;
}

void print(char s[7][5]){
  for(int i = 0; i < 7; i++){
    printf("%s\n",s[i]);
  }
}

char* cToSend(char c)
{
  switch(c){
    case 'a':
      return "x04";
      break;
    case 'b':
      return "x05";
      break;
    case 'c':
      return "x06";
      break;
    case 'd':
      return "x07";
      break;
    case 'e':
      return "x08";
      break;
    case 'f':
      return "x09";
      break;
    case 'g':
      return "x0a";
      break;
    case 'h':
      return "x0b";
      break;
    case 'i':
      return "x0c";
      break;
    case 'j':
      return "x0d";
      break;
    case 'k':
      return "x0e";
      break;
    case 'l':
      return "x0f";
      break;
    case 'm':
      return "x10";
      break;
    case 'n':
      return "x11";
      break;
    case 'o':
      return "x12";
      break;
    case 'p':
      return "x13";
      break;
    case 'q':
      return "x14";
      break;
    case 'r':
      return "x15";
      break;
    case 's':
      return "x16";
      break;
    case 't':
      return "x17";
      break;
    case 'u':
      return "x18";
      break;
    case 'v':
      return "x19";
      break;
    case 'w':
      return "x1a";
      break;
    case 'x':
      return "x1b";
      break;
    case 'y':
      return "x1c";
      break;
    case 'z':
      return "x1d";
      break;
    }
}
char inToC(int n){
    switch(n)
    {
      case 16:
        return 'q';
        break;
      case 17:
        return 'w';
        break;
      case 18:
        return 'e';
        break;
      case 19:
        return 'r';
        break;
      case 20:
        return 't';
        break;
      case 30:
        return 'y';
        break;
    }
    return 't';
}

