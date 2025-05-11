#include"UI.h"
#include"CharacterManager.h"
#include"CameraManager.h"

UI::UI()
{
	frame_break= new Animation(_T("HUD Anim/009.Blue Break/009-0%d.png"), 5, 1.0f / 20.0f, false, true);
	frame_idle = new IMAGE();
	loadimage(frame_idle, _T("HUD Anim/063.HUD Frame Idle GG/063-00-139.png"), 217,105);
	for (int i = 0; i < 10; i++)
	{
		Animation* temp = new Animation(_T("HUD Anim/008.Blue Idle/008-10 (%d).png"), 99, 1.0f / 15.0f, false, true);
		frame_list.push_back(temp);
	}
	player_last_hp = 10;
}

UI:: ~UI()
{
	for (int i = 0; i < frame_list.size(); i++)
	{
		delete frame_list[i];
	}
	delete frame_break;
}

void UI::on_draw()
{
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	Camera* camera = CameraManager::instance()->get_camera();
	right = 100 + 36 * enemy->get_hp();
	setfillcolor(RED);
	fillrectangle(left-camera->get_position().x, top-camera->get_position().y, right-camera->get_position().x, bottom-camera->get_position().y);
}

void UI::on_draw2()
{
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	Throne3* enemy3 = (Throne3*)CharacterManager::instance()->get_enemy3();
	Camera* camera = CameraManager::instance()->get_camera();
	right2 = 100 + 36 * enemy2->get_hp();
	right3 = 100 + 36 * enemy3->get_hp();
	setfillcolor(RED);
	fillrectangle(left-camera->get_position().x, top2-camera->get_position().y, right2-camera->get_position().x, bottom2-camera->get_position().y);
	fillrectangle(left-camera->get_position().x, top3-camera->get_position().y, right3-camera->get_position().x, bottom3-camera->get_position().y);
}

void UI::draw_player_hp(float delta)
{
	putimagealpha(hp_ilde_start_x, hp_idle_start_y, frame_idle);
	if (!frame_list.empty())
	{
		for (int i = 0; i < frame_list.size(); i++)
		{
			frame_list[i]->Play(hp_start_x + i * hp_interval, hp_start_y, delta);
		}
	}
	if (can_remove)
	{
		if(!frame_break->is_finish_loop)
		frame_break->Play(hp_start_x + frame_list.size()* hp_interval, hp_start_y, delta,true,true);
		else
		{
			frame_break->Reset();
			can_remove = false;
		}
	}

}

void UI::on_update(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	if (player->get_hp() < player_last_hp)
	{
		can_remove = true;
		if(!frame_list.empty())
		frame_list.pop_back();
	}
	player_last_hp = player->get_hp();
}

void UI::on_render(float delta)
{
	Player* player = (Player*)CharacterManager::instance()->get_player();
	Throne1* enemy = (Throne1*)CharacterManager::instance()->get_enemy();
	Throne2* enemy2 = (Throne2*)CharacterManager::instance()->get_enemy2();
	if (player->is_start && !enemy->be_death)
		on_draw();
	else if (enemy2->start_game2)
		on_draw2();

	draw_player_hp(delta);
}