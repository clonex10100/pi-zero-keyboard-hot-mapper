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
        char code[5];
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
(int)ev.code);
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
                                        set(keys,cToSend(remap((int)ev.code)));
                                }
                                else if((int)ev.value == 0){
                                        //sprintf(code, "%x",(int)ev.code);
                                        set(keys,cToSend(remap((int)ev.code)));
                                }
                                else if((int)ev.value == 0){
                                        //sprintf(code, "%x",(int)ev.code);
                                        rem(keys,cToSend(remap((int)ev.code)));
                                }
                        }
                        if(mods == 0){
ys[5]);
/dev/ttyAMA0",keys[0],keys[1],keys[2],keys[3],keys[4],keys[5]);
                        }
                        else{
eys[4],keys[5]);
s > /dev/ttyAMA0",mods,keys[0],keys[1],keys[2],keys[3],keys[4],keys[5]);
                        }
                        system(out);
                        //printf("\\0");
                        //for(int i = 0; i < 6; i++){
                                //printf("\\%s",keys[i]);
                        //}
                        //printf("\n");
                        //output
                }
        }
}
int set(char s[6][5],char key[]){
        for(int i = 0; i < 6; i++){
                if(strcmp(s[i],"0") == 0){
                        strncpy(s[i],key,5);
                        return 0;
                }
        }
        return -1;
}
int rem(char s[6][5], char key[]){
        for(int i = 0; i < 6; i++){
                if(strcmp(s[i], key) == 0){
                        strncpy(s[i], "0",3);
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
                default:
                        return "0";
    }
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
                default:
                        return n;
        }
}
