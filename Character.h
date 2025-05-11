#include"collision.h"
#include"gravity.h"
#include"State-Machine.h"
#include<easyx.h>
#include"Timer.h"
#include"Animation.h"
#include"collision.h"
#include<functional>

#pragma once
#ifndef CHARACTER_H
#define CHARCTER_H

class character
{
public:
	character();
	~character();
	virtual void ProcessEvent(const ExMessage& msg) ;  //按键信息
	virtual void on_update(float delta) ;
	virtual void on_render(float delta) ;

	virtual void on_hurt() {  };
	POINT get_pos();
	int get_hp();
	void set_pos(POINT& pos);
	void set_velocity_x(double vx);
	void set_velocity_y(double vy);
	void set_gravity(double g);
	double get_velocity_x();
	double get_velocity_y();
	double get_gravity();
	void make_invulnerable();
	void decrease_hp(int damage);
	void switch_state(const string& id);
	CollisionBox* get_hit_box_first();
	CollisionBox* get_hit_box_second();
	CollisionBox* get_hurt_box();
	void set_logic_center(POINT position)
	{
		this->logic_center = position;
	}
	virtual POINT get_logic_center()
	{
		return logic_center;
	}
	void set_invulnerable(bool x)
	{
		is_invulnerable = x;
	}
	bool get_blinking_invulnerable()
	{
		return is_blinking_invulnerable;
	}
	gravity& get_game_gravity()
	{
		return game_gravity;
	}


	boudary boundary;
	POINT pos = { 0 };
protected:
	gravity game_gravity;
	int hp = 10;
	bool is_facing_left = true;
	State_Machine state_machine;
	Timer time_invulnerable;
	Timer time_blinking_invulerable;
	bool is_invulnerable = false;
	bool is_blinking_invulnerable = false;
	CollisionBox* hit_box_first=nullptr ;
	CollisionBox* hit_box_second=nullptr ;
	CollisionBox* hurt_box=nullptr ;
	Animation* current_animation;

	POINT logic_center = { 0 };  //碰撞箱坐标
	long need_x = 0;   //临时存储碰撞想的横坐标;
	long need_y = 0;   //临时存储碰撞箱的纵坐标；
};

#endif // !CHARACTER_H

