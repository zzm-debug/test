#include<vector>
#include"Animation.h"

#pragma once
#ifndef UI_H
#define UI_H

class UI
{
public:
	UI();
	~UI();
	void on_draw();
	void on_draw2();

	void draw_player_hp(float delta);

	void on_update(float delta);
	void on_render(float delta);
private:
	int left = 100;
	int top = 650;
	int right = 1180;
	int bottom = 680;
	int top2 = 650;
	int bottom2 = 665;
	int right2 = 1180;
	int top3 = 670;
	int bottom3 = 685;
	int right3 = 1180;
	int player_last_hp = 0;
	int hp_ilde_start_x = 75;
	int hp_idle_start_y = 25;
	int hp_start_x = 170;
	int hp_start_y = 37;
	int hp_interval = 55;
	bool can_remove = false;   //是否要去掉血量
	vector<Animation*> frame_list;
	Animation* frame_break;
	IMAGE* frame_idle;
};


#endif // !UI_H
