#include "InputComponent.h"
#include "Actor.h"

//OpenGL�p�̍��W�n�ɏC��

InputComponent::InputComponent(Actor* owner, int updateOrder) 
	: MoveComponent(owner)
	, mForwardKey(0)
	, mBackwardKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	//MoveComponent�̂��߂̌v�Z
	/*
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	else if (keyState[mBackwardKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;		//�p���x�́{������CCW
	}
	else if (keyState[mCounterClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;		//�p���x�́{������CCW
	}
	SetAngularSpeed(angularSpeed);
	*/
	
	//�ÓT�����w��MoveComponent�̂��߂̌v�Z
	//MoveComponent�ɂ͑O�i����]�����̗͂̍ő�l������n��
	float forwardforce = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardforce += mMaxForwardForce;
	}
	else if (keyState[mBackwardKey])
	{
		forwardforce -= mMaxForwardForce;
	}
	SetMoveForce(forwardforce * mOwner->GetForward());
	
	float rotforce = 0.0f;
	if (keyState[mClockwiseKey])
	{
		rotforce -= mMaxRotForce;		//�p�x�́{������CCW
	}
	else if (keyState[mCounterClockwiseKey])
	{
		rotforce += mMaxRotForce;		//�p�x�́{������CCW
	}
	SetRotForce(rotforce);

}

