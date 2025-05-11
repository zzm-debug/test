#include<iostream>
#include<easyx.h>
#include<string>
#include<Windows.h>
#include<vector>
#include"Animation.h"
#include"Camera.h"
#include"CameraManager.h"


Animation::Animation(LPCTSTR path, int num, float interval)
{
	interval_ms = interval;
	TCHAR pathfile[255];
	for (size_t t = 0; t < num; t++)
	{
		_stprintf_s(pathfile, path, t);

		IMAGE* frame = new IMAGE();
		loadimage(frame, pathfile);
		
		int width = frame->getwidth();
		int height = frame->getheight();
		loadimage(frame, pathfile, width * 0.65, height * 0.65);
		frame_list.push_back(frame);
	}
}

Animation::Animation(LPCTSTR path, int num, float interval,bool x,bool y)   //boss构造函数
{
	interval_ms = interval;
	TCHAR pathfile[255];
	for (size_t t = 0; t < num; t++)
	{
		_stprintf_s(pathfile,path,t);

		IMAGE* frame = new IMAGE();
		IMAGE* temp = new IMAGE();
		loadimage(temp, pathfile);
		int width = temp->getwidth();
		int height = temp->getheight();
		if (x&&y)
		{
			loadimage(frame, pathfile, width * 0.65, height * 0.65);
		}
		else if(x&&!y)
		{
			loadimage(frame, pathfile, width*0.95, height*0.95);
		}
		else if (!x && !y)
		{
			loadimage(frame, pathfile, width * 1.25, height * 1.25);
		}
		else
		{
			loadimage(frame, pathfile, width * 0.6, height * 0.6);
		}
		frame_list.push_back(frame);
		delete temp;
	}
}

Animation::Animation(LPCTSTR path, int num, float interval, bool is_flip)  
{

	interval_ms = interval;
	
	TCHAR pathfile[255];
	IMAGE* frame_before=new IMAGE[num];
	for (size_t t = 0; t < num; t++)
	{
		_stprintf_s(pathfile, path, t);
 		IMAGE temp;
		loadimage(&temp, pathfile);
		int width = temp.getwidth();
		int height = temp.getheight();
		loadimage(&frame_before[t], pathfile, width * 0.65, height * 0.65,true);
	}
	IMAGE* frame_now = new IMAGE[num];
	flipAmination(frame_before, frame_now, num);
	for(size_t t = 0; t < num; t++)
	frame_list.push_back(&frame_now[t]);
	delete[] frame_before;

}

Animation::Animation(LPCTSTR path, int num, float interval, bool is_flip,char w)
{

	interval_ms = interval;

	TCHAR pathfile[255];
	IMAGE* frame_before = new IMAGE[num];
	for (size_t t = 0; t < num; t++)
	{
		_stprintf_s(pathfile, path, t);
		loadimage(&frame_before[t], pathfile);
		int width = frame_before[t].getwidth();
		int height = frame_before[t].getheight();
		loadimage(&frame_before[t], pathfile, width * 0.65, height * 0.65, true);
	}
	IMAGE* frame_now = new IMAGE[num];
	flipAmination(frame_before, frame_now, num);
	for (size_t t = 0; t < num; t++)
		frame_list.push_back(&frame_now[t]);
	delete[] frame_before;

}



Animation::~Animation()
{
	for (size_t i = 0; i < frame_list.size(); i++)
	{
		delete frame_list[i];
	}
}

void Animation::Play(int x, int y, float delta)
{
	timer += delta;
	if (timer >= interval_ms)
	{
		idx_frame = (idx_frame + 1) % frame_list.size();
		timer = 0;
	}

	Camera* camera = CameraManager::instance()->get_camera();
	putimagealpha(x-camera->get_position().x, y-camera->get_position().y, frame_list[idx_frame]);
}

void Animation::Play(int x, int y, float delta,bool is_running)//跑步动作从第六帧开始loop
{
	timer += delta;
	if (timer >= interval_ms)
	{
		idx_frame++;
		if (idx_frame == frame_list.size() - 1)
		{
			idx_frame = 6;
		}
		timer = 0;
	}

	Camera* camera = CameraManager::instance()->get_camera();
	putimagealpha(x-camera->get_position().x, y-camera->get_position().y, frame_list[idx_frame]);
}

void Animation::Play(int x, int y, float delta,double v) //跳跃动作分为上升下降两部分
{
	timer += delta;
	if (timer >= interval_ms)
	{
		if (v > 0)
		{
			if (idx_frame < 8)
				idx_frame++;
			else if (idx_frame == 8)
				idx_frame = 8;
		}
		else if (v <= 0)
		{
			idx_frame++;
			if (idx_frame == frame_list.size() - 1)
			{
				idx_frame = 9;
			}
		}
		timer = 0;
	}

	Camera* camera = CameraManager::instance()->get_camera();
	putimagealpha(x-camera->get_position().x, y-camera->get_position().y, frame_list[idx_frame]);
}

void Animation::Play(int x, int y, float delta,bool is_loop1,bool is_loop2) //非循环播放
{
	timer += delta;
	if (timer >= interval_ms)
	{
		if (idx_frame < frame_list.size() - 1)
		{
			idx_frame++;
		}
		timer = 0;
	}
	if ((idx_frame==frame_list.size()-1&&timer + delta >= interval_ms)||timer+delta>=(frame_list.size()-idx_frame)*interval_ms)
	{
		is_finish_loop = true;
	}
	Camera* camera = CameraManager::instance()->get_camera();
	putimagealpha(x-camera->get_position().x, y-camera->get_position().y, frame_list[idx_frame]);

}

void Animation::Reset()
{
	idx_frame = 0;
	timer = 0;
	is_finish_loop = false;
}

int Animation::NextIdex(float delta)
{
	if (frame_list.empty()) return 0;
	int next = (timer + delta >= interval_ms) ? idx_frame + 1 : idx_frame;
	return (next >= frame_list.size()) ? frame_list.size() - 1 : next;
}

int Animation::LastIdex(float delta)
{
	if (timer < delta) return idx_frame - 1;
	else return idx_frame;
}


int Animation::NextIdex_loop(float delta)
{
	int next_frame = 0;
	if (timer + delta >= interval_ms)
	{
		next_frame = (idx_frame + 1) % frame_list.size();
	}
	else
	{
		next_frame = idx_frame;
	}
	return next_frame;
}

bool Animation::finish_play(float delta)
{
	if (idx_frame>2)
		return true;
	return false;
}