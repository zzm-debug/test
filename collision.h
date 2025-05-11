
#ifndef COLLISION_H
#define COLLISION_H

#include"collision_sort.h"
#include<vector>
#include<functional>
#include<easyx.h>
#include<Windows.h>

//size.x,size.y 表示的是半径

struct boudary
{
	const int x_left = 62;
	const int x_right = 1219;
	const int x_platform_left = 234;
	const int x_platform_right = 1048;
	const int y_spike = 627;
	const int y_platform = 620;
};

class CollisionBox;  // 前向声明

class CollisionManager
{
public:
	static CollisionManager* instance();

	CollisionBox* create_collision_box();
	void destroty_collsion_box(CollisionBox* collision_box);

	void process_collide();
	void on_debug_render();
private:
	static CollisionManager* manager;
	std::vector<CollisionBox*> collision_box_list;

private:
	CollisionManager()=default ;
	~CollisionManager()=default ;
};

class CollisionBox
{
	friend class CollisionManager;
public:
	POINT size;
	POINT position;
	bool orientation = false;  //检测受击方向,false为左受击，true为右受击
	bool enable = true;
	std::function<void()> on_collide;
	CollisionSort layer_src = CollisionSort::None;
	CollisionSort layer_dst = CollisionSort::None;
	void set_enable(bool flag)
	{
		enable = flag;
	}
	void set_layer_src(CollisionSort layer)
	{
		layer_src = layer;
	}
	void set_layer_dst(CollisionSort layer)
	{
		layer_dst = layer;
	}
	void set_collide(std::function<void()> on_collide)
	{
		this->on_collide = on_collide;
	}
	void set_size(POINT size)
	{
		this->size = size;
	}
	void set_position(POINT position)
	{
		this->position = position;
	}
	const POINT& get_size()
	{
		return this->size;
	}
	const POINT& get_position()
	{
		return this->position;
	}

private:
	CollisionBox() = default;
	~CollisionBox() = default;
};

#endif // !COLLISION_H

