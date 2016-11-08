#include <stdlib.h>
#include <stdio.h>


typedef struct _node
{
    int num;
    int value;
    struct _node* next;

}node,*p_node;


p_node create_table()
{

    printf("create a root node\n");
    p_node ret = (p_node)malloc(sizeof(node));
    ret-> num = 0;
    ret-> value = 0;
    ret -> next = NULL;
    return ret;
}






p_node create_node(num, value)
{

    p_node ret = (p_node)malloc(sizeof(node));
    ret-> num = num;
    ret-> value = value;
    ret -> next = NULL;
    printf("create a node @%p\n", ret);
    return ret;

}




void insert_node (p_node pre_node,p_node node)
{

    p_node previous_node = pre_node;
    p_node next_node = pre_node->next;
    p_node this_node = node;
    previous_node -> next = this_node;
    this_node -> next = next_node;

}


p_node find_tail (p_node node)
{
    if (node -> next == NULL)
    {
	printf("already tail pointer\n");
	return node;
    }
    else
    {

	while(node->next != NULL)
	{

	    node = node -> next;
	}
	return node;
    }

}







void dump_list(p_node root)
{
    printf("dump!!!\n");

    if (root -> num != 0)
    {
	printf("not a root node");
    }

    do {

	printf("num: %02d, value: %02d, next: %p\n", root -> num, root -> value, root -> next);
	if (root -> next != NULL)
	{
	    printf("    |\n");
	    root = root -> next;
	}
	else
	{
	    break;

	}

    }while (root  != NULL);


}





void main () {
    printf("hello, pipicold, single node\n");

    p_node root = create_table();

    p_node tail = root;
    
    insert_node (tail, create_node(1,20));
    insert_node (tail, create_node(2,23));
    tail = find_tail(root);
    insert_node (tail, create_node(3,45));
    insert_node (tail, create_node(4,89));
    insert_node (tail, create_node(5,91));
    tail = find_tail(root);
    

    dump_list(root);


}

