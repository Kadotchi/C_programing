/*
 * stack.h
 *
 *  Created on: 2021/05/27
 *      Author: kador
 */

#include "constant.h"

#ifndef STACK_H_
#define STACK_H_

struct stack{
    long long int value[STACK_SIZE];//スタック数値を格納
    int head;//スタックに格納されている先頭のインデックス
    int flag_stack_over;//スタックがサイズを超えたらフラグ
};


#endif /* STACK_H_ */
