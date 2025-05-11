#include<iostream>
#include<easyx.h>
#include<string>
#include<Windows.h>
#include<vector>
#include"Player.h"
#include"Animation.h"
#include"gravity.h"
#include"bullet.h"
#include"Player_StateNode.h"
#include"collision_sort.h"
#include"collision.h"

using namespace std::placeholders;

Bullet bullet;

//缓冲计时器
time_buffer::time_buffer()
	:time(0)
{
}

void time_buffer::reset()
{
	time = 0;
}

void time_buffer::add(float delta)
{
	time += delta;
}

time_buffer slash_buffer;  //劈砍动作计时器，劈砍一后0.3s再次劈砍会触发劈砍二
time_buffer jump_buffer; //跳跃计时器

Player::Player()
{

	time_invulnerable.set_wait_time(1.3f);//无敌帧时间

	hurt_box->set_size({ 15,30 });
	hit_box_first->set_size({ 100,50 });
	hit_box_second->set_size({ 80,90 });

	hit_box_first->set_layer_src(CollisionSort::None);
	hit_box_second->set_layer_src(CollisionSort::None);
	hit_box_first->set_layer_dst(CollisionSort::Enemy);
	hit_box_second->set_layer_dst(CollisionSort::Enemy);
	hurt_box->set_layer_src(CollisionSort::Player);
	hurt_box->set_layer_dst(CollisionSort::None);

	hit_box_first->set_enable(false);
	hit_box_second->set_enable(false);
	
	hurt_box->set_collide([&]() {

		decrease_hp(1);
		
		});

	hit_box_second->set_collide([&]() {

		cout << "open" << endl;
		downslash_hit = true;
		});

    player_left = new Animation(_T("Knight/001.Idle/001-0%d.png"), PLAYER_ANIM_NUM_stop, 1.0f / 12.0f);
	player_run_left = new Animation(_T("Knight/005.Run/005-0%d.png"), PLAYER_ANIM_NUM_run, 1.0f / 12.0f);
	player_right = new Animation(_T("Knight/001.Idle/001-0%d.png"), PLAYER_ANIM_NUM_stop, 1.0f / 12.0f, true,'w');
	player_run_right = new Animation(_T("Knight/005.Run/005-0%d.png"), PLAYER_ANIM_NUM_run, 1.0f / 12.0f, true);
	player_jump_left = new Animation(_T("Knight/003.Airborne/003-0%d.png"), PLAYER_ANIM_NUM_jump, 1.0f / 16.0f);
	player_jump_right = new Animation(_T("Knight/003.Airborne/003-0%d.png"), PLAYER_ANIM_NUM_jump, 1.0f / 16.0f, true,'w');
	player_land_left = new Animation(_T("Knight/011.Land/011-0%d.png"), PLAYER_ANIM_NUM_Land, 1.0f / 16.0f);
	player_land_right = new Animation(_T("Knight/011.Land/011-0%d.png"), PLAYER_ANIM_NUM_Land, 1.0f / 16.0f, true,'w');
	player_dash_left = new Animation(_T("Knight/002.Dash/002-0%d.png"), PLAYER_ANIM_NUM_Dash, 1.0f / 32.0f);
	player_dash_right = new Animation(_T("Knight/002.Dash/002-0%d.png"), PLAYER_ANIM_NUM_Dash, 1.0f / 32.0f, true,'w');
	player_slash_left = new Animation(_T("Knight/006.Slash/006-0%d.png"), PLAYER_ANIM_NUM_Slash, 1.0f / 20.0f);
	player_slash_right = new Animation(_T("Knight/006.Slash/006-0%d.png"), PLAYER_ANIM_NUM_Slash, 1.0f / 20.0f,true,'w');
	player_slash_alt_left = new Animation(_T("Knight/004.SlashAlt/004-0%d.png"), PLAYER_ANIM_NUM_Slash_Alt, 1.0f / 20.0f);
	player_slash_alt_right = new Animation(_T("Knight/004.SlashAlt/004-0%d.png"), PLAYER_ANIM_NUM_Slash_Alt, 1.0f / 20.0f,true,'w');
	player_slash_up = new Animation(_T("Knight/009.UpSlash/009-0%d.png"), PLAYER_ANIM_NUM_UpSlash, 1.0f / 20.0f);
	player_slash_down = new Animation(_T("Knight/010.DownSlash/010-0%d.png"), PLAYER_ANIM_NUM_DownSlash, 1.0f / 20.0f);
	recoil_left= new Animation(_T("Knight/021.Recoil/021-0%d.png"), 7, 1.0f / 25.0f);
	recoil_right= new Animation(_T("Knight/021.Recoil/021-0%d.png"), 7, 1.0f / 25.0f,true);

	animation_pool["attack"] = std::bind(&Player::attack, this, _1);
	animation_pool["jump"] = std::bind(&Player::jump, this, _1);
	animation_pool["dash"] = std::bind(&Player::dash, this, _1);
	animation_pool["run"] = std::bind(&Player::run, this, _1);
	animation_pool["death"] = std::bind(&Player::death, this, _1);
	animation_pool["idle"] = std::bind(&Player::idle, this, _1);
	animation_pool["fall"] = std::bind(&Player::fall, this, _1);
	animation_pool["land"] = std::bind(&Player::land, this, _1);
	animation_pool["recoil_left"] = std::bind(&Player::hurt_left, this, _1);
	animation_pool["recoil_right"] = std::bind(&Player::hurt_right, this, _1);
	animation_pool["bounce"] = std::bind(&Player::bounce, this, _1);

	state_machine.register_state("attack", new PlayerAttackState());
	state_machine.register_state("death", new PlayerDeathState());
	state_machine.register_state("run", new PlayerRunState());
	state_machine.register_state("idle", new PlayerIdleState());
	state_machine.register_state("jump", new PlayerJumpState());
	state_machine.register_state("fall", new PlayerFallState());
	state_machine.register_state("dash", new PlayerDashState());
	state_machine.register_state("land", new PlayerLandState());
	state_machine.register_state("recoil", new PlayerHurtState());
	state_machine.register_state("bounce", new PlayerBounceState());

	state_machine.set_entry("idle");
}

Player::~Player()
{
	delete player_left;
	delete player_right;
	delete player_run_left;
	delete player_run_right;
	delete player_jump_left;
	delete player_jump_right;
	delete player_land_left;
	delete player_land_right;
	delete player_dash_left;
	delete player_dash_right;
	delete player_slash_left;
	delete player_slash_right;
	delete player_slash_alt_left;
	delete player_slash_alt_right;
	delete player_slash_up;
	delete player_slash_down;
	delete recoil_left;
	delete recoil_right;

}

void Player::set_current_function(const string& id)
{
	if (id == "null") current_function = nullptr;
	else current_function = animation_pool[id];
	cout << id << endl;
}


void Player::ProcessEvent(const ExMessage& msg)
{
	if (msg.message == WM_LBUTTONDOWN)
	{
		int x = msg.x;
		int y = msg.y;
		cout << x << ' ' << y << endl;
	}
	if (msg.message == WM_KEYUP)//是否松开按键
	{
		switch (msg.vkcode)
		{
		case(VK_LEFT):
			is_Down_Left = false;
			player_run_left->Reset();
			break;
		case(VK_RIGHT):
			player_run_right->Reset();
			is_Down_Right = false;
			break;
		case(VK_UP):
			if (!opera_upslash)
				is_down_up = false;
			break;
		case(VK_DOWN):
			if (!opera_downslash)
				is_down_down = false;
			break;
		case(VK_SPACE):
			is_Down_Space = false;
			if (!is_opera_downing_lose_space)
				is_finish_jump = false;
			if (is_starting_down)
			{
				downing_loose_space = true;
			}
			break;
		case(67):

			break;
		case('Z'):

			break;



		}
	}
	if (msg.message == WM_KEYDOWN)//是否按下按键
	{
		switch (msg.vkcode)
		{
		case (VK_LEFT):
			is_Down_Left = true;
			to_left = true;
			break;
	 	case(VK_RIGHT):
			to_left = false;
			is_Down_Right = true;
			break;
		case(VK_UP):
			is_down_up = true;
			break;
		case(VK_DOWN):
			is_down_down = true;
			break;
		case(VK_SPACE):
			if (!is_finish_jump)
			{
				is_Down_Space = true;
			}
			downing_loose_space = false;
			jump_buffer.reset();
			player_left->Reset();
			player_right->Reset();
			player_run_left->Reset();
			player_run_right->Reset();
			break;
		case(67):  //按下C键
			if (cooling_time_dash >= 0.4)
			{
				is_Down_C = true;
				to_left_when_dash = to_left;
			}
			break;
		case('Z'):
			is_down_z = true;
			is_face_left_when_slash = to_left;
			break;
		case(VK_RETURN):
			is_start = true;
			break;
		}
	}
}


POINT Player::getposition()
{
	return player_pos;
}

bool Player::if_start()
{
	return is_start;
}

void Player::on_update(float delta)
{
	if ((opera_downslash || opera_upslash) && current_animation)
	{
		character::set_logic_center({ current_center().x - 10,current_center().y + 5 });
	}
	else if (current_animation)
	{
		character::set_logic_center({ current_center().x,current_center().y + 5 });
	}
	jump_buffer.add(delta);
	slash_buffer.add(delta);  //劈砍动作计时器
	if (!is_Down_C)//冲刺冷却时间
	{
		cooling_time_dash += delta;
	}
	if (already_land && (is_looped || jump_buffer.time <= 0.1))//清除着陆状态
	{
		already_land = false;
		is_looped = false;
		player_land_left->Reset();
		player_land_right->Reset();
	}
	hurt_box->set_position(get_logic_center());
	character::on_update(delta);
	if (current_animation && player_pos.x + current_animation->frame_list[current_animation->idx_frame]->getwidth() > boundary.x_right) player_pos.x = boundary.x_right - current_animation->frame_list[current_animation->idx_frame]->getwidth();
	else if (player_pos.x <boundary.x_left) player_pos.x = boundary.x_left;


}

void Player::on_render(float delta)
{
	if (current_function == nullptr) return;
	else current_function(delta);
}

void Player::set_attacking(bool attack)
{
	is_attacking = attack;
}

void Player::attack(float delta)
{
	if (is_down_up && !opera_downslash && !opera_plantslash)
	{
		current_animation = player_slash_up;
		current_attack_dir = AttackDir::Up;
		if ((player_slash_up->frame_list[player_slash_up->idx_frame]->getheight() + player_pos.y < 620))
		{
			if (is_Down_Space)
				game_gravity.air_inspection1(delta);
			else if (!is_Down_Space)
				game_gravity.air_inspection3(delta);
			player_pos.y -= game_gravity.v*delta;
			game_gravity.add(delta);
		}
		opera_upslash = true;
		if (!bullet.UpSlashEffect->is_finish_loop)
		{
			bullet.UpSlashEffect->Play(player_pos.x + player_slash_up->frame_list[player_slash_up->idx_frame]->getwidth() / 2 - bullet.UpSlashEffect->frame_list[bullet.UpSlashEffect->NextIdex(delta)]->getwidth() / 2, player_pos.y - bullet.UpSlashEffect->frame_list[bullet.UpSlashEffect->NextIdex(delta)]->getheight() + 20, delta, true, true);
		}
		player_slash_up->Play(player_pos.x, player_pos.y, delta, true, true);
		if (player_slash_up->is_finish_loop) is_loop_slash = true;

	}
	else if (is_down_down && !opera_upslash && !opera_plantslash && is_on_air)
	{
		current_animation = player_slash_down;
		current_attack_dir = AttackDir::Down;
		if ((player_slash_down->frame_list[player_slash_down->idx_frame]->getheight() + player_pos.y < 620))
		{
			game_gravity.air_inspection3(delta);
			player_pos.y -= game_gravity.v*delta;
			game_gravity.add(delta);
		}
		opera_downslash = true;
		if (!bullet.DownSlashEffect->is_finish_loop)
			bullet.DownSlashEffect->Play(player_pos.x + player_slash_down->frame_list[player_slash_down->idx_frame]->getwidth() / 2 - bullet.DownSlashEffect->frame_list[bullet.DownSlashEffect->NextIdex(delta)]->getwidth() / 2, player_pos.y + player_slash_down->frame_list[player_slash_down->idx_frame]->getheight(), delta, true, true);
		player_slash_down->Play(player_pos.x, player_pos.y, delta, true, true);
		if (player_slash_down->is_finish_loop) is_loop_slash = true;
	}
	else {
		opera_plantslash = true;
		//检验下落
		if ((!opera_slash1 && player_slash_left->frame_list[player_slash_left->idx_frame]->getheight() + player_pos.y < 620) || (opera_slash1 && player_pos.y + player_slash_alt_left->frame_list[player_slash_alt_left->idx_frame]->getheight() < 620))
		{
			if (is_Down_Space)
				game_gravity.air_inspection1(delta);
			else if (!is_Down_Space)
				game_gravity.air_inspection3(delta);
			player_pos.y -= game_gravity.v*delta;
			game_gravity.add(delta);
		}
		if (slash_buffer.time >= 0.5 || !opera_slash1)  //攻击间隔大于500ms或者上次执行的是劈砍二时会执行劈砍一
		{

			if (is_face_left_when_slash)
			{
				current_animation = player_slash_left;
				current_attack_dir = AttackDir::Left;
				if (is_Down_Left) player_pos.x -= 600*delta;
				if (!bullet.SlashEffect_left->is_finish_loop)
				{
					
					bullet.SlashEffect_left->Play(player_pos.x - bullet.SlashEffect_left->frame_list[bullet.SlashEffect_left->NextIdex(delta)]->getwidth() + 40, player_pos.y + player_slash_left->frame_list[player_slash_left->NextIdex(delta)]->getheight() / 2 - bullet.SlashEffect_left->frame_list[bullet.SlashEffect_left->idx_frame]->getheight() / 2,delta, true, true);
				}
				player_slash_left->Play(player_pos.x, player_pos.y, delta, true, true);
				player_slash_right->idx_frame = player_slash_left->idx_frame;
				if (player_slash_left->is_finish_loop)
				{
					is_loop_slash = true;
					opera_slash1 = true;
				}
			}
			else
			{
				current_animation = player_slash_right;
				current_attack_dir = AttackDir::Right;
				if (is_Down_Right) player_pos.x += 600 * delta;
				if (!bullet.SlashEffect_right->is_finish_loop)
					bullet.SlashEffect_right->Play(player_pos.x + player_slash_right->frame_list[player_slash_right->NextIdex(delta)]->getwidth(), player_pos.y + player_slash_right->frame_list[player_slash_right->NextIdex(delta)]->getheight() / 2 - bullet.SlashEffect_right->frame_list[bullet.SlashEffect_right->idx_frame]->getheight() / 2,delta, true, true);
				player_slash_right->Play(player_pos.x, player_pos.y, delta, true, true);
				player_slash_left->idx_frame = player_slash_right->idx_frame;
				if (player_slash_right->is_finish_loop)
				{
					is_loop_slash = true;
					opera_slash1 = true;
				}
			}
		}
		else
		{
			if (is_face_left_when_slash)
			{
				current_animation = player_slash_alt_left;
				current_attack_dir = AttackDir::Left;
				if (is_Down_Left) player_pos.x -= 600 * delta;
				if (!bullet.SlashEffectAlt_left->is_finish_loop)
					bullet.SlashEffectAlt_left->Play(player_pos.x - bullet.SlashEffectAlt_left->frame_list[bullet.SlashEffect_left->NextIdex(delta)]->getwidth() + 40, player_pos.y + player_slash_alt_left->frame_list[player_slash_alt_left->NextIdex(delta)]->getheight() / 2 - bullet.SlashEffectAlt_left->frame_list[bullet.SlashEffectAlt_left->idx_frame]->getheight() / 2,delta, true, true);
				player_slash_alt_left->Play(player_pos.x, player_pos.y, delta, true, true);
				if (player_slash_alt_left->is_finish_loop)
				{
					is_loop_slash = true;
					opera_slash1 = false;
				}
			}
			else
			{
				current_animation = player_slash_alt_right;
				current_attack_dir = AttackDir::Right;
				if (is_Down_Right) player_pos.x += 600 * delta;
				if (!bullet.SlashEffectAlt_right->is_finish_loop)
					bullet.SlashEffectAlt_right->Play(player_pos.x + player_slash_alt_right->frame_list[player_slash_alt_right->NextIdex(delta)]->getwidth(), player_pos.y + player_slash_alt_right->frame_list[player_slash_alt_right->NextIdex(delta)]->getheight() / 2 - bullet.SlashEffectAlt_right->frame_list[bullet.SlashEffectAlt_right->idx_frame]->getheight() / 2,delta,true, true);
				player_slash_alt_right->Play(player_pos.x, player_pos.y, delta, true, true);
				player_slash_alt_left->idx_frame = player_slash_alt_right->idx_frame;

				if (player_slash_alt_right->is_finish_loop)
				{
					is_loop_slash = true;
					opera_slash1 = false;
				}

			}
		}
	}
}

void Player::jump(float delta)
{
		is_on_air = true;
		game_gravity.air_inspection1(delta);
		player_pos.y -= game_gravity.v*delta;
		if (game_gravity.v < 0)
		{
			is_starting_down = true;
			is_up = false;
		}
		else
		{
			is_up = true;
		}
		if (is_Down_Left)
		{
			player_pos.x -= 10;
			player_jump_left->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
		}
		else if (is_Down_Right)
		{
			player_pos.x += 10;
			player_jump_right->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
		}
		else if (to_left)
		{
			current_animation = player_jump_left;
			player_jump_left->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
		}
		else
		{
			current_animation = player_jump_right;
			player_jump_right->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
		}
		if (is_starting_down && player_pos.y + player_jump_left->frame_list[player_jump_left->idx_frame]->getheight() >= 619)//判断是否落地
		{
			player_pos.y = 620 - 132 * 0.65;
			game_gravity.reset();
			is_Down_Space = false;
			is_starting_down = false;
			player_jump_left->Reset();
			player_jump_right->Reset();
			is_up = false;
			already_land = true;
			is_on_air = false;
			facing_left_when_land = to_left;
			is_finish_slash = false;
			if (!downing_loose_space)  //只有在落地时还摁着空格才会执行
			{
				is_finish_jump = true;
			}
		}
		game_gravity.add(delta);  //加时
}

void Player::fall(float delta)
{
		if (is_lose_space)//只执行一次
		{
			if (game_gravity.v > 0)
				is_jump_when_slash = true;
			game_gravity.reset();
			is_lose_space = false;
			is_finish_jump = true;
			is_opera_downing_lose_space = true;
			
		}
		game_gravity.air_inspection2(delta);
		player_pos.y -= game_gravity.v*delta;
		if (player_pos.y + player_jump_left->frame_list[player_jump_left->idx_frame]->getheight() < 619)
		{
			if (is_Down_Left)
			{
				player_pos.x -= 600 * delta;
				current_animation = player_jump_left;
				player_jump_left->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
			}
			else if (is_Down_Right)
			{
				player_pos.x += 600 * delta;
				current_animation = player_jump_right;
				player_jump_right->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
			}
			else if (to_left)
			{
				current_animation = player_jump_left;
				player_jump_left->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
			}
			else
			{
				current_animation = player_jump_right;
				player_jump_right->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
			}
		}
		else                                                   //判断是否落地
		{
			player_pos.y = 620 - 132 * 0.65;
			game_gravity.reset();
			is_Down_Space = false;
			is_starting_down = false;
			player_jump_left->Reset();
			player_jump_right->Reset();
			is_lose_space = true;
			is_opera_downing_lose_space = false;
			is_finish_jump = false;
			is_up = false;
			already_land = true;
			facing_left_when_land = to_left;
			is_finish_Dash = false;
			is_on_air = false;
			is_finish_slash = false;
		}
		game_gravity.add(delta);
}

bool Player::is_move()
{
	return (is_Down_Left || is_Down_Right);
}


void Player::land_reset()
{
	if (already_land && (is_looped || jump_buffer.time <= 0.1))//清除着陆状态
	{
		already_land = false;
		is_looped = false;
		player_land_left->Reset();
		player_land_right->Reset();
	}
 }

bool Player::check_land()
{
	return (already_land && !is_looped && jump_buffer.time > 0.1);
	
}

void Player::run(float delta)
{
	if (is_Down_Left)
	{
		is_walk = true;
		player_pos.x -= 600 * delta;
		current_animation = player_run_left;
		player_run_left->Play(player_pos.x, player_pos.y, delta, is_walk);
	}//正在向左跑
	else if (is_Down_Right)
	{
		is_walk = true;
		player_pos.x += 600 * delta;
		current_animation = player_run_right;
		player_run_right->Play(player_pos.x, player_pos.y, delta, is_walk);
	}//正在向右跑
}

bool Player::check_fall()
{
	return ((!is_Down_Space && is_up) || is_finish_Dash || is_finish_slash);
}

bool Player::check_dash()
{
	return (is_Down_C && cooling_time_dash >= 0.4f);
}

bool Player::check_attack()
{
	return (is_down_z && !is_loop_slash);
}

bool Player::check_jump()
{
	return (is_Down_Space || is_starting_down);
}

void Player::exit_attack()
{
	if (opera_upslash)
	{
		is_down_up = false;
		opera_upslash = false;
		player_slash_up->Reset();
		bullet.UpSlashEffect->Reset();
	}
	else  if (opera_downslash)
	{
		is_down_down = false;
		opera_downslash = false;
		player_slash_down->Reset();
		bullet.DownSlashEffect->Reset();
	}
	else
	{
		player_slash_left->Reset();
		player_slash_right->Reset();
		player_slash_alt_left->Reset();
		player_slash_alt_right->Reset();
		bullet.SlashEffectAlt_left->Reset();
		bullet.SlashEffectAlt_right->Reset();
		bullet.SlashEffect_left->Reset();
		bullet.SlashEffect_right->Reset();
		opera_plantslash = false;
	}
	is_down_z = false;
	is_loop_slash = false;
	slash_buffer.reset();
	is_finish_slash = true;
}

void Player::idle(float delta)
{
	if (to_left)
	{
		current_animation = player_left;
		player_left->Play(player_pos.x, player_pos.y, delta);
	}
	else
	{
		current_animation = player_right;
		player_right->Play(player_pos.x, player_pos.y, delta);
	}
}

void Player::dash(float delta)
{
	if (to_left_when_dash)
	{
		current_animation = player_dash_left;
		player_dash_left->Play(player_pos.x, player_pos.y, delta, true, true);
		player_pos.x -= 1440*delta;
		if (player_dash_left->is_finish_loop)
		{
			is_Down_C = false;
			if (!already_land)
				is_finish_Dash = true;
			player_dash_left->Reset();
			cooling_time_dash = 0;
		}
	}
	else
	{
		current_animation = player_dash_right;
		player_dash_right->Play(player_pos.x, player_pos.y, delta, true, true);
		player_pos.x += 1440*delta;
		if (player_dash_right->is_finish_loop)
		{
			is_Down_C = false;
			if (!already_land)
				is_finish_Dash = true;
			player_dash_right->Reset();
			cooling_time_dash = 0;
		}
	}
}

void Player::land(float delta)
{
	if (to_left)
	{
		current_animation = player_land_left;
		player_land_left->Play(player_pos.x, player_pos.y, delta, true, true);
		is_looped = player_land_left->is_finish_loop;
		if (is_Down_Left)
			player_pos.x -= 600 * delta;
	}
	else
	{
		current_animation = player_land_right;
		player_land_right->Play(player_pos.x, player_pos.y, delta, true, true);
		is_looped = player_land_right->is_finish_loop;
		if (is_Down_Right)
			player_pos.x += 600 * delta;
	}
}

void Player::death(float delta)
{

}

bool Player::check_land_reset()
{
	return (already_land && (is_looped || jump_buffer.time <= 0.1));
}

POINT Player::current_center()
{
	if (to_left)
	{
		long logic_x = player_pos.x + 0.65 * current_animation->frame_list[current_animation->idx_frame]->getwidth() / 2;
		long logic_y = player_pos.y + 0.65 * current_animation->frame_list[current_animation->idx_frame]->getheight() / 2;
	    return {logic_x,logic_y};

    }
	return { player_pos.x + current_animation->frame_list[current_animation->idx_frame]->getwidth() / 2,player_pos.y + current_animation->frame_list[current_animation->idx_frame]->getheight() / 2 };
}

POINT Player::current_right()
{
	return { player_pos.x + current_animation->frame_list[current_animation->idx_frame]->getwidth(),player_pos.y + current_animation->frame_list[current_animation->idx_frame]->getheight() };

}

void Player::on_hurt()
{
	if (!is_invulnerable)
	{
		be_hurt = true;
	}
}

void Player::hurt_left(float delta)
{
	if (!recoil_left->is_finish_loop)
	{
		recoil_left->Play(player_pos.x, player_pos.y, delta, true, true);
		player_pos.y -= 60 * delta;
		player_pos.x += 150 * delta;
		if (recoil_left->is_finish_loop)
		{
			to_left = true;
			finish_hurt_animation = true;
		}
	}
}

void Player::hurt_right(float delta)
{
	if (!recoil_right->is_finish_loop)
	{
		recoil_right->Play(player_pos.x, player_pos.y, delta, true, true);
		player_pos.y -= 60 * delta;
		player_pos.x -= 150 * delta;
		if (recoil_right->is_finish_loop)
		{
			to_left = false;
			finish_hurt_animation = true;
		}
	}
}

void Player::reset_hurt()
{
	recoil_left->Reset();
	recoil_right->Reset();
}

void Player::bounce(float delta)
{
	is_on_air = true;
	game_gravity.air_inspection4(delta);
	player_pos.y -= game_gravity.v * delta;
	if (game_gravity.v < 0)
	{
		is_starting_down = true;
		is_up = false;
	}
	else
	{
		is_up = true;
	}
	if (is_Down_Left)
	{
		player_pos.x -= 10;
		player_jump_left->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
	}
	else if (is_Down_Right)
	{
		player_pos.x += 10;
		player_jump_right->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
	}
	else if (to_left)
	{
		current_animation = player_jump_left;
		player_jump_left->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
	}
	else
	{
		current_animation = player_jump_right;
		player_jump_right->Play(player_pos.x, player_pos.y, delta, game_gravity.v);
	}
	if (is_starting_down && player_pos.y + player_jump_left->frame_list[player_jump_left->idx_frame]->getheight() >= 619)//判断是否落地
	{
		player_pos.y = 620 - 132 * 0.65;
		game_gravity.reset();
		is_Down_Space = false;
		is_starting_down = false;
		player_jump_left->Reset();
		player_jump_right->Reset();
		is_up = false;
		already_land = true;
		is_on_air = false;
		facing_left_when_land = to_left;
		is_finish_slash = false;
		if (!downing_loose_space)  //只有在落地时还摁着空格才会执行
		{
			is_finish_jump = true;
		}
	}
	game_gravity.add(delta);  //加时

}

bool Player::check_bounce()
{
	return (opera_downslash&&downslash_hit);
}