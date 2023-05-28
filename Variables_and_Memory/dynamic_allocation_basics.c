#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALLOC_ERR "\nERROR: could not allocate requested memory\n"

int main(void)
{
    //Dynamic allocation is the concept of allocating memory for objects
    //such as variables and arrays, during the program's RUNTIME - as opposed
    //to rigidly allocating memory for them on a STACK FRAME.

    //What this means is, memory that was not allocated when the program started,
    //or automatically allocated on a stack frame when a function is called etc.,
    //is allocated MANUALLY while the program is running, and it is the programmer's
    //responsibility to manage it.

    //Recall that the program's memory contains a segment called the "HEAP";
    //This HEAP contains the data of all DYNAMICALLY-ALLOCATED variables in the
    //program.

    printf("*********************************DYNAMIC MEMORY ALLOCATION:*********************************\n");
    //There are a number of functions which provide the service of DYNAMIC MEMORY ALLOCATION,
    //and they are: `malloc`, `calloc` and `realloc` for memory ALLOCATION,
    //and the function `free` for DE-ALLOCATION.

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MALLOC:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //Let's examine the function: `void* malloc(size_t size);`
    //This function allocates a BLOCK of a specified number of BYTES on the HEAP, and returns a POINTER to the start
    //of that block.
    //`malloc` takes an argument `size` of type `size_t`, which is a special type that represents SIZES.
    //`size` is the number of BYTES to allocate, and the return type - `void*` - is a special GENERIC POINTER that
    //can be cast to any other pointer type.

    //If, for any reason, `malloc` cannot allocate the requested memory block, it will return a NULL POINTER.

    //Let's see `malloc` in action:
    printf("Attempting to allocate a block that can fit 16 chars, using `malloc`:\n");
    char* string = (char*)malloc(sizeof(char) * 16);

    //Let's unpack what we just did:
    //We used `malloc` to request a block that can contain 16 chars, and assigned the returned pointer
    //to the variable `string`. We passed the argument `sizeof(char) * 16` representing "16 of the size of `char`",
    //and cast the `void*` returned by `malloc` to a `char*`, so we can refer to our newly allocated memory block
    //as an array of `char`s (i.e., a STRING).

    //Since the allocation is not guaranteed to succeed, it's considered best practice to ALWAYS check if the pointer
    //returned by `malloc` is NULL, indicating a failed allocation:
    if(!string)
    {
        printf(ALLOC_ERR);
        exit(1);
    }

    //Now we can use our newly allocated string, however we need. This allocated memory will REMAIN allocated
    //until we MANUALLY DE-ALLOCATE it once we no longer need it.
    string[15] = '\0';
    printf("Successfully allocated a string of size 16, with:\n"
           "ADDRESS:\t%p\n"
           "CONTENTS:\t%s\n", string, string);

    strcpy(string, "malloc string");
    printf("And after `strcpy`:\n"
            "CONTENTS:\t%s\n", string);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CALLOC:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //Let's examine the function: `void* calloc(size_t nmemb, size_t size);`
    //It's similar in function to `malloc`, with a number of differences:
    //The argument `nmemb` that `calloc` takes is the SIZE of the REQUESTED BLOCK, measured
    //in units of `size`; I.e., `calloc` allocates a BLOCK of `nmemb` `sizes`s.
    //Another difference between `malloc` and `calloc` is that `calloc`, after allocating the
    //requested block, initializes all the block's BYTES to ARITHMETIC ZERO.

    //Let's see an example:
    int* arr = (int*)calloc(10, sizeof(int));
    if(!arr)
    {
        printf(ALLOC_ERR);
        exit(1);
    }

    printf("Successfully allocated an int array of size 10, with:\n"
           "ADDRESS:\t%p\n"
           "CONTENTS:\t[", arr);
    for(int i = 0; i < 10; i++) printf("%d%s", arr[i], (i < 9) ? ", " : "]\n");

    //Notice that every element in `arr` was initialized to 0.

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~REALLOC:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //Now we'll take a look at the function: `void* realloc(void* ptr, size_t size);`
    //This function also handles allocation, however, it is not used to allocate a NEW BLOCK
    //of memory, but rather to REZISE an existing DYNAMICALLY ALLOCATED block;
    //This means that the block we get can be either larger or smaller than
    //the block we passed `realloc`.
    //`realloc` takes a pointer `ptr` to an existing dynamically allocated block of memory,
    //and a size `size` which is the requested new size. `realloc` then resizes the block
    //to be of size `size`.
    //NOTE: There might NOT BE ENOUGH FREE MEMORY contiguous with the old block, and in that case,
    //`realloc` will look for enough memory SOMEWHERE ELSE, copy the contents of the old block to a 
    //new block, and return a pointer to the NEW BLOCK of size `size`.

    //Let's try to resize our array `arr` from the `calloc` example:
    printf("The ADDRESS of `arr` BEFORE `realloc`:\t%p\n", arr);
    arr = (int*)realloc(arr, sizeof(int) * 20);
    if(!arr)
    {
        printf(ALLOC_ERR);
        exit(1);
    }
    printf("The ADDRESS of `arr` AFTER `realloc`:\t%p\n", arr);

    //The ADDRESS of `arr` may or may not change as a result of `realloc`.
    //In any case, if succsessful, `arr` will now be double the size.

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FREE:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //Recall that dynamic allocation delegates the responsibility of memory management
    //to the programmer. Therefore, if we ALLOCATE memory, we must also DE-ALLOCATE that memory
    //once we no longer require it - to prevent memory leaks.

    //The function `void free(void* ptr);` DE-ALLOCATES the memory previously allocated
    //for the block at `ptr`. NOTICE: a pointer to a block of memory that was NOT previously
    //dynamically allocated must NEVER be passed to FREE, and similarly, a pointer that was
    //already freed must NOT be passed to `free` again. Doing those things results in UNDEFINED behaviour.

    free(string);
    free(arr);

    printf("Contents of `string` and `arr` have been freed.\n"); 

    return 0;
}