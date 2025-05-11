#include<easyx.h>
#include"Mantis Air Projectile.h"
#include"gravity.h"

Air_Projectile::Air_Projectile(bool is_low,bool is_left)
{
	fly = new Animation(_T("Mantis Lords Anim/033.Mantis Air Projectile/033-0%d.png"), 3, 1.0f / 15.0f,true,false);
	hit_box_first->set_layer_src(CollisionSort::Enemy);
	hit_box_first->set_layer_dst(CollisionSort::Player);
	hit_box_first->set_enable(true);
	hit_box_first->set_position(get_logic_center());
	hit_box_first->set_size({ 94,37 });
	if (is_low && is_left)
	{
		set_position(boundary.x_right - fly->frame_list[0]->getwidth(), boundary.y_platform - fly->frame_list[0]->getheight());
		gx = 1280;
		set_velocity(-1680, 40, 20);
	}
	else if (!is_low && is_left)
	{
		set_position(boundary.x_right - fly->frame_list[0]->getwidth(), boundary.y_platform - 200 - fly->frame_list[0]->getheight());
		gx=1580;
		set_velocity(-1880, -150, -120);
	}
	else if (is_low && !is_left)
	{
		set_position(boundary.x_left, boundary.y_platform - fly->frame_list[0]->getheight());
		gx = -1280;;
		set_velocity(1680, 40, 20);
	}
	else
	{
		set_position(boundary.x_left, boundary.y_platform - 200 - fly->frame_list[0]->getheight());
		gx= -1580;
		set_velocity(1880, -150, -120);
	}
}

Air_Projectile::Air_Projectile(bool is_low, bool is_left, bool x)
{
	fly = new Animation(_T("Mantis Lords Anim/033.Mantis Air Projectile/033-0%d.png"), 3, 1.0f / 15.0f, true, false);
	hit_box_first->set_layer_src(CollisionSort::Enemy);
	hit_box_first->set_layer_dst(CollisionSort::Player);
	hit_box_first->set_enable(true);
	hit_box_first->set_position(get_logic_center());
	hit_box_first->set_size({ 94,37 });
	if (is_low && is_left)
	{
		set_position(boundary.x_right - fly->frame_list[0]->getwidth(), boundary.y_platform - 300 - fly->frame_list[0]->getheight());
		gx = 1280;
		set_velocity(-1140, -200, -180);
	}
	else if (!is_low && is_left)
	{
		set_position(boundary.x_right - fly->frame_list[0]->getwidth(), boundary.y_platform - 300 - fly->frame_list[0]->getheight());
		gx = 1580;
		set_velocity(-1880, -180, -144);
	}
	else if (is_low && !is_left)
	{
		set_position(boundary.x_left, boundary.y_platform - 300 - fly->frame_list[0]->getheight());
		gx = -1280;;
		set_velocity(1140, -200, -180);
	}
	else
	{
		set_position(boundary.x_left, boundary.y_platform - 300 - fly->frame_list[0]->getheight());
		gx = -1580;
		set_velocity(1880, -180, -144);
	}
}

void Air_Projectile::on_update(float delta)
{
	if (is_start)
	{
		if (fly->frame_list.size() == 3)
			fly->frame_list.pop_back();
		vx = vx + gx * delta;
		pos_projectile.x = pos_projectile.x + vx * delta;
		if (vx*gx<=0)
		{
			pos_projectile.y = pos_projectile.y - vy1 * delta;
		}
		else pos_projectile.y = pos_projectile.y - vy2 * delta;
	}
	
	if (pos_projectile.x < -280 || pos_projectile.x>1280)
	{
		can_remove = true;
	}
	hit_box_first->set_position(get_logic_center());
	
}


void Air_Projectile::on_render(float delta)
{
	if (!is_start)
	{
		if (!is_start_alt)
		{
			fly->idx_frame = 2;
			is_start_alt = true;
		}
		fly->Play(pos_projectile.x, pos_projectile.y, delta);
		if (fly->timer+delta>=fly->interval_ms)
		{
			is_start = true;
			fly->idx_frame = 0;
		}
	}
	else
	{
		fly->Play(pos_projectile.x, pos_projectile.y, delta);
	}
}

void Air_Projectile::reset()
{
	is_start = false;      // 新增
	is_start_alt = false;  // 新增
	can_remove = false;
}

int Air_Projectile::get_x()
{
	return pos_projectile.x;
}

bool Air_Projectile::if_remove()
{
	return can_remove;
}

void Air_Projectile::set_position(int x, int y)
{
	pos_projectile.x = x;
	pos_projectile.y = y;
}

void Air_Projectile::set_velocity(int vx, int vy1, int vy2)
{
	Air_Projectile::vx = vx;
	Air_Projectile::vy1 = vy1;
	Air_Projectile::vy2 = vy2;
}

void Air_Projectile::set_gx(int g)
{
	gx = g;
}

POINT Air_Projectile::get_logic_center()
{
	return { pos_projectile.x + fly->frame_list[fly->idx_frame]->getwidth() / 2,pos_projectile.y + fly->frame_list[fly->idx_frame]->getheight() / 2 };
}
