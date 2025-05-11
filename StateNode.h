

#ifndef STATENODE_H
#define STATENODE_H

class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;
	virtual void on_enter() {};
	virtual void on_update(float delta) {};
	virtual void on_end() {};
private:

};

#endif // !STATENODE_H

