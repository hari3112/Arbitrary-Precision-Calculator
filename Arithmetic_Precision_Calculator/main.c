#include<stdio.h>
#include "types.h"
#include "operations.h"

int main(int argc, char *argv[]){
    if(argc == 4){
        Calc C1;
        printf("Info : required number of arguments satisfied\n");
        if(validate_operands(argv) == SUCCESS){
            printf("Info : The operands are numericals\n");
            if(validate_operator(argv[2],&C1) == SUCCESS){
                printf("Info : The operator is valid\n");
                if(create_list(argv,&C1) == SUCCESS){
                    printf("Info : List creation is successful\n");
                }
                else{
                    printf("Error : List creation failed\n");
                }
            }
            else{
                printf("Error : The operator is not valid\n");
            }
        }
        else{
            printf("Error : The operands are not numericals\n");
        }
    }
    else{
        printf("Error : exactly 4 arguments are required\n");
        printf("%d \n",argc);
    }
}