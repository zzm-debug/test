#include"CharacterManager.h"
#include"Player_StateNode.h"
#include"collision.h"
#include<windows.h>
#include"CameraManager.h"


PlayerAttackState::PlayerAttackState()
{
	timer.set_wait_time(0.3f);
	timer.set_one_shotted(true);
	timer.set_callback([&]()
		{
			Player* player = (Player*)CharacterManager::instance()->get_player();
			player->set_attacking(false);
		});
}

void PlayerAttackState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_current_function("attack");
	player->set_attacking(true);
	player->get_hit_box_first()->set_enable(true);
	player->get_hit_box_second()->set_enable(true);
	update_hit_box_position();
	timer.restart();
	int rand_num = rand() % 30;
	if (rand_num <= 10)
		PlaySound(_T("Effect/AudioClip/sword_2.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else if (rand_num <= 20)
		PlaySound(_T("Effect/AudioClip/sword_3.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound(_T("Effect/AudioClip/sword_4.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void PlayerAttackState::on_update(float delta)
{
	timer.update(delta);
	update_hit_box_position();
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0) player->switch_state("death");
	else if (player->be_hurt) player->switch_state("recoil");
	else if (player->check_land())
	{
		player->switch_state("land");
	}
	else if (player->check_bounce())
	{
		player->switch_state("bounce");
	}
	else if (player->check_dash())
	{
		player->switch_state("dash");
	}
	else if (!player->check_attack())
	{
		if (player->check_fall())
		{
			player->switch_state("fall");
		}
		else if (player->is_move())
		{
			player->switch_state("run");
		}
		else if (!player->is_move())
		{
			player->switch_state("idle");
		}
	}
}

void PlayerAttackState::on_end()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->get_hit_box_first()->set_enable(false);
	player->get_hit_box_second()->set_enable(false);
	player->set_attacking(false);
	player->exit_attack();
}

void PlayerAttackState::update_hit_box_position()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	POINT hit_box_pos = player->getposition();
	CollisionBox* hit_box_first = player->get_hit_box_first();
	CollisionBox* hit_box_second = player->get_hit_box_second();
	POINT hit_box_size_first = player->get_hit_box_first()->get_size();
	POINT hit_box_size_second = player->get_hit_box_second()->get_size();

	POINT hit_box_current_pos_first = { 0 };
	POINT hit_box_current_pos_second = { 0 };

	switch (player->get_attack_dir())
	{
	case Player::AttackDir::Left:
		hit_box_current_pos_first = { hit_box_pos.x - hit_box_size_first.x / 2,player->current_center().y };
		hit_box_current_pos_second = { 0 };
		break;

	case Player::AttackDir::Right:
		hit_box_current_pos_first = { player->current_right().x + hit_box_size_first.x / 2,player->current_center().y };
		hit_box_current_pos_second = { 0 };

		break;

	case Player::AttackDir::Up:
		hit_box_current_pos_second = { player->current_center().x,hit_box_pos.y - hit_box_size_second.y / 2 };
		hit_box_current_pos_first = { 0 };

		break;

	case Player::AttackDir::Down:
		hit_box_current_pos_second = { player->current_center().x,player->current_right().y + hit_box_size_second.y / 2 };
		hit_box_current_pos_first = { 0 };
		break;
	}
	hit_box_first->set_position(hit_box_current_pos_first);
	hit_box_second->set_position(hit_box_current_pos_second);
}


PlayerDeathState::PlayerDeathState()
{
	timer.set_wait_time(0.5f);
	timer.set_one_shotted(true);
	timer.set_callback([&]()
		{
			MessageBox(GetHWnd(),_T("任务失败"), _T("游戏结束"), MB_OK);
			exit(0);
		});
}

void PlayerDeathState::on_enter()
{
	Player* player=(Player*)CharacterManager::instance()->get_player();
	player->set_current_function("death");
	timer.restart();
}

void PlayerDeathState::on_update(float delta)
{
	timer.update(delta);
}

void PlayerFallState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_current_function("fall");
}

void PlayerFallState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0) player->switch_state("death");
	else if (player->be_hurt) player->switch_state("recoil");
	else if (player->check_land())
	{
		player->switch_state("land");
	}
	else if (player->check_dash())
	{
		player->switch_state("dash");
	}
	else if (player->check_attack())
	{
		player->switch_state("attack");
	}
	else if (!player->check_fall())
	{
	if (player->is_move())
	{
		player->switch_state("run");
	}
	else
	{
		player->switch_state("idle");
	}
	}
}

void PlayerIdleState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_current_function("idle");
}

void PlayerIdleState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0) player->switch_state("death");
	else if (player->be_hurt) player->switch_state("recoil");
	else if (player->check_land())
	{
		player->switch_state("land");
	}
	else if (player->check_dash())
	{
		player->switch_state("dash");
	}
	else if (player->check_attack())
	{
		player->switch_state("attack");
	}
	else if (player->check_jump())
	{
		player->switch_state("jump");
	}
	else if (player->is_move())
	{
		player->switch_state("run");
	}
}

void PlayerIdleState::on_end()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->get_current_animation()->Reset();
}

void PlayerJumpState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_current_function("jump");
}

void PlayerJumpState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0)
	{
		player->switch_state("death");
	}
	else if (player->be_hurt) player->switch_state("recoil");
	else if (player->check_land())
	{
		player->switch_state("land");
	}
	else if (player->check_dash())
	{
		player->switch_state("dash");
	}
	else if (player->check_attack())
	{
		player->switch_state("attack");
	}
	else if (!player->check_jump())
	{
		if (player->check_fall())
		{
			player->switch_state("fall");
		}
		else if (player->is_move())
		{
			player->switch_state("run");
		}
		else
		{
			player->switch_state("idle");
		}
	}
}

void PlayerDashState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_current_function("dash");
}

void PlayerDashState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0)
	{
		player->switch_state("death");
	}
	else if (player->be_hurt) player->switch_state("recoil");
	else if (player->check_land())
	{
		player->switch_state("land");
	}
	else if (!player->check_dash())
	{
		if (player->check_attack())
		{
			player->switch_state("attack");
		}
		else if (player->check_fall())
		{
			player->switch_state("fall");
		}
		else if (player->check_jump())
		{
			player->switch_state("jump");
		}
		else if (player->is_move())
		{
			player->switch_state("run");
		}
		else
		{
			player->switch_state("idle");
		}
	}
}

void PlayerLandState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_current_function("land");
}

void PlayerLandState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0)
	{
		player->switch_state("death");
	}
	else if (player->be_hurt) player->switch_state("recoil");
	else if (!player->check_land())
	{
		if (!player->check_dash())
		{
			player->switch_state("dash");
		}
		if (player->check_attack())
		{
			player->switch_state("attack");
		}
		else if (player->check_fall())
		{
			player->switch_state("fall");
		}
		else if (player->check_jump())
		{
			player->switch_state("jump");
		}
		else if (player->is_move())
		{
			player->switch_state("run");
		}
		else
		{
			player->switch_state("idle");
		}
	}
}


void PlayerRunState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_current_function("run");
}

void PlayerRunState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0)
	{
		player->switch_state("death");
	}
	else if (player->be_hurt) player->switch_state("recoil");
	else if (player->check_dash())
	{
		player->switch_state("dash");
	}
	else if (player->check_attack())
	{
		player->switch_state("attack");
	}
	else if (player->check_jump())
	{
		player->switch_state("jump");
	}
	else if (player->check_fall())
	{
		player->switch_state("fall");
	}
	else if (!player->is_move())
	{
		player->switch_state("idle");
	}
}

PlayerHurtState::PlayerHurtState()
{
	timer_sleep.set_one_shotted(true);
	timer_sleep.set_wait_time(0.05f);
	timer_sleep.set_callback([&]() {

		Sleep(300);
		});
}

void PlayerHurtState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Camera* camera = CameraManager::instance()->get_camera();
	if (player->get_hurt_box()->orientation)
	{
		player->set_current_function("recoil_right");
		
	}
	else
	{
		player->set_current_function("recoil_left");
	}
	camera->shake(10, 0.5);
}

void PlayerHurtState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	timer_sleep.update(delta);
	if (player->finish_hurt_animation)
	{
		if (player->get_hp() <= 0) player->switch_state("death");
		else 
		{
			player->switch_state("fall");
		}

	}
}

void PlayerHurtState::on_end()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->be_hurt = false;
	player->finish_hurt_animation = false;
	player->reset_hurt();
}


void PlayerBounceState::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->set_current_function("bounce");
	
	player->get_game_gravity().init4();
	cout << "v=" << player->get_game_gravity().get_v() << endl;
	player->downslash_hit = false;

}

void PlayerBounceState::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() <= 0)
	{
		player->switch_state("death");
	}
	else if (player->be_hurt) player->switch_state("recoil");
	else if (player->check_land())
	{
		player->switch_state("land");
	}
	else if (player->check_dash())
	{
		player->switch_state("dash");
	}
	else if (player->check_attack())
	{
		player->switch_state("attack");
	}
}

void PlayerBounceState::on_end()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	player->downslash_hit = false;
}