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
	void ProcessEvent(const ExMessage& msg);  //������Ϣ
	bool if_start();   //�Ƿ�ʼ��Ϸ
	POINT getposition();
	bool is_start = false;  //�ж��Ƿ�ʼ��Ϸ
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
	void bounce(float delta);  //����״̬
	bool check_bounce();
	bool downslash_hit = false;  //������������״̬

	void hurt_left(float delta);  //���˶���
	void hurt_right(float delta);  //���˶���
	void reset_hurt();
	void on_hurt() override;  //���˷���

	POINT current_center();  //��ȡ��ҵ�ʱ��λ������
	POINT current_right();   //��ȡ��ҵ����½�����
	bool be_hurt = false;  //�ж��Ƿ��ܻ�
	bool finish_hurt_animation = false;
	bool start_next_battle = false;  //�������׶�

	void set_current_function(const string& id);//���õ�ǰ����״̬
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

	AttackDir get_attack_dir()              //��ȡ��������
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


	const int PLAYER_ANIM_NUM_run = 13;//�ܲ�����13֡
	int Idex_Current_anim_run = 0;
	const int PLAYER_ANIM_NUM_stop = 9;//ֹͣ����9֡
	int Idex_Current_anim_stop = 0;
	const int PLAYER_ANIM_NUM_jump = 12;//��Ծ����12֡
	int Idex_Current_anim_jump = 0;
	const int PLAYER_ANIM_NUM_Land = 3;//��ض���3֡
	const int PLAYER_ANIM_NUM_Dash = 7;//��̶���7֡
	const int PLAYER_ANIM_NUM_Slash = 3;//��������һ��֡
	const int PLAYER_ANIM_NUM_Slash_Alt = 3;//������������֡
	const int PLAYER_ANIM_NUM_UpSlash = 6;  //����������֡
	const int PLAYER_ANIM_NUM_DownSlash = 4;  //����������֡


	int idex_num = 0;


	bool is_Down_Left = false;
	bool is_walk = false;
	bool is_stopping_walk = false;
	bool is_walk_once = false;        //�������߶����Ƿ��Ѿ�����һ�飬�ӵ���֡��ʼloop
	bool to_left = true;              //������ҳ���
	bool is_Down_Right = false;       //�Ƿ����Ҽ�
	bool is_Down_Space = false;  //�Ƿ��¿ո�
	bool is_finish_jump = false;  //�Ƿ��Ѿ����һ����Ծ����ֹ��غ��������
	bool is_starting_down = false; //�ж��Ƿ�ʼ����
	bool is_up = false;  //�Ƿ���������
	bool is_lose_space = true; //�ж��Ƿ�����Ծ��;�ɿ��ո�
	bool downing_loose_space = false;  //�ж��Ƿ���������;�ɿ��ո�
	bool is_opera_downing_lose_space = false; //�ж��Ƿ�����ִ�������ɿ��ո������
	bool already_land = false;  //�Ѿ����
	bool facing_left_when_land = false;  //�������ʱ�ĳ���
	bool is_looped = false;// �ж��Ƿ����ѭ��
	bool is_Down_C = false; //�ж��Ƿ���C��
	bool is_finish_Dash = false;//�ж��Ƿ���ɳ��
	bool to_left_when_dash = false;//�жϳ��ʱ�ĳ���
	float cooling_time_dash = 0.5f;  //�����ȴʱ��400ms
	bool is_on_air = false;  //�ж��Ƿ��ڿ���
	bool is_down_z = false;  //�ж��Ƿ��¹�����
	bool is_face_left_when_slash = false; //��������ʱ����
	bool is_loop_slash = false;  //�ж�����һ�Ƿ�loopһ��
	bool is_loop_slash_alt = false;
	bool opera_slash1 = false;  //�ж���һ��ִ�е�ʱ����һ����������
	bool is_jump_when_slash = false;  //�ж��Ƿ�����Ծʱ����
	bool is_finish_slash = false;  //�ж��Ƿ�����Ծʱ���һ������
	bool is_down_up = false;  //�Ƿ����ϼ�
	bool is_down_down = false;  //�Ƿ����¼�  
	bool opera_upslash = false;  //�ж��Ƿ�ִ������
	bool opera_downslash = false;  //�ж��Ƿ�ִ������
	bool opera_plantslash = false;  //�ж��Ƿ�ִ��ǰ��

	bool is_attacking = false;//������Ч�ж�



	AttackDir current_attack_dir = AttackDir::Right;

	POINT player_pos = {(long) (657 - 61 * 0.65), (long)(620 - 132 * 0.65) };

	unordered_map<string, std::function<void(float)>> animation_pool;                       //������
	std::function<void(float)> current_function = nullptr;              //Ŀǰ�Ķ���״̬

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

