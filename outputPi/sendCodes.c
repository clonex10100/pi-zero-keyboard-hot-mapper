#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[]){
	if(argc != 2){
		printf("Must be one input\n");
		return 1;
	}
	if(strlen(argv[1]) == 1){
		char c = argv[1][0];
		switch(c){
			case 'a':
				printf("x04");
				break;
			case 'b': 
				printf("x05");
				break;
			case 'c': 
				printf("x06");
				break;
			case 'd': 
				printf("x07");
				break;
			case 'e': 
				printf("x08");
				break;
			case 'f': 
				printf("x09");
				break;
			case 'g': 
				printf("x0a");
				break;
			case 'h': 
				printf("x0b");
				break;
			case 'i': 
				printf("x0c");
				break;
			case 'j': 
				printf("x0d");
				break;
			case 'k': 
				printf("x0e");
				break;
			case 'l': 
				printf("x0f");
				break;
			case 'm': 
				printf("x10");
				break;
			case 'n': 
				printf("x11");
				break;
			case 'o': 
				printf("x12");
				break;
			case 'p': 
				printf("x13");
				break;
			case 'q': 
				printf("x14");
				break;
			case 'r': 
				printf("x15");
				break;
			case 's': 
				printf("x16");
				break;
			case 't': 
				printf("x17");
				break;
			case 'u': 
				printf("x18");
				break;
			case 'v': 
				printf("x19");
				break;
			case 'w': 
				printf("x1a");
				break;
			case 'x': 
				printf("x1b");
				break;
			case 'y': 
				printf("x1c");
				break;
			case 'z': 
				printf("x1d");
				break;
		}
	}
	return 0;
}
