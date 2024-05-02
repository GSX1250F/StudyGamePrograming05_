#pragma once
#include "Actor.h"

class Farback : public Actor
{
public:
	Farback(Game* game , int id);
	void UpdateActor(float deltaTime) override;
	
private:
	int offset_x;
	int offset_y;
	float scrollspeed;
	std::vector<std::string> BGfiles;
};

