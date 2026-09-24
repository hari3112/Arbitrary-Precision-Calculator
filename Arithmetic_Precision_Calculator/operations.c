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

    while(temp1 != NULL){
        count++;
        temp1 = temp1->next;
    }
    temp1 = *head1;

    if(count < cInfo->count_list2)
        return FAILURE;
    else if(count > cInfo->count_list2)
        return SUCCESS;
    else{
        while(temp1 != NULL && temp2 != NULL){
            if(temp1->data > temp2->data)
                return SUCCESS;
            else if(temp1->data < temp2->data){
                return FAILURE;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    return SUCCESS;
}

Ilist* reverse_list(Ilist *head){
    Ilist *nextnode = head, *currentnode = head, *prev = NULL;

    while(nextnode != NULL){
        nextnode = nextnode->next;
        currentnode->next = prev;
        prev = currentnode;
        currentnode = nextnode;
    }

    return prev;

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

    while(head1 && head1->data == 0){
        head1 = head1->next;
        cInfo->count_list1--;
    }

    while(head2 && head2->data == 0){
        head2 = head2->next;
        cInfo->count_list2--;
    }

    print_list(head1);
    print_list(head2);

    if(cInfo->operator_name == '+')
        perform_addition(&tail1,&tail2,&res_head,&res_tail,cInfo,1);
    else if(cInfo->operator_name == '-')
        perform_subtraction(&head1,&tail1,&head2,&tail2,&res_head,&res_tail,cInfo,1);
    else if(cInfo->operator_name == 'x')
        perform_multiplication(&tail1,&tail2,&res_head,&res_tail,cInfo,1);
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

    Ilist *temp1 = *head1,*temp2 = *head2;
    Ilist *list_h1 = NULL,*list_h2 = NULL;
    cInfo->flag = 0;

    if(temp1 == NULL && temp2 == NULL){
        insert_at_first(res_head,res_tail,0);
        return SUCCESS;
    }

    list_h1 = temp1;
    list_h2 = temp2;

    if(cInfo->count_list1 < cInfo->count_list2){
        swap_list(&list_h1,&list_h2);
        cInfo->flag = 1;
    }
    else if(cInfo->count_list1 == cInfo->count_list2){
        while(temp1 != NULL && temp2 != NULL){
            if(temp1->data > temp2->data)
                break;
            else if(temp1->data < temp2->data){
                swap_list(&list_h1,&list_h2);
                cInfo->flag = 1;
                break;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    list_h1 = reverse_list(list_h1);
    list_h2 = reverse_list(list_h2);

    while(list_h1 != NULL){
        int small = 0;
        if(list_h2 != NULL){
            if(list_h1->data < list_h2->data){
                list_h1->data = list_h1->data + 10;
                list_h1->next->data--;
            }
            insert_at_first(res_head,res_tail,list_h1->data - list_h2->data);
        }
        else{
            if(list_h1->data < small){
                list_h1->data = list_h1->data + 10;
                list_h1->next->data--;
            }
            insert_at_first(res_head,res_tail,list_h1->data);
        }
        list_h1 = list_h1->next;

        if(list_h2 != NULL)
            list_h2 = list_h2->next;
    }

    while ((*res_head)->data == 0 && (*res_head)->next != NULL)
        *res_head = (*res_head)->next;


    if(cInfo->flag){
        (*res_head)->data = -1*((*res_head)->data);
    }
    
    if(flag)
        print_list(*res_head);

    print_list(*head1);
    print_list(*head2);

    return SUCCESS;
}

Status perform_multiplication(Ilist **tail1,Ilist **tail2,Ilist **res_head,Ilist **res_tail,Calc *cInfo,int flag){
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

    int mul, carry, i = 0;

    while(temp2 != NULL){
        temp1 = temp;
        carry = 0;
        while(temp1 != NULL){
            mul = temp1->data * temp2->data;
            insert_at_first(&list_h2,&list_t2,(mul % 10 + carry)%10);
            carry = ((mul + carry) > 9)? (mul + carry)/10 : 0;
            temp1 = temp1->prev;
        }
        if(carry)
            insert_at_first(&list_h2,&list_t2,carry);
        if(perform_addition(&list_t1,&list_t2,res_head,res_tail,cInfo,0) == FAILURE)
            return FAILURE;

        temp2 = temp2->prev;

        if(temp2 == NULL){
            if(flag){
                printf("The result of multiplication of 2 operands is : ");
                print_list(*res_head);
            }
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

    if(*head2 == NULL){
        printf("ERROR : Can't divisible by zero\n");
        return FAILURE;
    }

    Ilist *temp1_h = *head1, *temp2_h = *head2;
    Ilist *temp1_t = *tail1, *temp2_t = *tail2;

    Ilist *rem_h = NULL, *rem_t = NULL;
    Ilist *res_h = NULL, *res_t = NULL;

    while(temp1_h != NULL){
        cInfo->call_count = 0;
        printf("Check\n");
        insert_at_last(&rem_h,&rem_t,temp1_h->data);
        while(list_comparison(&rem_h,&temp2_h,cInfo) == SUCCESS){
            perform_subtraction(&rem_h,&rem_t,&temp2_h,&temp2_t,res_head,res_tail,cInfo,0);
            
            rem_h = *res_head;
            rem_t = *res_tail;

            *res_head = NULL;
            *res_tail = NULL;

            cInfo->call_count++;
        }
        insert_at_last(&res_h,&res_t,cInfo->call_count);

        temp1_h = temp1_h->next;
    }

    printf("Dividen : ");
    print_list(res_h);
    printf("\nRemainde : ");
    print_list(rem_h);     

    return SUCCESS;
}
