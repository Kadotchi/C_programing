#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define D 5    //桁の数
#define K 10   //1桁の数値の範囲
#define BUF 32 //バッファの数

void Rule(); //ルール説明

void CPU(int *cpu, int *cpuch);                                  //コンピュータの入力
void Input_Rece(int *usr, int *usrch);                           //入力受付
int Num_Check(int *cpu, int *cpuch, int *usr, int *usrch,int c); //判定

int main(void) {
	int usr[D], cpu[D] = { 1, 2, 3, 4, 5 };     //入力された数列
	int usrch[K], cpuch[K] = { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 }; //入力された数値の記憶
	int flag = 0;
	char Ustr[5] = "Yes"; //ゲームを続けるかの入力対象
	char Astr[5] = "Yes"; //ゲームを続けるための比較対象
	int *usr_ad = usr; //ユーザーの数列のアドレス
	int *cpu_ad = cpu; //CPUの数列のアドレス
	int *usrch_ad = usrch; //ユーザーの数値の記憶
	int *cpuch_ad = cpuch; //CPUの数値の記憶の配列
	int mode; //モード選択
	int count;

//	Rule();

	printf("0:ゲーム開始！！\n1:デバックモード\nモードを選択してください:");
	fflush(stdout);
	scanf("%d", &mode);
	fflush(stdin);
	switch(mode)
	{
		case 0:
		while (1) {
			count=0;
			CPU(cpu_ad, cpuch_ad); //コンピュータの入力
			while (1) {
				Input_Rece(usr_ad, usrch_ad); //ユーザからの入力
				count++;
				flag = Num_Check(cpu_ad, cpuch_ad, usr_ad, usrch_ad,count);
				if (flag == 1) {
					break;
				} else {
					continue;
				}
			}
			printf("もう一度遊びますか？ Yes or No ?：");
			fflush(stdout);
			fflush(stdin);
			scanf("%s", Ustr);
			if (strcmp(Ustr, Astr) == 0) {
				printf("もう一度ゲーム開始\n");
				fflush(stdout);
				continue;
			}
			fflush(stdin);
			break;
		}
		break;
		case 1:
		printf("デバックモード\n");
		printf("CPUの数列:12345\n");
		while (1) {
			count=0;
			while (1) {
				Input_Rece(usr_ad, usrch_ad); //ユーザからの入力
				count++;
				flag = Num_Check(cpu_ad, cpuch_ad, usr_ad, usrch_ad,count);
				if (flag == 1) {
					break;
				} else {
					continue;
				}
			}
			printf("もう一度遊びますか？ Yes or No ?：");
			fflush(stdout);
			fflush(stdin);
			scanf("%s", Ustr);
			if (strcmp(Ustr, Astr) == 0) {
				printf("もう一度ゲーム開始\n");
				fflush(stdout);
				fflush(stdin);
				continue;
			}
			printf("ゲーム終了\n");
			fflush(stdout);
			fflush(stdin);
			break;
		}
		break;

	}
	return 0;
}

void Rule() {
	FILE *fp;
	char str[256];
	fp = fopen("Rule_explanation.txt", "r");

	while (!feof(fp)) {
		fgets(str, 256, fp);
		printf("%s", str);
	}
	fclose(fp);
	printf("\n");
}

void Input_Rece(int *usr, int *usrch) {
	char str[BUF];    //入力バッファ
	int i;            //ループカウンタ
	int flag;    //繰り返しカウンタ
	int len;          //入力データサイズ
	//int digit;        //数字変換
	int num_check[K]; //使われた数字の記憶
	int num;          //入力された数値
	int num_dis[D];   //入力された数値を桁ごとに代入。
	int dis;          //桁ごとに数値を入れるときに使用

	while (1) {
		/*num_checkの初期化*/
		for (i = 0; i < K; i++) {
			num_check[i] = 0;
		}
		flag = 0; //フラグの初期化
		printf("\n0から%dまでの数字を入力してください。：", K);
		fflush(stdout);
		fgets(str, sizeof(str), stdin); //ユーザからの入力受付
		str[BUF - 2] = '\n';
		str[BUF - 1] = '\0';
		len = strlen(str); //データサイズ取得

		for (i = 0; i < len; i++) {
			//printf("str[%d]:%c\n", i, str[i]);
			fflush(stdout);
		}

		if (D + 1 < len) {
			printf(">>ERROR:%d桁を超えています。もう一度入力してください。\n", D);
			fflush(stdout);
			continue;
		} else if (len < D + 1) {
			printf(">>EROOR:%d桁に達していません。もう一度入力してください。\n", D);
			fflush(stdout);
			continue;
		}

		//printf("%d\n", len);
		for (i = 0; i < D; i++) //データサイズ文取得
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
		//printf("%d\n", num);
		fflush(stdout);
		for (i = 0; i < D; i++) {
			dis = pow(10, (D - i - 1));
			num_dis[i] = num / dis;
			num = num % dis;
			//printf("%d:%d\n", dis, num_dis[i]);
			fflush(stdout);
		}

		if (num_dis[0] == 0) {
			printf(">>ERROR:先頭の数字が０または文字になっています。\n");
			fflush(stdout);
			continue;
		}

		for (i = 0; i < len - 1; i++) //データサイズ文取得
				{
			if (num_check[num_dis[i]] == 0) {
				num_check[num_dis[i]] = 1;
			} else {
				printf(">>ERROR:同じ数字が2回以上使われています。もう一度入力してください。\n");
				fflush(stdout);
				flag = 1;
				break;
			}
		}
		if (flag)
			continue;
		break;
	}
	puts(str);
	fflush(stdout);
	for (i = 0; i < D; i++) {
		*(usr + i) = num_dis[i];
		//num_check[num_dis[i]] = 1;
	}
	for (i = 0; i < K; i++) {

		//printf("usr_check[%d]:%d\n:", i, num_check[i]);
		fflush(stdout);
		*(usrch + i) = num_check[i];
	}
	fflush(stdout);
}

void CPU(int *cpu, int *cpuch) {
	int i;            //ループカウンタ
	int num_cpu[D];   //コンピュータの数列
	int num_check[K]; //使われた数値のカウント

	printf("CPU考え中\n");
	fflush(stdout);
	fflush(stdin);

	/*num_checkの初期化*/
	for (i = 0; i < K; i++) {
		num_check[i] = 0;
	}
	for (i = 0; i < D; i++) {
		if (i == 0) //先頭は0以外
				{
			num_cpu[i] = rand() / (K - 1) + 1;
			num_check[num_cpu[i]] = 1;
			printf("num_cpu[%d]:%d\n", i, num_cpu[i]);
		} else {
			num_cpu[i] = rand() % K;
			if (num_check[num_cpu[i]] == 1) {
				continue;
			} else {
				num_check[num_cpu[i]] = 1;
				printf("num_cpu[%d]:%d\n", i, num_cpu[i]);
				fflush(stdout);
			}
		}
	}
	for (i = 0; i < D; i++) {
		*(cpu + i) = num_cpu[i];
	}
	for (i = 0; i < K; i++) {
		printf("num_check[%d]:%d\n", i, num_check[i]);
		*(cpuch + i) = num_check[i];
	}
}

int Num_Check(int *cpu, int *cpuch, int *usr, int *usrch,int c) {
	int i;
	int count = 0, count2 = 0; //使っている数字があっている数と数字と桁数があっている数
	/*使っている数字があっている数のカウント*/
	for (i = 0; i < K; i++) {
		//printf("cpu_ch[%d]:%d,usr_ch[%d]:%d\n", i, *(cpuch + i), i,
				//*(usrch + 1));
		fflush(stdout);
		if (*(cpuch + i) == 1 && *(usrch + i) == 1) {
			count++;
		}
		if (count == D) {
			break;
		}
	}
	/*桁も数も一致のカウント*/
	for (i = 0; i < D; i++) {
		if (*(cpu + i) == *(usr + i)) {
			count2++;
		}
	}

	if (count2 == D) {
		printf("おめでとうございます。%d回目での正解です。\n",c);
		fflush(stdout);
		return 1;
	} else {
		printf("数の一致は%d,桁も一致は%dとなります。\n", count, count2);
		fflush(stdout);
		return 0;
	}
}
