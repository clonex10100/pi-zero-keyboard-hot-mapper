#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

int set(char s[6][5],char key[]);
int rem(char s[6][5], char key[]);
void print(char s[6][5]);
char* cToSend(char c);
int remap(int n);
int modVal(int code);

int main(void) {
        char keys[6][5];
        char out[100];
        int mods = 0;
        for(int i = 0; i < 6; i++){
                strncpy(keys[i], "0", 5);
        }
        struct input_event ev;
        ssize_t n;
        int file = open("/dev/input/event0", O_RDONLY);
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
                                        set(keys,cToSend(remap((int)ev.code)));
                                }
                                else if((int)ev.value == 0){
					rem(keys,cToSend(remap((int)ev.code)));
                                }
                        }
                        if(mods == 0){
                                sprintf(out,"exec echo \\\\0\\\\0\\\\%s\\\\%s\\\\%s\\\\%s\\\\%s\\\\%s > /dev/ttyAMA0",keys[0],keys[1],keys[2],keys[3],keys[4],keys[5]);
                              
                        }
                        else{
                                sprintf(out,"exec echo \\\\0\\\\x%02x\\\\%s\\\\%s\\\\%s\\\\%s\\\\%s\\\\%s > /dev/ttyAMA0",mods,keys[0],keys[1],keys[2],keys[3],keys[4],keys[5]);
                        }
                        system(out);
                        //printf(out());

                }
        }
}
int set(char s[6][5],char key[]){
        for(int i = 0; i < 6; i++){
                if([i][0] == '0'){
			s[i][0] = key[0];
			s[i][1] = key[1];
			s[i][2] = key[2];
			s[i][3] = '\0';
                        return 0;
                }
        }
        return -1;
}
int rem(char s[6][5], char key[]){
        for(int i = 0; i < 6; i++){
                if(strcmp(s[i], key) == 0){
                        s[i][0] = '0';
			s[i][1] = '\0';
                        return 0;
                }
        }
        return -1;
}
void print(char s[6][5]){
        for(int i = 0; i < 6; i++){
                printf("%s\n",s[i]);
        }
}
char* cToSend(char c){
        switch(c){
		case KEY_1:
			return "x1e";
		case KEY_2:
			return "x1f";
		case KEY_3:
			return "x20";
		case KEY_4:
			return "x21";
		case KEY_5:
			return "x22";
		case KEY_6:
			return "x23";
		case KEY_7:
			return "x24";
		case KEY_8:
			return "x25";
		case KEY_9:
			return "x26";
		case KEY_0:
			return "x27";
                case KEY_A:
                        return "x04";
                case KEY_B:
                        return "x05";
                case KEY_C:
                        return "x06";
                case KEY_D:
                        return "x07";
                case KEY_E:
                        return "x08";
                case KEY_F:
                        return "x09";
                case KEY_G:
                        return "x0a";
                case KEY_H:
                        return "x0b";
                case KEY_I:
                        return "x0c";
                case KEY_J:
                        return "x0d";
                case KEY_K:
                        return "x0e";
                case KEY_L:
                        return "x0f";
                case KEY_M:
                        return "x10";
                case KEY_N:
                        return "x11";
                case KEY_O:
                        return "x12";
                case KEY_P:
                        return "x13";
                case KEY_Q:
                        return "x14";
                case KEY_R:
                        return "x15";
                case KEY_S:
                        return "x16";
                case KEY_T:
                        return "x17";
                case KEY_U:
                        return "x18";
                case KEY_V:
                        return "x19";
                case KEY_W:
                        return "x1a";
                case KEY_X:
                        return "x1b";
                case KEY_Y:
                        return "x1c";
                case KEY_Z:
                        return "x1d";
		case KEY_ENTER:
			return "x28";
		case KEY_ESC:
			return "x29";
		case KEY_BACKSPACE:
			return "x2a";
		case KEY_TAB:
			return "x2b";
		case KEY_SPACE:
			return "x2c";
		case KEY_MINUS:
			return "x2d";
		case KEY_EQUAL:
			return "x2e";
		case KEY_LEFTBRACE:
			return "x2f";
		case KEY_RIGHTBRACE:
			return "x30";
		case KEY_BACKSLASH:
			return "x31";
		case KEY_SEMICOLON:
			return "x33";
		case KEY_APOSTROPHE:
			return "x34";
		case KEY_GRAVE:
			return "x35";
		case KEY_COMMA:
			return "x36";
		case KEY_DOT:
			return "x37";
		case KEY_SLASH:
			return "x38";
                default:
                        return "0";
    }
}
int modVal(int){
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
		case KEY_EQUALS:
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

