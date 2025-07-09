#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

	int valid_ascii(const char *str) {
		while (*str){
			if ((unsigned char) *str > 127)
				return 0;
			str++;
		}
		return 1;
	}
	int32_t capitalize_ascii(char str[]) {
		int32_t count = 0;
		for (int i = 0; str[i] != '\0'; i++) {
        		if(str[i] >= 'a' && str[i] <= 'z'){
       	        		str[i] = str[i] - ( 'a' - 'A');
        			count++;
        		}
		}
		return count;
	}
	int32_t utf8_strlen(char str[]) {
		int32_t count = 0;
		for(int i = 0; str[i] != '\0'; i++){
        		unsigned char byte = (unsigned char) str[i];
       			if((byte & 0xC0) != 0x80) {
               			count++;
       			}
		}
		return count;
	}
	int main(int argc, char *argv[]) {
    		if (argc != 2) {
       			fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
       		 	return 1;
    		}
	char *input = argv[1];
    	char capitalized[1024];
    	strncpy(capitalized, input, sizeof(capitalized));
    	capitalized[sizeof(capitalized) - 1] = '\0'; // ensure null-terminated

    	printf("Valid ASCII: %s\n", valid_ascii(input) ? "true" : "false");

    	capitalize_ascii(capitalized);
    	printf("Uppercased ASCII: %s\n", capitalized);
    	printf("Length in bytes: %lu\n", strlen(input));
    	printf("Number of code points: %d\n", utf8_strlen(input));

	return 0;
	}


