#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
} Node;

//This function remains unchanged
Node* create_node(int value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node) return 0;

    new_node->value = value;
    new_node->next = 0;

    return new_node;
}

//This new function creates a linked list from an array of values
Node* create_list(const int* values, int num_values){
    if(!values || num_values <= 0) return 0;

    Node* head = create_node(values[0]);

    for(int i = 1; i < num_values; i++){
        Node* temp = head;
        head = create_node(values[i]);
        head->next = temp;
    }

    return head;
}

//This function now takes a DOUBLE POINTER to represent the list, and
//the return type is omitted, since it is no longer necessary to return
//the new "head"
void insert_node(Node** list, Node* new_node){
    if(!new_node || !list) return;

    if(!(*list)) (*list) = new_node;
    else{
        new_node->next = (*list);
        (*list) = new_node;
    }
}

//Similarly to what we did for `insert_node`, we take a DOUBLE POINTER
//to represent the list...
void print_list(Node** list){
    printf("List: ");
    if(!list) {printf("NULL pointer to list\n"); return;}
    else if(!(*list)) printf("List is empty!");

    for(Node* scan = (*list);scan;scan = scan->next) printf("%d ", scan->value);
    printf("\n");
}

//Here we can use the fact that we're taking
//a double pointer to represent the list to take
//care of assigning our list to be NULL to prevent a "Dangling Pointer"
void destroy_list(Node** list){
    if(!list) return;

    Node* scan = (*list);
    while(scan){
        Node* temp = scan;
        scan = scan->next;
        free(temp);
    }

    (*list) = 0;
}

int main(void){

    //This is the same linked list represented by its "head"
    Node* head = create_node(1);

    //Now, instead of keeping a direct pointer to the head,
    //we'll have a double pointer to represent the list, and
    //see how this helps us.

    Node** list = &head; //Notice the use of the '&' prefix to indicate "address-of" `head`...

    //Now, in order to use our print_list function,
    //we must pass the VALUE (which is the DIRECT pointer `head`) of `list`.
    print_list(list);

    //We'll insert a few more nodes into the list:
    insert_node(list, create_node(2));
    insert_node(list, create_node(3));
    insert_node(list, create_node(4));

    print_list(list);

    //Let's take a look at our new "destructor" for lists...
    destroy_list(list);
    print_list(list);

    //We can now see that we avoided a dangling pointer.
    //We can also see that `head` was pointed to NULL:
    printf("`head` is %s NULL!\n", (!head)? "" : "NOT");

    //Now let's take a look a multiple variables keeping track of our list:
    int list_values[5] = {1,2,3,4,5};
    *list = create_list(list_values, 5);
    Node** scan = list;

    printf("This is our `list` variable:\n");
    print_list(list);
    printf("This is our `scan` variable:\n");
    print_list(scan);

    //Now let's see that changing `list` will also change `scan`, and vice-versa
    insert_node(list, create_node(6));
    printf("This is our `list` variable:\n");
    print_list(list);
    printf("This is our `scan` variable:\n");
    print_list(scan);

    insert_node(scan, create_node(7));
    printf("This is our `list` variable:\n");
    print_list(list);
    printf("This is our `scan` variable:\n");
    print_list(scan);

    destroy_list(list);
    printf("This is our `list` variable:\n");
    print_list(list);
    printf("This is our `scan` variable:\n");
    print_list(scan);

    list = 0;
    scan = 0;

    return 0;
}