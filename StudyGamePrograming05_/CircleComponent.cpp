#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner) : Component(owner)
{
	//”¼Œa‚ÍActor‚Ì”¼Œa‚Å‰Šú‰»
	SetRadius(mOwner->GetRadius());		//Actor‚Ì”¼Œa=scale * radius
	//Actor‚ÌŠµ«ƒ‚[ƒƒ“ƒg‚ğİ’èBˆê—l‚Ì‰~”Â‚Æ‚·‚éB(I=1/2*mR^2)
	mOwner->SetImoment(mOwner->GetScale()*mOwner->GetScale()*mRadius*mRadius/2);
}

float CircleComponent::GetRadius() const
{
	return mRadius;
}

const Vector2& CircleComponent::GetCenter() const
{
	return  mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// ‚Q‚Â‚ÌCircleComponent‚Ì’†SŠÔ‹——£‚ğŒvZ
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float dist = diff.Length();

	// ‚Q‚Â‚ÌCircleComponent‚Ì”¼Œa‚Ì˜a‚ğŒvZ 
	float sumRadius = a.GetRadius() + b.GetRadius();

	// ’†SŠÔ‹——£ <= ”¼Œa‚Ì˜a ‚Ì‚Æ‚«AÕ“Ë‚µ‚½‚Æ”»’è
	if (dist <= sumRadius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
