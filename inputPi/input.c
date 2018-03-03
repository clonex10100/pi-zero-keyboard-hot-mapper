#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

int set(int s[6],int key);
int rem(int s[6], int key);
char* cToSend(char c);
int remap(int n);
int modVal(int code);
void outputPrep(char out[24], int mods, int keys[6]);

int main(void) {
        int keys[6];
        char out[24];
        int mods = 0;
        for(int i = 0; i < 6; i++){
                keys[i] = 0;
        }
        struct input_event ev;
        ssize_t n;
	int size;
        int file = open("/dev/input/event0", O_RDONLY);
	int outF = open("/home/pi/output.txt", O_WRONLY | O_CREAT);
	//uncomment for serial
	//int outF = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
        while(1){
                n = read(file, &ev, sizeof ev);
                if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
                        //printf("%i 0x%04x (%d)\n", (int)ev.value, (int)ev.code, (int)ev.code);
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
                                        set(keys,remap((int)ev.code));
                                }
                                else if((int)ev.value == 0){
					rem(keys,remap((int)ev.code));
                                }
                        }
			outputPrep(out, mods, keys);
                       	write(outF, out, size);
                }
        }
}
void outputPrep(char out[24], int mods, int keys[6]){
	char temp[4];
	int len;
	for(int i = 0; i < 6; i++){
		if(i == 0){
			len = sprintf(temp,"%i",mods);
		}
		else{
			len = sprintf(temp,"%i",keys[i-1]);
		}
		if(len == 1){
			out[i*4] = '0';
			out[i*4+1] = '0';
			out[i*4+2] = temp[0];
		}
		else if(len == 2){
			out[i*4] = '0';
			out[i*4+1] = temp[0];
			out[i*4+2] = temp[1];
		}
		else{
			out[i*4] = temp[0];
			out[i*4+1] = temp[1];
			out[i*4+2] = temp[2];
		}
		if(i + 1 < 6){
			out[i*4+3] = ':';
			out[i*4+4] = '\0';
		}
	}
}

int set(int s[6],int key){
        for(int i = 0; i < 6; i++){
                if(s[i] == 0){
			s[i] = key;
                        return 0;
                }
        }
        return -1;
}
int rem(int s[6], int key){
        for(int i = 0; i < 6; i++){
                if(s[i] == key){
                        s[i] = 0;
                        return 0;
                }
        }
        return -1;
}

int modVal(int code){
        switch(code){
                case KEY_LEFTCTRL:
                        return 1;
                case KEY_LEFTSHIFT:
                        return 2;
                case KEY_LEFTALT:
                        return 4;
                case KEY_LEFTMETA:
                        return 8;
                case KEY_RIGHTCTRL:
                        return 16;
                case KEY_RIGHTSHIFT:
                        return 32;
                case KEY_RIGHTALT:
                        return 64;
                case KEY_RIGHTMETA:
                        return 128;
                default:
                        return 0;
        }
}
int remap(int n){
        switch(n){
		case KEY_MINUS:
			return KEY_LEFTBRACE;
		case KEY_EQUAL:
			return KEY_RIGHTBRACE;
		case KEY_Q:
			return KEY_APOSTROPHE;
		case KEY_W:
			return KEY_COMMA;
		case KEY_E:
			return KEY_DOT;
		case KEY_R:
			return KEY_P;
		case KEY_T:
			return KEY_Y;
		case KEY_Y:
			return KEY_F;
		case KEY_U:
			return KEY_G;
		case KEY_I:
			return KEY_C;
		case KEY_O:
			return KEY_R;
		case KEY_P:
			return KEY_L;
		case KEY_LEFTBRACE:
			return KEY_SLASH;
		case KEY_RIGHTBRACE:
			return KEY_EQUAL;
		case KEY_S:
			return KEY_O;
		case KEY_D:
			return KEY_E;
		case KEY_F:
			return KEY_U;
		case KEY_G:
			return KEY_I;
		case KEY_H:
			return KEY_D;
		case KEY_J:
			return KEY_H;
		case KEY_K:
			return KEY_T;
		case KEY_L:
			return KEY_N;
		case KEY_SEMICOLON:
			return KEY_S;
		case KEY_APOSTROPHE:
			return KEY_MINUS;
		case KEY_Z:
			return KEY_SEMICOLON;
		case KEY_X:
			return KEY_Q;
		case KEY_C:
			return KEY_J;
		case KEY_V:
			return KEY_K;
		case KEY_B:
			return KEY_X;
		case KEY_N:
			return KEY_B;
		case KEY_COMMA:
			return KEY_W;
		case KEY_DOT:
			return KEY_V;
		case KEY_SLASH:
			return KEY_Z;
                default:
                        return n;
        }
}

