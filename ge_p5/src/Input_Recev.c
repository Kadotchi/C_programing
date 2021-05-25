#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constant.h"


int Input_Rece(int max_num,int min_num,int mode){//数値の入力 modeが0の時は不正な入力は0を返す
	char str[BUF];    //入力バッファ
	int i;            //ループカウンタ
	int flag;    //繰り返しカウンタ
	int len;          //入力データサイズ
	int num;          //入力された数値

	while (1) {
		flag = 0; //フラグの初期化
//		printf("\n0から%dまでの数字を入力してください。：", max_num);
		fflush(stdout);
		fgets(str, sizeof(str), stdin); //ユーザからの入力受付
		len = strlen(str); //データサイズ取得
		str[BUF - 2] = '\n';
		str[BUF - 1] = '\0';
        if(len<BUF){
            str[len + 1] = '\n';
		    str[len] = '\0';
        }

		//入力の数値に文字が入力されてた場合
		for (i = 0; i < len-1; i++) //データサイズ文取得
				{
			if (!isdigit(str[i])) {
				if(mode){
				printf(">>ERROR:入力に文字が含まれています。もう一度入力してください。\n");
				fflush(stdout);
				flag = 1;
				break;
				}else return 0;
			}
		}
		if (flag)
			continue;

		/*入力された文字列を数列に代入*/
		num = atoi(&str[0]);
//		printf("入力された数値：%d\n", num);
		fflush(stdout);
        if(num>max_num){
        	if(mode){
            printf(">>ERROR:上限を超えています。\n");
            continue;
        	}else return 0;
        }

        if(num<min_num){
        	if(mode){
            printf(">>ERROR:%dより大きい数値を入力してください。\n",min_num);
            continue;
        	}else return 0;
        }
		if (flag)
			continue;
		break;
	}
    return num;
	puts(str);
	fflush(stdout);

}
