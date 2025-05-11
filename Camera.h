#include<Windows.h>
#include<iostream>
#include"Timer.h"

#pragma once
#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:

	Camera()
	{
		timer_shake.set_one_shotted(true);
		timer_shake.set_callback([&]() {

			is_shaking = false;
			reset();
			});
	}
	void reset()
	{
		position = { 0,0 };
	}
	void shake(int shaking_strengths, float during_time)
	{
		shaking_strength = shaking_strengths;
		is_shaking = true;

		timer_shake.set_wait_time(during_time);
		timer_shake.restart();
	}
	void on_update(float delta)
	{
		timer_shake.update(delta);

		if (is_shaking)
		{
			int rand_num_x = rand() % (2 * shaking_strength + 1) - shaking_strength;
			int rand_num_y = rand() % (2 * shaking_strength + 1) - shaking_strength;
			position = { rand_num_x,rand_num_y };
		}
	}
	POINT get_position()
	{
		return position;
	}

private:
	POINT position = { 0,0 };
	Timer timer_shake;
	bool is_shaking = false;  //判断摄像机是否正在抖动
	int shaking_strength = 0;
};

#endif // !CAMERA_H

