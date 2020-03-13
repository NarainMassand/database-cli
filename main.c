#include <stdio.h>
#include <string.h>
#include <db.h>

int main(int argc, char* argv[])
{   
    char exec[] = "dbcli";
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
    }
    else if (strcmp(argv[2], "delete") == 0)
    {
         printf("The selected action is delete");
    }
    else if (strcmp(argv[2], "find") == 0)
    {
         printf("The selected action is find");
    }
    else
    {
         printf("Invalid Action specified. Use 'insert','find' or 'delete' ");
    }
    
    printf("\nTask Complete");
    return 0;
}