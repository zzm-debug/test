#include"StateNode.h"
#include"Timer.h"
#include<stdbool.h>
#include"collision.h"

#pragma once
#ifndef ENEMY_STATENODE3_H
#define ENEMY_STATENODE3_H

class Enemy_Idle_Node3 :public StateNode
{
public:
	Enemy_Idle_Node3()=default;
	~Enemy_Idle_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:

};

class Enemy_Stand_Node3 :public StateNode
{
public:
	Enemy_Stand_Node3()=default;
	~Enemy_Stand_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:

};

class Enemy_Leave_Node3 :public StateNode
{
public:
	Enemy_Leave_Node3()=default;
	~Enemy_Leave_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:

};

class Enemy_Idle_alt_Node3 :public StateNode
{
public:
	Enemy_Idle_alt_Node3();
	~Enemy_Idle_alt_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	Timer timer;
};

class Enemy_DashDstab_Node3 :public StateNode
{
public:
	Enemy_DashDstab_Node3()=default;
	~Enemy_DashDstab_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	boudary boundary;
	int temp = 0;
};

class Enemy_DstabDash_Node3 :public StateNode
{
public:
	Enemy_DstabDash_Node3()=default;
	~Enemy_DstabDash_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	bool dash_left = false;
};

class Enemy_DashDash_Node3 :public StateNode
{
public:
	Enemy_DashDash_Node3();
	~Enemy_DashDash_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	bool dash_left = false;
};

class Enemy_DstabDstab_Node3 :public StateNode
{
public:
	Enemy_DstabDstab_Node3()=default;
	~Enemy_DstabDstab_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	boudary boundary;
	int temp = 0;
};

class Enemy_MeanwhileDash_Node3 :public StateNode
{
public:
	Enemy_MeanwhileDash_Node3() = default;
	~Enemy_MeanwhileDash_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:

};

class Enemy_Wall_short_Node3 :public StateNode
{
public:
	Enemy_Wall_short_Node3();
	~Enemy_Wall_short_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	Timer timer_projectile;
	Timer timer_throw;
	bool is_left = false;
};

class Enemy_Wall_wide_Node3 :public StateNode
{
public:
	Enemy_Wall_wide_Node3();
	~Enemy_Wall_wide_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;


private:
	Timer timer_projectile;
	Timer timer_throw;
	bool is_left = false;
};

class Enemy_Restore_Dash_Node3 :public StateNode
{
public:
	Enemy_Restore_Dash_Node3() = default;
	~Enemy_Restore_Dash_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	bool dash_left = true;
};

class Enemy_Restore_Dstab_Node3 :public StateNode
{
public:
	Enemy_Restore_Dstab_Node3() = default;
	~Enemy_Restore_Dstab_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	boudary boundary;
	int temp = 0;
};

class Enemy_Restore_Wall_low_Node3 :public StateNode
{
public:
	Enemy_Restore_Wall_low_Node3();
	~Enemy_Restore_Wall_low_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	Timer timer_throw;
	Timer timer_projectile;
	bool is_left = false;
};

class Enemy_Restore_Wall_high_Node3 :public StateNode
{
public:
	Enemy_Restore_Wall_high_Node3();
	~Enemy_Restore_Wall_high_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	Timer timer_throw;
	Timer timer_projectile;
	bool is_left = false;
};

class Enemy_Restore_Idle_alt_Node3 :public StateNode
{
public:
	Enemy_Restore_Idle_alt_Node3();
	~Enemy_Restore_Idle_alt_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	Timer timer;
};

class Enemy_Dead_Land_Node3 :public StateNode
{
public:
	Enemy_Dead_Land_Node3();
	~Enemy_Dead_Land_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;
private:
	Timer timer;
};

class Enemy_Dead_Air_Node3 :public StateNode
{
public:
	Enemy_Dead_Air_Node3() ;
	~Enemy_Dead_Air_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;
private:
	Timer timer;
};

class Enemy_Dead_Leave_Node3 :public StateNode
{
public:
	Enemy_Dead_Leave_Node3();
	~Enemy_Dead_Leave_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	Timer timer;
};

class Enemy_Back_Node3 :public StateNode
{
public:
	Enemy_Back_Node3();
	~Enemy_Back_Node3() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	Timer timer;
};
#endif // !ENEMY_STATENODE3_H

