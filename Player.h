#include<vector>
#include<stdbool.h>
#include<iostream>
#include<easyx.h>
#include"Animation.h"
#include"gravity.h"
#include"Character.h"
#include"CharacterManager.h"
using namespace std; 



#ifndef PLAYER_H
#define PLAYER_H


class Player :public character
{
public:
	Player();
	~Player();
	void ProcessEvent(const ExMessage& msg);  //按键信息
	bool if_start();   //是否开始游戏
	POINT getposition();
	bool is_start = false;  //判断是否开始游戏
	void on_update(float delta) override;
	void on_render(float delta) override;
	void set_attacking(bool attack);
	void idle(float delta);
	void attack(float delta);
	void run(float delta);
	void jump(float delta);
	void fall(float delta);
	void dash(float delta);
	void death(float delta);
	void land(float delta);
	bool is_move();
	void land_reset();
	bool check_land();
	bool check_jump();
	bool check_fall();
	bool check_attack();
	bool check_dash();
	void exit_attack();
	bool check_land_reset();
	void bounce(float delta);  //反弹状态
	bool check_bounce();
	bool downslash_hit = false;  //检验下劈命中状态

	void hurt_left(float delta);  //受伤动画
	void hurt_right(float delta);  //受伤动画
	void reset_hurt();
	void on_hurt() override;  //受伤方法

	POINT current_center();  //获取玩家当时的位置中心
	POINT current_right();   //获取玩家的右下角坐标
	bool be_hurt = false;  //判断是否受击
	bool finish_hurt_animation = false;
	bool start_next_battle = false;  //开启二阶段

	void set_current_function(const string& id);//设置当前动画状态
	Animation* get_current_animation()
	{
		return current_animation;
	}


	enum class AttackDir {
		Up,
		Down,
		Left,
		Right,
	};                           

	AttackDir get_attack_dir()              //获取攻击方向
	{
		return current_attack_dir;
	};  

private:

	Animation* player_left;
	Animation* player_right;
	Animation* player_run_left;
	Animation* player_run_right;
	Animation* player_jump_left;
	Animation* player_jump_right;
	Animation* player_land_left;
	Animation* player_land_right;
	Animation* player_dash_left;
	Animation* player_dash_right;
	Animation* player_slash_left;
	Animation* player_slash_right;
	Animation* player_slash_alt_left;
	Animation* player_slash_alt_right;
	Animation* player_slash_up;
	Animation* player_slash_down;
	Animation* recoil_left;
	Animation* recoil_right;


	const int PLAYER_ANIM_NUM_run = 13;//跑步动作13帧
	int Idex_Current_anim_run = 0;
	const int PLAYER_ANIM_NUM_stop = 9;//停止动作9帧
	int Idex_Current_anim_stop = 0;
	const int PLAYER_ANIM_NUM_jump = 12;//跳跃动作12帧
	int Idex_Current_anim_jump = 0;
	const int PLAYER_ANIM_NUM_Land = 3;//落地动作3帧
	const int PLAYER_ANIM_NUM_Dash = 7;//冲刺动作7帧
	const int PLAYER_ANIM_NUM_Slash = 3;//劈砍动作一三帧
	const int PLAYER_ANIM_NUM_Slash_Alt = 3;//劈砍动作二三帧
	const int PLAYER_ANIM_NUM_UpSlash = 6;  //上劈动作六帧
	const int PLAYER_ANIM_NUM_DownSlash = 4;  //下劈动作四帧


	int idex_num = 0;


	bool is_Down_Left = false;
	bool is_walk = false;
	bool is_stopping_walk = false;
	bool is_walk_once = false;        //检验行走动画是否已经播放一遍，从第六帧开始loop
	bool to_left = true;              //检验玩家朝向
	bool is_Down_Right = false;       //是否按下右键
	bool is_Down_Space = false;  //是否按下空格
	bool is_finish_jump = false;  //是否已经完成一次跳跃（防止落地后二段跳）
	bool is_starting_down = false; //判断是否开始降落
	bool is_up = false;  //是否正在上升
	bool is_lose_space = true; //判断是否在跳跃中途松开空格
	bool downing_loose_space = false;  //判断是否在下落中途松开空格
	bool is_opera_downing_lose_space = false; //判断是否正在执行下落松开空格的命令
	bool already_land = false;  //已经落地
	bool facing_left_when_land = false;  //检验落地时的朝向
	bool is_looped = false;// 判断是否完成循环
	bool is_Down_C = false; //判断是否按下C键
	bool is_finish_Dash = false;//判断是否完成冲刺
	bool to_left_when_dash = false;//判断冲刺时的朝向
	float cooling_time_dash = 0.5f;  //冲刺冷却时间400ms
	bool is_on_air = false;  //判断是否在空中
	bool is_down_z = false;  //判断是否按下攻击键
	bool is_face_left_when_slash = false; //检验劈砍时朝向
	bool is_loop_slash = false;  //判断劈砍一是否loop一次
	bool is_loop_slash_alt = false;
	bool opera_slash1 = false;  //判断上一次执行的时劈砍一还是劈砍二
	bool is_jump_when_slash = false;  //判断是否在跳跃时劈砍
	bool is_finish_slash = false;  //判断是否在跳跃时完成一次劈砍
	bool is_down_up = false;  //是否按下上键
	bool is_down_down = false;  //是否按下下键  
	bool opera_upslash = false;  //判断是否执行上劈
	bool opera_downslash = false;  //判断是否执行下劈
	bool opera_plantslash = false;  //判断是否执行前劈

	bool is_attacking = false;//攻击有效判定



	AttackDir current_attack_dir = AttackDir::Right;

	POINT player_pos = {(long) (657 - 61 * 0.65), (long)(620 - 132 * 0.65) };

	unordered_map<string, std::function<void(float)>> animation_pool;                       //动画池
	std::function<void(float)> current_function = nullptr;              //目前的动画状态

};

class time_buffer
{
public:
	friend class Player;
	time_buffer();
	void add(float delta);
	void reset();
private:
	float time = 0;
};


#endif // !PLAYER_H

