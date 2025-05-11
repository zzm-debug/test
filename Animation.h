#include<vector>
#include<stdbool.h>
#include<iostream>
#include<easyx.h>
#include"Camera.h"
using namespace std;

#ifndef  ANIMATION_H
#define  ANIMATION_H

class Animation
{
public:
	friend class Player;
	friend class Bullet;
	friend class Enemy;
	friend class Throne1;
	friend class Throne2;
	friend class Throne3;
	friend class Air_Projectile;
	friend class character;
	friend  class Effect;
	friend class UI;
	Animation(LPCTSTR path,int num,float interval);  //玩家构造函数
	Animation(LPCTSTR path, int num, float interval, bool x, bool y);  //boss构造函数
	Animation(LPCTSTR path, int num, float interval, bool is_flip); //boss翻转图片导入
	Animation(LPCTSTR path, int num, float interval, bool is_flip,char w);  //角色翻转图片

	~Animation();
	void Play(int x,int y,float delta);
	void Play(int x, int y, float delta, int t);//圆环只循环前两帧
	void Play(int x, int y, float delta, bool is_running);////跑步动作从第六帧开始loop
	void Play(int x, int y, float delta, double v);  //跳跃动作分为上升下降两部分
	void Play(int x, int y, float delta, bool is_loop1, bool is_loop2);//非循环动画
	void Reset();   //重置动画
	bool finish_play(float delta);
	int NextIdex(float delta);  //输出动画的下一帧
	int LastIdex(float delta);
	int NextIdex_loop(float delta);

private:
	float interval_ms = 0;
	float timer = 0;  //动画计时器
	int idx_frame = 0;  //动画帧索引
	bool is_finish_loop = false;
	vector<IMAGE*> frame_list;

};

void putimagealpha(int x, int y, IMAGE* img);//实现透明图片
void flipAmination(IMAGE* img1, IMAGE* img2, int length);//图片翻转
void sketch_image(IMAGE* img1, IMAGE* img2);  //闪白图片

#endif // ! ANIMATION_H
