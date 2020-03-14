#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <db.h> 

db_t *target = NULL;

db_t * db_new(){
    // allocate the memory
    db_t *new = NULL; // declaring a new node
    new = (db_t *)malloc(sizeof(db_t));
    new->content = "";
    new->right = NULL;
    new->down = NULL;
    return new;
}


int db_open(db_t * db, const char * filename){
    // opens the 'filename' database
    db_t *current = db;
    int flag = 0;
    while (current != NULL){
        if (strcmp(current->content,filename) == 0) {
            flag = 1;
            target = current;
            return 0;
        }
        else
            current = current->right;
    }
    return 1;
    }

int db_insert(db_t *db, uint64_t id){
    // insert the id in the database
    db_t *new_node, *current;
    current = target;
    while(current->down != NULL)
    {
        current = current->down; // get to the end of the list vertically
    }
    new_node = db_new();
    current->down = new_node;
    current->down->content = id;
    current->down->down = NULL;
    return 0;
}

int db_find(db_t *db, uint64_t id){
    // find id in the database
    db_t *current = target;
    while (current->down != NULL)
    {
        if (strcmp(current->content, id) == 0)
            return 1;
        else
            current = current->down;
    }
    return 0;
}

int db_delete(db_t *db, uint64_t id){
    // remove id from the database
    db_t *current = target, *temp = NULL;
    // edge case for the length
    while (current->down != NULL)
    {
        if (strcmp(current->down->content, id) == 0)
        {
            temp = current->down;
            current->down = temp->down;
            db_free(temp);
            return 1;
        }
        else
            current = current->down;
    }
    
    return 0;
}

void db_free(db_t *db){
    // free the deleted node
    free(db);
}
