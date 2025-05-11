#include<string>
#include<unordered_map>
#include<stdbool.h>
#include"StateNode.h"
using namespace std;

#pragma once
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

class State_Machine
{
public:
	State_Machine() = default;
	~State_Machine() = default;

	void on_update(float delta);
	void set_entry(const string& id);
	void switch_to(const string& id);
	void register_state(const string& id,StateNode *state_node);

private:
	bool need_init = true;
	StateNode* current_state = nullptr;
	unordered_map<string, StateNode*> statepool;
};

#endif // !STATE-MACHINE_H

