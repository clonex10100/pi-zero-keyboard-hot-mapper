#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

char* cToSend(int c);

int main(void){
	char input[26];
	char out[100];

	int keys[6];
	int mods;
	
	char buffer[4];
	buffer[3] = '\0'; 
	int bIndex;

	int in = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
	struct termios options;	
	printf("%i\n",tcgetattr(in, &options));
	cfmakeraw(&options);
	cfsetspeed(&options, B9600);
	options.c_cflag &= ~CSTOPB;
	options.c_cflag |= CLOCAL;
	options.c_cflag |= CREAD;
	options.c_cc[VMIN] = 26;
	options.c_cc[VTIME] = 0;
	printf("%i\n",tcsetattr(in,TCSANOW, &options));
	tcflush(in, TCIFLUSH);
	while(1){
		printf("read\n");
		printf("%i\n",read(in,input,26));
		printf("%s\n",input);
		bIndex = 0;
		for(int i = 0; i < 25; i++){
			//printf("%c\n",input[i]);
			if(input[i] == ':'){
				bIndex = 0;
				if(i == 3){
					printf("mod: %i\n",atoi(buffer));
					mods = atoi(buffer);
				}
				else{
					printf("key: %i\n",atoi(buffer));
					keys[((i+1)/4)-2] = atoi(buffer);
				}
			}
			else{
				buffer[bIndex] = input[i];
				bIndex++;
			}		
		}
		if(mods == 0){
			sprintf(out,"exec echo -ne \\\\0\\\\0\\\\%s\\\\%s\\\\%s\\\\%s\\\\%s\\\\%s > /dev/hidg0",cToSend(keys[0]),cToSend(keys[1]),cToSend(keys[2]),cToSend(keys[3]),cToSend(keys[4]),cToSend(keys[5]));
							                              
		}
		else{
			sprintf(out,"exec echo -ne \\\\x%02x\\\\0\\\\%s\\\\%s\\\\%s\\\\%s\\\\%s\\\\%s > /dev/hidg0",mods,cToSend(keys[0]),cToSend(keys[1]),cToSend(keys[2]),cToSend(keys[3]),cToSend(keys[4]),cToSend(keys[5]));
		}
		printf("%s\n",out);
		system(out);
	}
	
}

char* cToSend(int c){
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