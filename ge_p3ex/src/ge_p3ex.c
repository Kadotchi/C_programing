#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <ctype.h>


#define T 52//トランプの枚数
#define V 13//トランプの強さ数
#define M 4 //トランプのマークの種類
#define MO 100//所持金
#define BUF 255//文字のバッファ


struct playing_cards{
	char mark[BUF];//マーク
	char num[BUF];//カードの表示数
	int value;//カードの強さ
	int next;//次のカードのインデックス番号
};

void card_deck(struct playing_cards *trump);//カードデッキの作成
int shuffle(struct playing_cards *trump);//デッキのシャッフルとデッキの先頭インデックス値を返す
int judgment(int *head,struct playing_cards *trump);//判定とデッキをめくる 勝てば真　負けは疑
void start_turn_display(int head,struct playing_cards *trump,int money);//ターンの始め
void midle_turn_display(int head,struct playing_cards *trump,int div);//ターン途中の表示
void end_turn_display(int div);//ターン終了時の配当金の表示
int Input_Rece(int max_num,int min_num);//数値の入力
int latch(int max_num);//掛け金入力
int div_math(int latch,int count);//配当金の計算
int up_down();//勝ちか負けか
int turn_deck(struct playing_cards *trump,int head);//デッキをめくる
int game_continue();//ゲーム続ける
int debug_mode();
void Rule();//ルール説明


int main(void){
	int head;//デッキの先頭のインデックス値
	struct playing_cards trump[T];//トランプの準備
	int money;//所持金
	int count;//勝利数をカウント
	int latch_money;//掛け金
	int div_money;//配当金
	int debug;//デバックモードに使用

	Rule();//ルールの説明
	card_deck(trump);//カードデッキの準備

	debug=debug_mode();//モードの選択

	do{
		/* 初期化 */
		money=MO;
		if(debug!=1) head=shuffle(trump);//デッキのシャッフル
		else head=10;
		do{
			div_money=0;//配当金の初期化
			count=0;//勝利数の初期化
			start_turn_display(head,trump,money);//ターン初回の表示
			latch_money=latch(money);//掛け金を入力
			while(1){

				if(up_down()){//賭け
					if(count==0){
						head=turn_deck(trump,head);//デッキをめくる
						midle_turn_display(head,trump,div_money);//ターンの途中表示
						continue;
					}else{
						div_money=div_math(latch_money,count);//配当金の計算
						money += div_money;//配当金獲得
						end_turn_display(div_money);
						break;
					}
				}else if(judgment(&head,trump)){//勝敗の判定
					if(count==0) money -= latch_money;//所持金から掛け金を引く
					count++;//勝利数のカウント
					div_money=div_math(latch_money,count);//配当金の計算
					midle_turn_display(head,trump,div_money);//ターンの途中表示
					continue;
				}else {
					if(count==0) money -= latch_money;//所持金から掛け金を引く
					break;
				}
			}


		}while(0<money && money<=MO);
		if(MO<money){
			printf("所持金が%dで$%dを超えました。\n",money,MO);
		}else{
			printf("所持金が0になりました。\n");
		}
	}while(game_continue());
	fflush(stdin);
}

/* トランプの準備 */
void card_deck(struct playing_cards *trump){
	int i,j;//ループ制御
//	int num[T];//トランプのネクストを与える時に使用
	char mark_dis[M][BUF]={"スペード","ハート","クラブ","ダイヤ"};
	char num_dis[V][3]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
	for(i=0;i<M;i++){
		for(j=0;j<V;j++){
			strcpy((trump+(i*V+j))->mark,mark_dis[i]);//マークの代入
			strcpy((trump+(i*V+j))->num,num_dis[j]);//カードの強さの代入
			(trump+(i*V+j))->value=j;//カードの強さの代入
			(trump+(i*V+j))->next=(i*V+j)+1;
			// printf("%sの%s:強さは%d次は%d\n",trump[i*V+j].mark,trump[i*V+j].num,trump[i*V+j].value,trump[i*V+j].next);
//			fflush(stdin);
		}
	}
//	(trump+(T-1))->next=NULL;
//	printf("%sの%s:強さは%d次は%d\n",trump[T-1].mark,trump[T-1].num,trump[T-1].value,trump[T-1].next);

}

/* ネクストにランダムに数字を格納 */
int shuffle(struct playing_cards *trump){
	int i,j,tmp,head;
	int num[T];
	/*数列の準備*/
	for(i=0;i<T-1;i++){
		num[i]=i;
//		printf("num[%d]:%d\n",i,num[i]);
	}
	/*0~52をランダムに並び替え*/
	for(i=0;i<T;i++){
		j=i+(rand()%(T-i));
		tmp=num[i];
		num[i]=num[j];
		num[j]=tmp;
		(trump+i)->next=num[i];
//		printf("num[%d]:%d\n",i,num[i]);
		// printf("trump[%d].next:%d\n",i,(trump+i)->next);
	}
	head=rand()%T-1;//デッキの初めのインデックス
	// printf("headは%d\n",head);
	return head;
}

/* 判定 */
int judgment(int *head,struct playing_cards *trump){
	while(1){
		if((trump+*head)->value==(trump+(trump+*head)->next)->value){
			*head=trump[*head].next;
			printf("次のカード；%sの%s\n",trump[*head].mark,trump[*head].num);
			printf("カードが同じ値だったのでもう一枚めくります。\n");
			continue;
		}else if((trump+*head)->value<(trump+(trump+*head)->next)->value){
			*head=trump[*head].next;
			printf("次のカード；%sの%s\n",trump[*head].mark,trump[*head].num);
			printf("勝ちました\n");
			return 1;
		}else if((trump+*head)->value>(trump+(trump+*head)->next)->value){
			*head=trump[*head].next;
			printf("次のカード；%sの%s\n",trump[*head].mark,trump[*head].num);
			printf("負けました\n");
			return 0;
		}
	}
	return 0;
}


void start_turn_display(int head,struct playing_cards *trump,int money){//ターンの始め
	printf("\nターン初回\n");
    printf("現在のカード:");
    printf("%sの%s\n",trump[head].mark,trump[head].num);
    printf("所持金:%d\n",money);
}

int latch(int max_num){
    int latch;
    printf("掛け金を入力してください：");
    latch=Input_Rece(max_num,0);
    return latch;
}

/* 配当金の計算 */
int div_math(int latch,int count){
	int div_money;
    div_money=latch*pow(2,count-1);
    return div_money;
}

/* 数値入力 */
int Input_Rece(int max_num,int min_num){//数値の入力
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
//		printf("入力された数値：%d\n", num);
		fflush(stdout);
        if(num>max_num){
            printf(">>ERROR:上限を超えています。\n");
            continue;
        }

        if(num<=min_num){
            printf(">>ERROR:%dより大きい数値を入力してください。\n",min_num);
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

/*賭け*/
int up_down(){
	int num;
	    printf("かけますか？=1:おりますか？=2:");
	    num=Input_Rece(2,0);
	    if(num==1){
	        return 0;
	    }else {
	        return 1;
	    }
}

/*デッキをめくる*/
int turn_deck(struct playing_cards *trump,int head){
	return (trump+head)->next;
}

/*ターン途中の表示*/
void midle_turn_display(int head,struct playing_cards *trump,int div){
	    printf("現在のカード：");
	    printf("%sの%s\n",trump[head].mark,trump[head].num);
		printf("配当金：%d\n",div);
	    fflush(stdout);
}

int game_continue(){
    int flag;
    printf("ゲームを続けますか？\nはい：1 いいえ：2");
    flag=Input_Rece(2,0);//数値の入力
    if(flag==1) return 1;
    else return 0;
}

/*ターン終了の表示*/
void end_turn_display(int div){
	printf("\nターン終了\n");
	    printf("配当金：%d\n",div);
}

int debug_mode(){
	int mode;
	printf("2:ゲーム開始　1:デバックモード");
	mode = Input_Rece(2,0);
	 return mode;
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

