#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define S 100//速度の初期値
#define D 500//距離の初期値
#define BMAX 10//ブレーキの最大値
#define BUF 10//入力のバッファ
#define C 3.6//時速から秒速に変化するときに使用
#define SC 5//表示の際の倍率

void display(int speed,int distance,int breaks);//表示
int speed_find(int speed,int breaks);//速度を求める
int distance_find(int first_speed,int end_speed,int distance);//距離を求める
int breaks_find(int breaks);//ブレーキの操作
void display_end(int time,int distance);//ゲーム終了時の表示
int Input_Rece(int max_num,int min_num,int digit);//数値の入力
int game_continue();//ゲームを続けるかの選択
int Input_Rece_0(int max_num,int min_num,int digit);//数値の入力
int ave_speed(int speed,int next_speed);//平均速度の計算
void Rule();//ルール説明


int main(void){
    int speed;//速度
    int after_speed;//ブレーキを踏む前にスピード
    int distance;//距離
    int breaks;//ブレーキ
    int seconds;//時間
    int f_end;//ループ判定

	Rule();//ルール説明

    do{
        /* 値の初期化 */
        speed=S;
        distance=D;
        breaks=0;
        seconds=0;
        // display(speed,distance,breaks);
        do{
            display(speed,distance,breaks);//表示
            breaks += breaks_find(breaks);//ブレーキの操作
            after_speed=speed;//ブレーキを踏む前のスピード
            speed = speed_find(speed,breaks);//速度の計算
            distance = distance_find(after_speed,speed,distance);//距離の計算
            seconds++;//時間を進める
            if(distance<-10) break;//駅を通り越した
        }while (0<speed);
        printf("ループを抜けました。");
        fflush(stdout);
        display(speed,distance,breaks);//表示
        display_end(seconds,distance);//ゲーム終了の表示
        f_end=game_continue();//ゲームを続けるかどうか
    }while(f_end);
    printf("ゲーム終了\n");
}

void display(int speed,int distance,int breaks){//表示
    int i;//ループ制御
    int train;
    train=distance/SC;
    if(speed==0||distance<-10){
        printf("[停止中]\n");
    }else printf("[走行中]\n");
    printf("|");
    if(distance<=0){
    	printf("□□");
    	for(i=0;i<D/SC;i++){
    	        printf("_");
    	    }
    }else{
		for(i=0;i<D/SC;i++){
			if(i==train){
				printf("□□□");
				i += 2;
			}else printf("_");
		}
    }
    printf("\n速度：%dkm/h 距離：%dm ブレーキ：%d (max%d)\n",speed,distance,breaks,BMAX);
}

int breaks_find(int breaks){//ブレーキの操作
    int flag;//ブレーキをどうするの判断；
    printf("2:強く　1:弱く　0:そのまま\n");
    flag=Input_Rece_0(2,0,1);//数値の入力
    if(flag==2){
        if(breaks==BMAX) return 0; //ブレーキがMAXだった場合強くできない
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

int distance_find(int first_speed,int end_speed ,int distance){//距離を求める
	int a_speed;//加速度
	int next_distance;
	a_speed=end_speed-first_speed;//加速度の計算
	next_distance=distance-(first_speed/C+a_speed/2/C);
	return next_distance;
}


void display_end(int time,int distance){//ゲーム終了時の表示
    printf("%d 秒　駅まで%dmで停止しました。\n",time,distance);
}
int Input_Rece(int max_num,int min_num,int digit){//数値の入力
	char str[BUF];    //入力バッファ
	int i;            //ループカウンタ
	int flag;    //繰り返しカウンタ
	int len;          //入力データサイズ
	int num;          //入力された数値

	while (1) {
		flag = 0; //フラグの初期化
		printf("\n0から%dまでの数字を入力してください。：", max_num);
		fflush(stdout);
		fgets(str, sizeof(str), stdin); //ユーザからの入力受付
		len = strlen(str); //データサイズ取得
		str[BUF - 2] = '\n';
		str[BUF - 1] = '\0';
        if(len<BUF){
            str[len + 1] = '\n';
		    str[len] = '\0';
        }

		if (digit + 1 < len) {
			printf(">>ERROR:%d桁を超えています。もう一度入力してください。\n", digit);
			fflush(stdout);
			continue;
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
    flag=Input_Rece(2,1,1);//数値の入力
    if(flag==2) return 1;
    else return 0;
}

/* 不正な入力は0を返すように変更 */
int Input_Rece_0(int max_num,int min_num,int digit){//数値の入力
	char str[BUF];    //入力バッファ
	int i;            //ループカウンタ
	int flag;    //繰り返しカウンタ
	int len;          //入力データサイズ
	int num;          //入力された数値

	while (1) {
		flag = 0; //フラグの初期化
		// printf("\n0から%dまでの数字を入力してください。：", max_num);
		fflush(stdout);
		fgets(str, sizeof(str), stdin); //ユーザからの入力受付
		len = strlen(str); //データサイズ取得
		str[BUF - 2] = '\n';
		str[BUF - 1] = '\0';
        if(len<BUF){
            str[len + 1] = '\n';
		    str[len] = '\0';
        }

		if (digit + 1 < len) {
			printf(">>ERROR:%d桁を超えています。もう一度入力してください。\n", digit);
			fflush(stdout);
            return 0;
			// continue;
		}

		//入力の数値に文字が入力されてた場合
		for (i = 0; i < len-1; i++) //データサイズ文取得
				{
			if (!isdigit(str[i])) {
				printf(">>ERROR:入力に文字が含まれています。もう一度入力してください。\n");
				fflush(stdout);
                return 0;
				// flag = 1;
				// break;
			}
		}
		if (flag)
			continue;

		/*入力された文字列を数列に代入*/
		num = atoi(&str[0]);
		fflush(stdout);

        if(num>max_num){
            printf(">>ERROR:上限を超えています。\n");
            return 0;
            // continue;
        }

        if(num<min_num){
            printf(">>ERROR:%dより大きい数値を入力してください。\n",min_num);
            return 0;
            // continue;
        }

		if (flag)
			continue;
		break;
	}
    return num;
	puts(str);
	fflush(stdout);

}

void Rule() {
	FILE *fp;
	char str[256];
	fp = fopen("Rule_explanation_p4.txt", "r");

	while (!feof(fp)) {
		fgets(str, 256, fp);
		printf("%s", str);
	}
	fclose(fp);
	printf("\n");
}

//平均速度の計算
int ave_speed(int speed,int next_speed){
	int sum;
	int after_time,next_time;
	sum=speed*next_speed;
	after_time = sum /speed;
	next_time = sum/next_speed;

	return (sum*2)/(after_time+next_time);

}
