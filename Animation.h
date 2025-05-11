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
	Animation(LPCTSTR path,int num,float interval);  //��ҹ��캯��
	Animation(LPCTSTR path, int num, float interval, bool x, bool y);  //boss���캯��
	Animation(LPCTSTR path, int num, float interval, bool is_flip); //boss��תͼƬ����
	Animation(LPCTSTR path, int num, float interval, bool is_flip,char w);  //��ɫ��תͼƬ

	~Animation();
	void Play(int x,int y,float delta);
	void Play(int x, int y, float delta, int t);//Բ��ֻѭ��ǰ��֡
	void Play(int x, int y, float delta, bool is_running);////�ܲ������ӵ���֡��ʼloop
	void Play(int x, int y, float delta, double v);  //��Ծ������Ϊ�����½�������
	void Play(int x, int y, float delta, bool is_loop1, bool is_loop2);//��ѭ������
	void Reset();   //���ö���
	bool finish_play(float delta);
	int NextIdex(float delta);  //�����������һ֡
	int LastIdex(float delta);
	int NextIdex_loop(float delta);

private:
	float interval_ms = 0;
	float timer = 0;  //������ʱ��
	int idx_frame = 0;  //����֡����
	bool is_finish_loop = false;
	vector<IMAGE*> frame_list;

};

void putimagealpha(int x, int y, IMAGE* img);//ʵ��͸��ͼƬ
void flipAmination(IMAGE* img1, IMAGE* img2, int length);//ͼƬ��ת
void sketch_image(IMAGE* img1, IMAGE* img2);  //����ͼƬ

#endif // ! ANIMATION_H
