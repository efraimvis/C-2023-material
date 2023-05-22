#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void callback_1()
{
    printf("\nThis callback function prints this message\n");
}

/**
 * @brief Picks a random number n in range [0...9],
 *        and prints an nxn matrix with all elements
 *        equal to n.
 */
void callback_2()
{
    srand(time(0));
    int num = (rand()) % 10;

    if(num == 0 || num == 1) printf("%d\n", num);
    else
    {
        for(int i = 0; i < num; i++)
        {
            for(int j = 0; j < num; j++)
            {
                printf("%d ", num);
            }
            printf("\n");
        }
    }
    printf("\n");
}


/**
 * @brief This is a simple case of a function that calls a function
 *        that's passed to it as an argument - a "callback function".
 *        Here, all our function does is wait a specified amount of seconds,
 *        and then it calls the function that we passed it.
 * 
 * @param msecs Number of seconds to wait before calling the callback function.
 * @param func Pointer to a callback function.
 */
void sleep_and_callback(int msecs, void(*func)())
{
    if(msecs < 0) return;
    sleep(msecs);
    func();
}


int main(void)
{
    // Here we'll explore the concept of function pointers in C.
    // A function in C is an "object", much like variables are;
    // A function's code is stored in the program's memory,
    // in the TEXT AREA.

    // One use of function pointers is as what's called a "callback" function -
    // A function called by another function.

    //Here's a simple example of a callback function employing a function pointer -
    //The function `sleep_and_callback` implemented above simply waits a specifed amount
    //of time, and then calls the function that we passed it using a function pointer:
    sleep_and_callback(0.5, &callback_1);

    //Here's a more interesting callback:
    sleep_and_callback(1.5, &callback_2);
    sleep_and_callback(1.5, &callback_2);
    sleep_and_callback(1.5, &callback_2);

    return 0;
}