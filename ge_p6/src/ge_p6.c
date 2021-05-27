#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "constant.h"
#include "stack.h"


extern void push(long long num,struct stack *five);//スタックに数値を格納
extern int pop(struct stack *five);//スタックから数字を取出す
extern void stack_display(struct stack *five);//スタックの表示
extern void stack_init(struct stack *five);//スタックの初期化

int main(void){
    char inverse_poland[INPUT_BUF];//入力を受ける文字列
    long long int num;//一つ一つ数字を取り出すときに使用
    struct stack five;//スタック数5のスタック。
    char *tmp;//文字を分けるのに使用
    char *endp;//数字に正しく変換できた　変換できなかった場合０が入る
    int char_count;//文字列のカウント
    long long int num_tmp1;//一時的な数宇の保管場所
    long long int num_tmp2;

	stack_init(&five);
	while(1) {

		//初期化
		char_count=0;
		//スタックの表示
		stack_display(&five);

		printf("式を入力してください。:");
		fflush(stdout);
		//式の入力
		fflush(0);
		fgets(inverse_poland,sizeof(inverse_poland),stdin) ;
		//printf("文字数:%lu\n",(long unsigned int)strlen(inverse_poland));
		if(strlen(inverse_poland)==1){
			printf("不正な入力です\n");
			printf("スタックを初期化します\n");
			stack_init(&five);
			continue;
		}
		fflush(stdout);
		inverse_poland[strlen(inverse_poland)-1]='\0';
		while(1){
			//文字列からの取り出し
			if(char_count==0){
				tmp = strtok(inverse_poland," "); //文字列の1つ目の取り出しの場合
				char_count=1;
				if(strcmp(tmp,"END")==0){
					printf("ゲームを終了します\n");
					fflush(stdout);
					return 0 ;
				}else if(strcmp(tmp,"C")==0){
					printf("Cを入力されたのでスタックを初期化します\n");
					fflush(stdin);
					stack_init(&five);
					continue;
				}else{
					//printf("ENDではない。\n");

				}
				if(tmp==NULL){
					//printf("end\n");//式の終端にいった場合
					break;
				}
			}
			else{
				tmp = strtok(NULL," ");//文字列の2つ目以降
				if(tmp==NULL){
					//printf("end\n");//式の終端にいった場合
					break;
				}
			}

			//数値変換
			num=strtoll(tmp,&endp,10);
			//if(num<LLONG_MIN||LLONG_MAX<num){
			if(errno==ERANGE){
				printf("数値が許容範囲を超えています。\n");
				printf("スタックを初期化します\n");
				stack_init(&five);
				break;
			}else{
				//printf("正常な数値です。\n");
			}



			//文字列を数字に変換
			//printf("tmpの状態：%s 変換後：%d \n",tmp,(int)num);//文字列を数値変換


			//数字か判断
			puts(endp);
			if(*endp==0){
				printf("数値変換\n");
				if(five.head<5){
					push(num,&five);
				}else{
					printf("スタックオーバーです。\n");
					printf("スタックを初期化します\n");
					stack_init(&five);
					break;
				}
				fflush(stdout);
			}else{
				printf("文字が混入\n");
				printf("文字数：%lu\n",(long unsigned int)strlen(tmp));
				if(strlen(tmp)==1){
					//スタックが2以上あるか確認
					if(five.head<2){
						printf("スタックが足りません\n");
						break;
					}else{
						//printf("スタックが足りています。\n");
					}

					if(*tmp=='+'){
						printf("足し算します。\n");
						num_tmp1=pop(&five);
						num_tmp2=pop(&five);
						if(num_tmp1>LLONG_MAX-num_tmp2||num_tmp1>LLONG_MIN-num_tmp2){
							printf("計算がオーバーフローします。\n");
							printf("スタックを初期化します\n");
							stack_init(&five);
							break;
						}else{
							//printf("正常な計算結果です。\n");
						}
						push(num_tmp1+num_tmp2,&five);
					}else if(*tmp=='-'){
						printf("引き算します。\n");
						num_tmp1=pop(&five);
						num_tmp2=pop(&five);
						if(num_tmp2<LLONG_MIN-num_tmp1||num_tmp2<LLONG_MAX-num_tmp1){
							printf("計算がオーバーフローします。\n");
							printf("スタックを初期化します\n");
							stack_init(&five);
							break;
						}else{
							//printf("正常な計算結果です\n");
						}

						push(num_tmp1-num_tmp2,&five);
					}else if(*tmp=='*'){
						printf("掛け算します。\n");
						num_tmp1=pop(&five);
						num_tmp2=pop(&five);
						if(num_tmp1>LLONG_MAX/num_tmp2||num_tmp1>LLONG_MIN/num_tmp2){
							printf("計算がオーバーフローします。\n");
							printf("スタックを初期化します\n");
							stack_init(&five);
							break;
						}

						push(num_tmp1*num_tmp2,&five);
					}else if(*tmp=='/'){
						printf("割り算します。\n");
						num_tmp1=pop(&five);
						num_tmp2=pop(&five);
						if(num_tmp1==0||num_tmp2==0){
							printf("0での除算はできません。\n");
							printf("スタックを初期化します\n");
							stack_init(&five);
							break;
						}
						push((double)num_tmp1/(double)num_tmp2+0.5,&five);
					}else{
						printf("不正な入力です\n");
						printf("スタックを初期化します\n");
						stack_init(&five);
						break;
					}
				}else{
					printf("不正な入力です。\n");
					printf("スタックを初期化します\n");
					stack_init(&five);
				}
			}
			puts("ループを抜けました");
			fflush(stdout);
			fflush(stdin);
		}
		//puts("1ループを抜けました");
		fflush(stdout);
	}
}
