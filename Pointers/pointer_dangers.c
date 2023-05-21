#include <stdio.h>
#include <stdlib.h>

#define ERR_MALLOC "ERROR: could not allocate memory\n"

/**
 * Utility function that prints the address of a variable.
*/
void print_ptr_address(void* ptr)
{
    printf("The pointer is %sNULL, its address: %p\n", ptr ? "NOT " : "", ptr);
}

/**
 * Utility function that prints the contents of an address pointed to
 * by an int pointer.
*/
void print_int_ptr_value(int* ptr)
{
    printf("The pointer is %sNULL, its contents are: %d\n", ptr ? "NOT " : "", *ptr);
}

void dangling_pointer()
{
    //Let's take a look at the following variable:
    int* num_ptr = (int*)malloc(sizeof(int));
    if(!num_ptr)
    {
        fprintf(stderr, ERR_MALLOC);
    }
    *num_ptr = 54;
    print_ptr_address(num_ptr);
    printf("The value of `num_ptr` is: %d\n", *num_ptr);

    //Now, say we deallocate the memory that was allocated to `num_ptr`:
    free(num_ptr);

    //The pointer `num_ptr` is now a DANGLING POINTER, meaning our program no longer
    //considers it to be pointing to what it was originally pointing to.
    //If we try to access `num_ptr`, we will get the contents of the memory
    //address in the variable `num_ptr` (the address `num_ptr` stores didn't change),
    //but those contents may no longer be what was there originally.
    print_ptr_address(num_ptr);
    printf("The value of `num_ptr` is: %d\n", *num_ptr);

    //If we free the memory allocated to a variable, it is considered best practice
    //to set its pointer to NULL (which is the same as 0), in order to be able to know
    //that that pointer no longer represents what it previously represented:
    num_ptr = 0;
}

/**
 * This function attempts to return the address
 * of a local variable. Most modern compilers will
 * refuse to compile it, and will raise an error -
 * since the variable `num` is local and is on the STACK, and therefore
 * will be destroyed once the function finishes - resulting in `&num`
 * becoming a DANGLING POINTER.
 * 
int* local_variable_ptr_return()
{
    int num = 47;
    return &num;
}
**/

int main(void)
{
    //When using pointers for direct memory manipulation,
    //we need to keep in mind that there can also be issues;

    printf("******************************DANGLING POINTERS:********************************\n");

    //First, we'll discuss the concept of "dangling pointers";
    //Take a look at the functioin `dangling_pointer` implemented above:
    dangling_pointer();

    //Another form of a "dangling pointer" can occur when trying to
    //return the address of a local vairable;
    //Take a look at the proposed function `local_variable_ptr_return` above;
    //Depending on the compiler, a compilation error may occur if we uncomment
    //it, and try to run the code below:

    //int* ptr = local_variable_ptr_return();
    //print_ptr_address(ptr);
    //print_int_ptr_value(ptr);

    printf("***********************USING AN INCORRECT POINTER TYPE:*************************\n");

    //Now we'll take a look at what happens when we try to access data
    //using the wrong pointer type:

    //Let's define an array of `float`:
    float* arr = (float*)calloc(10, sizeof(float));
    for(int i=0; i<10; i++) arr[i] = i*0.5;  
    float f5 = arr[4];

    //And take a look at its contents:
    printf("Contents of `arr`:\n");
    for(int i=0; i<10; i++) printf("%.2f ", arr[i]);
    printf("\n");
    printf("Value of `f5` %.2f:\n", f5);

    //Now, let's "convert" this array into a `char` array,
    //and see what we get:
    char* char_arr = (char*)arr;
    printf("Contents of `char_arr`:\n");
    for(int i=0; i<10; i++) printf("%c ", char_arr[i]);
    printf("\n");
    f5 = char_arr[4]; //C will automatically cast-up from `char` to `float`...
    printf("Value of `f5` %.2f:\n", f5);

    //We can see that we in fact did not get a conversion of the array `arr`
    //to a `char` array, instead we got garbage values:
    //The elements of `arr` and `char_arr` are MISALIGNED. This means that, for example, `arr[1]`
    //and `char_arr[1]` will select a DIFFERENT SET OF BYTES each.

    //Let's see what we mean by "select a DIFFERENT SET OF BYTES each":
    size_t arr1_start = (size_t)&arr[1];
    size_t char_arr1_start = (size_t)&char_arr[1];
    size_t arr1_end = (size_t)&arr[2] - 1;
    size_t char_arr1_end = (size_t)&char_arr[2] - 1;

    printf("`arr[1]` covers the addresses %lu to %lu\n", arr1_start, arr1_end);
    printf("`char_arr[1]` covers the addresses %lu to %lu\n", char_arr1_start, char_arr1_end);

    //Therefore, we cannot simply do a "conversion" like we attempted, and if we
    //want to convert an array of one type to another type, we must always give thought
    //to the types of the arrays in question.

    printf("***********************TRYING TO FREE A LOCAL VARIABLE:*************************\n");

    //The function `free(void* ptr)` can only be used on pointers to
    //dynamically allocated memory, meaning, pointers to memory addresses on THE HEAP.
    //Trying to `free()` a local variable will result in an error.

    int num = 55;
    printf("Value of `num`: %d\n", num);
    int* num_ptr = &num;
    print_ptr_address(num_ptr);
    print_int_ptr_value(num_ptr);

    printf("A local variable cannot be 'freed':\n");
    //free(num_ptr);

    //If we uncomment the line `free(num_ptr)`, we will inevitably
    //get an error. It is therefore important to avoid this kind of
    //mistake.

    return 0;
}