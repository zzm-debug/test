#include"collision.h"
#include"Enemy_StateNode3.h"
#include"CharacterManager.h"
#include"Enemy_StateNode.h"
#include"CameraManager.h"

int Hash_appear[8] = { 0 };
int Hash_disappear[9] = { 0 };

int Hash_appear3[5] = { 0 };
int Hash_disappear3[5] = { 0 };

void Enemy_Idle_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("idle");
}

void Enemy_Idle_Node3::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (player->start_next_battle)
	{
		enemy3->switch_state("stand");
	}
}

void Enemy_Stand_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("stand");
}

void Enemy_Stand_Node3::on_update(float delta)
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->finish_stand)
	{
		enemy3->switch_state("leave");
		enemy3->finish_stand = false;
	}
}

void Enemy_Leave_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("leave");
}

void Enemy_Leave_Node3::on_update(float delta)
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->finish_leave)
	{
		enemy3->switch_state("idle_alt");
		enemy3->finish_leave = false;
	}
}

Enemy_Idle_alt_Node3::Enemy_Idle_alt_Node3()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.4f);
	timer.set_callback([&]() {

		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		int rand_num = rand() % 140 + 1;
		int loop_num = 0;
		if (Hash_disappear[1] >= 10)
		{
			enemy2->switch_state("dashdash");
			Hash_appear[1]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
			Hash_disappear[1] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[7]++;
		}
		else if (Hash_disappear[2] >= 10)
		{
			enemy2->switch_state("dstabdstab");
			Hash_appear[2]++; Hash_appear[1] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
			Hash_disappear[2] = 0; Hash_disappear[1]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[7]++;
		}
		else if (Hash_disappear[3] >= 10)
		{
			enemy2->switch_state("dashdstab");
			Hash_appear[3]++; Hash_appear[2] = 0, Hash_appear[1] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
			Hash_disappear[3] = 0; Hash_disappear[2]++; Hash_disappear[1]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[7]++;
		}
		else if (Hash_disappear[4] >= 10)
		{
			enemy2->switch_state("dstabdash");
			Hash_appear[4]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[1] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
			Hash_disappear[4] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[1]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[7]++;
		}
		else if (Hash_disappear[5] >= 10)
		{
			enemy2->switch_state("meanwhiledash");
			enemy3->switch_state("meanwhiledash");
			Hash_appear[5]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[1] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
			Hash_disappear[5] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[1]++; Hash_disappear[6]++; Hash_disappear[7]++;
		}
		else if (Hash_disappear[6] >= 12)
		{
			enemy2->switch_state("wall_short");
			enemy3->switch_state("wall_short");
			Hash_appear[6]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[1] = 0, Hash_appear[7] = 0;
			Hash_disappear[6] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[1]++; Hash_disappear[7]++;
		}
		else if (Hash_disappear[7] >= 12)
		{
			enemy2->switch_state("wall_wide");
			enemy3->switch_state("wall_wide");
			Hash_appear[7]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[1] = 0;
			Hash_disappear[7] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[1]++;
		}
		else
		{
			while (((rand_num <= 20 && Hash_appear[1] >= 2) || (rand_num <= 40 && rand_num > 20 && Hash_appear[2] >= 2) || (rand_num <= 60 && rand_num > 40 && Hash_appear[3] >= 2) || (rand_num > 60 && rand_num <= 80 && Hash_appear[4] >= 2) || (rand_num > 80 && rand_num <= 100 && Hash_appear[5] >= 2) || (rand_num > 100 && rand_num <= 120 && Hash_appear[6] >= 1) || (rand_num > 120 && rand_num <= 140 && Hash_appear[7] >= 1))&&loop_num<=100)
			{
				rand_num = rand() % 140 + 1;
				loop_num++;
			}
			loop_num = 0;
			if (rand_num <= 20)
			{
				enemy2->switch_state("dashdash");
				Hash_appear[1]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
				Hash_disappear[1] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[7]++;
			}
			else if (rand_num <= 40)
			{
				enemy2->switch_state("dstabdstab");
				Hash_appear[2]++; Hash_appear[1] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
				Hash_disappear[2] = 0; Hash_disappear[1]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[7]++;
			}
			else if (rand_num <= 60)
			{
				enemy2->switch_state("dashdstab");
				Hash_appear[3]++; Hash_appear[2] = 0, Hash_appear[1] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
				Hash_disappear[3] = 0; Hash_disappear[2]++; Hash_disappear[1]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[7]++;
			}
			else if (rand_num <= 80)
			{
				enemy2->switch_state("dstabdash");
				Hash_appear[4]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[1] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
				Hash_disappear[4] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[1]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[7]++;
			}
			else if (rand_num <= 100)
			{
				enemy2->switch_state("meanwhiledash");
				enemy3->switch_state("meanwhiledash");
				Hash_appear[5]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[1] = 0, Hash_appear[6] = 0, Hash_appear[7] = 0;
				Hash_disappear[5] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[1]++; Hash_disappear[6]++; Hash_disappear[7]++;
			}
			else if (rand_num <= 120)
			{
				enemy2->switch_state("wall_short");
				enemy3->switch_state("wall_short");
				Hash_appear[6]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[1] = 0, Hash_appear[7] = 0;
				Hash_disappear[6] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[1]++; Hash_disappear[7]++;
			}
			else
			{
				enemy2->switch_state("wall_wide");
				enemy3->switch_state("wall_wide");
				Hash_appear[7]++; Hash_appear[2] = 0, Hash_appear[3] = 0, Hash_appear[4] = 0, Hash_appear[5] = 0, Hash_appear[6] = 0, Hash_appear[1] = 0;
				Hash_disappear[7] = 0; Hash_disappear[2]++; Hash_disappear[3]++; Hash_disappear[4]++; Hash_disappear[5]++; Hash_disappear[6]++; Hash_disappear[1]++;
			}
		}

		});
}

void Enemy_Idle_alt_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("null");
	timer.restart();
}

void Enemy_Idle_alt_Node3::on_update(float delta)
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	timer.update(delta);
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("dead_land");
	}
	else if (enemy2->get_hp() <= 0)
	{
		enemy3->switch_state("idle_alt_re");
	}
	
}

Enemy_DashDash_Node3::Enemy_DashDash_Node3()
{

}

void Enemy_DashDash_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
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
		enemy3->set_current_function("dash_left");
	}
	else
	{
		enemy3->set_current_function("dash_right");
	}
}

void Enemy_DashDash_Node3::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("death_land");
		enemy3->finish_dash = false;
	}
	else if (enemy3->finish_dash)
	{
		enemy3->finish_dash = false;
		if (enemy2->get_hp() <= 0)
		{
			enemy3->switch_state("idle_alt_re");
		}
		else
		{
			enemy3->switch_state("idle_alt");
		}
	}
}

void Enemy_DstabDash_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
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
		enemy3->set_current_function("dash_left");
	}
	else
	{
		enemy3->set_current_function("dash_right");
	}
}

void Enemy_DstabDash_Node3::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("death_land");
		enemy3->finish_dash = false;
	}
	else if (enemy3->finish_dash)
	{
		enemy3->finish_dash = false;
		if (enemy2->get_hp() <= 0)
		{
			enemy3->switch_state("idle_alt_re");
		}
		else
		{
			enemy3->switch_state("idle_alt");
		}
	}
}

void Enemy_DashDstab_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	Player* player = (Player*)CharacterManager::instance()->get_player();
	POINT pos = player->getposition();
	if (pos.x >= boundary.x_platform_left && pos.x <= boundary.x_platform_right) pos.x = pos.x;
	else
	{
		if (pos.x >= boundary.x_platform_right) pos.x = boundary.x_platform_right - 0.5 * 342;
		else if (pos.x <= boundary.x_platform_left) pos.x = boundary.x_platform_left + 5;
	}
	enemy3->change_enemy_point(pos.x, 75);

	temp = rand() % 2;
	if (temp) enemy3->set_current_function("dstab_left");
	else
	{
		enemy3->set_current_function("dstab_right");
	}

}

void Enemy_DashDstab_Node3::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("death_land");
		enemy3->finish_dstab = false;
	}
	else if (enemy3->finish_dstab)
	{
		enemy3->finish_dstab = false;
		if (enemy2->get_hp() <= 0)
		{
			enemy3->switch_state("idle_alt_re");
		}
		else
		{
			enemy3->switch_state("idle_alt");
		}
	}
}

void Enemy_DstabDstab_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	Player* player = (Player*)CharacterManager::instance()->get_player();
	POINT pos = player->getposition();
	if (pos.x >= boundary.x_platform_left && pos.x <= boundary.x_platform_right) pos.x = pos.x;
	else
	{
		if (pos.x >= boundary.x_platform_right) pos.x = boundary.x_platform_right - 0.5 * 342;
		else if (pos.x <= boundary.x_platform_left) pos.x = boundary.x_platform_left + 5;
	}
	enemy3->change_enemy_point(pos.x, 75);

	temp = rand() % 2;
	if (temp) enemy3->set_current_function("dstab_left");
	else
	{
		enemy3->set_current_function("dstab_right");
	}

}

void Enemy_DstabDstab_Node3::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("death_land");
		enemy3->finish_dstab = false;
	}
	else if (enemy3->finish_dstab)
	{
		enemy3->finish_dstab = false;
		if (enemy2->get_hp() <= 0)
		{
			enemy3->switch_state("idle_alt_re");
		}
		else
		{
			enemy3->switch_state("idle_alt");
		}
	}
}

void Enemy_MeanwhileDash_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("dash_right");
}

void Enemy_MeanwhileDash_Node3::on_update(float delta)
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("death_land");
		enemy3->finish_dash = false;
	}
	else if (enemy3->finish_dash)
	{
		enemy3->finish_dash = false;
		if (enemy2->get_hp() <= 0)
		{
			enemy3->switch_state("idle_alt_re");
		}
		else
		{
			enemy3->switch_state("idle_alt");
		}
	}
}

Enemy_Wall_short_Node3::Enemy_Wall_short_Node3()
{
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(0.7f);
	timer_projectile.set_callback([&]() {

		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		enemy3->throw_projectile(true, false, true);

		});
	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(2.7f);
	timer_throw.set_callback([&]() {

		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		if (enemy2->get_hp() <= 0)
		{
			enemy3->switch_state("idle_alt_re");
			enemy3->finish_wall_high = false;
			enemy3->finish_wall = false;
		}
		else
		{
			enemy3->switch_state("idle_alt");
			enemy3->finish_wall_high = false;
			enemy3->finish_wall = false;
		}

		});
}

void Enemy_Wall_short_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	timer_throw.restart();
	timer_projectile.restart();
	enemy3->set_current_function("wall_high_right");
	is_left = false;

}

void Enemy_Wall_short_Node3::on_update(float delta)
{
	timer_throw.update(delta);
	timer_projectile.update(delta);
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->death_left = false;
		enemy3->switch_state("death_air");
		enemy3->finish_wall_high = false;
	}

}

Enemy_Wall_wide_Node3::Enemy_Wall_wide_Node3()
{
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(0.7f);
	timer_projectile.set_callback([&]() {

		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		enemy3->throw_projectile(false, false, true);

		});
	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(2.7f);
	timer_throw.set_callback([&]() {

		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		if (enemy2->get_hp() <= 0)
		{
			enemy3->switch_state("idle_alt_re");
			enemy3->finish_wall_high = false;
			enemy3->finish_wall = false;
		}
		else
		{
			enemy3->switch_state("idle_alt");
			enemy3->finish_wall_high = false;
			enemy3->finish_wall = false;
		}

		});
}

void Enemy_Wall_wide_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	timer_throw.restart();
	timer_projectile.restart();
	enemy3->set_current_function("wall_high_right");
	is_left = false;
}

void Enemy_Wall_wide_Node3::on_update(float delta)
{
	timer_throw.update(delta);
	timer_projectile.update(delta);
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->death_left = false;
		enemy3->switch_state("death_air");
		enemy3->finish_wall_high = false;
	}
}

void Enemy_Restore_Dash_Node3::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
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
		enemy3->set_current_function("dash_left");
	}
	else
	{
		enemy3->set_current_function("dash_right");
	}

}

void Enemy_Restore_Dash_Node3::on_update(float delta)
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("death_land");
		enemy3->finish_dash = false;
	}
	else if (enemy3->finish_dash)
	{
		enemy3->switch_state("idle_alt_re");
		enemy3->finish_dash = false;
	}

}

void Enemy_Restore_Dstab_Node3::on_enter()
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	POINT pos = player->getposition();
	if (pos.x >= boundary.x_platform_left && pos.x <= boundary.x_platform_right) pos.x = pos.x;
	else
	{
		if (pos.x >= boundary.x_platform_right) pos.x = boundary.x_platform_right - 0.5 * 342;
		else if (pos.x <= boundary.x_platform_left) pos.x = boundary.x_platform_left + 5;
	}
	enemy3->change_enemy_point(pos.x, 75);

	temp = rand() % 2;
	if (temp) enemy3->set_current_function("dstab_left");
	else
	{
		enemy3->set_current_function("dstab_right");
	}
}

void Enemy_Restore_Dstab_Node3::on_update(float delta)
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("death_land");
		enemy3->finish_dstab = false;
	}
	else if (enemy3->finish_dstab)
	{
		enemy3->switch_state("idle_alt_re");
		enemy3->finish_dstab = false;
	}

}

Enemy_Restore_Wall_low_Node3::Enemy_Restore_Wall_low_Node3()
{
	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(0.7f);
	timer_throw.set_callback([&]()
		{
			Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
			enemy3->throw_projectile(true, is_left);
		}
	);
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(2.7f);
	timer_projectile.set_callback([&]()
		{
			Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();

			enemy3->switch_state("idle_alt_re");
			enemy3->finish_wall_low = false;
			enemy3->finish_wall = false;
		}
	);
}

void Enemy_Restore_Wall_low_Node3::on_enter()
{
	int temp = rand() % 100 + 1;
	if (temp <= 50) is_left = false;
	else is_left = true;
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	timer_throw.restart();
	timer_projectile.restart();
	if (is_left) enemy3->set_current_function("wall_low_left");
	else enemy3->set_current_function("wall_low_right");
}

void Enemy_Restore_Wall_low_Node3::on_update(float delta)
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	timer_throw.update(delta);
	timer_projectile.update(delta);
	if (enemy3->get_hp() <= 0)
	{
		enemy3->death_left = is_left;
		enemy3->switch_state("death_air");
		enemy3->finish_wall_low = false;
	}
}

Enemy_Restore_Wall_high_Node3::Enemy_Restore_Wall_high_Node3()
{
	timer_throw.set_one_shotted(true);
	timer_throw.set_wait_time(0.7f);
	timer_throw.set_callback([&]()
		{
			Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
			enemy3->throw_projectile(false, is_left);
		}
	);
	timer_projectile.set_one_shotted(true);
	timer_projectile.set_wait_time(2.7f);
	timer_projectile.set_callback([&]()
		{
			Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
			enemy3->switch_state("idle_alt_re");
			enemy3->finish_wall_high = false;
			enemy3->finish_wall = false;
		}
	);
}

void Enemy_Restore_Wall_high_Node3::on_enter()
{
	int temp = rand() % 100 + 1;
	if (temp <= 50) is_left = false;
	else is_left = true;
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	timer_throw.restart();
	timer_projectile.restart();
	if (is_left) enemy3->set_current_function("wall_high_left");
	else enemy3->set_current_function("wall_high_right");
}

void Enemy_Restore_Wall_high_Node3::on_update(float delta)
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	timer_throw.update(delta);
	timer_projectile.update(delta);
	if (enemy3->get_hp() <= 0)
	{
		enemy3->death_left = is_left;
		enemy3->switch_state("death_air");
		enemy3->finish_wall_high = false;
	}
}

Enemy_Restore_Idle_alt_Node3::Enemy_Restore_Idle_alt_Node3()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.4f);
	timer.set_callback([&]()
		{
			Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
			int rand_num = rand() % 120 + 1;
			int loop_num = 0;
			if (Hash_disappear3[1] >= 5)
			{
				if (rand_num <= 60) enemy3->switch_state("wall_high");
				else enemy3->switch_state("wall_low");
				Hash_appear3[1] = 1;
				Hash_appear3[2] = 0, Hash_appear3[3] = 0;
				Hash_disappear3[1] = 0; Hash_disappear3[2]++; Hash_disappear3[3]++;
			}
			else if (Hash_disappear3[2] >= 5)
			{
				enemy3->switch_state("dstab");
				Hash_appear3[2] = 1;
				Hash_appear3[1] = 0, Hash_appear3[3] = 0;
				Hash_disappear3[2] = 0; Hash_disappear3[1]++; Hash_disappear3[3]++;

			}
			else if (Hash_disappear3[3] >= 5)
			{
				enemy3->switch_state("dash");
				Hash_appear3[3] = 1;
				Hash_appear3[1] = 0, Hash_appear3[2] = 0;
				Hash_disappear3[3] = 0; Hash_disappear3[2]++; Hash_disappear3[1]++;
			}
			else
			{
				while (((rand_num <= 40 && Hash_appear3[1] >= 2) || (rand_num > 40 && rand_num <= 80 && Hash_appear3[2] >= 2) || (rand_num > 80 && Hash_appear3[3] >= 3))&&loop_num<=100)
				{
					rand_num = rand() % 120 + 1;
					loop_num++;
				}
				loop_num = 0;
				if (rand_num <= 20)
				{
					Hash_appear3[1]++;
					Hash_appear3[2] = 0, Hash_appear3[3] = 0;
					Hash_disappear3[1] = 0; Hash_disappear3[2]++; Hash_disappear3[3]++;
					enemy3->switch_state("wall_high_re");
				}
				else if (rand_num <= 40)
				{
					Hash_appear3[1]++;
					Hash_appear3[2] = 0, Hash_appear3[3] = 0;
					Hash_disappear3[1] = 0; Hash_disappear3[2]++; Hash_disappear3[3]++;
					enemy3->switch_state("wall_low_re");
				}
				else if (rand_num <= 80)
				{
					Hash_appear3[2]++;
					Hash_appear3[1] = 0, Hash_appear3[3] = 0;
					Hash_disappear3[2] = 0; Hash_disappear3[1]++; Hash_disappear3[3]++;
					enemy3->switch_state("dstab_re");
				}
				else
				{
					Hash_appear3[3]++;
					Hash_appear3[1] = 0, Hash_appear3[2] = 0;
					Hash_disappear3[3] = 0; Hash_disappear3[2]++; Hash_disappear3[1]++;
					enemy3->switch_state("dash_re");
				}
			}
		}
	);
}

void Enemy_Restore_Idle_alt_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("null");

	timer.restart();
}

void Enemy_Restore_Idle_alt_Node3::on_update(float delta)
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	timer.update(delta);
	if (enemy3->get_hp() <= 0)
	{
		enemy3->switch_state("death_land");
	}
}

Enemy_Dead_Land_Node3::Enemy_Dead_Land_Node3()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(1.2f);
	timer.set_callback([&]()
		{
			Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
			enemy3->switch_state("death_leave");
		}
	);
}

void Enemy_Dead_Land_Node3::on_enter()
{
	timer.restart();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("dead_land");
	enemy3->get_hit_box_first()->set_enable(false);
	enemy3->get_hit_box_second()->set_enable(false);
	enemy3->get_hurt_box()->set_enable(false);
	enemy3->set_invulnerable(true);
	enemy3->be_death = true;

	if (enemy3->get_enemy_pos().x <= 580)
	{
		enemy3->set_death_pos(310, 300);
	}
	else
	{
		enemy3->set_death_pos(901, 300);
	}
	Camera* camera = CameraManager::instance()->get_camera();
	camera->shake(10, 0.5);
}

void Enemy_Dead_Land_Node3::on_update(float delta)
{
	timer.update(delta);
}

void Enemy_Dead_Land_Node3::on_end()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_invulnerable(false);
	enemy3->set_enemy_pos(enemy3->get_death_pos().x + 50, enemy3->get_death_pos().y);
}

Enemy_Dead_Air_Node3::Enemy_Dead_Air_Node3()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.8f);
	timer.set_callback([&]()
		{
			Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
			enemy3->switch_state("death_leave");
		}
	);
}

void Enemy_Dead_Air_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("dead_land");
	timer.restart();
	if (enemy3->death_left)
		enemy3->set_death_pos(enemy3->get_enemy_pos().x - 40, enemy3->get_enemy_pos().y);
	else
		enemy3->set_death_pos(enemy3->get_enemy_pos().x, enemy3->get_enemy_pos().y);
	enemy3->get_hit_box_first()->set_enable(false);
	enemy3->get_hit_box_second()->set_enable(false);
	enemy3->get_hurt_box()->set_enable(false);
	enemy3->set_invulnerable(true);
	enemy3->be_death = true;
	Camera* camera = CameraManager::instance()->get_camera();
	camera->shake(10, 0.5);
}

void Enemy_Dead_Air_Node3::on_update(float delta)
{
	timer.update(delta);
}

void Enemy_Dead_Air_Node3::on_end()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();;
	enemy3->set_invulnerable(false);
}

Enemy_Dead_Leave_Node3::Enemy_Dead_Leave_Node3()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(1.0f);
	timer.set_callback([&]()
		{
			Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
			enemy3->death_leave_reset();
			enemy3->switch_state("back");
		}
	);
}

void Enemy_Dead_Leave_Node3::on_enter()
{
	timer.restart();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	if (enemy3->death_left) enemy3->set_current_function("death_leave_right");
	else enemy3->set_current_function("death_leave_left");
}

void Enemy_Dead_Leave_Node3::on_update(float delta)
{
	timer.update(delta);
}

Enemy_Back_Node3::Enemy_Back_Node3()
{
	timer.set_one_shotted(true);
	timer.set_wait_time(0.3f);
	timer.set_callback([&]() {

		Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
		Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
		if (enemy3->be_death && enemy2->be_death)
		{
			MessageBox(GetHWnd(), _T("任务成功"), _T("游戏结束"), MB_OK);
			exit(0);
		}

		}
	);
}

void Enemy_Back_Node3::on_enter()
{
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	enemy3->set_current_function("back_right");
}

void Enemy_Back_Node3::on_update(float delta)
{
	timer.update(delta);
}
