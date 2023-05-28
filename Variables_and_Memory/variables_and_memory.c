#include <stdio.h>

int global_int; //This is a global variable

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
 * @brief Demonstrates value persistence of local static variables.
 * 
 */
void local_static_variable()
{
    static int static_int;
    printf("The ADDRESS of `static_int` is:\t%p\n", &static_int);
    printf("The VALUE of `static_int` is:\t%d\n", static_int++);
}


int main(void)
{
    //Here we'll take a look at where and how variables
    //in C are stored in memory, and the concepts of variable scope and lifetime.

    printf("******************************VARIABLE ADDRESSES:********************************\n");

    //Here are some variables of primitive types:
    int a;
    float b;
    char c = 'D';
    double d = 84.5;

    //Every variable has an ADDRESS, indicating the START OF THE MEMORY BLOCK which stores the variable's VALUE
    //We can access the ADDRESS of a variable using the `&` operator, with the syntax: `&<variable name>`
    //Let's take a look at the addresses of the variables that we defined:
    printf("Our variable's addresses:\n\
            \ta:\t%p\n\
            \tb:\t%p\n\
            \tc:\t%p\n\
            \td:\t%p\n",
            &a,
            &b,
            &c,
            &d);

    //A variable will be allocated an amount of memory in one of a NUMBER OF DIFFERENT
    //DESIGNATED SECTIONS of the program's memory, depending on the variable's SCOPE and LIFETIME;

    printf("******************************VARIABLE SCOPE AND LIFETIME:********************************\n");
    //A variable's SCOPE is the part of the program in which the variable
    //"exists" or is recognized:

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LOCAL VARIABLES:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //LOCAL variables are defined within a function or block, and are destroyed once the program exits that scope.
    //LOCAL variables are stored in the program memory's STACK, within the STACK FRAME of their respective
    //function or block. Let's take a look at an example:
    int first = 5;
    int second = -5;
    local_int_swap_wrong(a,b);
    printf("`main`'s a,b values:\n\
            \t%d\n\
            \t%d\n", first, second);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GLOBAL VARIABLES:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //GLOBAL variables are defined OUTSIDE of functions or blocks, and can be accessed from ANYWHERE in the program.
    //They are created when the program starts, and continue to exist until it terminates.
    //GLOBAL variables are stored in the program memory's DATA SEGMENT.

    //Let's look at the address of the GLOBAL variable `global_int` defined above:
    printf("Address of GLOBAL variable `global_int`: %p\n", &global_int);

    //Since `global_int` is a GLOBAL VARIABLE, we can access and change it FROM ANYWHERE in the program.
    //Let's see this in action:
    printf("Value of GLOBAL variable `global_int`, "
           "before change: %d\n", global_int);
    global_int = 123;
    printf("Value of GLOBAL variable `global_int`, "
           "after change: %d\n", global_int);

    //We can see that the address of the GLOBAL variable `global_int` is relatively far away from the
    //addresses of our `main` function's LOCAL variables, which gives us a clue that it is in fact
    //stored in a different segment of the program's memory.

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~STATIC VARIABLES:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //STATIC variables are defined either as LOCAL or GLOBAL variables, and once they are created - they persist
    //until the program terminates. For example, if a static variable is created in a function, the next time
    //that function is called, the variable will have the value that it had in the previous call.
    //STATIC variables are stored in the program memory's DATA SEGMENT, like global variables.

    //Let's take a look at a STATIC VARIABLE defined in the function `local_static_variable` implemented above:
    local_static_variable();
    local_static_variable();
    local_static_variable();


    const int const_int = 47;

    //DYNAMICALLY ALLOCATED variables can be defined anywhere in the program, and the memory allocated to them
    //continues to be allocated to them (and therefore cannot be allocated to other variables) until
    //that memory is explicitly FREED, or until the program terminates.
    //DYNAMICALLY ALLOCATED variables are stored in the program memory's HEAP.

    //The variables `a`,`b`,`c` and `d` are LOCAL variables, and we can see that their addresses
    //are relatively close toghether - since they exist on the same STACK FRAME.

    return 0;
}