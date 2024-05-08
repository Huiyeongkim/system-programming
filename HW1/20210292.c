#include <stdio.h>
#include <malloc.h>
#include "20210292.h"
long filesize = 0;
int main(void) {
        FILE *input = fopen("input.txt", "r");
        if (input==NULL) {
                printf("not file");
                return 0;
        }

        fseek(input, 0, SEEK_END);
        filesize = ftell(input);
	printf("BUFSIZ : %ld\n",filesize);
        rewind(input);

        char *buffer = (char*) malloc(filesize*sizeof(char));
        fgets(buffer, filesize, input);
        printf("input : %s\n",buffer);


     	toSignedChar(buffer);
	toAscii(buffer);
    	toUnsignedChar(buffer);
    	toSignedInt(buffer);
    	toUnsignedInt(buffer);
    	toFloat(buffer);
    	toDouble(buffer);

	free(buffer);
	return 0;
}
long binaryToDecimal(const char*buffer, int i, int b){
	char data[b];
	for (int j = 0; j < b; j++) {
                        data[j] = buffer[i * b + j];
        }
        long a = 0;
	for (int j=0; j<b; j++) {
                a = (a << 1) + (data[j] - '0');
        }
	return a;
}

void toSignedChar(const char* buffer) {
	printf("1. signed char : ");
	for (int i = (filesize-1)/8-1; i >= 0; i--) {
		printf("%d ",(signed char)binaryToDecimal(buffer,i, 8));
	}
	printf("\n");
}
void toAscii(const char* buffer) {
    	printf("2. ASCII codes : ");
	for (int i= (filesize-1)/8-1; i>=0; i--) { 
		int a = binaryToDecimal(buffer, i, 8);
		if (0 <= a && a <= 126) {
        		printf("%c ", a);
     		} 
		else {
            		printf(". ");
		}
	}
	printf("\n");
}

void toUnsignedChar(const char* buffer) {
	printf("3. unsigned char : ");
        for (int i = (filesize-1)/8-1; i >= 0; i--) {
		printf("%lu ", binaryToDecimal(buffer, i, 8));
    	}
    	printf("\n");
}

void toSignedInt(const char* buffer) {
	printf("4. signed int : ");
        for (int i = (filesize-1)/32-1; i >= 0; i--) {
		printf("%d ", (signed int)binaryToDecimal(buffer, i, 32));
	}
	printf("\n");
}

void toUnsignedInt(const char* buffer) {
	printf("5. unsigned int : ");
	for (int i = (filesize-1)/32-1; i >= 0; i--) {
		printf("%lu ", binaryToDecimal(buffer, i, 32));
        }
        printf("\n");
}

void toFloat(const char* buffer) {
	printf("6. float : ");
       	for (int i = (filesize-1)/32-1; i >= 0; i--) {
	       printf("%.4f ",(float)(signed int)binaryToDecimal(buffer, i, 32));
	}
	printf("\n");
}

void toDouble(const char* buffer) {
	printf("7. double : ");
	for (int i = (filesize-1)/64-1; i >= 0; i--) {
                printf("%.4f ",(double)(signed long)binaryToDecimal(buffer, i, 64));
        }
	printf("\n");
}
