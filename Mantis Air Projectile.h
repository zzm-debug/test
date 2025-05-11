#include"Animation.h"
#include<easyx.h>
#include"Character.h"
#include"collision.h"
#include<stdbool.h>

#pragma once
#ifndef MANTIS_AIR_PROJECTILE_H
#define MANTIS_AIR_PROJECTILE_H

class Air_Projectile :public character
{
public:
	Air_Projectile(bool is_low,bool is_left);
	Air_Projectile(bool is_low, bool is_left, bool x);  //二阶段构造函数
	void on_update(float delta);
	void on_render(float delta);
	void reset();
	int get_x();
	bool if_remove();
	void set_position(int x,int y);
	void set_velocity(int vx, int vy1,int vy2);
	void set_gx(int g);
	POINT get_logic_center() override;


private:
	Animation* fly;
	int vx ;
	int vy1 ;
	int vy2 ;
	int gx;
	POINT pos_projectile = { 0,0 };
	bool is_start = false;
	bool is_start_alt = false;
	bool can_remove = false;
};

#endif // !MANTIS_AIR_PROJECTILE_H
