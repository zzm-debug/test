#include"Effect.h"
#include"Animation.h"
#include<easyx.h>

Effect::Effect()
{
	Sword_effect=new Animation(_T("Strikes/001.Sword/001-0%d.png"), 3, 1.0f / 15.0f, false,false);
	Stun_impact=new Animation(_T("Effect/Texture2D/stun_impact_effect000%d.png"), 7, 1.0f / 50.0f, false,false);
}

Effect::~Effect()
{
	delete Sword_effect;
}

void Effect::Play(int x, int y, float delta)
{
	if (!Sword_effect->is_finish_loop)
	{
		Sword_effect->Play(x, y, delta, true, true);
	}
	finish_loop = Sword_effect->is_finish_loop;
}

bool Effect::if_finish_loop()
{
	return finish_loop;
}

void Effect::Reset()
{
	Sword_effect->Reset();
}