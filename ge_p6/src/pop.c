/*
 * pop.c
 *
 *  Created on: 2021/05/27
 *      Author: kador
 */
#include <stdio.h>
#include "stack.h"

int pop(struct stack *five){
    five->head--;//スタックの先頭のインデックスを変更
    printf("スタック[%d]の%lldをpop\n",five->head,five->value[five->head]);//スタック先頭の数値を格納
    return five->value[five->head];//スタック先頭の数値を格納
}

