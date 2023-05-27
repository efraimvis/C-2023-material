#include <stdio.h>


int main(void)
{
    //Here we'll explain the concept of datatypes and variables
    //in C, and see some of their properties.

    printf("******************************VARIABLES:********************************\n");

    //A variable in C is an object used to store data.
    //Every variable in C has a DATA TYPE, a NAME, a VALUE, and an ADDRESS. 
    //A variable can be declared with the following syntax:

    //<type> <variable name>;
    //Where `type` is the variable's DATA TYPE, and `variable name` is the variable's name.

    //(In C99 and up) A variable can be declared and assigned a value in the same statement:
    //<type> <variable name> = <value>;

    //There is a number of "primitive" data types built into C, some examples:
    //int : Integers
    //float : Real numbers, represented in "floating point" representation
    //double : Like float, but can store a larger range of numbers
    //char : Smallest numeric data unit in C, most commonly used to represent alphanumeric characters in ASCII
    //etc...

    //Some primitive data types have "signed" and "unsigned" versions - "signed" means the data type
    //can hold either positive or negative numeric values, and "unsigned" data types can only hold
    //non-negative values. Since signed and unsigned versions of a type have the same SIZE, this means
    //that representing signed numbers comes at the cost of the range of numbers that can be represented -
    //hence the need to have two versions.

    //Some examples of variables of primitive types:
    int a = 1674;
    float b;
    char c = 'D';
    double d = 84.5;

    //As stated earlier, every variable has a TYPE, a NAME, a VALUE and an ADDRESS.
    //In particular, a variable's TYPE determines the NUMBER OF BYTES IN MEMORY that
    //the variable's VALUE will take up, as well as in what format the variable's VALUE
    //will be.

    //We can examine a DATA TYPE's SIZE by using the `sizeof` operator, like so:
    printf("Data type sizes:\n\
            \tchar:\t%lu\n\
            \tint:\t%lu\n\
            \tfloat:\t%lu\n\
            \tdouble:\t%lu\n",
            sizeof(char),
            sizeof(int),
            sizeof(float),
            sizeof(double));

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

    return 0;
}