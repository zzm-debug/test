#include<easyx.h>
#include"bullet.h"

Bullet::Bullet()
{
	SlashEffect_left = new Animation(_T("Knight/007.SlashEffect/007-0%d.png"), PLAYER_ANIM_NUM_SlashEffect, 1.0f / 40.0f);
	SlashEffect_right = new Animation(_T("Knight/007.SlashEffect/007-0%d.png"), PLAYER_ANIM_NUM_SlashEffect, 1.0f / 40.0f,true);
	SlashEffectAlt_left=new Animation(_T("Knight/008.SlashEffectAlt/008-0%d.png"), PLAYER_ANIM_NUM_SlashEffect, 1.0f / 40.0f);
	SlashEffectAlt_right=new Animation(_T("Knight/008.SlashEffectAlt/008-0%d.png"), PLAYER_ANIM_NUM_SlashEffect, 1.0f / 40.0f,true);
	UpSlashEffect=new Animation(_T("Knight/015.UpSlashEffect/015-0%d.png"), PLAYER_ANIM_NUM_UpSlashEffect, 1.0f / 40.0f);
	DownSlashEffect=new Animation(_T("Knight/016.DownSlashEffect/016-0%d.png"), PLAYER_ANIM_NUM_DownSlashEffect, 1.0f / 40.0f);
}