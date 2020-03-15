#include <stdio.h>
#include <string.h>
#include <db.h>

db_t *head = NULL, *target = NULL;

int main(int argc, char* argv[])
{   
    char exec[] = "dbcli";
    // malloc head
    head = (db_t *)malloc(sizeof(db_t));
    db_t *new_node, *current;
    int result_open, result_action, choice=1;
    // checking for input correctness
    do
    {
        if(argc != 4 || strcmp(exec,argv[0]) != 0)
        {
            printf("The input should be off the form 'dbcli <filename> <action> <id>'");
            return 0;
        }

        // char *action = argv[2], *filename=argv[1], *id=argv[3];

        //printf("Action:%s\nFilename:%s\nID:%s\n", action,filename,id);

        if (strcmp(argv[2], "insert") == 0)
        {
            printf("The selected action is insert");
            do
            {
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
                    current->right->content = malloc(sizeof(argv[1]));
                    strcpy(((char*) current->right->content), argv[1]);
                    // current->right->content = argv[1];
                    current->right->right = NULL;
                }
            } while (result_open != 0);

            result_action = db_insert(target, argv[3]);
            if (result_action == 0)
                printf("ID successfully inserted");
            else if (result_action == 1)
                printf("ID insertion failed!");

        }
        else if (strcmp(argv[2], "delete") == 0)
        {
            printf("The selected action is delete");
            result_open = db_open(head ,argv[1]);
            if (result_open == 1)
                printf("No such filename found, Can't delete id!");
            else if (result_open == 0)
            {
                result_action = db_delete(target, argv[3]);
                if (result_action == 1)
                    printf("ID successfully deleted");
                else if (result_action == 0)
                    printf("ID not found!");
            }
            
        }
        else if (strcmp(argv[2], "find") == 0)
        {
            printf("The selected action is find");
            result_open = db_open(head ,argv[1]);
            if (result_open == 1)
                printf("No such filename found, Can't find id!");
            else if (result_open == 0)
            {
                result_action = db_find(target, argv[3]);
                if (result_action == 1)
                    printf("ID found in the database");
                else if (result_action == 0)
                    printf("ID not found!");
            }

        }
        else
        {
            printf("Invalid Action! Use 'insert','find' or 'delete' ");
        }
        
        printf("\nEnter 1 to continue or 0 to exit\n");
        scanf("%d", choice);
        if (choice == 0)
            return 0;
        
        printf("Enter next command in the form dbcli <filenmae> <action> <id>");
        
        for(int i=0 ; i<4 ; i++)
            scanf("%d",&argv[i]);

    } while (choice != 0 );
}