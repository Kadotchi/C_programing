/*
 * push.c
 *
 *  Created on: 2021/05/27
 *      Author: kador
 */
#include <stdio.h>
#include "stack.h"

void push(long long num,struct stack *five){
    // if(five->head==STACK_SIZE){
    //     five->frag_stack_over=0;//スタックがサイズを超えるためフラグに０を格納
    //     exit;
    // }
    five->value[five->head]=num;
    printf("スタック[%d]に%lldをpush\n",five->head,five->value[five->head]);
    five->head++;
}

