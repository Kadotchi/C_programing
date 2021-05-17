#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define T 13 //トランプの強さの数
#define M 1000//初期所持金
#define BUF 10//入力のバッファ

int cpu();//cpuの出力
void start_turn(int number,int money);//ターンの始め
void middle_turn(int number,int div_money,int count);//ターンの途中
void end_turn(int latch_money);//ターンを降りたとき
void card_display(int num);//カードの表示
int latch(int max_num);//掛け金入力
void up_down(int *flag);//勝ちか負けか
int div_math(int latch,int count);//配当金の計算
int judgment(int *number);//判定
int Input_Rece(int max_num);//数値の入力
int game_continue();
void Rule();//ルール説明


int main(void){
    int now_card;//現在場にあるカード
    int money_in_poss;//所持金
    int div;//配当金
    int flag;//勝ちか負けかを判断
    int latch_money;//掛け金の入力
    int count;//勝った回数
    int first_latch_money;

    Rule();//ルール説明

    do{
		//初期化
		now_card=0;//現在場にあるカード
		latch_money=0;//掛け金の入力
		first_latch_money=0;//最初の掛け金
		money_in_poss=M;//所持金の初期化
		flag=1;//勝ちか負けかを判断
        do{//所持金がなくなるか、$1000を超えたゲーム終了。
            count=0;//勝った回数の初期化
            flag=1;//フラグの初期化
            now_card=cpu();//cpuのカード決定
            start_turn(now_card,money_in_poss);//ターン初回の表示
            latch_money=latch(money_in_poss);//掛け金の入力
            first_latch_money=latch_money;
            // Input_Rece(latch_money_addr,1);
            money_in_poss -= latch_money;//所持金から掛け金文を引く
            do{
            	if(count==0){

            	}else div=div_math(latch_money,count);//配当金の計算
                up_down(&flag);//どっちに掛けるか入力
                if(flag==0){//降りる場合、配当金をもらいターンをぬける
                	if(count==0){
                        printf("勝負数0なので掛け金を戻します。");
                        money_in_poss += first_latch_money;//所持金に配当金を入れる。
                        break;
                	}
                middle_turn(now_card,div,count);//現在のカードと配当金の表示
                    end_turn(div);//ターン終了時の表示
                    money_in_poss += div;//所持金に配当金を入れる。
                    break;
                }
                flag=judgment(&now_card);//判定の関数
                if(flag==0) break;//判定の結果負けていた場合ターンの終了
                count++;
            }while(flag);
        }while(0<money_in_poss && money_in_poss<=M);
        if(M<=money_in_poss){
            printf("所持金が$%dを超えました。\n",M);
        }else{
            printf("所持金が0になりました。\n");
        }
    }while(game_continue());
    printf("ゲーム終了");
    return 0;
}

/*cpuの数字決定*/
int cpu(){
    int card;
    card = rand()%T;
    //printf("%d\n",card);
    return card;
}

/*ターン初回*/
void start_turn(int number,int money){
    printf("\nターン初回\n");
    printf("現在のカード:");
    card_display(number);
    printf("所持金:%d\n",money);
}

//ターンの途中
void middle_turn(int number,int div_money,int count){
    printf("\nターン入力待ち\n");
    printf("現在のカード：");
    card_display(number);
    if(count==0){
    	printf("配当金：%d\n",0);
    }else printf("配当金：%d\n",div_money);
    fflush(stdout);
}

//ターン終了時
void end_turn(int latch_money){
    printf("\nターン終了時\n");
    printf("配当金：%d\n",latch_money);
}

//カードの表示
void card_display(int num){
    char card[T][3]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
    printf("%s\n",card[num]);
}

//掛け金の入力
int latch(int max_num){
    int latch;
    printf("掛け金を入力してください：");
    latch=Input_Rece(max_num);
    // scanf("%d",&latch);
    return latch;
}

//勝ちか負けか
void up_down(int *flag){
//    int up_down=0;
    int num;
    printf("かけますか？=1:おりますか？=2:");
    num=Input_Rece(2);
    if(num==1){
        *flag=1;
    }else {
        *flag=0;
    }
//    printf("flag:%d\n",*flag);
}

//配当金の計算
int div_math(int latch,int count){
    latch=latch*pow(2,count-1);
    return latch;
}

//判定
int judgment(int *number){
    int c;
    while(1){
    c=cpu();
    if(c==*number) continue;
    printf("次のカード:");
    card_display(c);
    if(c<*number){
        printf("負けました。\n");
        return 0;
    }
    else {
        *number=c;
        printf("勝ちました。\n");
        return 1;
    }
    }
}

//入力
int Input_Rece(int max_num) {
	char str[BUF];    //入力バッファ
	int i;            //ループカウンタ
	int flag;    //繰り返しカウンタ
	int len;          //入力データサイズ
	//int digit;        //数字変換
	int num;          //入力された数値

	while (1) {
		/*num_checkの初期化*/
		flag = 0; //フラグの初期化
		fflush(stdin);
		//printf("\n0から%dまでの数字を入力してください。：", max_num);
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
				printf(">>ERROR:入力に文字が含まれています。もう一度入力してください。\n");
				fflush(stdout);
				flag = 1;
				break;
			}
		}
		if (flag)
			continue;

		/*入力された文字列を数列に代入*/
		num = atoi(&str[0]);
		fflush(stdout);

        if(num>max_num){
            printf(">>ERROR:上限を超えています。\n");
            continue;
        }

        if(num==0){
            printf(">>ERROR:0より大きい数値を入力してください。\n");
            continue;
        }

		if (flag)
			continue;
		break;
	}
    return num;
	puts(str);
	fflush(stdout);
}

int game_continue(){
    int flag;
    printf("ゲームを続けますか？\nはい：1 いいえ：2");
    flag=Input_Rece(2);//数値の入力
    if(flag==1) return 1;
    else return 0;
}

void Rule() {
	FILE *fp;
	char str[256];
	fp = fopen("Rule_explanation_p3.txt", "r");

	while (!feof(fp)) {
		fgets(str, 256, fp);
		printf("%s", str);
	}
	fclose(fp);
	printf("\n");
}
