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
				printf("a\n");
				break;
			case 'b': 
				printf("b\n");
				break;
			default:
				printf("fail\n");
		}
	}
	return 0;
}
