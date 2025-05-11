#include<iostream>

#ifndef GRAVITY_H
#define GRAVITY_H

class gravity
{
public:
	friend class Player;
	gravity();
	void air_inspection1(float delta); 
	void air_inspection2(float delta);  //����;���ɿ�����
	void air_inspection3(float delta); //�ı��������ٶ�
	void air_inspection4(float delta);  //�����ٶȱ仯
	void init4()
	{
		v = v_bounce;
	}
	double get_v()
	{
		return v;
	}
	void reset();
	void add(float delta);
	double vx =600;  //ˮƽ�ٶ�
	double vy = 0; //��ֱ�ٶ�
	double gy = 0;

private:
	const double g = 7740;    //ƽ�����������ٶ�
	double t = 0;  //������ʱ��
	const double v_start = 1130; //��ʼ�ٶ�
	const double v_bounce = 825;
	double v = 0; //Ŀǰ�������ٶ�
	const double g_alt = 4860;
};


#endif // !GRAVITY_H
