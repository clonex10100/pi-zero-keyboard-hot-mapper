#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

int cToSend(int c);
void output(FILE out, int mods, int keys[6]);
void parse(char input[26], int* mods, int keys[]);
	
int main(void){
	//Buffer for serial input
	char input[26];
	
	//Stores currently pressed keys
	int keys[6];
	int mods;
	
	//open keyboard port
	FILE *out = fopen("/dev/hidg0", "wb");
	//Open serial port
	int in = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
	
	//Setup serial
	struct termios options;	
	tcgetattr(in, &options);
	cfmakeraw(&options);
	cfsetspeed(&options, B9600);
	options.c_cflag &= ~CSTOPB;
	options.c_cflag |= CLOCAL;
	options.c_cflag |= CREAD;
	options.c_cc[VMIN] = 26;
	options.c_cc[VTIME] = 0;
	tcsetattr(in,TCSANOW, &options);
	tcflush(in, TCIFLUSH);
	
	while(1){
		printf("read\n");
		printf("%i\n",read(in,input,26));
		printf("%s\n",input);
		
		//Parses input into keys and mods
		parse(input, &mods, keys);

		//Just for printing. Delete for speed
		if(mods == 0){
			printf("\\0\\0\\%s\\%s\\%s\\%s\\%s\\%s",cToSend(keys[0]),cToSend(keys[1]),cToSend(keys[2]),cToSend(keys[3]),cToSend(keys[4]),cToSend(keys[5]));
							                              
		}
		else{
			printf("\\x%02x\\0\\%s\\%s\\%s\\%s\\%s\\%s",mods,cToSend(keys[0]),cToSend(keys[1]),cToSend(keys[2]),cToSend(keys[3]),cToSend(keys[4]),cToSend(keys[5]));
		}
		output(out, mods, keys[]);
	}
	
}
void parse(char input[26], int* mods, int keys[]){
		char buffer[4];
		buffer[3] = '\0'; 
		int bIndex = 0;
		for(int i = 0; i < 25; i++){
			if(input[i] == ':'){
				bIndex = 0;
				if(i == 3){
					//The : at the 3rd postion is right after a mod int
					printf("mod: %i\n",atoi(buffer));
					*mods = atoi(buffer);
				}
				else{
					printf("key: %i\n",atoi(buffer));
					keys[((i-3)/4)] = atoi(buffer);
				}
			}
			else{
				buffer[bIndex] = input[i];
				bIndex++;
			}		
		}
}
//Potentially replace fwrite with write
void output(FILE out, int mods, int keys[6]){
	fwrite(&mods, 1, 1, out);
	fwrite(0, 1, 1, out);
	for(int i = 0; i < 6; i++){
		fwrite(&cToSend(keys[i]), 1, 1, out);
	}
}
int cToSend(int c){
        switch(c){
		case KEY_1:
			return 0x1e;
		case KEY_2:
			return 0x1f;
		case KEY_3:
			return 0x20;
		case KEY_4:
			return 0x21;
		case KEY_5:
			return 0x22;
		case KEY_6:
			return 0x23;
		case KEY_7:
			return 0x24;
		case KEY_8:
			return 0x25;
		case KEY_9:
			return 0x26;
		case KEY_0:
			return 0x27;
                case KEY_A:
                        return 0x04;
                case KEY_B:
                        return 0x05;
                case KEY_C:
                        return 0x06;
                case KEY_D:
                        return 0x07;
                case KEY_E:
                        return 0x08;
                case KEY_F:
                        return 0x09;
                case KEY_G:
                        return 0x0a;
                case KEY_H:
                        return 0x0b;
                case KEY_I:
                        return 0x0c;
                case KEY_J:
                        return 0x0d;
                case KEY_K:
                        return 0x0e;
                case KEY_L:
                        return 0x0f;
                case KEY_M:
                        return 0x10;
                case KEY_N:
                        return 0x11;
                case KEY_O:
                        return 0x12;
                case KEY_P:
                        return 0x13;
                case KEY_Q:
                        return 0x14;
                case KEY_R:
                        return 0x15;
                case KEY_S:
                        return 0x16;
                case KEY_T:
                        return 0x17;
                case KEY_U:
                        return 0x18;
                case KEY_V:
                        return 0x19;
                case KEY_W:
                        return 0x1a;
                case KEY_X:
                        return 0x1b;
                case KEY_Y:
                        return 0x1c;
                case KEY_Z:
                        return 0x1d;
		case KEY_ENTER:
			return 0x28;
		case KEY_ESC:
			return 0x29;
		case KEY_BACKSPACE:
			return 0x2a;
		case KEY_TAB:
			return 0x2b;
		case KEY_SPACE:
			return 0x2c;
		case KEY_MINUS:
			return 0x2d;
		case KEY_EQUAL:
			return 0x2e;
		case KEY_LEFTBRACE:
			return 0x2f;
		case KEY_RIGHTBRACE:
			return 0x30;
		case KEY_BACKSLASH:
			return 0x31;
		case KEY_SEMICOLON:
			return 0x33;
		case KEY_APOSTROPHE:
			return 0x34;
		case KEY_GRAVE:
			return 0x35;
		case KEY_COMMA:
			return 0x36;
		case KEY_DOT:
			return 0x37;
		case KEY_SLASH:
			return 0x38;
                default:
                        return 0;
    }
}
