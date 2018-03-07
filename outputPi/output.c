#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

unsigned char cToSend(int c);
void parse(char input[26], unsigned char keys[]);
	
int main(void){
	//Buffer for serial input
	char input[26];
	
	//Stores currently pressed keys and mods for transmitting
	//Unsigned char is c's byte datatype
	unsigned char sendBytes[8];
	for(int i = 0; i < 8; i++){
		sendBytes[i] = 0;
	}
	
	//open keyboard port
	int out = open("/dev/hidg0", O_RDWR);
	
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
		//Parses input
		parse(input, sendBytes);
		
		//Send the keystrokes to the pc.
		write(out,&sendBytes,8)
	}
	
}
void parse(char input[26], unsigned char output[]){
		//Buffer for holding each number sent by serial
		char buffer[4];
		buffer[3] = '\0'; 
		int bIndex = 0;
	
		for(int i = 0; i < 24; i++){
			if(input[i] == ':'){
				bIndex = 0;
				if(i == 3){
					//The first segment contains the mod value and should NOT go through cToSend()
					printf("mod: %i\n",atoi(buffer));
					output[0] = atoi(buffer);
				}
				else{
					//All other values shoud go into keys[2]-keys[5]
					//Keys [1] is the oem byte and should have nothig in it as of now
					printf("key: %i\n",atoi(buffer));
					output[(i+1)/2] = cToSend(atoi(buffer));
				}
			}
			else{
				buffer[bIndex] = input[i];
				bIndex++;
			}		
		}
}
//Converts int to sendcode byte
unsigned char cToSend(int c){
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
		case KEY_F1:
			return 0x3a;
		case KEY_F2:
			return 0x3b;
		case KEY_F3:
			return 0x3c;
		case KEY_F4:
			return 0x3d;
		case KEY_F5:
			return 0x3e;
		case KEY_F6:
			return 0x3f;
		case KEY_F7:
			return 0x40;
		case KEY_F8:
			return 0x41;
		case KEY_F9:
			return 0x42;
		case KEY_F10:
			return 0x43;
		case KEY_F11:
			return 0x44;
		case KEY_F12:
			return 0x45;
		case KEY_SYSRQ:
			return 0x46;
		case KEY_PAUSE:
			return 0x48;
		case KEY_INSERT:
			return 0x49;
		case KEY_HOME:
			return 0x4a;
		case KEY_PAGEUP:
			return 0x4b;
		case KEY_DELETE:
			return 0x4c;
		case KEY_END:
			return 0x4d;
		case KEY_PAGEDOWN:
			return 0x4e;
		case KEY_RIGHT:
			return 0x4f;
		case KEY_LEFT:
			return 0x50;
		case KEY_DOWN:
			return 0x51;
		case KEY_UP:
			return 0x52;
                default:
                        return 0;
    }
}
