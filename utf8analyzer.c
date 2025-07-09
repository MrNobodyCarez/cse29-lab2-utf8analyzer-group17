#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }
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

    // implement the UTF-8 analyzer here
}
