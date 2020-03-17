#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <db.h>

db_t *head = NULL, *target = NULL;

int main(int argc, char* argv[])
{   
    char exec[] = "dbcli", input_string[100], newString[20][20];
    db_t *new_node, *current;
    uint64_t id = 0;
    int result_open, result_action, choice = -1, req_args = 4, j_iter = 0, ctr = 0;
    // malloc head
    printf("MS1\n");
    //head = malloc(sizeof(db_t));
    head = (db_t *) malloc (sizeof(db_t));
    head->down = NULL;
    head->right = NULL;
    *((int*)head->content) = -1; // initializing head
    // checking for input correctness
    do
    {   
        id = 0;
        choice = -1;
        j_iter = 0;
        ctr = 0;
        
        if(argc != req_args || strcmp(exec,argv[0]) != 0)
        {
            printf("The input should be off the form 'dbcli <filename> <action> <id>'");
            choice = 1;
        }

        id = strtoull(argv[3], NULL, 10); // converting char * argument into uint64_t
        // id = _strtoui64(argv[3], NULL, 10); // converting char * argument into uint64_t

        // char *action = argv[2], *filename=argv[1], *id=argv[3];

        //printf("Action:%s\nFilename:%s\nID:%s\n", action,filename,id);

        if (strcmp(argv[2], "insert") == 0)
        {
            printf("The selected action is insert\n");
            do
            {
                result_open = db_open(head ,argv[1]);
                if (result_open == 1){
                    printf("Filename not found, creating one\n");
                    printf("MS1\n");
                    new_node = db_new();
                    printf("MS2\n");
                    // adding the new node at the end of the list
                    current = head;
                    printf("MS3\n");
                    while(current->right != NULL){
                        current=current->right;
                    }
                    printf("MS4\n");
                    current->right = new_node;
                    printf("MS5\n");
                    current->right->content = malloc(sizeof(argv[1]));
                    strcpy((current->right->content), argv[1]);
                    // strcpy(((char*) current->right->content), argv[1]);
                    // current->right->content = argv[1];
                    current->right->right = NULL;
                }
            } while (result_open != 0);

            result_action = db_insert(target, id);
            if (result_action == 0)
                printf("ID successfully inserted\n");
            else if (result_action == 1)
                printf("ID insertion failed!\n");

        }
        else if (strcmp(argv[2], "delete") == 0)
        {
            printf("The selected action is delete\n");
            result_open = db_open(head ,argv[1]);
            if (result_open == 1)
                printf("No such filename found, Can't delete id!\n");
            else if (result_open == 0)
            {
                result_action = db_delete(target, id);
                if (result_action == 1)
                    printf("ID successfully deleted\n");
                else if (result_action == 0)
                    printf("ID not found!\n");
            }
            
        }
        else if (strcmp(argv[2], "find") == 0)
        {
            printf("The selected action is find\n");
            result_open = db_open(head ,argv[1]);
            if (result_open == 1)
                printf("No such filename found, Can't find id!\n");
            else if (result_open == 0)
            {
                result_action = db_find(target, id);
                if (result_action == 1)
                    printf("ID found in the database\n");
                else if (result_action == 0)
                    printf("ID not found!\n");
            }

        }
        else
        {
            printf("Invalid Action! Use 'insert','find' or 'delete' \n");
        }
        
        printf("\nEnter 1 to continue or 0 to exit\n");
        scanf("%d", &choice);
        getchar();  // to capture the additional new line character left in by scanf
        if (choice == 0)
        {
            return 0;
        }    

        printf("Enter next command in the form dbcli <filename> <action> <id> : ");
        fgets(input_string, sizeof input_string, stdin);

        for(int idx=0; idx <= (strlen(input_string)); idx++)
        {
        // if space or NULL found, assign NULL into newString[ctr]
            if(input_string[idx]==' '||input_string[idx]=='\0')
            {
                newString[ctr][j_iter]='\0';
                ctr++;  //for next word
                j_iter=0;    //for next word, init index to 0
            }
            else
            {
                newString[ctr][j_iter]=input_string[idx];
                j_iter++;
            }
        }
        for(int idx=0; idx < ctr; idx++)
            strcpy(argv[idx], newString[idx]);
        
        argc = ctr;  //counting the number of terms
        //printf("%s %s %s %s %d\n", argv[0], argv[1], argv[2], argv[3], argc);

    } while (choice != 0 );
}