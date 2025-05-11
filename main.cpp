#include<iostream>
#include<easyx.h>
#include<Windows.h>
#include<conio.h>
#include<stdbool.h>
#include<string>
#include<vector>
#include<chrono>
#include<thread>
#include"Animation.h"
#include"Player.h"
#include"bullet.h"
#include"Enemy.h"
#include"collision.h"
#include"Mantis Air Projectile.h"
#include"CharacterManager.h"
#include"collision.h"
#include"Camera.h"
#include"CameraManager.h"
#include"UI.h"
#include <mmsystem.h>

bool play_bgm1 = false;
bool run = true;

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")

UI ui;

//可以尝试一下状态机

void load_bgm()
{
	mciSendString(_T("open Effect/AudioClip/sword_2.wav alias sword2"), NULL, 10, NULL);
	mciSendString(_T("open Effect/AudioClip/sword_3.wav alias sword3"), NULL, 10, NULL);
	mciSendString(_T("open Effect/AudioClip/sword_3.wav alias sword4"), NULL, 10, NULL);
}

void play_bgm() {
	MCIERROR error = mciSendStringA(
		"open \"Effect/AudioClip/Christopher Larkin - Mantis Lords.mp3\" alias bgm",
		NULL, 0, NULL
	);
	if (error) {
		char errorMsg[256];
		mciGetErrorStringA(error, errorMsg, sizeof(errorMsg));

		return;
	}
	mciSendStringA("play bgm repeat", NULL, 0, NULL);
}

int main()
{
	using namespace std::chrono;
	srand((unsigned)time(nullptr));

	IMAGE imgbackground;
	loadimage(&imgbackground, L"Godhome_Arena_Mantis_Lords_Sisters_of_Battle.png", 1280, 720);
	load_bgm();

	initgraph(1280, 720);
	ExMessage msg;


	const nanoseconds frame_duration(1000000000 / 90);
	steady_clock::time_point last_tick = steady_clock::now();

	BeginBatchDraw();

	while (run)
	{
		Player* player = (Player*)CharacterManager::instance()->get_player();
		if (player->is_start)
		{
			play_bgm();
		}

		while (peekmessage(&msg))
		{
			CharacterManager::instance()->on_input(msg);
		}

		steady_clock::time_point start_time = steady_clock::now();
		duration<float> delta = duration<float>(start_time - last_tick);

		CollisionManager::instance()->process_collide();
		CharacterManager::instance()->on_update(delta.count());
		ui.on_update(delta.count());

		cleardevice();

		Camera* camera = CameraManager::instance()->get_camera();
		camera->on_update(delta.count());
		putimage(0-camera->get_position().x, 0-camera->get_position().y, &imgbackground);
		

		CharacterManager::instance()->on_render(delta.count());
		CollisionManager::instance()->on_debug_render();
		ui.on_render(delta.count());

		FlushBatchDraw();

		last_tick = start_time;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - start_time);
		if (sleep_duration > nanoseconds(0))
				std::this_thread::sleep_for(sleep_duration);
	}
	EndBatchDraw();
	return 0;
}

//中心点为657，620