#include<functional>
#include<stdbool.h>
using namespace std;


#ifndef TIME_H
#define TIME_H



class Timer
{
public:
	Timer() = default;
	~Timer() = default;
	void restart()
	{
		passtime = 0;
		shotted = false;
	}
	void set_one_shotted(bool flag)
	{
		one_shotted = flag;
	}
	void set_wait_time(float delta)
	{
		waittime = delta;
	}
	void set_callback(function<void()> callback)
	{
		this->callback = callback;
	}
	void ispause()
	{
		pause = true;
	}
	void resume()
	{
		pause = false;
	}
	void update(float delta)
	{
		if (pause) return;
		passtime += delta;
		if (passtime >= waittime)
		{
			if ((!one_shotted || (one_shotted && !shotted)) && callback)
				callback();
			passtime = 0;
			shotted = true;
		}
	}

private:
	float passtime = 0;
	float waittime = 0;
	bool pause = false;
	bool shotted = false;    //�Ƿ��ѱ�����
	bool one_shotted = false;   //�Ƿ��ǵ��δ���
	function<void()> callback;
};


#endif // !TIME_H




