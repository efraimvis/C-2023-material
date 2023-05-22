#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>

typedef enum type
{
    INT,
    FLOAT,
    STRING
} Type;


const char* type_names[3] = {"int", "float", "string"};


int cmp_int(const char* str_a, const char* str_b)
{
    int a = atoi(str_a);
    int b = atoi(str_b);

    return  a < b ? -1 :
            a > b ? 1 : 0;
}


int cmp_float(const char* str_a, const char* str_b)
{
    int a = atof(str_a);
    int b = atof(str_b);

    return  a < b ? -1 :
            a > b ? 1 : 0;
}


/**
 * @brief Compares two variables, represented as strings.
 * 
 * @param type Type of variables, as defined in enum `Type`
 * @param a First variable
 * @param b Second variable
 * @param cmp_funcs Array of pointers to comparison functions
 * @return Negative value if `a` < `b`, positive value if `a` > `b`,
 *         0 if `a` and `b` are equal.
 */
int var_cmp(Type type, const char* a, const char* b, int (*cmp_funcs[])(const char*, const char*))
{
    return cmp_funcs[type](a, b);
}

/**
 * @brief Takes two variables of a given type from user, and prints
 *        what relation in {<,>,=} holds between them.
 * 
 * @param type Variable type
 */
void input_vars(Type type)
{
    char type_name[10];
    strcpy(type_name, type_names[type]);

    printf("Enter two %ss: ", type_name);

    char a[32] = {};
    char b[32] = {};
    char relation[3] = {};

    scanf("%s %s", a, b);

    int (*cmp_funcs[3])(const char* a, const char* b) = {&cmp_int, &cmp_float, &strcmp};
    int res = var_cmp(type, a, b, cmp_funcs);

    strcpy(relation, res > 0 ? ">" : res < 0 ? "<"
                                             : "=");

    printf("%s %s %s holds.\n", a, relation, b);
}


/**
 * @brief Runs a generic multiple-choice text menu based on parameters.
 * 
 * @param title Menu title (optional); To use the default title, pass an empty string.
 * @param choice_text The choices displayed to the user. NOTICE: The size of `choice_text`
 *                    must match `num_choices`.
 * @param functions An array of void functions;
 *                  For choice i, the ith function in `functions` will be called.
 *                  NOTICE: The size of `functions` must match `num_choices`.
 * @param num_choices The number of choices.
 */
void run_menu(const char *title, const char **choice_text, void((*(functions[]))()), int num_choices)
{
    if (!choice_text || !functions || (num_choices <= 0))
        return;

    int choice = 0;

    do
    {
        if (!title || !strcmp("", title))
            printf("Select an option:\n");
        else
            printf("%s\n", title);

        for (int i = 0; i < num_choices; i++)
        {
            printf("%d. %s\n", (i + 1), choice_text[i]);
        }
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (!((choice >= 1 && choice <= num_choices)))
            printf("\nPlease select a valid choice\n\n");
    } while (!((choice >= 1 && choice <= num_choices)));

    void (*chosen_func)() = (functions[(choice - 1)]);
    chosen_func();

    return;
}


void input_vars_int()
{
    input_vars(INT);
}

void input_vars_float()
{
    input_vars(FLOAT);
}

void input_vars_string()
{
    input_vars(STRING);
}


void choice1()
{
    printf("This is choice 1\n");
}


void choice2()
{
    printf("This is choice 2\n");
}


void choice3()
{
    printf("This is choice 3\n");
}


void quit()
{
    return;
}


int main(void)
{
    // Here we'll explore the concept of function pointers in C.
    // A function in C is an "object", much like variables are;
    // A function's code is stored in the program's memory,
    // in the TEXT AREA.

    // One use of function pointers is as what's called a "callback" function -
    // A function called by another function.

    // Let's take running text menus as an example of the usefullness of
    // having function pointers: instead of painstakingly coding out a long
    // function that runs a specific menu, utilizing big (and rigid) switch-case
    // or (worse) if-else-if-else statements for the choices, we can instead
    // create a single interface that can take ANY NUMBER of functions, and
    // run a selection menu, which calls the apropriate function for a given choice.
    // In order to "pass a function" as an argument to another function, we must actually
    // pass a FUNCTION POINTER (or in the case of our menu, an ARRAY OF FUNCTION POINTERS)
    // to the function which will call the desired function.

    // Let's take a look at how we can use the function `run_menu` implemented above:
    const char* option_text_1[4] = {
                                        "Choice 1",
                                        "Choice 2",
                                        "Choice 3",
                                        "Quit"
                                    };

    void (*menu_funcs_1[])() = {&choice1, &choice2, &choice3, &quit};

    printf("******************************PASSING SIMPLE FUNCTIONS TO OUR GENERIC MENU:********************************\n");
    run_menu("", option_text_1, menu_funcs_1, 4);


    printf("***********************PASSING SLIGHTLY MORE COMPLEX FUNCTIONS TO OUR GENERIC MENU:************************\n");
    const char *option_text_2[3] = {
        "Compare two `int`s",
        "Compare two `float`s",
        "Compare two strings"};

    void (*menu_funcs_2[])() = {&input_vars_int, &input_vars_float, &input_vars_string};

    run_menu("Select a comparison:", option_text_2, menu_funcs_2, 3);

    return 0;
}