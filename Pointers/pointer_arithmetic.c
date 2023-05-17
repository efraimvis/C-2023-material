#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 500
#define MAX_BUFF_SIZE 1000
#define M 10
#define N 10
#define FIT(x) (x-1)

/**
 * This is an implementation of the `strcat` function,
 * using the [] operator, without using functions
 * from `string.h`.
 * 
 * @param dst Destination string, to which `src` will be
 *            concatenated. NOTICE: `dst` must have enough free
 *            space to accomodate src.
 * @param src The source string which will be concatenated to `dst`
*/
void strcat_subscript(char* dst, char* src){

    if(!dst || !src) return;

    //Here, we need TWO index variables `i` and `j` to keep track of our
    //position within `dst` and `src`, respectively.
    int i,j = 0;
    if(dst[0]){
        for(i = 0 ;dst[i] ;++i);
    }
    if(src[0]){
        dst[i] = src[j];
        for(;dst[j] ;++j){
            dst[i] = src[j];
            ++i;
        }
    }
    dst[i] = '\0';
}

/**
 * This is an implementation of the `strcat` function,
 * employing pointer arithmetic, without using functions
 * from `string.h`.
 * 
 * @param dst Destination string, to which `src` will be
 *            concatenated. NOTICE: `dst` must have enough free
 *            space to accomodate src.
 * @param src The source string which will be concatenated to `dst`
*/
void strcat_pointer(char* dst, char* src){

    if(!dst || !src) return;

    if(*dst){
        //This traverses `dst` in an elegant way, that does not require us to keep an index variable
        //and employ the [] operator
        for(;(*dst);++dst);
    }
    if(*src){
        //Notice that we only need ONE variable `scan` to keep track of our position within
        //src
        char* scan = src;
        *dst = *scan;
        for(;(*scan);++scan) {*dst = *scan; ++dst;}
    }
    *dst = '\0';
}

/**
 * Returns the length of a given string, employing pointer arithmetic.
 * 
 * @param str A given string
 * 
 * @returns The length of `str`, the string termination character, or
 *          0 if `str` is NULL or on error.
*/
int strlen_pointer(char* str){

    if (!str){
        return 0;
    }
    
    char* scan = str;
    while (*scan){
        scan++;
    }
    
    return (scan - str);
}

/**
 * Returns a deep-copy of a given string
 * 
 * @param src The source string which needs to be copied
 * 
 * @returns A deep-copy of `src` if successful, NULL otherwise.
*/
char* strdup_pointer(char* src) {
    if (!src){
        return 0;
    }
    
    int length = strlen_pointer(src);
    char* copy = (char*)malloc((length + 1) * sizeof(char));
    
    if (!copy){
        return 0;
    }
    
    char* scan = copy;
    while (*src != '\0'){
        *scan = *src;
        scan++;
        src++;
    }
    
    *scan = '\0';
    
    return copy;
}

/**
 * Finds the nth string in a buffer, employing pointer arithmetic.
 * 
 * @param buffer Given buffer
 * 
 * @param n The order (place, i.e. first, second, etc.) of the 
 *          desired string in the buffer.
 * 
 * @returns The string of the desired order, or NULL if
 *          no complete string of that ordered was found. 
*/
char* nth_string(char* buffer, int n){

    if(!buffer || n <= 0) return 0;

    char* first_loc = buffer;
    int str_len = 0;
    bool started_next = false;

    while((buffer - first_loc) < MAX_BUFF_SIZE){

        if(str_len >= MAX_STR_LEN) return 0;
        if(started_next) {str_len = 0; started_next = false;}
        if(*buffer == '\0') {n--; started_next = true;}
        if(n == 0) return strdup_pointer(buffer - str_len);

        buffer++;
        str_len++;
    }

    return 0;
}

int main(void){

    //We'll take a look at the syntax and uses of pointer arithmetic.

    char buffer[MAX_BUFF_SIZE] = {}; // We'll use this array to simulate an input buffer
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

    //But what if we want to add MORE strings to the buffer?
    //We COULD use the subscript operator ([]), but there's a more elegant way to do this, using
    //POINTER ARITHMETIC:
    strcat_pointer(buffer, " This is another sentence.");
    printf("%s\n", buffer);

    //Let's divide our two sentences in the buffer into two distinct
    //strings again, and use `nth_string` to find the second string.
    *(buffer + 19) = '\0';
    char* string2 = nth_string(buffer, 2);
    printf("The second string in the buffer is:\n%s\n", string2);
    free(string2);
    string2 = 0;

    //We can also use pointer arithmetic to access elements of an n-dimensional array,
    //but for now let's look at a 2D array of size NxM (N,M were defined above).
    //The array `arr` define below is, in essence, a ONE dimensional array representation
    //of a 2D array.
    int* arr = (int*)calloc(M*N, sizeof(int));
    bool arr_null = !arr;

    //We'll assign the values of the multiplication table to `arr`
    //(with the help of the macro `FIT` defined above):
    for(int row = 1; row <= N; row++){
        for(int col = 1; col <= M; col++){
            *(arr + FIT(row)*M + FIT(col)) = row*col;
        }
    }

    //To get the (5,5) element of `arr`, we can ask for the element
    //at index (0 + FIT(5)*10 + FIT(5)) = 44, since each row is 10 units wide,
    //the starting index of row n will be n*10, and so we also need to add an
    //offset of m to the start of the row, to get the element in place (n,m). 
    int e5_5 = *(arr + FIT(5)*M + FIT(5));
    printf("The (5,5) element in arr is: %d\n", e5_5);

    //Similarly for element (7,4):
    int e7_4 = *(arr + FIT(7)*M + FIT(4));
    printf("The (7,4) element in arr is: %d\n", e7_4);

    free(arr);
    arr = 0;

    //If we want to define our array using the subscript syntax,
    //we will need to adjust our syntax:
    int arr2[M][N]; //This is, in effect, the same as `int* arr2;`
    int* ptr = *arr2; //ptr contains the address of the start of arr2

    for(int row = 1; row <= N; row++){
        for(int col = 1; col <= M; col++){
            *(ptr + FIT(row)*M + FIT(col)) = row*col;
        }
    }

    int e2_5_5 = *(ptr + FIT(5)*M + FIT(5));
    printf("The (5,5) element in arr is: %d\n", e2_5_5);

    int e2_7_4 = *(ptr + FIT(7)*M + FIT(4));
    printf("The (7,4) element in arr is: %d\n", e2_7_4);    

    return 0;
}