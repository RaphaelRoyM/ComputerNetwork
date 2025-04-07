#include <stdio.h>
#include <ctype.h>  // Include for toupper() and tolower() functions

int main() {
    char str[100];
    printf("Enter the string:\n");
    scanf("%s", str);
    for(int i = 0; str[i] != '\0'; i++) {
        // If character is lowercase, convert it to uppercase
        if(islower(str[i])) {
            str[i] = toupper(str[i]);
        }
        else if(isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
    printf("Converted string: %s\n", str);
    return 0;
}

