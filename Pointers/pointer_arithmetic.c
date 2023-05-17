#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

    //We'll take a look at the syntax and uses of pointer arithmetic.

    char buffer[1000]; // We'll use this array to simulate an input buffer
    strcpy(buffer, "This is a sentence.");

    //Say we want to traverse this buffer, and find the first valid string;
    //We COULD use `strlen`, which will give us the distance (in bytes) between
    //the start of the buffer and the first '\0':
    int string_end = strlen(buffer);
    printf("The first string in the buffer is %d characters long.\n", string_end);

    //However, we can get the same result using pointer arithmetic:
    char* scan = buffer;
    for(; (*scan); ++scan); //Notice the '++' operation on the char* `scan`
    string_end = (int)(scan-buffer); //Notice the '-' operation between two POINTERS
    printf("The first string in the buffer is %d characters long.\n", string_end);

    //If we want to print the first string, we could use `printf` directly (since there's a '\0'):
    printf("%s\n", buffer);

    //But what if we want to add MORE strings to the buffer? Maybe find the second, third, nth string?
    //We COULD use the subscript operator ([]), but there's a more elegant way to do this, using
    //POINTER ARITHMETIC:


    return 0;
}