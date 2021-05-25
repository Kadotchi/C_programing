#include<stdio.h>
#include "ship.h"
#include "constant.h"

extern int Input_Rece(int max_num,int min_num,int mode);//数値の入力 modoが0の時は不正な入力は0を返す


//着陸船の操作
void landing(struct ship *landing_ship){
	int fuel;//燃料
	double before_speed;//速度が変化する前の速度
	double acceleration;//加速度

	//燃料の受付
	printf("投下する燃料を入力してください。:");
	if(landing_ship->holding_fuel<UNIT_MAXIMUM){//保持燃料が一度に投下出来るユニット数よりも少なかった場合
	fuel=Input_Rece(landing_ship->holding_fuel,0,0);
	}else fuel=Input_Rece(UNIT_MAXIMUM,0,0);

	//所持燃料から今回の燃料分を引く
	landing_ship->holding_fuel -= fuel;
	//変化前の速度を格納
	before_speed=landing_ship->speed;
	//速度の計算
	landing_ship->speed += MONTH_LANDING_SPEED-fuel*LANDING_VALUE;
	//加速度の計算
	acceleration=landing_ship->speed-before_speed;
	//高度の変化の計算
	landing_ship->altitude -=before_speed+acceleration/2;
	if(landing_ship->altitude<0) landing_ship->altitude=0;
	//着陸船の時間を進める
	landing_ship->time ++;
	//月面着陸した場合フラグを０にする
	if(landing_ship->altitude<=0){
		landing_ship->f_landing=0;
	}
}
