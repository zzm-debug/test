
#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include"Character.h"
#include"Enemy.h"
#include<easyx.h>

class CharacterManager
{
public:
	static CharacterManager* instance();

	character* get_player()
	{
		return player;
	}

	character* get_enemy()
	{
		return throne1;
	}
	character* get_enemy2()
	{
		return throne2;
	}
	character* get_enemy3()
	{
		return throne3;
	}

	void on_input(const ExMessage& msg);
	void on_update(float delta);
	void on_render(float delta);


private:
	character* player=nullptr;
	character* throne1 = nullptr;
	character* throne2 = nullptr;
	character* throne3 = nullptr;
	static CharacterManager* manager;

	CharacterManager();
	~CharacterManager();
    
};

#endif // !CHARACTERMANAGER_H

