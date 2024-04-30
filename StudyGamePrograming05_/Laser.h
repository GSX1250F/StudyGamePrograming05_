#pragma once
#include "Actor.h"

class Laser : public Actor
{
public:
	Laser(Game* game);

	void UpdateActor(float deltaTime) override;

	class CircleComponent* GetCircle() { return mCircle; }

protected:

private:
	float mDeathTime;
	class CircleComponent* mCircle;		//�Փ˃`�F�b�N�̂��߂̃A�N�Z�X�|�C���^�B���̃I�u�W�F�N�g����Q�Ƃ��邽�߁B
};

