#include<easyx.h>
#include<vector>
#include<unordered_map>
#include"Animation.h"
#include"Mantis Air Projectile.h"
#include"Player.h"
#include"collision.h"
#include"Character.h"
#include"CharacterManager.h"
#include"Mantis Air Projectile.h"
#include"Effect.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy:public character
{
public:

	Enemy();
	~Enemy();
	void dash_left_clear();
	void dash_right_clear();
	void dstab_left_clear();
	void dstab_right_clear();
	void wall_left_clear();
	void wall_right_clear();

	bool is_play_projectile = false;  //播放圆环的时机
	bool finish_dash = false;
	bool finish_dstab = false;
	bool finish_wall = false;
	bool finish_wall_low = false;
	bool finish_wall_high = false;
	bool finish_stand = false;
	bool finish_leave = false;
	bool finish_death_leave = false;
	bool finish_back = false;
	bool death_left = false;
	bool be_death = false; //是否死亡

	virtual void Idle(float delta);
	virtual void stand(float delta) ;
	virtual void leave(float delta);
	void throw_projectile(bool is_low,bool is_left);
	void throw_projectile(bool is_low,bool is_left,bool x);
	void wall_left(float delta);
	void wall_right(float delta);
	void wall_left_low(float delta);
	void wall_left_high(float delta);
	void wall_right_low(float delta);
	void wall_right_high(float delta);
	void dash_left(float delta);
	void dash_right(float delta);
	void dstab_left(float delta);
	void dstab_right(float delta);
	void death_land(float delta);
	void death_air_left(float delta);
	void death_air_right(float delta);
	void back_left(float delta);
	void back_right(float delta);
	void death_leave_left(float delta);
	void death_leave_right(float delta);
	void death_leave_reset();
	void set_current_function(const string& id);//设置当前动画状态
	void change_enemy_point(int x, int y);  //得到玩家的位置

	void on_hurt() override;

	POINT get_enemy_pos();
	POINT get_logic_center_enemy() ;
	POINT get_logic_down();
	void set_death_pos(int x, int y);
	void set_enemy_pos(int x, int y);
	POINT get_death_pos()
	{
		return death_pos;
	}

	virtual void on_update(float delta);
	virtual void on_render(float delta);


protected:
	IMAGE Throne_Idle_left;
	IMAGE Throne_Idle_right;
	Animation* Throne_Stand_left;
	Animation* Throne_Stand_right;

	Animation* Throne_Leave_left;
	Animation* Throne_Leave_right;

	Animation* Dash_Arrive_left;
	Animation* Dash_Antic_left;
	Animation* Dash_Attack_left;
	Animation* Dash_Recover_left;
	Animation* Dash_Leave_left;
	Animation* Dash_Arrive_right;
	Animation* Dash_Antic_right;
	Animation* Dash_Attack_right;
	Animation* Dash_Recover_right;
	Animation* Dash_Leave_right;

	Animation* Dstab_Arrive_left;
	Animation* Dstab_Land_left;
	Animation* Dstab_Attack_left;
	Animation* Dstab_Leave_left;
	Animation* Dstab_Arrive_right;
	Animation* Dstab_Land_right;
	Animation* Dstab_Attack_right;
	Animation* Dstab_Leave_right;

	Animation* Wall_Arrive_left;
	Animation* Wall_Ready_left;
	Animation* Throw_Antic_left;
	Animation* Throw_left;
	Animation* Wall_leave1_left;
	Animation* Wall_leave2_left;
	Animation* Wall_Arrive_right;
	Animation* Wall_Ready_right;
	Animation* Throw_Antic_right;
	Animation* Throw_right;
	Animation* Wall_leave1_right;
	Animation* Wall_leave2_right;

	Animation* Death_land;
	Animation* Death_air_left;
	Animation* Death_air_right;
	Animation* Death_leave_left;
	Animation* Death_leave_right;
	Animation* Death_back_left;
	Animation* Death_back_right;

	IMAGE image_sketch;  //临时闪白图像
	IMAGE image_sketch_air_left;
	IMAGE image_sketch_air_right;

	Effect* effect;   //创建效果


	bool facing_left = false;
	POINT &enemy_point =character::pos;
	Air_Projectile* projectile=nullptr;
	bool position = false;  //玩家定位系统
	bool height_generation = false;//生成随机高度
	int height = 0;
	int height_foot = 0;
	vector<Air_Projectile*> air_projectile;
	bool is_throw_projectile = false;
	bool death_on_land = false;
	bool death_on_air = false;
	bool is_left = false;  //初始idel时是向左还是向右

	bool be_hurt = false;  //是否受伤
	POINT start_point;  //起始时坐标
	POINT death_pos;   //标记死亡动画位置

	POINT leave_start_point;

	unordered_map<string, std::function<void(float)>> animation_pool;                       //动画池
	std::function<void(float)> current_function=nullptr;              //目前的动画状态
};

class Throne1 :public Enemy
{
public:
	Throne1();
	~Throne1();

	void back();
	void gesture();
	void stand(float delta);
	void dash_left_clear1();
	void dash_right_clear1();
	void dstab_left_clear1();
	void dstab_right_clear1();
	void wall_left_clear1();
	void wall_right_clear1();
	void set_finish_battle();
	bool if_finish_battle();

	void on_update(float delta) override;
	void on_render(float delta) override;
private:
	bool finish_battle = false;  //是否结束战斗
};

class Throne2 :public Enemy 
{
public:
	Throne2();
	void Idel();
	bool start_game2 = false; 

	void on_update(float delta) override;
	void on_render(float delta) override;
private:

};

class Throne3 :public Enemy 
{
public:
	Throne3();
	void Idel();
	void set_action(bool x)
	{
		finish_action = x;
	}
	bool get_action()
	{
		return finish_action;
	}

	void on_update(float delta) override;
	void on_render(float delta) override;
private:
	int x=749;
	int y=173;
	bool finish_action = false;  //是否完成行动
};

#endif // !ENEMY.H

//310 349
//901 350