#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "ship.h"
#include "constant.h"

extern int Input_Rece(int max_num,int min_num,int mode);//数値の入力 modoが0の時は不正な入力は0を返す

void month_display(struct ship *landing_ship){//表示
    int i;//ループ制御
    int train;
    train=landing_ship->altitude/DISPLAY_MAFNIFICATION;
    if(landing_ship->speed==0||landing_ship->altitude<-10){
        printf("[停止中]\n");
    }else printf("[走行中]\n");
    printf("|");

	if(landing_ship->altitude<=0){
		printf("□□");
		for(i=0;i<INITIAL_ALTITUDE/DISPLAY_MAFNIFICATION;i++){
			printf("_");
		}
	}else{
		for(i=0;i<INITIAL_ALTITUDE/DISPLAY_MAFNIFICATION;i++){
			if(i==train){
				printf("□□□");
				i += 2;
			}else printf("_");
		}
    }
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
