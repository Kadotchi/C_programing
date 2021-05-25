#include<stdio.h>

extern int Input_Rece(int max_num,int min_num,int mode);//数値の入力 modoが0の時は不正な入力は0を返す


int game_continue(){//ゲームを続けるかの選択
    int flag;
    printf("ゲームを続けますか？\n2:はい：1:いいえ");
    flag=Input_Rece(2,1,1);//数値の入力
    if(flag==2) return 1;
    else return 0;
}
