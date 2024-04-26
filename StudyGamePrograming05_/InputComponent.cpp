#include "InputComponent.h"
#include "Actor.h"


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
	//MoveComponent‚Ì‚½‚ß‚ÌŒvZ
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
		angularSpeed -= mMaxAngularSpeed;		//Šp‘¬“x‚Ì{•ûŒü‚ÍCCW
	}
	else if (keyState[mCounterClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;		//Šp‘¬“x‚Ì{•ûŒü‚ÍCCW
	}
	SetAngularSpeed(angularSpeed);
	*/
	
	//ŒÃ“T•¨—Šw‚ÅMoveComponent‚Ì‚½‚ß‚ÌŒvZ
	//MoveComponent‚É‚Í‘Oi‚©‰ñ“]•ûŒü‚Ì—Í‚ÌÅ‘å’l‚¾‚¯‚ğ“n‚·
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
		rotforce -= mMaxRotForce;		//Šp“x‚Ì{•ûŒü‚ÍCCW
	}
	else if (keyState[mCounterClockwiseKey])
	{
		rotforce += mMaxRotForce;		//Šp“x‚Ì{•ûŒü‚ÍCCW
	}
	SetRotForce(rotforce);

}

