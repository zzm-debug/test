#include<stdbool.h>
#include<iostream>
#include"StateNode.h"
#include"State-Machine.h"
using namespace std;

void State_Machine::on_update(float delta)
{
	if (!current_state)  return;
	if (need_init)
	{
		current_state->on_enter();
		need_init = false;
	}
	current_state->on_update(delta);
}

void State_Machine::set_entry(const string &id)
{
	current_state = statepool[id];
}

void State_Machine::switch_to(const string& id)
{
	if (current_state) current_state->on_end();
	current_state = statepool[id];
	if(current_state) current_state->on_enter();
}

void State_Machine::register_state(const string& id, StateNode* state_node)
{
	statepool[id] = state_node;
}