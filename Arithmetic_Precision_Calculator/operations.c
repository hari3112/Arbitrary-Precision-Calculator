#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "types.h"
#include "operations.h"

Status validate_operands(char *argv[]){
    int i = 1,j;
    while(i <= 4){
        j = 0;
        while(argv[i][j] != '\0'){
            if(!(argv[i][j] >= '0' && argv[i][j] <= '9')){
                return FAILURE;
            }
            j++;
        }
        i = i + 2;
    }
    return SUCCESS;    
}

Status validate_operator(char *operator, Calc *cInfo){
    char valid_operators[4] = {'+','-','x','/'};
    char operation_name[5][20] = {"Addition", "Subtraction", "Multiplication", "Division"};
    for(int i = 0;i < 4;i++){
        if(strchr(operator,valid_operators[i]) != NULL){
            cInfo->operator_name = valid_operators[i];
            printf("Info : %s operation is selected\n",operation_name[i]);
            return SUCCESS;
        }
    }
    return FAILURE;
}

Status insert_at_first(Ilist **head, Ilist **tail, int data){

    Ilist *newnode = (Ilist*)malloc(sizeof(Ilist));

    if(newnode == NULL)
        return FAILURE;

    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;

    if(*head == NULL && *tail == NULL){
        *head = newnode;
        *tail = newnode;
        return SUCCESS;
    }

    newnode->next = *head;
    (*head)->prev = newnode;
    *head = newnode;

    return SUCCESS;
}

Status insert_at_last(Ilist **head, Ilist **tail, int data){

    Ilist *newnode = (Ilist*)malloc(sizeof(Ilist));

    if(newnode == NULL)
        return FAILURE;

    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;

    if(*head == NULL && *tail == NULL){
        *head = newnode;
        *tail = newnode;
        return SUCCESS;
    }

    (*tail)->next = newnode;
    newnode->prev = *tail;
    *tail = newnode;

    return SUCCESS;    
}

void swap_list(Ilist **head1, Ilist **head2){

    Ilist *temp = *head1;
    *head1 = *head2;
    *head2 = temp;
}

Status print_list(Ilist *head){
    Ilist *temp = head, *temp1 = head;
    int flag = 1;
    printf("head->");
    while(temp != NULL){
        printf("%d<->",temp->data);
        temp = temp->next;
    }
    printf("tail\n");

    printf("The result is : ");
    while(temp1 != NULL){
        if(temp1->data != 0){
            flag = 0;
            break;
        }
        temp1 = temp1->next;
    }
    
    while(temp1 != NULL){
        printf("%d",temp1->data);
        temp1 = temp1->next;
    }

    if(flag)
        printf("%d",flag - 1);

    printf("\n");

    return SUCCESS;
}

Status list_comparison(Ilist **head1, Ilist **head2,Calc *cInfo){

    Ilist *temp1 = *head1;
    Ilist *temp2 = *head2;

    int count = 0;

    while(temp2 != NULL){
        count++;
        temp2 = temp2->next;
    }

    if(cInfo->count_list1 < count)
        return FAILURE;
    else if(cInfo->count_list1 > count){
        cInfo->call_count++;
        return SUCCESS;
    }
    else{
        temp2 = *head2;
        while(temp1 != NULL){
            if(temp1->data > temp2->data){
                cInfo->call_count++;
                return SUCCESS;
            }
            else if(temp1->data < temp2->data)
                return FAILURE;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    cInfo->call_count++;

    return FAILURE;
}

Status create_list(char *argv[], Calc *cInfo){
    int i = 1,j,data;
    cInfo->count_list1 = 0;
    cInfo->count_list2 = 0;

    Ilist *head1 = NULL;
    Ilist *tail1 = NULL;

    Ilist *head2 = NULL;
    Ilist *tail2 = NULL;

    Ilist *res_head = NULL;
    Ilist *res_tail = NULL;

    while(i <= 3){
        j = 0;
        while(argv[i][j] != '\0'){
            data = argv[i][j] - 48;
            if(i == 1){
                cInfo->count_list1++;
                if(insert_at_last(&head1,&tail1,data) == FAILURE)
                    return FAILURE;
            }
            else{
                cInfo->count_list2++;
                if(insert_at_last(&head2,&tail2,data) == FAILURE)
                    return FAILURE;
            }
            j++;
        }
        i = i + 2;
    }

    print_list(head1);
    print_list(head2);

    if(cInfo->operator_name == '+')
        perform_addition(&tail1,&tail2,&res_head,&res_tail,cInfo,1);
    else if(cInfo->operator_name == '-')
        perform_subtraction(&head1,&tail1,&head2,&tail2,&res_head,&res_tail,cInfo,1);
    else if(cInfo->operator_name == 'x')
        perform_multiplication(&tail1,&tail2,&res_head,&res_tail,cInfo);
    else if(cInfo->operator_name == '/')
        perform_division(&head1,&tail1,&head2,&tail2,&res_head,&res_tail,cInfo);

    return SUCCESS;
}

Status perform_addition(Ilist **tail1,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo,int flag){
    Ilist *temp1 = *tail1,*temp2 = *tail2;

    if(temp1 == NULL && temp2 == NULL)
        return FAILURE;

    int sum = 0, carry = 0;

    while(temp1 != NULL || temp2 != NULL){
        if(temp1 == NULL){
            sum = temp2->data + carry;
            temp2 = temp2->prev;
        }
        else if(temp2 == NULL){
            sum = temp1->data + carry;
            temp1 = temp1->prev;
        }
        else{
            sum = temp1->data + temp2->data + carry;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        } 

        if(sum > 9){
            carry = 1;
            sum = sum % 10;
        }
        else 
            carry = 0;

        if(insert_at_first(res_head,res_tail,sum) == FAILURE)
            return FAILURE;
    }
    
    if(carry){
        if(insert_at_first(res_head,res_tail,1) == FAILURE)
            return FAILURE;
    }
    if(flag){
        printf("The result of addition of 2 operands is : ");
        print_list(*res_head);
    }

    return SUCCESS;
}

Status perform_subtraction(Ilist **head1,Ilist **tail1,Ilist **head2,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo,int flag){

    Ilist *temp_t1 = *tail1, *temp_t2 = *tail2, *temp_h1 = *head1, *temp_h2 = *head2;
    cInfo->flag = 0;

    if(temp_t1 == NULL && temp_t2 == NULL)
        return FAILURE;
    
    if(cInfo->count_list1 < cInfo->count_list2){
        swap_list(&temp_t1,&temp_t2);
        cInfo->flag = 1;
    }
    else if(cInfo->count_list1 == cInfo->count_list2){
        while(temp_h1 != NULL && temp_h2 != NULL){
            if(temp_h1->data < temp_h2->data){
                swap_list(&temp_t1,&temp_t2);
                cInfo->flag = 1;
                break;
            }
            else if(temp_h1->data > temp_h2->data)
                break;

            temp_h1 = temp_h1->next;
            temp_h2 = temp_h2->next;
        }
    }

    int borrow = 0;

    while(temp_t1 != NULL){
        if(temp_t2 == NULL){
            if(insert_at_first(res_head,res_tail,temp_t1->data) == FAILURE)
                return FAILURE;
        }
        else{
            if(temp_t1->data < temp_t2->data){
                temp_t1->data = temp_t1->data + 10;
                borrow = 1;
            }
            else
                borrow = 0;

            if(insert_at_first(res_head,res_tail,temp_t1->data - temp_t2->data) == FAILURE)
                return FAILURE;

            temp_t2 = temp_t2->prev;
        }

        if(borrow)
            if(temp_t1->prev != NULL)
                temp_t1->prev->data--;
        
        temp_t1 = temp_t1->prev;
    }

    if(cInfo->flag){
        Ilist *first_data = *res_head;

        while(first_data != NULL){
            if(first_data->data != 0){
                first_data->data = -1 * first_data->data;
                break;
            }
            first_data = first_data->next;
        }
    }
    
    if(flag){
        printf("The result of subtraction of 2 operands is : ");
        print_list(*res_head);
    }

    return SUCCESS;
}

Status perform_multiplication(Ilist **tail1,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo){
    Ilist *temp1 = *tail1, *temp2 = *tail2;
    Ilist *temp = temp1;

    if(cInfo->count_list1 < cInfo->count_list2){
        swap_list(&temp1,&temp2);
        temp = temp1;
    }

    Ilist *list_h1 = NULL;
    Ilist *list_t1 = NULL;

    Ilist *list_h2 = NULL;
    Ilist *list_t2 = NULL;

    int mul, carry = 0, i = 0;

    while(temp2 != NULL){
        temp1 = temp;
        while(temp1 != NULL){
            mul = temp1->data * temp2->data;
            insert_at_first(&list_h2,&list_t2,mul%10 + carry);
            carry = (mul > 9)? mul/10 : 0;
            temp1 = temp1->prev;
        }
        if(carry)
            insert_at_first(&list_h2,&list_t2,carry);
        if(perform_addition(&list_t1,&list_t2,res_head,res_tail,cInfo,0) == FAILURE)
            return FAILURE;

        temp2 = temp2->prev;

        if(temp2 == NULL){
            printf("The result of multiplication of 2 operands is : ");
            print_list(*res_head);
            break;
        }

        list_h1 = *res_head;
        list_t1 = *res_tail;

        list_h2 = NULL;
        list_t2 = NULL;
        *res_head = NULL;
        *res_tail = NULL;
        i++;
        for(int j = 0;j < i;j++)
            insert_at_first(&list_h2,&list_t2,0);
    }

    return SUCCESS;
}

Status perform_division(Ilist **head1,Ilist **tail1,Ilist **head2,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo){
    
    Ilist *list_h1 = *head2;
    Ilist *list_t1 = *tail2;

    Ilist *list_h2 = *head2;
    Ilist *list_t2 = *tail2;

    Ilist *div_h = NULL;
    Ilist *div_t = NULL;

    Ilist *rem_h = NULL;
    Ilist *rem_t = NULL;

    cInfo->call_count = 0;
 
    while(list_comparison(head1,&list_h1,cInfo) == SUCCESS){
        perform_addition(&list_t1,&list_t2,res_head,res_tail,cInfo,0);
        list_h1 = *res_head;
        list_t1 = *res_tail;
        
        //print_list(list_h1);

        *res_head = NULL;
        *res_tail = NULL;
    }
    //printf("%d\n",cInfo->call_count);
    if(cInfo->call_count == 0)
        insert_at_first(&div_h,&div_t,cInfo->call_count);
    else{
        while(cInfo->call_count != 0){
            insert_at_first(&div_h,&div_t,cInfo->call_count % 10);
            cInfo->call_count /= 10;
        }
    }
    printf("The result of division of 2 operands : ");
    print_list(div_h);
    perform_multiplication(&div_t,tail2,res_head,res_tail,cInfo);
    perform_subtraction(head1,tail1,res_head,res_tail,&rem_h,&rem_t,cInfo,0);

    printf("The remainder is : ");
    print_list(rem_h);
    
    if(rem_h->data < 0){
        rem_h = *head1;
        rem_t = *tail1;
    }
    printf("The remainder is : ");
    print_list(rem_h);

    return SUCCESS;
}
