#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

Node *create_node(int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        return 0;

    new_node->value = value;
    new_node->next = 0;

    return new_node;
}

Node *insert_node(Node *head, Node *new_node)
{
    if (!new_node)
        return 0;

    if (!head)
        head = new_node;
    else
    {
        new_node->next = head;
    }

    return new_node;
}

void print_list(Node *head)
{
    printf("List: ");
    for (; head; head = head->next)
        printf("%d ", head->value);
    printf("\n");
}

Node *destroy_list(Node *head)
{
    if (!head)
        return 0;
    if (head->next)
        return destroy_list(head->next);
    else
    {
        free(head);
        return 0;
    }
}

int main(void)
{

    // This is a linked list represented by its "head"
    Node *list = create_node(1);
    print_list(list);

    // Once we insert a node into the list, we need to make sure that we update
    // its head to point to the new head.
    list = insert_node(list, create_node(2));
    print_list(list);
    list = destroy_list(list);

    // It's fine if we have a single instance of the list, but what if we
    // want MULTIPLE variables to keep track of this list? What if we FORGET to
    // update the pointers?

    // We'll create the same list again, and this time we'll have a "scan" variable
    // which we could use to traverse the list
    list = create_node(1);
    Node *scan = list;

    printf("List: ");
    print_list(list);
    printf("Scanner: ");
    print_list(scan);

    // Let's insert a new node into the list...
    list = insert_node(list, create_node(2));

    printf("Updated list: ");
    print_list(list);
    printf("Scanner: ");
    print_list(scan);

    // We can see that `scan` did not update, since we're only keeping track
    // of the DIRECT address of the "head" of the list. We would like to solve this problem.

    destroy_list(list);
    scan = 0;

    return 0;
}