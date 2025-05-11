#include"StateNode.h"
#include"Timer.h"
#include<stdbool.h>
#include"collision.h"
#include"Enemy_StateNode2.h"
#include"CharacterManager.h"
#include"CameraManager.h"

int Hash_appear2[5];
int Hash_disappear2[5];

void Enemy_Idle_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_current_function("idle");
}

void Enemy_Idle_Node2::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	if (player->start_next_battle)
	{
		enemy2->switch_state("stand");
	}
    
}


void Enemy_Stand_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_current_function("stand");
}

void Enemy_Stand_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	if (enemy2->finish_stand)
	{
		enemy2->switch_state("leave");
		enemy2->finish_stand = false;
	}
}

void Enemy_Leave_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_current_function("leave");
	enemy2->start_game2 = true;
}

void Enemy_Leave_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	if (enemy2->finish_leave)
	{
		enemy2->switch_state("idle_alt");
		enemy2->finish_leave = false;
	}
	cout << "enemy2=" << enemy2->get_enemy_pos().x << endl;
}

Enemy_Idle_alt_Node2::Enemy_Idle_alt_Node2()
{
	
}

void Enemy_Idle_alt_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_current_function("null");
}

void Enemy_Idle_alt_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
	}
	else if (enemy3->get_hp() <= 0)
	{
		enemy2->switch_state("idle_alt_re");
	}
}

Enemy_DashDash_Node2::Enemy_DashDash_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(1.5f);
	timer.set_callback([&]() {

		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		enemy3->switch_state("dashdash");

		});
}

void Enemy_DashDash_Node2::on_enter()
{
	timer.restart();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Player* player = (Player*)CharacterManager::instance()->get_player();
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
		enemy2->set_current_function("dash_left");
	}
	else
	{
		enemy2->set_current_function("dash_right");
	}

}

void Enemy_DashDash_Node2::on_update(float delta)
{
	timer.update(delta);
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
		enemy2->finish_dash = false;
	}
	else if (enemy2->finish_dash)
	{
		if (enemy3->get_hp() <= 0)
		{
			enemy2->switch_state("idle_alt_re");
		}
		else
		{
			enemy2->switch_state("idle_alt");
		}
		enemy2->finish_dash = false;
	}
}

Enemy_DstabDash_Node2::Enemy_DstabDash_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.8f);
	timer.set_callback([&]() {
		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		enemy3->switch_state("dstabdash");

		});
}

void Enemy_DstabDash_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer.restart();
	Player* player = (Player*)CharacterManager::instance()->get_player();
	POINT pos = player->getposition();
	if (pos.x >= boundary.x_platform_left && pos.x <= boundary.x_platform_right) pos.x = pos.x;
	else
	{
		if (pos.x >= boundary.x_platform_right) pos.x = boundary.x_platform_right - 0.5 * 342;
		else if (pos.x <= boundary.x_platform_left) pos.x = boundary.x_platform_left + 5;
	}
	enemy2->change_enemy_point(pos.x, 75);

	temp = rand() % 2;
	if (temp) enemy2->set_current_function("dstab_left");
	else
	{
		enemy2->set_current_function("dstab_right");
	}
}

void Enemy_DstabDash_Node2::on_update(float delta)
{
	timer.update(delta);
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
		enemy2->finish_dstab = false;
	}
	else if (enemy2->finish_dstab)
	{
		if (enemy3->get_hp() <= 0)
		{
			enemy2->switch_state("idle_alt_re");
		}
		else
		{
			enemy2->switch_state("idle_alt");
		}
		enemy2->finish_dstab = false;
	}

}

Enemy_DashDstab_Node2::Enemy_DashDstab_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(1.5f);
	timer.set_callback([&]() {

		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		enemy3->switch_state("dashdstab");

		});
}

void Enemy_DashDstab_Node2::on_enter()
{
	timer.restart();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Player* player = (Player*)CharacterManager::instance()->get_player();
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
		enemy2->set_current_function("dash_left");
	}
	else
	{
		enemy2->set_current_function("dash_right");
	}
}

void Enemy_DashDstab_Node2::on_update(float delta)
{
	timer.update(delta);
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
		enemy2->finish_dash = false;
	}
	else if (enemy2->finish_dash)
	{
		if (enemy3->get_hp() <= 0)
		{
			enemy2->switch_state("idle_alt_re");
		}
		else
		{
			enemy2->switch_state("idle_alt");
		}
		enemy2->finish_dash = false;
	}
}

Enemy_DstabDstab_Node2::Enemy_DstabDstab_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.75f);
	timer.set_callback([&]() {
		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		enemy3->switch_state("dstabdstab");

		});

}

void Enemy_DstabDstab_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer.restart();
	Player* player = (Player*)CharacterManager::instance()->get_player();
	POINT pos = player->getposition();
	if (pos.x >= boundary.x_platform_left && pos.x <= boundary.x_platform_right) pos.x = pos.x;
	else
	{
		if (pos.x >= boundary.x_platform_right) pos.x = boundary.x_platform_right - 0.5 * 342;
		else if (pos.x <= boundary.x_platform_left) pos.x = boundary.x_platform_left + 5;
	}
	enemy2->change_enemy_point(pos.x, 75);

	temp = rand() % 2;
	if (temp) enemy2->set_current_function("dstab_left");
	else
	{
		enemy2->set_current_function("dstab_right");
	}
}

void Enemy_DstabDstab_Node2::on_update(float delta)
{
	timer.update(delta);
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
		enemy2->finish_dstab = false;
	}
	else if (enemy2->finish_dstab)
	{
		if (enemy3->get_hp() <= 0)
		{
			enemy2->switch_state("idle_alt_re");
		}
		else
		{
			enemy2->switch_state("idle_alt");
		}
		enemy2->finish_dstab = false;
	}
}

void Enemy_MeanwhileDash_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_current_function("dash_left");
}

void Enemy_MeanwhileDash_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
		enemy2->finish_dash = false;
	}
	else if (enemy2->finish_dash)
	{
		if (enemy3->get_hp() <= 0)
		{
			enemy2->switch_state("idle_alt_re");
		}
		else
		{
			enemy2->switch_state("idle_alt");
		}
		enemy2->finish_dash = false;
	}

}

Enemy_Wall_short_Node2::Enemy_Wall_short_Node2()
{
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(0.7f);
	timer_projectile.set_callback([&]() {

		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		enemy2->throw_projectile(true,true , true);

		});
	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(2.7f);
	timer_throw.set_callback([&]() {

		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		if (enemy3->get_hp() <= 0)
		{
			enemy2->switch_state("idle_alt_re");
			enemy2->finish_wall_high = false;
			enemy2->finish_wall = false;
		}
		else
		{
			enemy2->switch_state("idle_alt");
			enemy2->finish_wall_high = false;
			enemy2->finish_wall = false;
		}

		});
}

void Enemy_Wall_short_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer_throw.restart();
	timer_projectile.restart();
	enemy2->set_current_function("wall_high_left");
	is_left = true;
}

void Enemy_Wall_short_Node2::on_update(float delta)
{
	timer_throw.update(delta);
	timer_projectile.update(delta);
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->death_left = true;
		enemy2->switch_state("death_air");
		enemy2->finish_wall_high = false;
	}

}

Enemy_Wall_wide_Node2::Enemy_Wall_wide_Node2()
{
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(0.7f);
	timer_projectile.set_callback([&]() {

		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		enemy2->throw_projectile(false, true, true);

		});
	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(2.7f);
	timer_throw.set_callback([&]() {

		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		if (enemy3->get_hp() <= 0)
		{
			enemy2->switch_state("idle_alt_re");
			enemy2->finish_wall_high = false;
			enemy2->finish_wall = false;
		}
		else
		{
			enemy2->switch_state("idle_alt");
			enemy2->finish_wall_high = false;
			enemy2->finish_wall = false;
		}

		});
}

void Enemy_Wall_wide_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer_throw.restart();
	timer_projectile.restart();
	enemy2->set_current_function("wall_high_left");
	is_left = true;
}

void Enemy_Wall_wide_Node2::on_update(float delta)
{
	timer_throw.update(delta);
	timer_projectile.update(delta);
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->death_left = true;
		enemy2->switch_state("death_air");
		enemy2->finish_wall_high = false;
	}
}



void Enemy_Restore_Dash_Node2::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
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
		enemy2->set_current_function("dash_left");
	}
	else
	{
		enemy2->set_current_function("dash_right");
	}

}

void Enemy_Restore_Dash_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
		enemy2->finish_dash = false;
	}
	else if (enemy2->finish_dash)
	{
		enemy2->switch_state("idle_alt_re");
		enemy2->finish_dash = false;
	}

}

void Enemy_Restore_Dstab_Node2::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	POINT pos = player->getposition();
	if (pos.x >= boundary.x_platform_left && pos.x <= boundary.x_platform_right) pos.x = pos.x;
	else
	{
		if (pos.x >= boundary.x_platform_right) pos.x = boundary.x_platform_right - 0.5 * 342;
		else if (pos.x <= boundary.x_platform_left) pos.x = boundary.x_platform_left + 5;
	}
	enemy2->change_enemy_point(pos.x, 75);

	temp = rand() % 2;
	if (temp) enemy2->set_current_function("dstab_left");
	else
	{
		enemy2->set_current_function("dstab_right");
	}
}

void Enemy_Restore_Dstab_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
		enemy2->finish_dstab = false;
	}
	else if (enemy2->finish_dstab)
	{
		enemy2->switch_state("idle_alt_re");
		enemy2->finish_dstab = false;
	}

}

Enemy_Restore_Wall_low_Node2::Enemy_Restore_Wall_low_Node2()
{
	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(0.7f);
	timer_throw.set_callback([&]()
		{
			Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
			enemy2->throw_projectile(true, is_left);
		}
	);
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(2.7f);
	timer_projectile.set_callback([&]()
		{
			Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();

			enemy2->switch_state("idle_alt_re");
			enemy2->finish_wall_low = false;
			enemy2->finish_wall = false;
		}
	);
}

void Enemy_Restore_Wall_low_Node2::on_enter()
{
	int temp = rand() % 100 + 1;
	if (temp <= 50) is_left = false;
	else is_left = true;
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer_throw.restart();
	timer_projectile.restart();
	if (is_left) enemy2->set_current_function("wall_low_left");
	else enemy2->set_current_function("wall_low_right");
}

void Enemy_Restore_Wall_low_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer_throw.update(delta);
	timer_projectile.update(delta);
	if (enemy2->get_hp() <= 0)
	{
		enemy2->death_left = is_left;
		enemy2->switch_state("death_air");
		enemy2->finish_wall_low = false;
	}
}

Enemy_Restore_Wall_high_Node2::Enemy_Restore_Wall_high_Node2()
{
	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(0.7f);
	timer_throw.set_callback([&]()
		{
			Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
			enemy2->throw_projectile(false, is_left);
		}
	);
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(2.7f);
	timer_projectile.set_callback([&]()
		{
			Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
			enemy2->switch_state("idle_alt_re");
			enemy2->finish_wall_high = false;
			enemy2->finish_wall = false;
		}
	);
}

void Enemy_Restore_Wall_high_Node2::on_enter()
{
	int temp = rand() % 100 + 1;
	if (temp <= 50) is_left = false;
	else is_left = true;
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer_throw.restart();
	timer_projectile.restart();
	if (is_left) enemy2->set_current_function("wall_high_left");
	else enemy2->set_current_function("wall_high_right");
}

void Enemy_Restore_Wall_high_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer_throw.update(delta);
	timer_projectile.update(delta);
	if (enemy2->get_hp() <= 0)
	{
		enemy2->death_left = is_left;
		enemy2->switch_state("death_air");
		enemy2->finish_wall_high = false;
	}
}

Enemy_Restore_Idle_alt_Node2::Enemy_Restore_Idle_alt_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.4f);
	timer.set_callback([&]()
		{
			Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
			int rand_num = rand() % 120 + 1;
			int loop_num = 0;
			if (Hash_disappear2[1] >= 5)
			{
				if (rand_num <= 60) enemy2->switch_state("wall_high_re");
				else enemy2->switch_state("wall_low_re");
				Hash_appear2[1] = 1;
				Hash_appear2[2] = 0, Hash_appear2[3] = 0;
				Hash_disappear2[1] = 0; Hash_disappear2[2]++; Hash_disappear2[3]++;
			}
			else if (Hash_disappear2[2] >= 5)
			{
				enemy2->switch_state("dstab_re");
				Hash_appear2[2] = 1;
				Hash_appear2[1] = 0, Hash_appear2[3] = 0;
				Hash_disappear2[2] = 0; Hash_disappear2[1]++; Hash_disappear2[3]++;

			}
			else if (Hash_disappear2[3] >= 5)
			{
				enemy2->switch_state("dash_re");
				Hash_appear2[3] = 1;
				Hash_appear2[1] = 0, Hash_appear2[2] = 0;
				Hash_disappear2[3] = 0; Hash_disappear2[2]++; Hash_disappear2[1]++;
			}
			else
			{
				while (((rand_num <= 40 && Hash_appear2[1] >= 2) || (rand_num > 40 && rand_num <= 80 && Hash_appear2[2] >= 2) || (rand_num > 80 && Hash_appear2[3] >= 3))&&loop_num<=100)
				{
					rand_num = rand() % 120 + 1;
					loop_num++;
				}
				loop_num = 0;
				if (rand_num <= 20)
				{
					Hash_appear2[1]++;
					Hash_appear2[2] = 0, Hash_appear2[3] = 0;
					Hash_disappear2[1] = 0; Hash_disappear2[2]++; Hash_disappear2[3]++;
					enemy2->switch_state("wall_high_re");
				}
				else if (rand_num <= 40)
				{
					Hash_appear2[1]++;
					Hash_appear2[2] = 0, Hash_appear2[3] = 0;
					Hash_disappear2[1] = 0; Hash_disappear2[2]++; Hash_disappear2[3]++;
					enemy2->switch_state("wall_low_re");
				}
				else if (rand_num <= 80)
				{
					Hash_appear2[2]++;
					Hash_appear2[1] = 0, Hash_appear2[3] = 0;
					Hash_disappear2[2] = 0; Hash_disappear2[1]++; Hash_disappear2[3]++;
					enemy2->switch_state("dstab_re");
				}
				else
				{
					Hash_appear2[3]++;
					Hash_appear2[1] = 0, Hash_appear2[2] = 0;
					Hash_disappear2[3] = 0; Hash_disappear2[2]++; Hash_disappear2[1]++;
					enemy2->switch_state("dash_re");
				}
			}
		}
	);
}

void Enemy_Restore_Idle_alt_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_current_function("null");

	timer.restart();
}

void Enemy_Restore_Idle_alt_Node2::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer.update(delta);
	if (enemy2->get_hp() <= 0)
	{
		enemy2->switch_state("death_land");
	}
}

Enemy_Dead_Land_Node2::Enemy_Dead_Land_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(1.2f);
	timer.set_callback([&]()
		{
			Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
			enemy2->switch_state("death_leave");
		}
	);
}

void Enemy_Dead_Land_Node2::on_enter()
{
	timer.restart();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_current_function("dead_land");
	enemy2->get_hit_box_first()->set_enable(false);
	enemy2->get_hit_box_second()->set_enable(false);
	enemy2->get_hurt_box()->set_enable(false);
	enemy2->set_invulnerable(true);
	enemy2->be_death = true;

	if (enemy2->get_enemy_pos().x <= 580)
	{
		enemy2->set_death_pos(310, 300);
	}
	else
	{
		enemy2->set_death_pos(901, 300);
	}
	Camera* camera = CameraManager::instance()->get_camera();
	camera->shake(10, 0.5);
}

void Enemy_Dead_Land_Node2::on_update(float delta)
{
	timer.update(delta);
}

void Enemy_Dead_Land_Node2::on_end()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_invulnerable(false);
	enemy2->set_enemy_pos(enemy2->get_death_pos().x + 50, enemy2->get_death_pos().y);
}

Enemy_Dead_Air_Node2::Enemy_Dead_Air_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.8f);
	timer.set_callback([&]()
		{
			Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
			enemy2->switch_state("death_leave");
		}
	);
}

void Enemy_Dead_Air_Node2::on_enter()
{
	timer.restart();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	if(enemy2->death_left)
	enemy2->set_death_pos(enemy2->get_enemy_pos().x-40, enemy2->get_enemy_pos().y);
	else
		enemy2->set_death_pos(enemy2->get_enemy_pos().x, enemy2->get_enemy_pos().y);
	enemy2->set_current_function("dead_land");
	enemy2->get_hit_box_first()->set_enable(false);
	enemy2->get_hit_box_second()->set_enable(false);
	enemy2->get_hurt_box()->set_enable(false);
	enemy2->set_invulnerable(true);
	enemy2->be_death = true;
	Camera* camera = CameraManager::instance()->get_camera();
	camera->shake(10, 0.5);
}

void Enemy_Dead_Air_Node2::on_update(float delta)
{
	timer.update(delta);
}

void Enemy_Dead_Air_Node2::on_end()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_invulnerable(false);
}

Enemy_Dead_Leave_Node2::Enemy_Dead_Leave_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(1.0f);
	timer.set_callback([&]()
		{
			Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
			enemy2->death_leave_reset();
			enemy2->switch_state("back");
		}
	);
}

void Enemy_Dead_Leave_Node2::on_enter()
{
	timer.restart();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	if (enemy2->death_left) enemy2->set_current_function("death_leave_right");
	else enemy2->set_current_function("death_leave_left");
}

void Enemy_Dead_Leave_Node2::on_update(float delta)
{
	timer.update(delta);
}

Enemy_Back_Node2::Enemy_Back_Node2()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(3.0f);
	timer.set_callback([&]() {

		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		if (enemy3->be_death && enemy2->be_death)
		{
			MessageBox(GetHWnd(), _T("ÈÎÎñ³É¹¦"), _T("ÓÎÏ·½áÊø"), MB_OK);
			exit(0);
		}
		
		}
	);
}

void Enemy_Back_Node2::on_enter()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	enemy2->set_current_function("back_right");
}

void Enemy_Back_Node2::on_update(float delta)
{
	timer.update(delta);
}
