#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "ship.h"
#include "constant.h"


//着陸船の操作
void landing(struct ship *landing_ship){
	int fuel;//燃料
	double before_speed;//速度が変化する前の速度
	double acceleration;//加速度

	//燃料の受付
	printf("投下する燃料を入力してください。:");
	fuel=Input_Rece(landing_ship->holding_fuel,0,0);
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
