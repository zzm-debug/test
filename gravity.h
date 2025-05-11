#include<iostream>

#ifndef GRAVITY_H
#define GRAVITY_H

class gravity
{
public:
	friend class Player;
	gravity();
	void air_inspection1(float delta); 
	void air_inspection2(float delta);  //上升途中松开按键
	void air_inspection3(float delta); //改变重力加速度
	void air_inspection4(float delta);  //反弹速度变化
	void init4()
	{
		v = v_bounce;
	}
	double get_v()
	{
		return v;
	}
	void reset();
	void add(float delta);
	double vx =600;  //水平速度
	double vy = 0; //竖直速度
	double gy = 0;

private:
	const double g = 7740;    //平地上重力加速度
	double t = 0;  //上升计时器
	const double v_start = 1130; //起始速度
	const double v_bounce = 825;
	double v = 0; //目前的上升速度
	const double g_alt = 4860;
};


#endif // !GRAVITY_H
