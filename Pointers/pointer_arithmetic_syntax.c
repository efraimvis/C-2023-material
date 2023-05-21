#include <stdio.h>
#define ARR_SIZE 50

int main(void)
{

    // Let's take a look at the syntax syntax of pointer arithmetic,
    // and what "pointer arithmetic" actually means.

    // We're familiar with the subscript operator ('[]') which allows us to access elements
    // of an array; Now we'll become familiar with accessing array elements using pointers, and
    // pointer arithmetic.

    // Recall that all arrays in C are contiguous blocks of a certain size in memory.
    // For any array `arr` that we can define, the variable `arr` is actually a POINTER TO THE FIRST
    // ELEMENT OF THE ARRAY `arr`. Therefore, the expression `arr[0]` is equivalent to the
    // expression `*(arr + 0)`, which is ultimately equivalent to `*arr`.
    // Similarly, the expression `arr[5]` is equivalent to `arr[0+5]`, which
    // is ultimately equivalent to the expression `*(arr + 5)`. This way of memory access,
    // in the form '<pointer> + <integer offset>', employs the syntax of pointer arithmetic.

    // Now we'll define an array, and see how we can access different elements
    // in the array using pointer arithmetic.
    int arr[ARR_SIZE] = {}; // We defined an int array, with all elements initialized to be '0'.

    // Let's assign the natural numbers 1...ARR_SIZE to `arr`, in the familiar fashion:
    for (int i = 0; i < ARR_SIZE; i++)
        arr[i] = (i + 1);

    // To access the 5th element in `arr` using the subscript operator, we can:
    int arr_5 = arr[4];
    printf("5th element of `arr` is: %d\n", arr_5);

    // To do the same with pointer arithmetic, we'll:
    int arr_5_pa = *(arr + 4); // Here, our '<pointer>' is `arr`, and our '<integer offset>' is `4`.
    printf("5th element of `arr` is: %d\n", arr_5_pa);

    // Now let's see another feature of pointer arithmetic:
    // If we want to find the DISTANCE between two memory addresses
    // stored in pointers, we can use the '-' operator between them,
    // keeping in mind that we can only subtract the LOWER address from the HIGHER address;
    // This is useful for finding the length of some contiguous block in memory, for example:
    int arr_len = arr[ARR_SIZE - 1] - arr[0] + 1; // Notice `arr[ARR_SIZE-1]` and `arr[0]` are POINTERS.
    printf("The length of `arr` is: %d\n", arr_len);

    // If we'd like to reassign the values of `arr` to be the doubles of what they were,
    // we could employ pointer arithmetic, like so:
    int *ptr = arr; // We define an int pointer `ptr`, which we will use to traverse `arr`.

    for (; (ptr - arr) < ARR_SIZE; ++ptr) // Notice that `(ptr - arr)` is the DISTANCE between `ptr` and `arr`
        (*ptr) = (*ptr) * 2;

    // And now to print out `arr`:
    ptr = arr;
    printf("The contents of `arr` are:\n");
    for (; (ptr - arr) < ARR_SIZE; ++ptr)
    {
        printf("%d ", (*ptr));
    }
    printf("\n");
    ptr = arr;

    // Notice that the operators '*' and '/' are NOT DEFINED for
    // pointer arithmetic, and an attempt to use them between POINTERS
    // or between POINTERS AND INTEGERS will result in an ERROR;
    // For example, the expressions `ptr = ptr * 2;` and `ptr = ptr * arr;` are invalid.

    return 0;
}