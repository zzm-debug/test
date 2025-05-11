#include<easyx.h>
#include"Animation.h"
#include"Enemy.h"
#include"collision.h"
#include"main.h"
#include"Character.h"
#include"Mantis Air Projectile.h"
#include"Enemy_StateNode.h"
#include"Enemy_StateNode2.h"
#include"Enemy_StateNode3.h"
#include"CameraManager.h"
#include"Effect.h"

using namespace std::placeholders;

const int alt = 0;
Enemy::Enemy()
{

	time_invulnerable.set_wait_time(0.5f);//ÎÞµÐÖ¡Ê±¼ä

	hit_box_first->set_enable(false);
	hit_box_second->set_enable(false);
	hurt_box->set_enable(false);

	hit_box_first->set_layer_src(CollisionSort::None);
	hit_box_first->set_layer_dst(CollisionSort::Player);
	hit_box_second->set_layer_src(CollisionSort::None);
	hit_box_second->set_layer_dst(CollisionSort::Player);
	hurt_box->set_layer_src(CollisionSort::Enemy);
	hurt_box->set_layer_dst(CollisionSort::None);

	hurt_box->set_collide([&]() {

		decrease_hp(1);

		});

	IMAGE* temp = new IMAGE();
	loadimage(temp, _T("Mantis Lords Anim/009.Throne Idle/009-00.png"));
	int height = temp->getheight();
	int width = temp->getwidth();
	loadimage(&Throne_Idle_left, _T("Mantis Lords Anim/009.Throne Idle/009-00.png"),0.65*width,0.65*height);
	loadimage(&Throne_Idle_right, _T("Mantis Lords Anim/009.Throne Idle/009-00.png"),0.65*width,0.65*height);
	flipAmination(&Throne_Idle_left, &Throne_Idle_right, 1);
	Throne_Stand_left = new Animation(_T("Mantis Lords Anim/010.Throne Stand/010-0%d.png"), 6, 1.0f / 12.0f,true,true);
	Throne_Stand_right = new Animation(_T("Mantis Lords Anim/010.Throne Stand/010-0%d.png"), 6, 1.0f / 12.0f,true);

	Throne_Leave_left = new Animation(_T("Mantis Lords Anim/011.Throne Leave/011-0%d.png"),4,1.0f/ 25.0f,true,true);
	Throne_Leave_right = new Animation(_T("Mantis Lords Anim/011.Throne Leave/011-0%d.png"),4,1.0f/ 25.0f,true);

	Dash_Antic_left= new Animation(_T("Mantis Lords Anim/003.Dash Antic/003-0%d.png"), 5, 1.0f / 15.0f,true,true);
	Dash_Antic_right = new Animation(_T("Mantis Lords Anim/003.Dash Antic/003-0%d.png"), 5, 1.0f / 15.0f,true);
	Dash_Arrive_left= new Animation(_T("Mantis Lords Anim/002.Dash Arrive/002-0%d.png"), 6, 1.0f / 20.0f,true,true);
	Dash_Arrive_right = new Animation(_T("Mantis Lords Anim/002.Dash Arrive/002-0%d.png"), 6, 1.0f / 20.0f,true);
	Dash_Attack_left = new Animation(_T("Mantis Lords Anim/004.Dash Attack/004-0%d.png"), 3, 1.0f/ 20.0f,true,true);
	Dash_Attack_right = new Animation(_T("Mantis Lords Anim/004.Dash Attack/004-0%d.png"), 3, 1.0f / 20.0f,true);
	Dash_Leave_left = new Animation(_T("Mantis Lords Anim/006.Dash Leave/006-0%d.png"), 4, 1.0f / 20.0f,true,true);
	Dash_Leave_right = new Animation(_T("Mantis Lords Anim/006.Dash Leave/006-0%d.png"), 4, 1.0f / 20.0f,true);
	Dash_Recover_left = new Animation(_T("Mantis Lords Anim/005.Dash Recover/005-0%d.png"), 10, 1.0f / 16.0f,true,true);
	Dash_Recover_right = new Animation(_T("Mantis Lords Anim/005.Dash Recover/005-0%d.png"), 10, 1.0f / 16.0f,true);

	Dstab_Arrive_left = new Animation(_T("Mantis Lords Anim/012.Dstab Arrive/012-0%d.png"), 12, 1.0f / 20.0f,true,true);
	Dstab_Arrive_right = new Animation(_T("Mantis Lords Anim/012.Dstab Arrive/012-0%d.png"), 12, 1.0f / 20.0f,true);
	Dstab_Attack_left = new Animation(_T("Mantis Lords Anim/013.Dstab Attack/013-0%d.png"), 2, 1.0f / 30.0f,true,true);
	Dstab_Attack_right = new Animation(_T("Mantis Lords Anim/013.Dstab Attack/013-0%d.png"), 2, 1.0f / 30.0f,true);
	Dstab_Land_left = new Animation(_T("Mantis Lords Anim/014.Dstab Land/014-0%d.png"), 8, 1.0f / 12.0f,true,true);
	Dstab_Land_right = new Animation(_T("Mantis Lords Anim/014.Dstab Land/014-0%d.png"), 8, 1.0f / 12.0f,true);
	Dstab_Leave_left = new Animation(_T("Mantis Lords Anim/015.Dstab Leave/015-0%d.png"), 3, 1.0f / 20.0f,true,true);
	Dstab_Leave_right = new Animation(_T("Mantis Lords Anim/015.Dstab Leave/015-0%d.png"), 3, 1.0f / 20.0f,true);
	
	Wall_Arrive_left = new Animation(_T("Mantis Lords Anim/001.Wall Arrive/001-0%d.png"), 9, 1.0f / 20.0f,true,true);
	Wall_Arrive_right = new Animation(_T("Mantis Lords Anim/001.Wall Arrive/001-0%d.png"), 9, 1.0f / 20.0f,true);
	Wall_leave1_left = new Animation(_T("Mantis Lords Anim/018.Wall Leave 1/018-0%d.png"), 2, 1.0f / 12.0f,true,true);
	Wall_leave1_right = new Animation(_T("Mantis Lords Anim/018.Wall Leave 1/018-0%d.png"), 2, 1.0f / 12.0f,true);
	Wall_leave2_left = new Animation(_T("Mantis Lords Anim/019.Wall Leave 2/019-0%d.png"), 3, 1.0f / 20.0f,true,true);
	Wall_leave2_right = new Animation(_T("Mantis Lords Anim/019.Wall Leave 2/019-0%d.png"), 3, 1.0f / 20.0f,true);
	Wall_Ready_left = new Animation(_T("Mantis Lords Anim/008.Wall Ready/008-0%d.png"), 3, 1.0f / 12.0f,true,true);
	Wall_Ready_right = new Animation(_T("Mantis Lords Anim/008.Wall Ready/008-0%d.png"), 3, 1.0f / 12.0f,true);
	Throw_Antic_left = new Animation(_T("Mantis Lords Anim/016.Throw Antic/016-0%d.png"), 5, 1.0f / 12.0f,true,true);
	Throw_Antic_right = new Animation(_T("Mantis Lords Anim/016.Throw Antic/016-0%d.png"), 5, 1.0f / 12.0f,true);
	Throw_left = new Animation(_T("Mantis Lords Anim/017.Throw/017-0%d.png"), 11, 1.0f / 12.0f,true,true);
	Throw_right = new Animation(_T("Mantis Lords Anim/017.Throw/017-0%d.png"), 11, 1.0f / 12.0f,true);
	Death_land = new Animation(_T("Mantis Lords Anim/025.Death Land/025-0%d.png"), 3, 1.0f / 12.0f,true,true);
	Death_air_left= new Animation(_T("Mantis Lords Anim/024.Death Air/024-0%d.png"), 1, 1.0f / 12.0f, true,true);
	Death_air_right= new Animation(_T("Mantis Lords Anim/024.Death Air/024-0%d.png"), 1, 1.0f / 12.0f, true);
	Death_leave_left= new Animation(_T("Mantis Lords Anim/035.Death New 2/035-0%d.png"), 2, 1.0f / 20.f, true,true);
	Death_leave_right= new Animation(_T("Mantis Lords Anim/035.Death New 2/035-0%d.png"), 2, 1.0f / 20.0f, true);
	Death_back_left= new Animation(_T("Mantis Lords Anim/007.Throne Wounded/007-0%d.png"), 7, 1.0f/ 20.0f, true,true);
	Death_back_right= new Animation(_T("Mantis Lords Anim/007.Throne Wounded/007-0%d.png"), 7, 1.0f / 20.0f, true);

	animation_pool["dash_left"] = std::bind( & Enemy::dash_left,this,_1);
	animation_pool["dash_right"] = std::bind(&Enemy::dash_right, this, _1);
	animation_pool["dstab_left"] = std::bind(&Enemy::dstab_left, this, _1);
	animation_pool["dstab_right"] = std::bind(&Enemy::dstab_right, this, _1);
	animation_pool["wall_low_left"] = std::bind(&Enemy::wall_left_low, this, _1);
	animation_pool["wall_low_right"] = std::bind(&Enemy::wall_right_low, this, _1);
	animation_pool["wall_high_left"] = std::bind(&Enemy::wall_left_high, this, _1);
	animation_pool["wall_high_right"] = std::bind(&Enemy::wall_right_high, this, _1);
	animation_pool["idle"] = std::bind(&Enemy::Idle, this, _1);
	animation_pool["stand"] = std::bind(&Enemy::stand, this, _1);
	animation_pool["leave"] = std::bind(&Enemy::leave, this, _1);
	animation_pool["dead_land"] = std::bind(&Enemy::death_land, this, _1);
	animation_pool["back_left"] = std::bind(&Enemy::back_left, this, _1);
	animation_pool["back_right"] = std::bind(&Enemy::back_right, this, _1);
	animation_pool["death_leave_left"] = std::bind(&Enemy::death_leave_left, this, _1);
	animation_pool["death_leave_right"] = std::bind(&Enemy::death_leave_right, this, _1);
	

	

	hp = 30;
	effect = new Effect();

}

Enemy::~Enemy()
{
	delete Throne_Stand_left;
	delete Throne_Stand_right;

	delete Throne_Leave_left;
	delete Throne_Leave_right;

	delete Dash_Antic_left;
	delete Dash_Antic_right;
	delete Dash_Arrive_left;
	delete Dash_Arrive_right;
	delete Dash_Attack_left;
	delete Dash_Attack_right;
	delete Dash_Leave_left;
	delete Dash_Leave_right;
	delete Dash_Recover_left;
	delete Dash_Recover_right;

	delete Dstab_Arrive_left;
	delete Dstab_Arrive_right;
	delete Dstab_Attack_left;
	delete Dstab_Attack_right;
	delete Dstab_Land_left;
	delete Dstab_Land_right;
	delete Dstab_Leave_left;
	delete Dstab_Leave_right;

	delete Wall_Arrive_left;
	delete Wall_Arrive_right;
	delete Wall_leave1_left;
	delete Wall_leave1_right;
	delete Wall_leave2_left;
	delete Wall_leave2_right;
	delete Wall_Ready_left;
	delete Wall_Ready_right;
	delete Throw_Antic_left;
	delete Throw_Antic_right;
	delete Throw_left;
	delete Throw_right;
	delete Death_land;
	delete Death_air_left;
	delete Death_air_right;
	delete Death_leave_left;
	delete Death_leave_right;
	delete Death_back_left;
	delete Death_back_right;
}

Throne1::Throne1()
{
	Enemy::enemy_point = { 614,95 };
	start_point = { 614,95 };
	srand((unsigned)time(nullptr));
	is_left = false;
	hp = 30;
	state_machine.register_state("dash", new Enemy_Dash_Node());
	state_machine.register_state("dstab", new Enemy_Dstab_Node());
	state_machine.register_state("wall_low", new Enemy_Wall_low_Node());
	state_machine.register_state("wall_high", new Enemy_Wall_high_Node());
	state_machine.register_state("idle", new Enemy_Idle_Node());
	state_machine.register_state("idle_alt", new Enemy_Idle_alt_Node());
	state_machine.register_state("stand", new Enemy_Stand_Node());
	state_machine.register_state("leave", new Enemy_Leave_Node());
	state_machine.register_state("death_land", new Enemy_Death_land_Node());
	state_machine.register_state("death_air", new Enemy_Death_air_Node());
	state_machine.register_state("death_leave", new Enemy_Death_leave_Node());
	state_machine.register_state("back", new Enemy_Back_Node());
	state_machine.set_entry("idle");
}

Throne2::Throne2()
{
	Enemy::enemy_point = { 455,174 };
	Enemy::start_point = { 455,174 };
	is_left = true;
	hp = 30;
	state_machine.register_state("dashdash", new Enemy_DashDash_Node2());
	state_machine.register_state("dstabdstab", new Enemy_DstabDstab_Node2());
	state_machine.register_state("dashdstab", new Enemy_DashDstab_Node2());
	state_machine.register_state("dstabdash", new Enemy_DstabDash_Node2());
	state_machine.register_state("meanwhiledash", new Enemy_MeanwhileDash_Node2());
	state_machine.register_state("wall_short", new Enemy_Wall_short_Node2());
	state_machine.register_state("wall_wide", new Enemy_Wall_wide_Node2());
	state_machine.register_state("idle", new Enemy_Idle_Node2());
	state_machine.register_state("stand", new Enemy_Stand_Node2());
	state_machine.register_state("leave", new Enemy_Leave_Node2());
	state_machine.register_state("idle_alt", new Enemy_Idle_alt_Node2());
	state_machine.register_state("idle_alt_re", new Enemy_Restore_Idle_alt_Node2());
	state_machine.register_state("death_land", new Enemy_Dead_Land_Node2());
	state_machine.register_state("death_air", new Enemy_Dead_Air_Node2());
	state_machine.register_state("wall_high_re", new Enemy_Restore_Wall_high_Node2());
	state_machine.register_state("wall_low_re", new Enemy_Restore_Wall_low_Node2());
	state_machine.register_state("dstab_re", new Enemy_Restore_Dstab_Node2());
	state_machine.register_state("dash_re", new Enemy_Restore_Dash_Node2());
	state_machine.register_state("death_leave", new Enemy_Dead_Leave_Node2());
	state_machine.register_state("back", new Enemy_Back_Node2());

	state_machine.set_entry("idle");
}



Throne3::Throne3()
{
	Enemy::enemy_point = { 784,173 };
	Enemy::start_point = { 784,173 };
	is_left = false;
	hp = 30;
	state_machine.register_state("dashdash", new Enemy_DashDash_Node3());
	state_machine.register_state("dstabdstab", new Enemy_DstabDstab_Node3());
	state_machine.register_state("dashdstab", new Enemy_DashDstab_Node3());
	state_machine.register_state("dstabdash", new Enemy_DstabDash_Node3());
	state_machine.register_state("meanwhiledash", new Enemy_MeanwhileDash_Node3());
	state_machine.register_state("wall_short", new Enemy_Wall_short_Node3());
	state_machine.register_state("wall_wide", new Enemy_Wall_wide_Node3());
	state_machine.register_state("idle", new Enemy_Idle_Node3());
	state_machine.register_state("stand", new Enemy_Stand_Node3());
	state_machine.register_state("leave", new Enemy_Leave_Node3());
	state_machine.register_state("idle_alt", new Enemy_Idle_alt_Node3());
	state_machine.register_state("idle_alt_re", new Enemy_Restore_Idle_alt_Node3());
	state_machine.register_state("death_land", new Enemy_Dead_Land_Node3());
	state_machine.register_state("death_air", new Enemy_Dead_Air_Node3());
	state_machine.register_state("wall_high_re", new Enemy_Restore_Wall_high_Node3());
	state_machine.register_state("wall_low_re", new Enemy_Restore_Wall_low_Node3());
	state_machine.register_state("dstab_re", new Enemy_Restore_Dstab_Node3());
	state_machine.register_state("dash_re", new Enemy_Restore_Dash_Node3());
	state_machine.register_state("death_leave", new Enemy_Dead_Leave_Node3());
	state_machine.register_state("back", new Enemy_Back_Node3());

	state_machine.set_entry("idle");
}


void Enemy::on_update(float delta)
{
	character::on_update(delta);


}

void Enemy::set_current_function(const string& id)
{
	if (id == "null")
	{
		current_function = nullptr;
	}
	else current_function = animation_pool[id];
}

void Enemy::on_render(float delta)
{
	if (current_function == nullptr) return;
	else current_function(delta);
	if (be_hurt&&!be_death)
	{
		if (!effect->Sword_effect->is_finish_loop)
		{
			long x =hurt_box->get_position().x - effect->Sword_effect->frame_list[effect->Sword_effect->NextIdex(delta)]->getwidth() / 2;
			long y = hurt_box->get_position().y - effect->Sword_effect->frame_list[effect->Sword_effect->NextIdex(delta)]->getheight() / 2;
			effect->Sword_effect->Play(x, y, delta, true, true);
		}
		if (!effect->Stun_impact->is_finish_loop)
		{
			long x_alt = hurt_box->get_position().x - effect->Stun_impact->frame_list[effect->Sword_effect->NextIdex(delta)]->getwidth() / 2;
			long y_alt = hurt_box->get_position().y - effect->Stun_impact->frame_list[effect->Sword_effect->NextIdex(delta)]->getheight() / 2;
			effect->Stun_impact->Play(x_alt, y_alt, delta,true, true);
		}
		else
		{
			be_hurt = false;
			effect->Stun_impact->Reset();
			effect->Sword_effect->Reset();
		}

	}
}

void Throne1::on_update(float delta)
{
	Enemy::on_update(delta);

	for (Air_Projectile* projectile_current : air_projectile)
	{
		projectile_current->on_update(delta);
	}

	air_projectile.erase(std::remove_if(air_projectile.begin(), air_projectile.end(), [](Air_Projectile* projectile_current)
		{
			bool can_remove = projectile_current->if_remove();
			if (can_remove)
			{
				projectile_current->reset();
				delete projectile_current;
			}
			return can_remove;
		})
		, air_projectile.end());

}

void Throne1::on_render(float delta)
{
	for (Air_Projectile* projectile_current : air_projectile)
	{
		projectile_current->on_render(delta);
	}

	Enemy::on_render(delta);

}

void Throne2::on_update(float delta)
{
	Enemy::on_update(delta);

	for (Air_Projectile* projectile_current : air_projectile)
	{
		projectile_current->on_update(delta);
	}

	air_projectile.erase(std::remove_if(air_projectile.begin(), air_projectile.end(), [](Air_Projectile* projectile_current)
		{
			bool can_remove = projectile_current->if_remove();
			if (can_remove)
			{
				projectile_current->reset();
				delete projectile_current;
			}
			return can_remove;
		})
		, air_projectile.end());
}

void Throne2::on_render(float delta)
{
	for (Air_Projectile* projectile_current : air_projectile)
	{
		projectile_current->on_render(delta);
	}

	Enemy::on_render(delta);
}

void Throne3::on_update(float delta)
{
	Enemy::on_update(delta);

	for (Air_Projectile* projectile_current : air_projectile)
	{
		projectile_current->on_update(delta);
	}

	air_projectile.erase(std::remove_if(air_projectile.begin(), air_projectile.end(), [](Air_Projectile* projectile_current)
		{
			bool can_remove = projectile_current->if_remove();
			if (can_remove)
			{
				projectile_current->reset();
				delete projectile_current;
			}
			return can_remove;
		})
		, air_projectile.end());

}

void Throne3::on_render(float delta)
{
	for (Air_Projectile* projectile_current : air_projectile)
	{
		projectile_current->on_render(delta);
	}

	Enemy::on_render(delta);
}

void Enemy::dash_left_clear()
{
	Dash_Antic_left->Reset();
	Dash_Arrive_left->Reset();
	Dash_Attack_left->Reset();
	Dash_Leave_left->Reset();
	Dash_Recover_left->Reset();
}

void Enemy::dash_right_clear()
{
	Dash_Antic_right->Reset();
	Dash_Arrive_right->Reset();
	Dash_Attack_right->Reset();
	Dash_Leave_right->Reset();
	Dash_Recover_right->Reset();
}

void Enemy::dstab_left_clear()
{
	Dstab_Arrive_left->Reset();
	Dstab_Attack_left->Reset();
	Dstab_Land_left->Reset();
	Dstab_Leave_left->Reset();
}

void Enemy::dstab_right_clear()
{
	Dstab_Arrive_right->Reset();
	Dstab_Land_right->Reset();
	Dstab_Leave_right->Reset();
	Dstab_Attack_right->Reset();
}

void Enemy::wall_left_clear()
{
	Wall_Arrive_left->Reset();
	Wall_leave1_left->Reset();
	Wall_leave2_left->Reset();
	Wall_Ready_left->Reset();
	Throw_left->Reset();
	height_generation = false;
}

void Enemy::wall_right_clear()
{
	Wall_Arrive_right->Reset();
	Wall_leave1_right->Reset();
	Wall_leave2_right->Reset();
	Wall_Ready_right->Reset();
	Throw_right->Reset();
	height_generation = false;
}




Throne1::~Throne1()
{
	delete[] projectile;
}

void Enemy::stand(float delta)
{
	if (is_left)
	{
		if (!Throne_Stand_left->is_finish_loop)
		{
			enemy_point.y = start_point.y + Throne_Idle_left.getheight() - Throne_Stand_left->frame_list[Throne_Stand_left->NextIdex(delta)]->getheight();
			enemy_point.x = start_point.x + Throne_Idle_left.getwidth() / 2 - Throne_Stand_left->frame_list[Throne_Stand_left->NextIdex(delta)]->getwidth() / 2;
			current_animation = Throne_Stand_left;
			Throne_Stand_left->Play(enemy_point.x, enemy_point.y, delta, true, true);
			if (Throne_Stand_left->is_finish_loop)
			{
				finish_stand = true;
				Throne_Stand_left->Reset();
				leave_start_point.y = enemy_point.y + Throne_Stand_right->frame_list[2]->getheight() - Throne_Leave_right->frame_list[Throne_Leave_right->NextIdex(delta)]->getheight();
				leave_start_point.x = enemy_point.x;
			}
		}
	}
	else
	{
		if (!Throne_Stand_right->is_finish_loop)
		{
			enemy_point.y = start_point.y + Throne_Idle_right.getheight() - Throne_Stand_right->frame_list[Throne_Stand_right->NextIdex(delta)]->getheight();
			enemy_point.x = start_point.x + Throne_Idle_right.getwidth() / 2 - Throne_Stand_right->frame_list[Throne_Stand_right->NextIdex(delta)]->getwidth() / 2;
			current_animation = Throne_Stand_right;
			Throne_Stand_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
			if (Throne_Stand_right->is_finish_loop)
			{
				finish_stand = true;
				Throne_Stand_right->Reset();
				leave_start_point.y = enemy_point.y + Throne_Stand_right->frame_list[2]->getheight() - Throne_Leave_right->frame_list[Throne_Leave_right->NextIdex(delta)]->getheight() ;
				leave_start_point.x = enemy_point.x ;
			}
		}
	}
	hit_box_first->set_position(get_logic_center_enemy());
	hit_box_first->set_size({ 52,173 });
	hurt_box->set_position(get_logic_center_enemy());
	hurt_box->set_size({ 52,173 });
}

void Enemy::leave(float delta)
{
	if(is_left)
	{
		if (!Throne_Leave_left->is_finish_loop)
		{
			enemy_point.y = leave_start_point.y   - 1200*delta * Throne_Leave_left->NextIdex(delta);
			enemy_point.x = leave_start_point.x  + 1200*delta * Throne_Leave_left->NextIdex(delta);
			current_animation = Throne_Stand_left;
			Throne_Leave_left->Play(enemy_point.x, enemy_point.y, delta,true,true);
		}
		else
		{
			finish_leave = true;
			Throne_Leave_left->Reset();
		}
	}
	else
	{
		if (!Throne_Leave_right->is_finish_loop)
		{
			enemy_point.y = leave_start_point.y - 1200*delta * Throne_Leave_right->NextIdex(delta);
			enemy_point.x = leave_start_point.x  - 1200*delta * Throne_Leave_right->NextIdex(delta);
			current_animation = Throne_Leave_right;
			Throne_Leave_right->Play(enemy_point.x, enemy_point.y, delta,true,true);
		}
		else
		{
			finish_leave = true;
			Throne_Leave_right->Reset();
		}
	}

}

void Enemy::Idle(float delta)
{
	Camera* camera = CameraManager::instance()->get_camera();
	if (is_left)
	{
		putimagealpha(start_point.x-camera->get_position().x, start_point.y-camera->get_position().y, &Throne_Idle_left);
	}
    else
	{
		putimagealpha(start_point.x-camera->get_position().x, start_point.y-camera->get_position().y, &Throne_Idle_right);
	}

}

void Enemy::on_hurt()
{
	if (!is_invulnerable)
	{
		be_hurt = true;
	}
}

void Enemy::dash_left(float delta)
{
	if (!Dash_Arrive_left->is_finish_loop)
	{
		current_animation = Dash_Arrive_left;
		if (Dash_Arrive_left->idx_frame == 0) enemy_point.x = boundary.x_platform_left + 112 - Dash_Arrive_left->frame_list[Dash_Arrive_left->NextIdex(delta)]->getwidth();
		else enemy_point.x = enemy_point.x;
		if(Dash_Arrive_left->NextIdex(delta)<=2)
		enemy_point.y = boundary.y_platform - Dash_Arrive_left->frame_list[Dash_Arrive_left->NextIdex(delta)]->getheight()-25;
		else
		{
			enemy_point.y = boundary.y_platform - Dash_Arrive_left->frame_list[Dash_Arrive_left->NextIdex(delta)]->getheight();

			hit_box_first->set_enable(true);
			hurt_box->set_enable(true);

			long current_x = enemy_point.x + 0.6 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
			long current_y = enemy_point.y + 0.75 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();
			hit_box_first->set_position({ current_x,current_y});
			hurt_box->set_position({current_x,current_y });
			hit_box_first->set_size({ 91,66 });
			hurt_box->set_size({ 91,66 });
		}
		Dash_Arrive_left->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Dash_Antic_left->is_finish_loop)
	{
		current_animation = Dash_Antic_left;
		enemy_point.x = boundary.x_platform_left+189 - Dash_Arrive_left->frame_list[Dash_Arrive_left->NextIdex(delta)]->getwidth();
		enemy_point.y = boundary.y_platform - Dash_Antic_left->frame_list[Dash_Antic_left->NextIdex(delta)]->getheight();
		hit_box_first->set_position( get_logic_center_enemy() );
		hurt_box->set_position(get_logic_center_enemy());
		hit_box_first->set_size({ 76,74 });
		hurt_box->set_size({ 76,74 });
		Dash_Antic_left->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (enemy_point.x + Dash_Arrive_left->frame_list[Dash_Arrive_left->idx_frame]->getwidth() < boundary.x_right-5)
	{
		current_animation = Dash_Attack_left;
		if (enemy_point.x < boundary.x_platform_left) enemy_point.x = boundary.x_platform_left;
		enemy_point.y = boundary.y_platform - Dash_Attack_left->frame_list[Dash_Attack_left->NextIdex(delta)]->getheight()-8;

		hit_box_second->set_enable(true);
		long current_x = enemy_point.x + 0.8 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
		hit_box_first->set_position({ get_logic_center_enemy() });
		hurt_box->set_position({ get_logic_center_enemy() });
		hit_box_second->set_position({current_x,get_logic_center_enemy().y});
		hit_box_first->set_size({115,35 });
		hurt_box->set_size({ 115,35 });
		hit_box_second->set_size({ 55,10 });

		Dash_Attack_left->Play(enemy_point.x, enemy_point.y, delta);
		enemy_point.x += 1800 * delta;
	}
	else if (!Dash_Recover_left->is_finish_loop)
	{
		current_animation = Dash_Recover_left;
		if (Dash_Recover_left->NextIdex(delta) == 0) enemy_point.x = boundary.x_right - Dash_Recover_left->frame_list[0]->getwidth()+1;
		else enemy_point.x = enemy_point.x;
		enemy_point.y = boundary.y_platform - Dash_Recover_left->frame_list[Dash_Recover_left->NextIdex(delta)]->getheight();

		hit_box_second->set_position({ 0,0 });
		hit_box_second->set_enable(false);
		long current_x = enemy_point.x + 0.4 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
		long current_y = enemy_point.y + 0.75 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();
		hit_box_first->set_position({current_x ,current_y});
		hurt_box->set_position({current_x,current_y});
		hit_box_first->set_size({ 75,52 });
		hurt_box->set_size({ 75,52 });

		Dash_Recover_left->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Dash_Leave_left->is_finish_loop)
	{
		current_animation = Dash_Leave_left;
		enemy_point.x = boundary.x_right - Dash_Leave_left->frame_list[Dash_Leave_left->NextIdex(delta)]->getwidth();
		enemy_point.y = boundary.y_platform - Dash_Leave_left->frame_list[Dash_Leave_left->NextIdex(delta)]->getheight() ;
		if (current_animation->idx_frame <= 1)
		{
			long current_x = enemy_point.x + 0.4 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
			long current_y = enemy_point.y + 0.8 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();

			hit_box_first->set_position({current_x,current_y});
			hurt_box->set_position({current_x,current_y});
			hit_box_first->set_size({ 60,45 });
			hurt_box->set_size({ 60,45 });
		}
		else
		{
			hit_box_first->set_enable(false);
			hurt_box->set_enable(false);
			hit_box_second->set_enable(false);
		}
		Dash_Leave_left->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else
	{
		finish_dash = true;
		dash_left_clear();
	}

}

void Enemy::dash_right(float delta)
{
	if (!Dash_Arrive_right->is_finish_loop)
	{
		current_animation = Dash_Arrive_right;
		if (Dash_Arrive_right->idx_frame == 0) enemy_point.x = boundary.x_platform_right - 112;
		else enemy_point.x= enemy_point.x+Dash_Arrive_right->frame_list[Dash_Arrive_right->idx_frame]->getwidth()-Dash_Arrive_right->frame_list[Dash_Arrive_right->NextIdex(delta)]->getwidth();
		if (Dash_Arrive_right->NextIdex(delta) <= 2)
			enemy_point.y = boundary.y_platform - Dash_Arrive_right->frame_list[Dash_Arrive_right->NextIdex(delta)]->getheight() - 25;
		else
		{
			enemy_point.y = boundary.y_platform - Dash_Arrive_right->frame_list[Dash_Arrive_right->NextIdex(delta)]->getheight();

			hit_box_first->set_enable(true);
			hurt_box->set_enable(true);

			long current_x = enemy_point.x + 0.4 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
			long current_y = enemy_point.y + 0.75 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();
			hit_box_first->set_position({ current_x,current_y });
			hurt_box->set_position({ current_x,current_y });
			hit_box_first->set_size({ 91,66 });
			hurt_box->set_size({ 91,66 });

		}

		Dash_Arrive_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Dash_Antic_right->is_finish_loop)
	{
		current_animation = Dash_Antic_right;
		enemy_point.x = boundary.x_platform_right - 189;
		enemy_point.y = boundary.y_platform - Dash_Antic_right->frame_list[Dash_Antic_right->NextIdex(delta)]->getheight();

		hit_box_first->set_position(get_logic_center_enemy());
		hurt_box->set_position(get_logic_center_enemy());
		hit_box_first->set_size({ 76,74 });
		hurt_box->set_size({ 76,74 });
		
		Dash_Antic_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (enemy_point.x  > boundary.x_left+5)
	{
		current_animation = Dash_Attack_right;
		if (enemy_point.x+Dash_Attack_right->frame_list[Dash_Attack_right->NextIdex(delta)]->getwidth() > boundary.x_platform_right) enemy_point.x = boundary.x_platform_right - Dash_Attack_right->frame_list[Dash_Attack_right->idx_frame]->getwidth();
		enemy_point.y = boundary.y_platform - Dash_Attack_right->frame_list[Dash_Attack_right->NextIdex(delta)]->getheight() - 8;

		hit_box_second->set_enable(true);
		long current_x = enemy_point.x + 0.2 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
		hit_box_first->set_position({ get_logic_center_enemy() });
		hurt_box->set_position({ get_logic_center_enemy() });
		hit_box_second->set_position({ current_x,get_logic_center_enemy().y });
		hit_box_first->set_size({ 115,35 });
		hurt_box->set_size({ 115,35 });
		hit_box_second->set_size({ 55,10 });

		Dash_Attack_right->Play(enemy_point.x, enemy_point.y, delta);
		enemy_point.x -= 1800 * delta;
	}
	else if (!Dash_Recover_right->is_finish_loop)
	{
		current_animation = Dash_Recover_right;
		if (Dash_Recover_right->idx_frame == 0) enemy_point.x = boundary.x_left-1 ;
		else enemy_point.x = enemy_point.x-Dash_Recover_left->frame_list[Dash_Recover_left->NextIdex(delta)]->getwidth() + Dash_Recover_left->frame_list[Dash_Recover_left->idx_frame]->getwidth();
		enemy_point.y = boundary.y_platform - Dash_Recover_right->frame_list[Dash_Recover_right->NextIdex(delta)]->getheight();
	
		hit_box_second->set_position({ 0,0 });
		hit_box_second->set_enable(false);
		long current_x = enemy_point.x + 0.6 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
		long current_y = enemy_point.y + 0.75 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();
		hit_box_first->set_position({ current_x ,current_y });
		hurt_box->set_position({ current_x,current_y });
		hit_box_first->set_size({ 75,52 });
		hurt_box->set_size({ 75,52 });

		Dash_Recover_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Dash_Leave_right->is_finish_loop)
	{
		current_animation = Dash_Leave_right;
		enemy_point.x = boundary.x_left ;
		enemy_point.y = boundary.y_platform - Dash_Leave_right->frame_list[Dash_Leave_right->NextIdex(delta)]->getheight();

		if (current_animation->idx_frame <= 1)
		{
			long current_x = enemy_point.x + 0.6 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
			long current_y = enemy_point.y + 0.8 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();

			hit_box_first->set_position({ current_x,current_y });
			hurt_box->set_position({ current_x,current_y });
			hit_box_first->set_size({ 60,45 });
			hurt_box->set_size({ 60,45 });
		}
		else
		{
			hit_box_first->set_enable(false);
			hurt_box->set_enable(false);
			hit_box_second->set_enable(false);
		}

		Dash_Leave_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else
	{
		finish_dash = true;
		dash_right_clear();
	}
}

void Enemy::dstab_left(float delta)
{
	if (!Dstab_Arrive_left->is_finish_loop)
	{
		current_animation = Dstab_Arrive_left;
		if (!position)
		{
			enemy_point.x = enemy_point.x - 0.7 * Dstab_Arrive_left->frame_list[0]->getwidth();
			position = true;
		}
		else if (Dstab_Arrive_left->NextIdex(delta) >1 && Dstab_Arrive_left->idx_frame == 1)
		{
			hit_box_first->set_enable(true);
			hurt_box->set_enable(true);
			enemy_point.x = enemy_point.x + 0.5 * Dstab_Arrive_left->frame_list[1]->getwidth();
			enemy_point.y = enemy_point.y + Dstab_Arrive_left->frame_list[1]->getheight() - Dstab_Arrive_left->frame_list[2]->getheight();
		}
		else if (Dstab_Arrive_left->NextIdex(delta) >= 8)
		{
			enemy_point.x = enemy_point.x + 0.5 * Dstab_Arrive_left->frame_list[Dstab_Arrive_left->idx_frame]->getwidth() - 0.5 * Dstab_Arrive_left->frame_list[Dstab_Arrive_left->NextIdex(delta)]->getwidth();
			enemy_point.y = enemy_point.y + Dstab_Arrive_left->frame_list[Dstab_Arrive_left->idx_frame]->getheight() - Dstab_Arrive_left->frame_list[Dstab_Arrive_left->NextIdex(delta)]->getheight();
		}
		else
		{
			
			enemy_point.y = enemy_point.y + Dstab_Arrive_left->frame_list[Dstab_Arrive_left->idx_frame]->getheight() - Dstab_Arrive_left->frame_list[Dstab_Arrive_left->NextIdex(delta)]->getheight();
		}
		if (Dstab_Arrive_left->NextIdex(delta) >= 2 && Dstab_Arrive_left->NextIdex(delta) <= 4)
		{
			long current_x = enemy_point.x + 0.25 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
			hit_box_first->set_position({ current_x,get_logic_center_enemy().y });
			hurt_box->set_position({ current_x,get_logic_center_enemy().y });
			hit_box_first->set_size({ 60,60 });
			hurt_box->set_size({ 60,60 });
		}
		else if (Dstab_Arrive_left->NextIdex(delta) >= 5)
		{
			hit_box_first->set_position(get_logic_center_enemy());
			hurt_box->set_position(get_logic_center_enemy());
		}
		Dstab_Arrive_left->Play(enemy_point.x, enemy_point.y, delta,true,true);
		if(Dstab_Arrive_left->is_finish_loop) enemy_point.x = enemy_point.x + 0.4 * Dstab_Arrive_left->frame_list[11]->getwidth();
	}
	else if (enemy_point.y + Dstab_Attack_left->frame_list[Dstab_Attack_left->NextIdex(delta)]->getheight() <= boundary.y_platform)
	{
		current_animation = Dstab_Attack_left;

		long current_y = enemy_point.y + 0.6 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();
		hit_box_first->set_position({ get_logic_center_enemy().x,current_y });
		hurt_box->set_position({ get_logic_center_enemy().x,current_y });
		hit_box_first->set_size({40,157});
		hurt_box->set_size({40,157});
		need_y = hit_box_first->get_position().y;

		Dstab_Attack_left->Play(enemy_point.x, enemy_point.y, delta);
		enemy_point.x = enemy_point.x;
		enemy_point.y += 4000 * delta;
	}
	else if (!Dstab_Land_left->is_finish_loop)
	{
		current_animation = Dstab_Land_left;

		hit_box_first->set_position({ hit_box_first->get_position().x,need_y+97 });
		hurt_box->set_position({ hit_box_first->get_position().x,need_y+97 });
		hit_box_first->set_size({ 50,70 });
		hurt_box->set_size({ 50,70 });

		if (enemy_point.y + Dstab_Attack_left->frame_list[Dstab_Attack_left->NextIdex(delta)]->getheight() > boundary.y_platform&&position==true)
		{
			enemy_point.y = boundary.y_platform - Dstab_Land_left->frame_list[Dstab_Land_left->NextIdex(delta)]->getheight();
			enemy_point.x = enemy_point.x + Dstab_Attack_left->frame_list[Dstab_Attack_left->NextIdex(delta)]->getwidth() / 2 - Dstab_Land_left->frame_list[0]->getwidth() / 2;
			position = false;
		}
		else if (Dstab_Land_left->NextIdex(delta) <= 5)
		{

			enemy_point.x = enemy_point.x + Dstab_Land_left->frame_list[Dstab_Land_left->idx_frame]->getwidth() - Dstab_Land_left->frame_list[Dstab_Land_left->NextIdex(delta)]->getwidth();
			enemy_point.y = boundary.y_platform - Dstab_Land_left->frame_list[Dstab_Land_left->NextIdex(delta)]->getheight();
		}
		else if (Dstab_Land_left->NextIdex(delta) > 5)
		{
			enemy_point.x = enemy_point.x + Dstab_Land_left->frame_list[Dstab_Land_left->idx_frame]->getwidth() / 2 - Dstab_Land_left->frame_list[Dstab_Land_left->NextIdex(delta)]->getwidth() / 2;
			enemy_point.y = boundary.y_platform - Dstab_Land_left->frame_list[Dstab_Land_left->NextIdex(delta)]->getheight();
		}

		Dstab_Land_left->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Dstab_Leave_left->is_finish_loop)
	{
		current_animation = Dstab_Leave_left;

		hit_box_first->set_enable(false);
		hurt_box->set_enable(false);

		if (Dstab_Leave_left->idx_frame == 0 && Dstab_Leave_left->LastIdex(delta) == -1)
		{
			enemy_point.x += 2400 * delta;
			enemy_point.y = boundary.y_platform - Dstab_Leave_left->frame_list[Dstab_Leave_left->NextIdex(delta)]->getheight() - 1200 * delta;
		}
		else if (Dstab_Leave_left->NextIdex(delta) == 1 && Dstab_Leave_left->idx_frame == 0)
		{
			enemy_point.x += 2400 * delta;
			enemy_point.y = boundary.y_platform - Dstab_Leave_left->frame_list[Dstab_Leave_left->NextIdex(delta)]->getheight() - 3000 * delta;
		}

		Dstab_Leave_left->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else
	{
		finish_dstab = true;
		dstab_left_clear();
	}
}

void Enemy::dstab_right(float delta)
{
	if (!Dstab_Arrive_right->is_finish_loop)
	{
		current_animation = Dstab_Arrive_right;
		if (!position)
		{
			enemy_point.x = enemy_point.x - 0.3 * Dstab_Arrive_right->frame_list[0]->getwidth();
			position = true;
		}
		else if (Dstab_Arrive_right->NextIdex(delta) > 1 && Dstab_Arrive_right->idx_frame == 1)
		{
			hit_box_first->set_enable(true);
			hurt_box->set_enable(true);
			enemy_point.x = enemy_point.x + 0.5 * Dstab_Arrive_right->frame_list[1]->getwidth()-Dstab_Arrive_right->frame_list[Dstab_Arrive_right->NextIdex(delta)]->getwidth();
			enemy_point.y = enemy_point.y + Dstab_Arrive_right->frame_list[1]->getheight() - Dstab_Arrive_right->frame_list[2]->getheight();
		}
		else if (Dstab_Arrive_right->NextIdex(delta) >= 8)
		{
			enemy_point.x = enemy_point.x + 0.5 * Dstab_Arrive_right->frame_list[Dstab_Arrive_right->idx_frame]->getwidth() - 0.5 * Dstab_Arrive_right->frame_list[Dstab_Arrive_right->NextIdex(delta)]->getwidth();
			enemy_point.y = enemy_point.y + Dstab_Arrive_right->frame_list[Dstab_Arrive_right->idx_frame]->getheight() - Dstab_Arrive_right->frame_list[Dstab_Arrive_right->NextIdex(delta)]->getheight();
		}
		else
		{
			enemy_point.x = enemy_point.x + Dstab_Arrive_right->frame_list[Dstab_Arrive_right->idx_frame]->getwidth() - Dstab_Arrive_right->frame_list[Dstab_Arrive_right->NextIdex(delta)]->getwidth();
			enemy_point.y = enemy_point.y + Dstab_Arrive_right->frame_list[Dstab_Arrive_right->idx_frame]->getheight() - Dstab_Arrive_right->frame_list[Dstab_Arrive_right->NextIdex(delta)]->getheight();
		}
		if (Dstab_Arrive_right->NextIdex(delta) >= 2 && Dstab_Arrive_right->NextIdex(delta) <= 4)
		{
			long current_x = enemy_point.x + 0.75 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
			hit_box_first->set_position({ current_x,get_logic_center_enemy().y });
			hurt_box->set_position({ current_x,get_logic_center_enemy().y });
			hit_box_first->set_size({ 60,60 });
			hurt_box->set_size({ 60,60 });
		}
		else if (Dstab_Arrive_right->NextIdex(delta) >= 5)
		{
			hit_box_first->set_position(get_logic_center_enemy());
			hurt_box->set_position(get_logic_center_enemy());
		}
		Dstab_Arrive_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
		if (Dstab_Arrive_right->is_finish_loop) enemy_point.x = enemy_point.x + 0.6 * Dstab_Arrive_right->frame_list[11]->getwidth()-Dstab_Attack_right->frame_list[0]->getwidth();
	}
	else if (enemy_point.y + Dstab_Attack_right->frame_list[Dstab_Attack_right->idx_frame]->getheight() <= boundary.y_platform)
	{
		current_animation = Dstab_Attack_right;

		long current_y = enemy_point.y + 0.6 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();
		hit_box_first->set_position({ get_logic_center_enemy().x,current_y });
		hurt_box->set_position({ get_logic_center_enemy().x,current_y });
		hit_box_first->set_size({ 40,157 });
		hurt_box->set_size({ 40,157 });
		need_y = hit_box_first->get_position().y;

		Dstab_Attack_right->Play(enemy_point.x, enemy_point.y, delta);
		enemy_point.x = enemy_point.x;
		enemy_point.y += 4000 * delta;
	}
	else if (!Dstab_Land_right->is_finish_loop)
	{
		current_animation = Dstab_Land_right;

		hit_box_first->set_position({ hit_box_first->get_position().x,need_y + 97 });
		hurt_box->set_position({ hit_box_first->get_position().x,need_y + 97 });
		hit_box_first->set_size({ 50,70 });
		hurt_box->set_size({ 50,70 });

		if (enemy_point.y + Dstab_Attack_right->frame_list[Dstab_Attack_right->NextIdex(delta)]->getheight() > boundary.y_platform&&position==true)
		{
			enemy_point.y = boundary.y_platform - Dstab_Land_right->frame_list[Dstab_Land_right->NextIdex(delta)]->getheight();
			enemy_point.x = enemy_point.x + Dstab_Attack_right->frame_list[Dstab_Attack_right->NextIdex(delta)]->getwidth() / 2 - Dstab_Land_right->frame_list[0]->getwidth() / 2;
			position = false;
		}
		else if (Dstab_Land_right->idx_frame <= 5)
		{
			enemy_point.x = enemy_point.x;
			enemy_point.y = boundary.y_platform - Dstab_Land_right->frame_list[Dstab_Land_right->NextIdex(delta)]->getheight();
		}
		else if (Dstab_Land_right->idx_frame > 5)
		{
			enemy_point.x = enemy_point.x + Dstab_Land_right->frame_list[Dstab_Land_right->idx_frame]->getwidth() / 2 - Dstab_Land_right->frame_list[Dstab_Land_right->NextIdex(delta)]->getwidth() / 2;
			enemy_point.y = boundary.y_platform - Dstab_Land_right->frame_list[Dstab_Land_right->NextIdex(delta)]->getheight();
		}

		Dstab_Land_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Dstab_Leave_right->is_finish_loop)
	{
		current_animation = Dstab_Leave_right;

		hit_box_first->set_enable(false);
		hurt_box->set_enable(false);

		if (Dstab_Leave_right->idx_frame == 0 && Dstab_Leave_right->LastIdex(delta) == -1)
		{
			enemy_point.x -= 2400 * delta;
			enemy_point.y = boundary.y_platform - Dstab_Leave_right->frame_list[Dstab_Leave_right->NextIdex(delta)]->getheight() - 1200 * delta;
		}
		else if (Dstab_Leave_right->NextIdex(delta) == 1 && Dstab_Leave_right->idx_frame == 0)
		{
			enemy_point.x -= 2400 * delta;
			enemy_point.y = boundary.y_platform - Dstab_Leave_right->frame_list[Dstab_Leave_right->NextIdex(delta)]->getheight() - 3000 * delta;
		}

		Dstab_Leave_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else
	{
		finish_dstab = true;
		dstab_right_clear();
	}
}

void Enemy::wall_left(float delta)
{

	if (!Wall_Arrive_left->is_finish_loop)
	{
		current_animation = Wall_Arrive_left;
		if(Wall_Arrive_left->NextIdex(delta)==0)  enemy_point.x = boundary.x_right - Wall_Arrive_left->frame_list[Wall_Arrive_left->NextIdex(delta)]->getwidth()- 2400 * delta;
		else enemy_point.x = boundary.x_right - Wall_Arrive_left->frame_list[Wall_Arrive_left->NextIdex(delta)]->getwidth();
		if (Wall_Arrive_left->NextIdex(delta) <= 2)
		{
			enemy_point.y = height - Wall_Arrive_left->frame_list[Wall_Arrive_left->NextIdex(delta)]->getheight()/2+20*Wall_Arrive_left->NextIdex(delta);
		}
		else
		{
			enemy_point.y = height;
			height_foot = height + Wall_Arrive_left->frame_list[Wall_Arrive_left->NextIdex(delta)]->getheight() * 35 / 48;

			hit_box_first->set_enable(true);
			hurt_box->set_enable(true);
			long current_x = enemy_point.x + 0.6 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
			long current_y = enemy_point.y + 0.3 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();
			hit_box_first->set_position({ current_x, current_y });
			hurt_box->set_position({ current_x, current_y });
			hit_box_first->set_size({ 45,90 });
			hurt_box->set_size({ 45,90 });

		}
		Wall_Arrive_left->Play(enemy_point.x, enemy_point.y, delta,true,true);
	}
	else if (!Wall_Ready_left->is_finish_loop)
	{
		enemy_point.y = height_foot - Wall_Ready_left->frame_list[Wall_Ready_left->NextIdex(delta)]->getheight();
		if (Wall_Ready_left->NextIdex(delta) == 0)  enemy_point.x = boundary.x_right - Wall_Ready_left->frame_list[Wall_Ready_left->NextIdex(delta)]->getwidth();
		else enemy_point.x= boundary.x_right - Wall_Ready_left->frame_list[Wall_Ready_left->NextIdex(delta)]->getwidth()+ 1500 * delta;
		current_animation = Wall_Ready_left;
		Wall_Ready_left->Play(enemy_point.x, enemy_point.y, delta,true,true);
	}
	else if (!Throw_left->is_finish_loop)
	{
		is_play_projectile = true; 
		if (Throw_left->NextIdex(delta) <= 1) enemy_point.y = height_foot - Throw_left->frame_list[Throw_left->NextIdex(delta)]->getheight();
		else enemy_point.y = height;
		if (Throw_left->NextIdex(delta) == 1) enemy_point.x = boundary.x_right - Throw_left->frame_list[1]->getwidth() + 1800 * delta;
		else enemy_point.x = boundary.x_right - Throw_left->frame_list[Throw_left->NextIdex(delta)]->getwidth();
		current_animation = Throw_left;
		Throw_left->Play(enemy_point.x, enemy_point.y, delta,true,true);
	}
	else if (!Wall_leave1_left->is_finish_loop)
	{
		enemy_point.y = height;
		enemy_point.x = boundary.x_right - Wall_leave1_left->frame_list[Wall_leave1_left->NextIdex(delta)]->getwidth();
		current_animation = Wall_leave1_left;
		Wall_leave1_left->Play(enemy_point.x, enemy_point.y, delta,true,true);
	}
	else if (!Wall_leave2_left->is_finish_loop)
	{
		hit_box_first->set_enable(false);
		hurt_box->set_enable(false);

		enemy_point.x = boundary.x_right - Wall_leave2_left->frame_list[Wall_leave2_left->NextIdex(delta)]->getwidth();
		enemy_point.y = height - 1200 * delta - 1200 * delta *(Wall_leave2_left->NextIdex(delta)+1)/2;
		current_animation = Wall_leave2_left;
		Wall_leave2_left->Play(enemy_point.x, enemy_point.y, delta,true,true);
	}
	else
	{
		wall_left_clear();
		height_generation = false;
		finish_wall = true;
	}

}

void Enemy::wall_right(float delta)
{

	if (!Wall_Arrive_right->is_finish_loop)
	{
		if (Wall_Arrive_right->NextIdex(delta) == 0)  enemy_point.x = boundary.x_left + 2400 * delta;
		else enemy_point.x = boundary.x_left ;
		if (Wall_Arrive_right->NextIdex(delta) <= 2)
		{
			enemy_point.y = height - Wall_Arrive_right->frame_list[Wall_Arrive_right->NextIdex(delta)]->getheight()/2 + 1200 * delta * Wall_Arrive_right->NextIdex(delta);
		}
		else
		{
			enemy_point.y = height;
			height_foot = height + Wall_Arrive_right->frame_list[Wall_Arrive_right->NextIdex(delta)]->getheight() * 35 / 48;

			hit_box_first->set_enable(true);
			hurt_box->set_enable(true);
			long current_x = enemy_point.x + 0.4 * current_animation->frame_list[current_animation->NextIdex(delta)]->getwidth();
			long current_y = enemy_point.y + 0.3 * current_animation->frame_list[current_animation->NextIdex(delta)]->getheight();
			hit_box_first->set_position({ current_x, current_y });
			hurt_box->set_position({ current_x, current_y });
			hit_box_first->set_size({ 45,90 });
			hurt_box->set_size({ 45,90 });
		}
		current_animation = Wall_Arrive_right;
		Wall_Arrive_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Wall_Ready_right->is_finish_loop)
	{
		enemy_point.y = height_foot - Wall_Ready_right->frame_list[Wall_Ready_right->NextIdex(delta)]->getheight();
		if (Wall_Ready_right->NextIdex(delta) == 0)  enemy_point.x = boundary.x_left;
		else enemy_point.x = boundary.x_left - 1500 * delta;
		current_animation = Wall_Ready_right;
		Wall_Ready_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Throw_right->is_finish_loop)
	{
		is_play_projectile = true;
		if (Throw_right->NextIdex(delta) <= 1) enemy_point.y = height_foot - Throw_right->frame_list[Throw_right->NextIdex(delta)]->getheight();
		else enemy_point.y = height;
		if (Throw_right->NextIdex(delta) == 1) enemy_point.x = boundary.x_left - 1800 * delta;
		else enemy_point.x = boundary.x_left ;
		current_animation = Throw_right;
		Throw_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Wall_leave1_right->is_finish_loop)
	{
		enemy_point.y = height;
		enemy_point.x = boundary.x_left ;
		current_animation = Wall_leave1_right;
		Wall_leave1_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else if (!Wall_leave2_right->is_finish_loop)
	{
		hit_box_first->set_enable(false);
		hurt_box->set_enable(false);

		enemy_point.x = boundary.x_left ;
		enemy_point.y = height - 1200 * delta - 1200 * delta * (Wall_leave2_right->NextIdex(delta) + 1) / 2;
		current_animation = Wall_leave2_right;
		Wall_leave2_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
	else
	{
		wall_right_clear();
		height_generation = false;
		finish_wall = true;
	}

}

void Enemy::wall_left_low(float delta)
{
	if (!height_generation)
	{
		height = 310 - rand() % 10;
		height_generation = true;
	}
	if (!finish_wall)
	{
		wall_left(delta);
	}
}

void Enemy::wall_right_low(float delta)
{
	if (!height_generation)
	{
		height = 310 - rand() % 10;
		height_generation = true;
	}
	if (!finish_wall)
	{
		wall_right(delta);
	}

}

void Enemy::wall_left_high(float delta)
{
	if (!height_generation)
	{
		height = 238 - rand() % 10;
		height_generation = true;
	}
	if (!finish_wall)
	{
		wall_left(delta);
	}
}

void Enemy::wall_right_high(float delta)
{
	if (!height_generation)
	{
		height = 238 - rand() % 10;
		height_generation = true;
	}
	if (!finish_wall)
	{
		wall_right(delta);
	}
}

void Enemy::throw_projectile(bool is_low,bool is_left)
{
	if (air_projectile.empty())
	{
		Air_Projectile* projectile = new Air_Projectile(is_low,is_left);
		air_projectile.push_back(projectile);
	}

}

void Enemy::throw_projectile(bool is_low, bool is_left, bool x)
{
	if (air_projectile.empty())
	{
		Air_Projectile* projectile = new Air_Projectile(is_low, is_left,x);
		air_projectile.push_back(projectile);
	}
}

POINT Enemy::get_logic_down()
{
	if (current_animation) return { enemy_point.x + current_animation->frame_list[current_animation->idx_frame]->getwidth(),enemy_point.y + current_animation->frame_list[current_animation->idx_frame]->getheight() };
	return { 0,0 };
}

POINT Enemy::get_enemy_pos()
{
	return enemy_point;
}

void Enemy::set_death_pos(int x,int y)
{
	death_pos.x = x;
	death_pos.y = y;
}

void Enemy::set_enemy_pos(int x, int y)
{
	enemy_point.x = x;
	enemy_point.y = y;
}


void Enemy::death_land(float delta)
{
	current_animation = Death_land;
	if (get_blinking_invulnerable())
	{
		sketch_image(current_animation->frame_list[current_animation->idx_frame], &image_sketch);
		putimagealpha(death_pos.x, death_pos.y, &image_sketch);
		current_animation->timer += delta;
		if (current_animation->timer >= current_animation->interval_ms)
		{
			current_animation->idx_frame = (current_animation->idx_frame + 1) % current_animation->frame_list.size();
			current_animation->timer = 0;
		}

	}
	else
	{
		Death_land->Play(death_pos.x, death_pos.y, delta);
	}

}

void Enemy::back_left(float delta)
{
	
}

void Enemy::back_right(float delta)
{

}

void Enemy::death_leave_left(float delta)
{
	current_animation = Death_leave_left;
	if (!Death_leave_left->is_finish_loop)
	{
		enemy_point.y -= 1800 * delta;
		Death_leave_left->Play(enemy_point.x, enemy_point.y, delta, true, true);
	
	}

}

void Enemy::death_leave_right(float delta)
{
	current_animation = Death_leave_right;
	if (!Death_leave_right->is_finish_loop)
	{
		enemy_point.y -= 1800 * delta;
		Death_leave_right->Play(enemy_point.x, enemy_point.y, delta, true, true);
	}
}

void Enemy::death_leave_reset()
{
	Death_leave_left->Reset();
	Death_leave_right->Reset();
}

void Enemy:: change_enemy_point(int x,int y)
{
	enemy_point.x= x;
	enemy_point.y = y;
}

POINT Enemy::get_logic_center_enemy()
{
	if (current_animation)
		return { enemy_point.x + current_animation->frame_list[current_animation->idx_frame]->getwidth() / 2,enemy_point.y + current_animation->frame_list[current_animation->idx_frame]->getheight() / 2 };
	else
		return{ 0,0 };
}

void Throne1::dash_left_clear1()
{
	Enemy::dash_left_clear();
}

void Throne1::dash_right_clear1()
{
	Enemy::dash_right_clear();
}

void Throne1::dstab_left_clear1()
{
	Enemy::dstab_left_clear();
}

void Throne1::dstab_right_clear1()
{
	Enemy::dstab_right_clear();
}

void Throne1::wall_left_clear1()
{
	Enemy::wall_left_clear();
	height_generation = false;
}

void Throne1::wall_right_clear1()
{
	Enemy::wall_right_clear();
	height_generation = false;
}

void Throne1::stand(float delta)
{
	Enemy::stand(delta);
}

bool Throne1::if_finish_battle()
{
	return finish_battle;
}

void Throne1::set_finish_battle()
{
	finish_battle = true;
}





