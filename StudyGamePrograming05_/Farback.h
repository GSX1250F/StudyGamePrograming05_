#pragma once
#include "Actor.h"
class Farback : public Actor
{
public:
	Farback(Game* game);
	void UpdateActor(float deltaTime) override;

private:
	std::vector<class Actor>Farbacks;
	float offset;
	float scrollspeed;
};

