#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <db.h> 

extern db_t *target;

db_t * db_new(){
    // allocate the memory
    printf("ms1\n");
    db_t *new; // declaring a new node
    printf("ms2\n %d", sizeof(db_t));
    //new = malloc(sizeof(db_t));
    new = (db_t *) malloc (sizeof(db_t));
    printf("ms3\n");
    //new->content = "";
    new->right = NULL;
    new->down = NULL;
    printf("ms1\n");
    return new;
}

int db_open(db_t * db, const char * filename){
    // opens the 'filename' database
    db_t *current = db;
    target = db;
    while (current != NULL)
    {
        if (strcmp(current->content,filename) == 0) {
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
    current = db;
    while(current->down != NULL)
    {
        current = current->down; // get to the end of the list vertically
    }
    new_node = db_new();
    current->down = new_node;
    current->down->content = malloc(sizeof(uint64_t));
    current->down->content = &id;
    //*((uint64_t*) current->down->content) = &id;
    // current->down->content = id;
    current->down->down = NULL;
    return 0;
}

int db_find(db_t *db, uint64_t id){
    // find id in the database
    db_t *current = db;
    while (current->down != NULL)
    {
        // if (strcmp(current->content, id) == 0)
        if (current->content == &id)
            return 1;
        else
            current = current->down;
    }
    return 0;
}

int db_delete(db_t *db, uint64_t id){
    // remove id from the database
    db_t *current = db, *temp = NULL;
    // edge case for the length
    while (current->down != NULL)
    {
        //if (strcmp(current->down->content, id) == 0)
        if (current->down->content == &id)
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
