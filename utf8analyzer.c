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
	int32_t codepoint_at(char str[], int32_t byte_index) {
		uint8_t b = (uint8_t)str[byte_index];
		uint8_t b1 = (uint8_t)str[byte_index + 1];
		uint8_t b2 = (uint8_t)str[byte_index + 2];
		uint8_t b3 = (uint8_t)str[byte_index + 3];
		
		//one
		if (b <= 0x7F) {
			return b;
		}

		//two
		if ((b & 0xE0) == 0xC0) {
			if ((b1 & 0xC0) != 0x80) {
				return -1;
			}
			return ((b & 0x1F) << 6) | (b1 & 0x3F);
		}
		//three
		if ((b & 0xF0) == 0xE0) {
			if (((b1 & 0xC0) != 0x80) || ((b2 & 0xC0) != 0x80)) {
				return -1;
			}
			return ((b & 0xF) << 12) || ((b1 & 0x3F) << 6) | (b2 & 0x3F);
		}
		//four
		if ((b & 0xF8) == 0xF0) {
			if ((b1 & 0xC0) != 0x80 || (b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80) {
				return -1;
			}
			return ((b & 0x07) << 18) | ((b1 & 0x3F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
		}
		return -1;
	}
	

