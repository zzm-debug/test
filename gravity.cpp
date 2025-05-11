#include<iostream>
#include<easyx.h>
#include<string>
#include<Windows.h>
#include<vector>
#include"gravity.h"

gravity::gravity()
{
	t = 0;  //上升计时器
	v = 0; //目前的上升速度
}

void gravity::air_inspection1(float delta)
{
	if (t <= 0.2)
	{
		v = v_start;
	}
	else
	{
		v -= g * delta ;
	}

	if (v >= 1505) v = 1505;
	else if (v <= -1505) v = -1505;

}

//上升途中松开按键
void gravity::air_inspection2(float delta)
{
	v -= g * delta ;
	if (v > 0) v = 0;
}

void gravity::air_inspection3(float delta)
{
	v -= g_alt * delta ;
	if (v > 0) v = 0;
}

void gravity::reset()
{
	v = 0;
	t = 0;
}

void gravity::add(float delta)
{
	t +=(double)delta;

}



void gravity::air_inspection4(float delta)
{
	v -= g * delta;
}