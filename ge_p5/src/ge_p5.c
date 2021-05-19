#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BUF 10//入力のバッファ
#define C 3.6//時速から秒速に変化するときに使用

/* 月面着陸ゲーム */
#define INITIAL_ALTITUDE 100//初期高度
#define HOLDING_FUEL 250//初期の燃料
#define MONTH_LANDING_SPEED 1.62//月の落下速度
#define LANDING_VALUE 0.1//１ユニット投下時の落下速度減少値
#define UNIT_MAXIMUM 50//１度にできるユニットの数
#define DISPLAY_MAFNIFICATION 1//表示の際の倍率
#define CLEAR_SPEED 1.0//クリア条件の落下速度

struct ship{
	double altitude;//高度
	double speed;//速度
	int holding_fuel;//保持燃料数
	int time;//着陸にかかった時間
	int f_landing;//着陸したかのフラグ
};

// void init();//初期化
void Rule();//ルール説明
int game_continue();//ゲームを続けるかの選択
int Input_Rece(int max_num,int min_num);//数値の入力
int Input_Rece_0(int max_num,int min_num);//数値の入力

/* 月面着陸ゲーム */
void month_display(struct ship *landing_ship);//表示
void landing(struct ship *landing_ship);//着陸船の操作


int main(void){
	struct ship landing_ship;//着陸船の準備

    /* 月面着陸ゲーム用 */
	Rule();//ルール説明


    /*月面着陸ゲーム  */
    do{
        /* 値の初期化 */
        landing_ship.speed=0;
        landing_ship.altitude=INITIAL_ALTITUDE;//高度の初期化
        landing_ship.time=0;//時間の初期化
        landing_ship.holding_fuel=HOLDING_FUEL;//保持燃料の初期化
        landing_ship.f_landing=1;//着陸フラグの初期化
        do{
            month_display(&landing_ship);//表示
            landing(&landing_ship);//着陸船の操作
        }while (landing_ship.f_landing);
        month_display(&landing_ship);//表示
    }while(game_continue());
}


int breaks_find(int breaks){//ブレーキの操作
    int flag;//ブレーキをどうするの判断；
    printf("2:強く　1:弱く　0:そのまま\n");
    flag=Input_Rece_0(2,0);//数値の入力
    if(flag==2){
        if(breaks==UNIT_MAXIMUM) return 0; //ブレーキがMAXだった場合強くできない
        /* ブレーキを強く */
        return 1;
    }else if(flag==1){
        if(breaks==0) return 0;//ブレーキが0だった場合弱くできない
        /* ブレーキを弱く */
        return -1;
    }else return 0;
}
int speed_find(int speed,int breaks){//速度を求める
    int next_speed;
    next_speed=speed-breaks;
    return next_speed;
}
int distance_find(int speed,int distance){//距離を求める
    int next_distance;
    next_distance=distance-(speed/C);
    return next_distance;
}


void display_end(int time,int distance){//ゲーム終了時の表示
    printf("%d 秒　駅まで%dmで停止しました。\n",time,distance);
}
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

        if(num<min_num){
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
int game_continue(){//ゲームを続けるかの選択
    int flag;
    printf("ゲームを続けますか？\n2:はい：1:いいえ");
    flag=Input_Rece(2,1);//数値の入力
    if(flag==2) return 1;
    else return 0;
}

/* 不正な入力は0を返すように変更 */
int Input_Rece_0(int max_num,int min_num){//数値の入力
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
				return 0;
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
            return 0;
        }

        if(num<min_num){
            printf(">>ERROR:%dより大きい数値を入力してください。\n",min_num);
            return 0;
        }
		if (flag)
			continue;
		break;
	}
    return num;
	puts(str);
	fflush(stdout);

}

void month_display(struct ship *landing_ship){//表示
//    int i;//ループ制御
//    int train;
//    train=distance/DISPLAY_MAFNIFICATION;
//    if(speed==0||distance<-10){
//        printf("[停止中]\n");
//    }else printf("[走行中]\n");
//    printf("|");
//    for(i=0;i<INITIAL_ALTITUDE/DISPLAY_MAFNIFICATION;i++){
//        if(i==train){
//            printf("□□□");
//            i += 2;
//        }else printf("_");
//    }
    printf("\n速度：%.2fm/s 現在の高度：%.2fm 残燃料：%d (max%d)\n",landing_ship->speed,landing_ship->altitude,landing_ship->holding_fuel,UNIT_MAXIMUM);
    //月面着陸していた場合
    if(landing_ship->f_landing==0){
    	if(landing_ship->speed<CLEAR_SPEED){
    		printf("月面着陸成功！！");
    	}else{
    		printf("月面着陸失敗");
    	}
    }
}

int month_speed_find(int speed,int breaks){//速度を求める
    int next_speed;
    next_speed=speed+MONTH_LANDING_SPEED-breaks*LANDING_VALUE;
    return next_speed;
}

void Rule() {
	FILE *fp;
	char str[256];
	fp = fopen("Rule_explanation_p5.txt", "r");

	while (!feof(fp)) {
		fgets(str, 256, fp);
		printf("%s", str);
	}
	fclose(fp);
	printf("\n");
}
//着陸船の操作
void landing(struct ship *landing_ship){
	int fuel;//燃料
	double before_speed;//速度が変化する前の速度
	double acceleration;//加速度

	//燃料の受付
	printf("投下する燃料を入力してください。:");
	fuel=Input_Rece_0(landing_ship->holding_fuel,0);
	//所持燃料から今回の燃料分を引く
	landing_ship->holding_fuel -= fuel;
	//変化前の速度を格納
	before_speed=landing_ship->speed;
	//速度の計算
	landing_ship->speed += MONTH_LANDING_SPEED-fuel;
	//加速度の計算
	acceleration=landing_ship->speed-before_speed;
	//高度の変化の計算
	landing_ship->altitude -=before_speed+acceleration/2;
	//着陸船の時間を進める
	landing_ship->time ++;
	//月面着陸した場合フラグを０にする
	if(landing_ship->altitude<=0){
		landing_ship->f_landing=0;
	}
}
