/*
 * ship.h
 *
 *  Created on: 2021/05/20
 *      Author: kador
 */

#ifndef SHIP_H_
#define SHIP_H_//おんなじヘッダーファイルを作らないようにする

struct ship{
	double altitude;//高度
	double speed;//速度
	int holding_fuel;//保持燃料数
	int time;//着陸にかかった時間
	int f_landing;//着陸したかのフラグ
};

#endif /* SHIP_H_ */
