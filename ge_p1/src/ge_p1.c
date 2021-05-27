#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define CRANGE 100//有効数字の範囲
#define BUF 10//バッファーの数

int User_Number,Correct_Number,Count,Range;//ユーザーからの入力数字、CPの数字、カウント、範囲

void Description();//問題の説明
void Init(int *correct,int *c);//初期化
void InNumber(int *user,int *range);//ユーザーからの数字の入力。
void NumberCheck(int *user,int *correct,int *count,int *range);//数字の判定
void Continue(char *ustr);


int main(void) {

	int User_Number=CRANGE+1;//正解外を初期値として入れる。;//ユーザーからの入力数字
	int Correct_Number;//CPの数字
	int Count;//カウント
	int Range;//範囲

	char Ustr[5]="Yes";//ゲームを続けるかの入力対象
	char Astr[5]="Yes";//ゲームを続けるための比較対象

	Description();//問題の説明
	while (strcmp(Ustr,Astr)==0){

		Init(&Correct_Number,&Count);//初期化
		printf("正解：%d\n",Correct_Number);
		fflush(stdout);

		while(User_Number!=Correct_Number){
			InNumber(&User_Number,&Range);//ユーザーからの数字の入力
			NumberCheck(&User_Number,&Correct_Number,&Count,&Range);//正解とユーザーからの数字の判定
			fflush(stdout);
		}
//	 Continue(&Ustr);
//	 fflush(stdout);
		printf("もう一度遊びますか？ Yes or No ?：");
		fflush(stdout);
		scanf("%s",Ustr);
		if(strcmp(Ustr,Astr)==0){
			printf("もう一度ゲーム開始\n");
		}
		fflush(stdin);
	}
	printf("終了");
	fflush(stdout);
	return EXIT_SUCCESS;
}
void Description(){//問題の説明
	printf("数字あてゲーム1\n");//タイトルコール
	printf("ルール\nルール以下に示します。\n・利用者はプログラムが作成した0～%dまでの数字を当てます。\n・正解でない場合はヒントを表示します。\n・ヒントは、入力者が入力した値が正解から1入力した範囲内にあるかです。\n",CRANGE);
	fflush(stdout);

}

void Init(int *correct,int *c){
	*c=0;//カウントの初期化
	*correct=rand() % CRANGE+1;//1から100の準備
}

void InNumber(int *user,int *range){

	int inuser,inrange,sw,sw2;
	char buf[BUF];

	do{
		printf("0から%dまでの数字を入力してください。：",CRANGE);
		fflush(stdout);
		fgets(buf,sizeof(buf),stdin);
		buf[BUF-2]='\n';
		buf[BUF-1]='\0';
		fflush(stdin);
		/*文字などの数値以外が入力された時*/
		if(sscanf(buf,"%d",&inuser)>0){
			//printf(">>%d/n",inuser);
			sw=1;
		}else {
			printf(">>ERROR:数値ではありません。もう一度入力してください。\n");
			fflush(stdout);
			sw=0;
		}

		*user=inuser;//入力された数値を代入

		/*有効数字以上の数字が入力された時*/
		if(*user<0||*user>CRANGE){
			sw2 = 0;
			printf("有効数字を超えています。もう一度入力してください。\n");
			fflush(stdout);
			}else{
				sw2=1;
		}

	}while(sw != 1||sw2!=1);

	do{
		printf("範囲を入力してください。：");
		fflush(stdout);
		fgets(buf,sizeof(buf),stdin);
		/*文字などの数値以外が入力された時*/
		if(sscanf(buf,"%d",&inrange)>0){
			sw=1;
		}else {
			printf(">>ERROR:数値ではありません。もう一度入力してください。\n");
			sw=0;
		}
		*range=inrange;
		if(*range<0||*range>CRANGE){
			sw2 = 0;
			printf("有効数字を超えています。もう一度入力してください。\n");
			fflush(stdout);
		}else{
			sw2=1;
		}
	}while(sw!=1||sw2 !=1);
}

void NumberCheck(int *user,int *correct,int *count,int *range){
//	printf("%d回目\n",*count);
	printf("結果の表示\n");
	if(*user==*correct){//正解の場合
		*count += 1;
		printf("おめでとうございます。%d回目での正解です！！\n",*count);
		return;
	}else if((*correct-*user)*(*correct-*user)<=(*range)*(*range)){//不正解だが範囲内
		printf("不正解です。入力値は範囲以内です。再度入力してください。\n");
		*count += 1;
		return;
	}else{//不正解で範囲外
		printf("不正解です。入力値は範囲外です。再度入力してください。\n");
		*count += 1;
		return;
	}
}

void Continue(char *ustr){
	char str[5];
	printf("もう一度遊びますか？ Yes or No ?：");
	fflush(stdout);
	scanf("%s",str);
	*ustr=*str;
}
