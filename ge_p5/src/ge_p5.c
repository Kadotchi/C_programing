#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "ship.h"
#include "constant.h"



// void init();//初期化
extern void Rule();//ルール説明
extern int game_continue();//ゲームを続けるかの選択

/* 月面着陸ゲーム */
extern void month_display(struct ship *landing_ship);//表示
extern void landing(struct ship *landing_ship);//着陸船の操作


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









