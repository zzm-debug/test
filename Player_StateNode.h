#include"StateNode.h"
#include"Timer.h"


#pragma once
#ifndef PLAYER_STATENODE_H
#define PLAYER_STATENODE_H

class PlayerIdleState :public StateNode
{
public:
	PlayerIdleState()=default;
	~PlayerIdleState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;

private:

};

class PlayerRunState :public StateNode
{
public:
	PlayerRunState() = default;
	~PlayerRunState() = default;

	void on_enter() override;
	void on_update(float delta) override;
private:

};

class PlayerJumpState :public StateNode
{
public:
	PlayerJumpState()=default;
	~PlayerJumpState() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:

};

class PlayerDashState :public StateNode
{
public:
	PlayerDashState()=default;
	~PlayerDashState() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:

};

class PlayerAttackState :public StateNode
{
public:
	PlayerAttackState();
	~PlayerAttackState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;

	void update_hit_box_position();
private:
	Timer timer;
};

class PlayerDeathState :public StateNode
{
public:
	PlayerDeathState();
	~PlayerDeathState() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:
	Timer timer;
};

class PlayerFallState :public StateNode
{
public:
	PlayerFallState()=default;
	~PlayerFallState() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:

};

class PlayerLandState :public StateNode
{
public:
	PlayerLandState()=default;
	~PlayerLandState() = default;

	void on_enter() override;
	void on_update(float delta) override;

private:

};

class PlayerHurtState :public StateNode
{
public:
	PlayerHurtState();
	~PlayerHurtState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;

private:
	Timer timer_sleep;
};

class PlayerBounceState:public StateNode
{
public:
	PlayerBounceState()=default;
	~PlayerBounceState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_end() override;
private:

};

#endif // !PLAYER_STATENODE_H

