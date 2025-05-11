#include"StateNode.h"
#include"Timer.h"
#include<stdbool.h>
#include"collision.h"

#pragma once
#ifndef ENEMY_STATENODE_H
#define ENEMY_STATENODE_H

class Enemy_Dash_Node:public StateNode
{
public:
	Enemy_Dash_Node();
	~Enemy_Dash_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;

	bool dash_orientation();

private:
	const float speed = 1800.0f;
	bool dash_left = false;
};

class Enemy_Dstab_Node :public StateNode
{
public:
	Enemy_Dstab_Node();
	~Enemy_Dstab_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	const float speed = 3000.0f;
	int temp = 0;
	boudary boundary;
};

class Enemy_Wall_low_Node:public StateNode
{
public:
	Enemy_Wall_low_Node() ;
	~Enemy_Wall_low_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;
	bool get_left();

private:
	Timer timer_throw;
	Timer timer_projectile;
	bool is_left = false;
};

class Enemy_Wall_high_Node :public StateNode
{
public:
	Enemy_Wall_high_Node() ;
	~Enemy_Wall_high_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	Timer timer_throw;
	Timer timer_projectile;
	bool is_left = false;
};

class Enemy_Idle_Node :public StateNode
{
public:
	Enemy_Idle_Node()=default ;
	~Enemy_Idle_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:

};

class Enemy_Stand_Node :public StateNode
{
public:
	Enemy_Stand_Node()=default ;
	~Enemy_Stand_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:

};

class Enemy_Leave_Node :public StateNode
{
public:
	Enemy_Leave_Node()=default ;
	~Enemy_Leave_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:

};

class Enemy_Idle_alt_Node :public StateNode
{
public:
	Enemy_Idle_alt_Node() ;
	~Enemy_Idle_alt_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;

private:
	Timer timer;
};

class Enemy_Death_land_Node :public StateNode
{
public:
	Enemy_Death_land_Node();
	~Enemy_Death_land_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;

private:
	Timer timer;
};

class Enemy_Death_air_Node :public StateNode
{
public:
	Enemy_Death_air_Node();
	~Enemy_Death_air_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;

private:
	Timer timer;
};

class Enemy_Death_leave_Node :public StateNode
{
public:
	Enemy_Death_leave_Node();
	~Enemy_Death_leave_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;

private:
	Timer timer;
};

class Enemy_Back_Node :public StateNode
{
public:
	Enemy_Back_Node() ;
	~Enemy_Back_Node() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	Timer timer;
};



#endif // !ENEMY_STATENODE_H
