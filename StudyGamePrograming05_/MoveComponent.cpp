#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner), 
	mMoveForce(Vector2::Zero),
	mMoveAccel(Vector2::Zero),
	mRotForce(0.0f),
	mRotAccel(0.0f),
	mMoveResist(0.0f),
	mRotResist(0.0f)
{
	
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	// ActorÇÃèdêSë¨ìxÇ∆âÒì]ë¨ìxÇçXêV
	// ActorÇÃà íuÇ∆äpìxÇÕActorÇÃUpdateÇ≈çXêV
	if (mOwner->GetMass() != 0) {
		mMoveAccel = mMoveForce * (1.0f / mOwner->GetMass());	//èdêSâ¡ë¨ìxÇÃåvéZÅ@F=ma  a=F*(1/m)
		//íÔçRóÕ = ë¨Ç≥*íÔçRåWêî    å∏ë¨ = -ë¨Ç≥*íÔçRåWêî/éøó 
		Vector2 movedecel = mOwner->GetVelocity() * mMoveResist *0.01f * (1 / mOwner->GetMass());
		mMoveAccel -= movedecel;
	}
	else { mMoveAccel = Vector2::Zero; }
	if (mOwner->GetImoment() != 0 && mOwner->GetRadius() != 0) {
		mRotAccel = mRotForce * mOwner->GetRadius() / mOwner->GetImoment();	//âÒì]â¡ë¨ìxÇÃåvéZ Fr=Ia  a=Fr/I
		//íÔçRóÕ = ë¨Ç≥*íÔçRåWêî    å∏ë¨ = -ë¨Ç≥*íÔçRåWêî*îºåa/äµê´ÉÇÅ[ÉÅÉìÉg
		float rotdecel = mOwner->GetRotSpeed() * mOwner->GetRadius() * mRotResist / mOwner->GetImoment();
		mRotAccel -= rotdecel;
	}
	else { mRotAccel = 0; }
	mOwner->SetVelocity(mOwner->GetVelocity() + mMoveAccel * deltatime);	//v = vo + at
	mOwner->SetRotSpeed(mOwner->GetRotSpeed() + mRotAccel * deltatime);		//É÷ = É÷o + É÷t
}
