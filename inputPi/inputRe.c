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
char remap(char c);
int modVal(int code);

int main(void) {
	char keys[7][5];
	char code[5];
	int mods = 0;
	for(int i = 0; i < 7; i++){
		strncpy(keys[i], "0", 5);
	}
	struct input_event ev;
	ssize_t n;
	int file = open("/dev/input/event0", O_RDONLY);
	while(1){
		n = read(file, &ev, sizeof ev);
		if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
			printf("%i 0x%04x (%d)\n", (int)ev.value, (int)ev.code, (int)ev.code);
			//if it's a mod key do somthing else
			if(modVal((int)ev.code) != 0){
				if((int)ev.value == 1){
					mods += modVal((int)ev.code);
				}
				else if((int)ev.value == 0){
					mods -= modVal((int)ev.code);
				}
			}
			else{
				if((int)ev.value == 1){
					//sprintf(code,"%x",(int)ev.code);
					set(keys,inToC((int)ev.code));
				}
				else if((int)ev.value == 0){
					//sprintf(code, "%x",(int)ev.code);
					rem(keys,inToC((int)ev.code));
				}
			}
			if(mods == 0){
				printf("\\0");
			}
			else{
				printf("\\x%02x",mods);
			}
			for(int i = 0; i < 7; i++){
				printf("\\%s",keys[i]);
			}
			printf("\n");
			//print(keys);
			//output
		}
	}
}
int set(char s[7][5],char key[]){
	for(int i = 0; i < 7; i++){
		if(strcmp(s[i],"0") == 0){
			strncpy(s[i],key,5);
			return 0;
		}
	}
	return -1;
}
int rem(char s[7][5], char key[]){
	for(int i = 0; i < 7; i++){
		if(strcmp(s[i], key) == 0){
			strncpy(s[i], "0",3);
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
char* cToSend(char c){
	switch(c){
		case KEY_A:
			return "x04";
			break;
		case KEY_B:
			return "x05";
			break;
		case KEY_C:
			return "x06";
			break;
		case KEY_D:
			return "x07";
			break;
		case KEY_E:
			return "x08";
			break;
		case KEY_F:
			return "x09";
			break;
		case KEY_G:
			return "x0a";
			break;
		case KEY_H:
			return "x0b";
			break;
		case KEY_I:
			return "x0c";
			break;
		case KEY_J:
			return "x0d";
			break;
		case KEY_K:
			return "x0e";
			break;
		case KEY_L:
			return "x0f";
			break;
		case KEY_M:
			return "x10";
			break;
		case KEY_N:
			return "x11";
			break;
		case KEY_O:
			return "x12";
			break;
		case KEY_P:
			return "x13";
			break;
		case KEY_Q:
			return "x14";
			break;
		case KEY_R:
			return "x15";
			break;
		case KEY_S:
			return "x16";
			break;
		case KEY_T:
			return "x17";
			break;
		case KEY_U:
			return "x18";
			break;
		case KEY_V:
			return "x19";
			break;
		case KEY_W:
			return "x1a";
			break;
		case KEY_X:
			return "x1b";
			break;
		case KEY_Y:
			return "x1c";
			break;
		case KEY_Z:
			return "x1d";
			break;
    }
}
int modVal(int code){
	switch(code){
		case 29:
			return 1;
			break;
		case 42:
			return 2;
			break;
		case 56:
			return 4;
			break;
		case 97:
			return 16;
			break;
		case 54:
			return 32;
			break;
		case 100:
			return 64;
			break;
		default:
			return 0;
			break;
	}
}
char remap(char c){
	switch(c){
		default:
			return c;
			break;
	}
}
