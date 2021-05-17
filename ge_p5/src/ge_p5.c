#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* 電車でGO */
#define D 500//距離の初期値
#define BMAX 10//ブレーキの最大値
#define BUF 10//入力のバッファ
#define C 3.6//時速から秒速に変化するときに使用
#define SC 20//表示の際の倍率

/* 月面着陸ゲーム */
#define AL 100//初期高度
#define FU 250//初期の燃料
#define MS 1.62//月の落下速度
#define Y 0.1//１ユニット投下時の落下速度減少値
#define OY 50//１度にできるユニットの数
#define MSC 5//表示の際の倍率



// #define D 5    //桁の数
#define K 10   //1桁の数値の範囲

// void init();//初期化
void Rule();//ルール説明
void display(int speed,int distance,int breaks);//表示
int speed_find(int speed,int breaks);//速度を求める
int distance_find(int speed,int distance);//距離を求める
int breaks_find(int breaks);//ブレーキの操作
void display_end(int time,int distance);//ゲーム終了時の表示
int Input_Rece(int max_num,int min_num,int digit);//数値の入力
int game_continue();//ゲームを続けるかの選択
int Input_Rece_ver2(int max_num,int min_num,int digit);//数値の入力

/* 月面着陸ゲーム */
int month_speed_find(int speed,int breaks);//月面用の距離計算
int month_breaks_find(int breaks,int *fuel);//月面用の操作
void month_display(int speed,int distance,int breaks);//表示


int main(void){
    int speed;//速度
    int distance;//距離
    int breaks;//ブレーキ
    int seconds;//時間
    int flag;//ループ判定
    /* 月面着陸ゲーム用 */
    int fuel;//燃料
    int *fuel_addr;//燃料のアドレス

	Rule();//ルール説明


    /*月面着陸ゲーム  */
    do{
        /* 値の初期化 */
        speed=0;
        distance=AL;
        breaks=0;
        seconds=0;
        fuel=FU;
        fuel_addr=&fuel;

        // display(speed,distance,breaks);
        do{
            month_display(speed,distance,fuel);//表示
            breaks += month_breaks_find(breaks,fuel_addr);//ブレーキの操作
            speed = month_speed_find(speed,breaks);//速度の計算
            distance = distance_find(speed,distance);//距離の計算
            seconds++;//時間を進める
            if(distance<-10) break;//駅を通り越した
        }while (0<speed);
        month_display(speed,distance,fuel);//表示
        display_end(seconds,distance);//ゲーム終了の表示
        flag=game_continue();//ゲームを続けるかどうか
    }while(flag);


}

void display(int speed,int distance,int breaks){//表示
    int i;//ループ制御
    int train;
    train=distance/SC;
    if(speed==0||distance<-10){
        printf("[停止中]\n");
    }else printf("[走行中]\n");
    printf("|");
    for(i=0;i<D/SC;i++){
        if(i==train){
            printf("□□□");
            i += 2;
        }else printf("_");
    }
    printf("\n速度：%dkm/h 距離：%dm ブレーキ：%d (max%d)\n",speed,distance,breaks,BMAX);
}

int breaks_find(int breaks){//ブレーキの操作
    int flag;//ブレーキをどうするの判断；
    printf("2:強く　1:弱く　0:そのまま\n");
    flag=Input_Rece_ver2(2,0,1);//数値の入力
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
int distance_find(int speed,int distance){//距離を求める
    int next_distance;
    next_distance=distance-(speed/C);
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
	//int digit;        //数字変換
	int num_check[K]; //使われた数字の記憶
	int num;          //入力された数値
	int num_dis[digit];   //入力された数値を桁ごとに代入。
	int dis;          //桁ごとに数値を入れるときに使用

	while (1) {
		/*num_checkの初期化*/
		for (i = 0; i < K; i++) {
			num_check[i] = 0;
		}
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

		// for (i = 0; i < len; i++) {
		// 	printf("str[%d]:%c\n", i, str[i]);
		// 	fflush(stdout);
		// }

		if (digit + 1 < len) {
			printf(">>ERROR:%d桁を超えています。もう一度入力してください。\n", digit);
			fflush(stdout);
			continue;
		}
        // else if (len < digit + 1) {
		// 	printf(">>EROOR:%d桁に達していません。もう一度入力してください。\n", digit);
		// 	fflush(stdout);
		// 	continue;
		// }

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
		printf("入力された数値：%d\n", num);
		fflush(stdout);
		// for (i = 0; i < digit; i++) {
		// 	dis = pow(10, (digit - i - 1));
		// 	num_dis[i] = num / dis;
		// 	num = num % dis;
		// 	fflush(stdout);
		// }

		// if (num_dis[0] == 0) {
		// 	printf(">>ERROR:先頭の数字が０または文字になっています。\n");
		// 	fflush(stdout);
		// 	continue;
		// }

        if(num>max_num){
            printf(">>ERROR:上限を超えています。\n");
            continue;
        }

        if(num<min_num){
            printf(">>ERROR:%dより大きい数値を入力してください。\n",min_num);
            continue;
        }

		// for (i = 0; i < len - 1; i++) //データサイズ文取得
		// 		{
		// 	if (num_check[num_dis[i]] == 0) {
		// 		num_check[num_dis[i]] = 1;
		// 	} else {
		// 		printf(">>ERROR:同じ数字が2回以上使われています。もう一度入力してください。\n");
		// 		fflush(stdout);
		// 		flag = 1;
		// 		break;
		// 	}
		// }
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
int Input_Rece_ver2(int max_num,int min_num,int digit){//数値の入力
	char str[BUF];    //入力バッファ
	int i;            //ループカウンタ
	int flag;    //繰り返しカウンタ
	int len;          //入力データサイズ
	//int digit;        //数字変換
	int num_check[K]; //使われた数字の記憶
	int num;          //入力された数値
	int num_dis[digit];   //入力された数値を桁ごとに代入。
	int dis;          //桁ごとに数値を入れるときに使用

	while (1) {
		/*num_checkの初期化*/
		for (i = 0; i < K; i++) {
			num_check[i] = 0;
		}
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

        /* 変数確認 */
		// for (i = 0; i < len; i++) {
		// 	printf("str[%d]:%c\n", i, str[i]);
		// 	fflush(stdout);
		// }

		if (digit + 1 < len) {
			printf(">>ERROR:%d桁を超えています。もう一度入力してください。\n", digit);
			fflush(stdout);
            return 0;
			// continue;
		}
        // else if (len < digit + 1) {
		// 	printf(">>EROOR:%d桁に達していません。もう一度入力してください。\n", digit);
		// 	fflush(stdout);
		// 	continue;
		// }

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
		// printf("入力された数値：%d\n", num);
		fflush(stdout);
		// for (i = 0; i < digit; i++) {
		// 	dis = pow(10, (digit - i - 1));
		// 	num_dis[i] = num / dis;
		// 	num = num % dis;
		// 	fflush(stdout);
		// }

		// if (num_dis[0] == 0) {
		// 	printf(">>ERROR:先頭の数字が０または文字になっています。\n");
		// 	fflush(stdout);
		// 	continue;
		// }

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

		// for (i = 0; i < len - 1; i++) //データサイズ文取得
		// 		{
		// 	if (num_check[num_dis[i]] == 0) {
		// 		num_check[num_dis[i]] = 1;
		// 	} else {
		// 		printf(">>ERROR:同じ数字が2回以上使われています。もう一度入力してください。\n");
		// 		fflush(stdout);
		// 		flag = 1;
		// 		break;
		// 	}
		// }
		if (flag)
			continue;
		break;
	}
    return num;
	puts(str);
	fflush(stdout);

}

// int speed_find(int speed,int breaks){//速度を求める
//     int next_speed;
//     next_speed=speed-breaks;
//     return next_speed;
// }
// int month_distance_find(int speed,int distance){//距離を求める
//     int next_distance;
//     next_distance=distance-(speed/C);
//     return next_distance;
// }

void month_display(int speed,int distance,int breaks){//表示
    int i;//ループ制御
    int train;
    train=distance/MSC;
    if(speed==0||distance<-10){
        printf("[停止中]\n");
    }else printf("[走行中]\n");
    printf("|");
    for(i=0;i<AL/MSC;i++){
        if(i==train){
            printf("□□□");
            i += 2;
        }else printf("_");
    }
    printf("\n速度：%dkm/h 現在の高度：%dm 残燃料：%d (max%d)\n",speed,distance,breaks,BMAX);
}

int month_speed_find(int speed,int breaks){//速度を求める
    int next_speed;
    next_speed=speed+MS-breaks*Y;
    return next_speed;
}
int month_breaks_find(int breaks,int *fuel){//ブレーキの操作
    int flag;//ブレーキをどうするの判断；
    printf("どのくらいユニットを投下しますか。\n");
    flag=Input_Rece_ver2(50,0,2);//数値の入力
    if(*fuel<flag){
        printf("残燃料数が足りません。\n");
        return 0;
    }else{
        *fuel -=flag;
        return Y*flag;
    }
    // if(flag==2){
    //     if(breaks=OY) return 0; //ブレーキがMAXだった場合強くできない
    //     /* ブレーキを強く */
    //     return 1;
    // }else if(flag==1){
    //     if(breaks==0) return 0;//ブレーキが0だった場合弱くできない
    //     /* ブレーキを弱く */
    //     return -1;
    // }else return 0;
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
