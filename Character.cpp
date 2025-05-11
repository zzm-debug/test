#include"Character.h"
#include"collision.h"

int character::get_hp()
{
	return this->hp;
}

POINT character::get_pos()
{
	return this->pos;
}

void character::set_pos(POINT& pos)
{
	this->pos = pos;
}
void character::set_velocity_x(double vx)
{
	this->game_gravity.vx = vx;
}

void character::set_velocity_y(double vy)
{
	this->game_gravity.vy = vy;
}

void character::set_gravity(double g)
{
	this->game_gravity.gy = g;
}
double character::get_velocity_x()
{
	return this->game_gravity.vx;
}

double character::get_velocity_y()
{
	return this->game_gravity.vy;
}

double character::get_gravity()
{
	return this->game_gravity.gy;
}


void character::make_invulnerable()
{
	is_invulnerable = true;
	time_invulnerable.restart();
}

character::character()
{
	hurt_box = CollisionManager::instance()->create_collision_box();
	hit_box_first = CollisionManager::instance()->create_collision_box();
	hit_box_second = CollisionManager::instance()->create_collision_box();

	time_invulnerable.set_one_shotted(true);
	
	time_invulnerable.set_callback([&]()
		{
			is_invulnerable = false;
		});

	time_blinking_invulerable.set_one_shotted(false);
	time_blinking_invulerable.set_wait_time(0.075f);
	time_blinking_invulerable.set_callback([&]()
		{
			is_blinking_invulnerable = !is_blinking_invulnerable;
		});


}

character::~character()
{
	CollisionManager::instance()->destroty_collsion_box(hit_box_first);
	CollisionManager::instance()->destroty_collsion_box(hit_box_second);
	CollisionManager::instance()->destroty_collsion_box(hurt_box);
}

void character::decrease_hp(int damage)
{
	if (is_invulnerable) return;
	this->hp -= damage;
	on_hurt();
	if (this->hp > 0)
	{
		make_invulnerable();
	}
}

void character::on_update(float delta)
{
	state_machine.on_update(delta);
	if (hp <= 0)  set_velocity_x(0);

	time_invulnerable.update(delta);
	if (is_invulnerable)
	{
		time_blinking_invulerable.update(delta);
	}
}

void character::on_render(float delta)
{
	if ((is_invulnerable && !is_blinking_invulnerable) || !current_animation) return;
	current_animation->Play(pos.x, pos.y, delta);
}

void character::switch_state(const string& id)
{
	state_machine.switch_to(id);
}


void character::ProcessEvent(const ExMessage& msg)
{
	
}

CollisionBox* character::get_hit_box_first()
{
	return this->hit_box_first;
}

CollisionBox* character::get_hit_box_second()
{
	return this->hit_box_second;
}

CollisionBox* character::get_hurt_box()
{
	return this->hurt_box;
}