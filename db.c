#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <db.h> 

FILE *fptr = NULL;

int db_open(db_t * db, const char * filename){
    if(access(filename, F_OK) != -1){
        printf("File Exists! Opening It!\n");
    }
    else
    {
        printf("File doesn't exist! Creating it!\n");
    }
    fptr = fopen(filename, "w+");
    if(fptr == NULL){
        printf("Opening/Creating of file failed!");
        exit(0);
    }
    return 0;
}

int db_insert(db_t *db, uint64_t id){
    db_open(db, id);
    fputs(id, fptr);
    fprintf(fptr, "\n");
    fclose(fptr);
    return 0;
}

int db_find(db_t *db, uint64_t id){
    char buffer[1000], buff[8];
    db_open(db, id);
    int totalRead = 0, flag=0;
    while(fgets(buffer, 1000, fptr) != NULL) 
    {
        /* Total character read count */
        totalRead = strlen(buffer);
        /*
         * Trim new line character from last if exists.
         */
        buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];
        //printf("%s\n", buffer);
        snprintf(buff, 8, id);
        if (strcmp(buff,buffer)==0)
            flag = 1;
    }
    return 0;
}

int db_delete(db_t *db, uint64_t id){
    return 0;
}

void db_free(db_t *db){
    free();
    return 0;
}
