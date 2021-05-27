/*
 * stack_init.c
 *
 *  Created on: 2021/05/27
 *      Author: kador
 */
#include <stdio.h>
#include "constant.h"
#include "stack.h"


void stack_init(struct stack *five){
	int i;
	five->head=0;
	five->flag_stack_over=1;
	for(i=0;i<STACK_SIZE;i++){
		five->value[i]=0;
	}
}
