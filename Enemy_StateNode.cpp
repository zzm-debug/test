#include"CharacterManager.h"
#include"Enemy_StateNode.h"
#include"CameraManager.h"
int Hash_appear1[4] = { 0 };
int Hash_disappear1[4] = { 0 };

//Dash
Enemy_Dash_Node::Enemy_Dash_Node()
{

}

void Enemy_Dash_Node::on_enter()
{
	srand((unsigned)time(nullptr));
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	if (player->getposition().x < 600)
	{
		dash_left = false;
	}
	else if (player->getposition().x > 680)
	{
		dash_left = true;
	}
	else
	{
		int temp = rand() % 2;
		if (temp) dash_left = false;
		else dash_left = true;;
	}
	if (dash_left)
	{
		enemy->set_current_function("dash_left");
	}
	else
	{
		enemy->set_current_function("dash_right");
	}
}

void Enemy_Dash_Node::on_update(float delta)
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	if (enemy->get_hp() <= 0)
	{
		enemy->switch_state("death_land");
		enemy->finish_dash = false;
	}
	else if (enemy->finish_dash)
	{
		enemy->switch_state("idle_alt");
		enemy->finish_dash = false;
	}

}



bool Enemy_Dash_Node::dash_orientation()
{
	return dash_left;
}

//Dstab
Enemy_Dstab_Node::Enemy_Dstab_Node()
{

}

void Enemy_Dstab_Node::on_enter()
{
	srand((unsigned)time(nullptr));
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	POINT pos = player->getposition();
	if (pos.x >= boundary.x_platform_left && pos.x <= boundary.x_platform_right) pos.x = pos.x;
	else
	{
		if (pos.x >= boundary.x_platform_right) pos.x = boundary.x_platform_right - 0.5 * 342;
		else if (pos.x <= boundary.x_platform_left) pos.x = boundary.x_platform_left + 5;
	}
	enemy->change_enemy_point(pos.x, 75);
	
	temp = rand() % 2;
	if (temp) enemy->set_current_function("dstab_left");
	else
	{
		enemy->set_current_function("dstab_right");
	}
}

void Enemy_Dstab_Node::on_update(float delta)
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	if (enemy->get_hp() <= 0)
	{
		enemy->switch_state("death_land");
		enemy->finish_dstab = false;
	}
	else if (enemy->finish_dstab)
	{
		enemy->switch_state("idle_alt");
		enemy->finish_dstab = false;
	}
}

//Throw
Enemy_Wall_low_Node::Enemy_Wall_low_Node()
{

	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(0.7f);
	timer_throw.set_callback([&]()
		{
			Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
			enemy->throw_projectile(true,is_left);
		}
	);
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(2.7f);
	timer_projectile.set_callback([&]()
		{
			Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
			enemy->switch_state("idle_alt");
			enemy->finish_wall_low = false;
			enemy->finish_wall = false;
		}
	);
}

void Enemy_Wall_low_Node::on_enter()
{
	int temp = rand()%100+1;
	if (temp <= 50) is_left = false;
	else is_left = true;
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	timer_throw.restart();
	timer_projectile.restart();
	if (is_left) enemy->set_current_function("wall_low_left");
	else enemy->set_current_function("wall_low_right");
}

void Enemy_Wall_low_Node::on_update(float delta)
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	timer_throw.update(delta);
	timer_projectile.update(delta);
	if (enemy->get_hp() <= 0)
	{
		enemy->death_left = is_left;
		enemy->switch_state("death_air");
		enemy->finish_wall_low = false;
	}

}



Enemy_Wall_high_Node::Enemy_Wall_high_Node()
{

	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(0.7f);
	timer_throw.set_callback([&]()
		{
			Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
			enemy->throw_projectile(false,is_left);
		}
	);
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(2.7f);
	timer_projectile.set_callback([&]()
		{
			Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
			enemy->switch_state("idle_alt");
			enemy->finish_wall_high = false;
			enemy->finish_wall = false;
		}
	);
}

void Enemy_Wall_high_Node::on_enter()
{
	int temp = rand() % 100 + 1;
	if (temp <= 50) is_left = false;
	else is_left = true;
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	timer_throw.restart();
	timer_projectile.restart();
	if (is_left) enemy->set_current_function("wall_high_left");
	else enemy->set_current_function("wall_high_right");
}

void Enemy_Wall_high_Node::on_update(float delta)
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	timer_throw.update(delta);
	timer_projectile.update(delta);
	if (enemy->get_hp() <= 0)
	{
		enemy->death_left = is_left;
		enemy->switch_state("death_air");		
		enemy->finish_wall_high = false;
	}
}

//Idle
void Enemy_Idle_Node::on_enter()
{

	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	enemy->set_current_function("idle");

	
}

void Enemy_Idle_Node::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	if (player->if_start() && !enemy->if_finish_battle())
	{
		enemy->switch_state("stand");
	}
}

void Enemy_Stand_Node::on_enter()
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();

	enemy->set_current_function("stand");

}

void Enemy_Stand_Node::on_update(float delta)
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	if (enemy->finish_stand)
	{
		enemy->switch_state("leave");
		enemy->finish_stand = false;
	}
}

void Enemy_Leave_Node::on_enter()
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	enemy->set_current_function("leave");
}

void Enemy_Leave_Node::on_update(float delta)
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	if (enemy->finish_leave)
	{
		enemy->switch_state("idle_alt");
		enemy->finish_leave = false;
	}
}

Enemy_Idle_alt_Node::Enemy_Idle_alt_Node()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.4f);
	timer.set_callback([&]()
		{
			Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
			int rand_num = rand() % 120 + 1;
			int loop_num = 0;
			if (Hash_disappear1[1] >= 5)
			{
				if (rand_num <= 60) enemy->switch_state("wall_high");
				else enemy->switch_state("wall_low");
				Hash_appear1[1]=1;
				Hash_appear1[2] = 0, Hash_appear1[3] = 0;
				Hash_disappear1[1] = 0; Hash_disappear1[2]++; Hash_disappear1[3]++;
			}
			else if (Hash_disappear1[2] >= 5)
			{
				enemy->switch_state("dstab");
				Hash_appear1[2]=1;
				Hash_appear1[1] = 0, Hash_appear1[3] = 0;
				Hash_disappear1[2] = 0; Hash_disappear1[1]++; Hash_disappear1[3]++;
				
			}
			else if (Hash_disappear1[3] >= 5)
			{
				enemy->switch_state("dash");
				Hash_appear1[3]=1;
				Hash_appear1[1] = 0, Hash_appear1[2] = 0;
				Hash_disappear1[3] = 0; Hash_disappear1[2]++; Hash_disappear1[1]++;
			}
			else
			{
				while (((rand_num <= 40 && Hash_appear1[1] >= 2) || (rand_num > 40 && rand_num <= 80 && Hash_appear1[2] >= 2) || (rand_num > 80 && Hash_appear1[3] >= 3))&&loop_num<=100)
				{
					rand_num = rand() % 120 + 1;
					loop_num++;
				}
				loop_num = 0;
				if (rand_num <= 20)
				{
					Hash_appear1[1]++;
					Hash_appear1[2] = 0, Hash_appear1[3] = 0;
					Hash_disappear1[1] = 0; Hash_disappear1[2]++; Hash_disappear1[3]++;
					enemy->switch_state("wall_high");
				}
				else if (rand_num <= 40)
				{
					Hash_appear1[1]++;
					Hash_appear1[2] = 0, Hash_appear1[3] = 0;
					Hash_disappear1[1] = 0; Hash_disappear1[2]++; Hash_disappear1[3]++;
					enemy->switch_state("wall_low");
				}
				else if (rand_num <= 80)
				{
					Hash_appear1[2]++;
					Hash_appear1[1] = 0, Hash_appear1[3] = 0;
					Hash_disappear1[2] = 0; Hash_disappear1[1]++; Hash_disappear1[3]++;
					enemy->switch_state("dstab");
				}
				else
				{
					Hash_appear1[3]++;
					Hash_appear1[1] = 0, Hash_appear1[2] = 0;
					Hash_disappear1[3] = 0; Hash_disappear1[2]++; Hash_disappear1[1]++;
					enemy->switch_state("dash");
				}
			}
		});
}

void Enemy_Idle_alt_Node::on_enter()
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	enemy->set_current_function("null");

	timer.restart();
}

void Enemy_Idle_alt_Node::on_update(float delta)
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	timer.update(delta);
	if (enemy->get_hp() <= 0)
	{
		enemy->switch_state("death_land");
	}
}

void Enemy_Idle_alt_Node::on_end()
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	timer.restart();
	
}

Enemy_Death_land_Node::Enemy_Death_land_Node()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(1.2f);
	timer.set_callback([&]()
		{
			Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
			enemy->switch_state("death_leave");
		}
	);
}

void Enemy_Death_land_Node::on_enter()
{
	timer.restart();
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	enemy->set_finish_battle();
	enemy->set_current_function("dead_land");
	enemy->get_hit_box_first()->set_enable(false);
	enemy->get_hit_box_second()->set_enable(false);
	enemy->get_hurt_box()->set_enable(false);
	enemy->set_invulnerable(true);
	enemy->be_death = true;

	if (enemy->get_enemy_pos().x <= 580)
	{
		enemy->set_death_pos(310, 300);
	}
	else
	{
		enemy->set_death_pos(901, 300);
	}
	Camera* camera = CameraManager::instance()->get_camera();
	camera->shake(10, 0.5);
}

void Enemy_Death_land_Node::on_update(float delta)
{
	timer.update(delta);
}

void Enemy_Death_land_Node::on_end()
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	enemy->set_invulnerable(false);
	enemy->set_enemy_pos(enemy->get_death_pos().x+50, enemy->get_death_pos().y);
}

Enemy_Death_air_Node::Enemy_Death_air_Node()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.8f);
	timer.set_callback([&]()
		{
			Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
			enemy->switch_state("death_leave");
		}
	);
}

void Enemy_Death_air_Node::on_enter()
{
	timer.restart();
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	enemy->set_finish_battle();
	if (enemy->death_left)
		enemy->set_death_pos(enemy->get_enemy_pos().x - 40, enemy->get_enemy_pos().y);
	else
		enemy->set_death_pos(enemy->get_enemy_pos().x, enemy->get_enemy_pos().y);
	enemy->set_current_function("dead_land");
	enemy->get_hit_box_first()->set_enable(false);
	enemy->get_hit_box_second()->set_enable(false);
	enemy->get_hurt_box()->set_enable(false);
	enemy->set_invulnerable(true);
	enemy->be_death = true;
	Camera* camera = CameraManager::instance()->get_camera();
	camera->shake(10, 0.5f);
}

void Enemy_Death_air_Node::on_update(float delta)
{
	timer.update(delta);
}

void Enemy_Death_air_Node::on_end()
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	enemy->set_invulnerable(false);
}

Enemy_Death_leave_Node::Enemy_Death_leave_Node()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(1.0f);
	timer.set_callback([&]()
		{
			Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
			enemy->death_leave_reset();
			enemy->switch_state("back");
		}
	);
}

void Enemy_Death_leave_Node::on_enter()
{
	timer.restart();
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	if (enemy->death_left) enemy->set_current_function("death_leave_right");
	else enemy->set_current_function("death_leave_left");
}

void Enemy_Death_leave_Node::on_update(float delta)
{
	timer.update(delta);

}

void Enemy_Death_leave_Node::on_end()
{	

}

Enemy_Back_Node::Enemy_Back_Node()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.3f);
	timer.set_callback([&]() {

		Player* player = (Player*)CharacterManager::instance()->get_player();
		player->start_next_battle = true;

		}
	);
}

void  Enemy_Back_Node::on_enter()
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	enemy->set_current_function("back_right");
	timer.restart();
}

void  Enemy_Back_Node::on_update(float delta)
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	timer.update(delta);
	if (enemy->finish_back)
	{
		enemy->finish_back = false;
	}
}
	