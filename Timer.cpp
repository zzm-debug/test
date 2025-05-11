#include<functional>
#include<stdbool.h>
using namespace std;


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
	void set_wait_time(int delta)
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
	void update(int delta)
	{
		if (pause) return;
		passtime += delta;
		if (passtime >= waittime)
		{
			if ((!one_shotted || (one_shotted && !shotted)) && callback)
				callback();
			passtime = 0;
			shotted = false;
		}
	}

private:
	int passtime = 0;
	int waittime = 0;
	bool pause = false;
	bool shotted = false;    //是否已被触发
	bool one_shotted = false;   //是否是单次触发
	function<void()> callback;
};