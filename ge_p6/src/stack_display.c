/*
 * stack_display.c
 *
 *  Created on: 2021/05/27
 *      Author: kador
 */
#include <stdio.h>
#include "stack.h"


void stack_display(struct stack *five){
	int i;
	for(i=0;i<five->head;i++){
		printf("stack[%d]:%lld\n",i,five->value[i]);
	}
}
