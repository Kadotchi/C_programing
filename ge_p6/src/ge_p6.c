#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <math.h>



#define STACK_SIZE 5 //スタックのサイズ
#define INPUT_BUF 50 //入力のバッファの数値


struct stack{
    long long value[STACK_SIZE];//スタック数値を格納
    int head;//スタックに格納されている先頭のインデックス
    int flag_stack_over;//スタックがサイズを超えたらフラグ
};

void push(long long num,struct stack *five);//スタックに数値を格納
int pop(struct stack *five);//スタックから数字を取出す
void stack_display(struct stack *five);//スタックの表示
void stack_init(struct stack *five);//スタックの初期化

int main(void){
    char inverse_poland[INPUT_BUF];//入力を受ける文字列
    long long num;//一つ一つ数字を取り出すときに使用
    struct stack five;//スタック数5のスタック。
    char *tmp;//文字を分けるのに使用
    char *endp;//数字に正しく変換できた　変換できなかった場合０が入る
    int char_count;//文字列のカウント
    long long num_tmp;



	while(1) {

			//初期化
			char_count=0;
			stack_init(&five);
			stack_display(&five);

			printf("式を入力してください:");
			fflush(stdout);
			//式の入力
			fgets(inverse_poland,INPUT_BUF,stdin) ;
			//printf("文字数：%lu\n",strlen(inverse_poland));
			inverse_poland[strlen(inverse_poland)-1]='\0';
		while(tmp!=NULL){
			//文字列からの取り出し
			if(char_count==0){
				tmp = strtok(inverse_poland," "); //文字列の1つ目の取り出しの場合
				char_count=1;
				if(strcmp(tmp,"END")==0){
					printf("ゲームを終了します\n");
					fflush(stdout);
					return 0 ;
				}else{
					printf("ENDではない。\n");
				}
			}
			else{
				tmp = strtok(NULL," ");//文字列の2つ目以降
			}

			//数値変換
			num=strtoll(tmp,&endp,10);

			//文字列を数字に変換
			printf("tmpの状態：%s 変換後：%lld \n",tmp,num);//文字列を数値変換


			//数字か判断
			puts(endp);
			if(*endp==0){
				printf("数値変換\n");
				if(num<=LLONG_MIN||LLONG_MAX<=num){
					printf("数値が許容範囲を超えています。\n");
					break;
				}else{
					printf("正常な数値です。\n");
				}
				push(num,&five);

			}else{
				printf("文字が混入\n");
				printf("文字数：%lu\n",strlen(tmp));
				if(strlen(tmp)==1){
					//スタックが2以上あるか確認
					if(five.head<2){
						printf("スタックが足りません\n");
						break;
					}else{
						printf("スタックが足りています。\n");
					}

					if(*tmp=='+'){
						printf("足し算します。\n");
						num_tmp=pop(&five);
						push(num_tmp+pop(&five),&five);
					}else if(*tmp=='-'){
						printf("引き算します。'\n");
						num_tmp=pop(&five);
						push(num_tmp-pop(&five),&five);
					}else if(*tmp=='*'){
						printf("掛け算します。\n");
						num_tmp=pop(&five);
						push(num_tmp*pop(&five),&five);
					}else if(*tmp=='/'){
						printf("割り算します。\n");
						num_tmp=pop(&five);
						push(num_tmp/pop(&five),&five);
					}else{
						printf("不正な入力です\n");
					}
				}else
					printf("不正な入力です。\n");
			}
			puts("ループを抜けました");
			fflush(stdout);
			fflush(stdin);
		}
		puts("1ループを抜けました");
		fflush(stdout);
		fflush(stdin);
	}
	puts("2ループを抜けました");
	fflush(stdout);
	fflush(stdin);

}

void push(long long num,struct stack *five){
    // if(five->head==STACK_SIZE){
    //     five->frag_stack_over=0;//スタックがサイズを超えるためフラグに０を格納
    //     exit;
    // }
	if(num<=LLONG_MIN||LLONG_MAX<=num){
		printf("数値が許容範囲を超えています。\n");
		five->flag_stack_over=0;//スタックがサイズを超えるためフラグに０を格納
		exit (EXIT_SUCCESS);
	}else{
		printf("正常な数値です。\n");
	}
    five->value[five->head]=num;
    printf("スタック[%d]に%lldをpush\n",five->head,five->value[five->head]);
    five->head++;
}

int pop(struct stack *five){
    five->head--;//スタックの先頭のインデックスを変更
    printf("スタック[%d]の%lldをpop\n",five->head,five->value[five->head]);//スタック先頭の数値を格納
    return five->value[five->head];//スタック先頭の数値を格納
}

void stack_display(struct stack *five){
	int i;
	for(i=0;i<STACK_SIZE;i++){
		printf("stack[%d]:%lld\n",i,five->value[i]);
	}
}

void stack_init(struct stack *five){
	int i;
	five->head=0;
	five->flag_stack_over=1;
	for(i=0;i<STACK_SIZE;i++){
		five->value[i]=0;
	}
}
