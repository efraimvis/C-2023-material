#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/**
 * @brief Tries to swap a,b. Will not work,
 *        because the FUNCTION's a,b are LOCAL
 *        to it, and don't have the same ADDRESSES
 *        as the a,b passed to it. therefore, it will
 *        swap its own a,b, but not affect what was passed
 *        to it. 
 * 
 * @param first First number
 * @param second Second number
 */
void local_int_swap_wrong(int first, int second)
{
    int temp = second;
    second = first;
    first = temp;    
}

/**
 * @brief Swaps the values of two `int` variables inplace.
 *        This is the correct way to do this kind of inplace swapping,
 *        since we can directly access the VALUES at the ADDRESSES
 *        passed to the function.
 * 
 * @param first First number
 * @param second Second number
 */
void local_int_swap_correct(int* first, int* second)
{
    //Notice that since we need to access the VALUES
    //at the POINTERS (addresses) `first` and `second`
    //using the DEREFERENCE OPERATOR, we MUST first make
    //sure that the pointers themselves are not NULL.
    //The dereference operation on a NULL pointer is UNDEFINED,
    //and will cause the program to crash.
    if(!first || !second) return;

    int temp = *second;
    *second = *first;
    *first = temp;
}


int main(void)
{
    printf("*********************************POINTERS - OVERVIEW:*********************************\n");
    //We'll explore the concept of pointers in C,
    //their syntax and uses.

    //A pointer in C is a variable that stores
    //AN ADDRESS IN (the program's) MEMORY.
    //A pointer is declared with the following syntax:

    //<type name>* <variable name>;
    //OR
    //<type name> *<variable name>;

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~POINTERS - SYNTAX:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //For example:
    int* int_ptr;
    float *float_ptr;

    //Let's create some variables, and assign their addresses to
    //the pointers that we created:
    int a = 30;
    float b = 2.5;
    int_ptr = &a; //Note the use of the '&' ("address-of") operator
    float_ptr = &b;

    //We can convince ourselves that a pointer in fact
    //stores a memory address:
    printf("The address of `a` is: %p\n", int_ptr);
    printf("The address of `b` is: %p\n", float_ptr);

    //We can access the VALUE of the memory in the address
    //stored in the pointer by using the '*' (dereference) operator:
    printf("The value of `a` is: %d\n", *int_ptr); //Here, `*int_ptr` is the VALUE in the address `int_ptr`
    printf("The value of `b` is: %.2f\n", *float_ptr);

    //When coding in C, pointers are our way of keeping track of memory addresses, and
    //determining what data is stored in them.

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~POINTERS - SIMPLE SWAP FUNCTION:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //The uses for pointers are many and varied, but let's see
    //a very basic example;
    //Say we have two variables (possibly elements in an array),
    //and we wish to swap their values. We can implement this basic and common operation
    //each time we wish to perform it, however, that is tiresome and unnecessary - we would
    //like to write a function that does that.
    //Let's take a look:
    int first = -20;
    int second = 5;
    printf("The values of `first`, `second`:\n"
           "`first`:\t%d\n"
           "`second`:\t%d\n", first, second);

    //Let's try a naive approach. Please see the function `void local_int_swap_wrong(int first, int second)`
    //defined above:
    local_int_swap_wrong(first, second);
    printf("The values of `first`, `second`:\n"
           "`first`:\t%d\n"
           "`second`:\t%d\n", first, second);

    //Nothing happened! Why is that?

    //We need to remember that `first` and `second` are LOCAL variables,
    //and exist on our `main` function's STACK FRAME.

    //When we pass a variable to a function, the VALUE of that variable is COPIED
    //to the STACK FRAME of the function being called, and assigned to a variable
    //with the name matching the name of the matching argument in the function's SIGNATURE.

    //In short, the functions we call know NOTHING about the actual VARIABLES we pass to them
    //as arguments, except for their VALUES, which get COPIED into the function's STACK FRAMES.

    //What we would like to do is pass the ADDRESSES of the two variables whos values we
    //wish to swap - and that way the function that we're calling can access the
    //MEMORY CONTENTS AT THE ADDRESSES that we passed. The function we call can
    //change the contents of the program's memory, and those changes will persist in the
    //locations whose contents were changed.

    //A CORRECT version of the swap function we wanted is implemented above; Let's try it:
    int* first_ptr = &first;
    int* second_ptr = &second;
    local_int_swap_correct(first_ptr, second_ptr);
    printf("The values of `first`, `second`:\n"
           "`first`:\t%d\n"
           "`second`:\t%d\n", first, second);

    //We used direct memory access to change the values of variables,
    //and that direct memory access is what pointers provide.

    return 0;
}