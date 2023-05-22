#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_STACK_SIZE 10

/**
 * Implementation of an `int` stack data structure.
 * 
 * @param stack_arr An `int` array, which will hold the stack's data
 * @param size The maximum size of the stack
 * @param top Pointer to the top of the stack
*/
typedef struct stack
{
    int* stack_arr; //An array of `int` that implements our stack's data storage
    int size; //Size of `stack_arr`
    int* top; //A POINTER to the top of the stack
} Stack;

/**
 * Creates an `int` stack with a specified maximum size
 * 
 * @param size The maximum size of the stack
 * 
 * @returns A new stack with the given maximum size,
 *          or NULL on error.
*/
Stack* create_stack(int size)
{
    if(size <= 0) return 0;

    Stack* stack = (Stack*)calloc(1, sizeof(Stack)); //In order to use the dynamic allocation functions, we MUST use a pointer!
    if(!stack) return 0;

    stack->stack_arr = (int*)calloc(size, sizeof(int));
    if(!(stack->stack_arr))
    {
        free(stack);
        return 0;
    }
    stack->size = size;
    stack->top = stack->stack_arr;

    return stack;
}

/**
 * Checks if the given stack is empty.
 * 
 * @param stack Given stack
 * 
 * @returns 1 if the stack is empty, 0 if not - or on error.
*/
int is_empty(Stack* stack)
{
    if(!stack || !(stack->stack_arr) || (stack->top == stack->stack_arr)) return 1;
    else return 0;
}

/**
 * Checks if the given stack is full
 * 
 * @param stack Given stack
 * 
 * @returns 1 if the stack is full, 0 if not - or on error.
*/
int is_full(Stack* stack)
{
    if(!stack || !(stack->stack_arr)) return 0;
    else if((stack->top) - (stack->stack_arr) == (stack->size )) return 1;

    return 0;
}

/**
 * Pushes a given value to a given stack
 * 
 * @param stack Given stack
 * @param value Value to push onto the stack
 * 
 * @returns 1 if the value was pushed successfully, 0 if
 *          the stack is full or on error.
*/
int push(Stack* stack, int value)
{
    if(!stack || !(stack->stack_arr) || is_full(stack)) 
        return 0; //Checking that the stack exists, and is not full.

    stack->top++; //This is pointer arithmetic, we moved `top` to point to the next address in `stack_arr`
    *(stack->top) = value; //Here, the left hand side of the '=' is an ACCESS TO THE VALUE OF A POINTER
    
    return 1;
}

/**
 * Pops the element at the top of the stack, and returns its value.
 * 
 * @param stack Given stack
 * 
 * @returns The element that was at the top of the stack,
 *          or `INT_MAX` if the stack is empty, or on error.
*/
int pop(Stack* stack)
{
    if(!stack || !(stack->top) || is_empty(stack)) return INT_MAX;

    int top = *(stack->top); //Here, the right hand side of the '=' is an ACCESS TO THE VALUE OF A POINTER
    stack->top--; //This is pointer arithmetic, we moved `top` to point to the previous address in `stack_arr`

    return top;
}

void destroy_stack(Stack* stack)
{
    if(!stack) return;

    if(stack->stack_arr)
    {
        free(stack->stack_arr);
        stack->stack_arr = 0;
    }

    free(stack);
}

int main(void)
{
    //We'll explore the concept of pointers in C,
    //their syntax and uses.

    //A pointer in C is a variable that stores
    //AN ADDRESS IN (the program's) MEMORY.
    //A pointer is declared with the following syntax:

    //<type name>* <variable name>;
    //OR
    //<type name> *<variable name>;

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

    //In order to dynamically allocate memory, the use of pointers is MANDATORY.
    //Let's take a look at an example implementation of a stack data structure (defined above):
    Stack* stack = create_stack(MAX_STACK_SIZE); //We have to use a POINTER to a `Stack`!

    if(!stack) return 0; //Checking if `stack` was created successfully

    int i = 0;

    //Pushing the numbers 0..9 onto the stack...
    while(!(is_full(stack)))
    {
        push(stack, i);
        i++;
        if(is_full(stack)) printf("Stack is full!\n");
    }

    printf("Contents of the stack are:\n");
    while(!(is_empty(stack)))
    {
        printf("%d\n", pop(stack));
        if(is_empty(stack)) printf("Stack is empty!\n");
    }

    destroy_stack(stack);
    stack = 0; //Assigning `0` to `stack` to prevent a "dangling pointer"

    return 0;
}