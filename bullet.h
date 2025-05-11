#include<easyx.h>
#include"Animation.h"


#ifndef BULLET_H
#define BULLET_H

class Bullet
{
friend class Player;
public:
Bullet();

private:
	Animation* SlashEffect_left;
	Animation* SlashEffect_right;
	Animation* SlashEffectAlt_left;
	Animation* SlashEffectAlt_right;
	Animation* UpSlashEffect;
	Animation* DownSlashEffect;
	const int PLAYER_ANIM_NUM_SlashEffect = 4;    //������Чһ4֡
	const int PLAYER_ANIM_NUM_SlashEffectAlt = 4;    //������Ч��4֡
	const int PLAYER_ANIM_NUM_UpSlashEffect = 4;    //������Ч��4֡
	const int PLAYER_ANIM_NUM_DownSlashEffect = 4;  //������Ч4֡
};

#endif // !BULLET_H

