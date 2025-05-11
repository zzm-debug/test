#include"CharacterManager.h"
#include"Player.h"
#include"Enemy.h"

CharacterManager* CharacterManager::manager = nullptr;

CharacterManager* CharacterManager::instance()
{
	if (!manager) manager = new CharacterManager();
	return manager;
}

void CharacterManager::on_input(const ExMessage& msg)
{
	player->ProcessEvent(msg);
}

void CharacterManager::on_update(float delta)
{

	throne2->on_update(delta);
	throne3->on_update(delta);
	throne1->on_update(delta);
	player->on_update(delta);
}

void CharacterManager::on_render(float delta)
{
	throne2->on_render(delta);
	throne3->on_render(delta);
	throne1->on_render(delta);
	player->on_render(delta);
}

CharacterManager::CharacterManager()
{
	player = new Player();
	throne1 = new Throne1();
	throne2 = new Throne2();
	throne3 = new Throne3();
}

CharacterManager::~CharacterManager()
{
	delete player;
	delete throne1;
	delete throne2;
	delete throne3;
}

