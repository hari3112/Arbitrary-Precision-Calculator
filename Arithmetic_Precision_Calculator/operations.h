#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "types.h"

typedef struct _Calc
{
    char operator_name;
    int count_list1;
    int count_list2;
    int call_count;
    int flag;
}Calc;


Status validate_operands(char *argv[]);

Status validate_operator(char *operator, Calc *cInfo);

Status create_list(char *argv[], Calc *cInfo);

Status insert_at_first(Ilist **head, Ilist **tail, int data);

Status insert_at_last(Ilist **head, Ilist **tail, int data);

void swap_list(Ilist **head1, Ilist **head2);

Ilist* reverse_list(Ilist *head);

Status print_list(Ilist *head);

Status list_comparison(Ilist **head1, Ilist **head2, Calc *cInfo);

Status perform_addition(Ilist **tail1,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo,int flag);

Status perform_subtraction(Ilist **head1,Ilist **tail1,Ilist **head2,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo,int flag);

Status perform_multiplication(Ilist **tail1,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo,int flag);

Status perform_division(Ilist **head1,Ilist **tail1,Ilist **head2,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo);

#endif