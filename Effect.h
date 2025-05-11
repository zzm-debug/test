#include"Animation.h"

#pragma once
#ifndef EFFECT_H
#define EFFECT_H

class Effect
{
	friend class Enemy;
public:
	Effect();
	~Effect();

	void Play(int x,int y, float delta);
	bool if_finish_loop();
	void Reset();

private:
	Animation* Sword_effect;
	Animation* Stun_impact;
	bool finish_loop=false;
};

class Particle
{



};

#endif // !EFFECT_H

