#include <stdio.h>
#include <string.h>
#include <db.h>

db_t * head = NULL;

int main(int argc, char* argv[])
{   
    char exec[] = "dbcli";
    int result_open, result_action;
    db_t *new_node, *current;
    // checking for input correctness
    if(argc != 4)
    {
        printf("The input should be off the form 'dbcli <filename> <action> <id>'");
        return 0;
    }

    // char *action = argv[2], *filename=argv[1], *id=argv[3];

    //printf("Action:%s\nFilename:%s\nID:%s\n", action,filename,id);

    if (strcmp(argv[2], "insert") == 0)
    {
         printf("The selected action is insert");
         open:
         result_open = db_open(head ,argv[1]);
         if (result_open == 1){
             printf("Filename not found, creating one");
             new_node = db_new();
             // adding the new node at the end of the list
             current = head;
             while(current->right != NULL){
                 current=current->right;
             }
             current->right = new_node;
             current->right->content = argv[1];
             current->right->right = NULL;
             goto open;
         }
         else if (result_open == 0){
             result_action = db_insert(head, argv[3]);
             if (result_action == 0)
                printf("ID successfully inserted");
            else if (result_action == 1)
                printf("ID insertion failed!");
         }
    }
    else if (strcmp(argv[2], "delete") == 0)
    {
         printf("The selected action is delete");
         result_open = db_open(head ,argv[1]);
         if (result_open == 1)
            printf("No such filename found, Can't delete id!");
         else if (result_open == 0)
        {
            result_action = db_delete(head, argv[3]);
            if (result_action == 1)
                printf("ID successfully deleted");
            else if (result_action == 0)
                printf("ID not found!");
        }
        
    }
    else if (strcmp(argv[2], "find") == 0)
    {
         printf("The selected action is find");
         if (result_open == 1)
            printf("No such filename found, Can't find id!");
         else if (result_open == 0)
        {
            result_action = db_find(head, argv[3]);
            if (result_action == 1)
                printf("ID found in the database");
            else if (result_action == 0)
                printf("ID not found!");
        }

    }
    else
    {
         printf("Invalid Action specified. Use 'insert','find' or 'delete' ");
    }
    
    printf("\nTask Complete");
    return 0;
}