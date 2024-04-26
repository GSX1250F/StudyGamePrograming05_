#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(Game* game);
	
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	void Init();

	class CircleComponent* GetCircle() { return mCircle; }


protected:


private:
	float mLaserCooldown;
	class CircleComponent* mCircle;		//�Փ˃`�F�b�N�̂��߂̃A�N�Z�X�|�C���^�B���̃I�u�W�F�N�g����Q�Ƃ��邽�߁B
	Vector2 crashPos;		//�Փ˂����Ƃ��̈ʒu
	float crashRot;		//�Փ˂����Ƃ��̌���
	bool crash;				//�Փˌ��m
	float crashTime;		//�Փˉ��o����
	float deactiveTime;		//�Փˉ��o��A���Z�b�g�����܂ŃX�v���C�g����������

	class AnimSpriteComponent* mAnimComponent;

};

