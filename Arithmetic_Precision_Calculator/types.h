#ifndef TYPES_H
#define TYPES_H

typedef enum{
    FAILURE,
    SUCCESS,
}Status;

typedef struct Input_list
{
    int data;
    struct Input_list *prev;
    struct Input_list *next;
}Ilist;


#endif