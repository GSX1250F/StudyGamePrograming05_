#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner) : Component(owner)
{
	//���a��Actor�̔��a�ŏ�����
	SetRadius(mOwner->GetRadius());		//Actor�̔��a=scale * radius
	//Actor�̊������[�����g��ݒ�B��l�̉~�Ƃ���B(I=1/2*mR^2)
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
	// �Q��CircleComponent�̒��S�ԋ������v�Z
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// �Q��CircleComponent�̔��a�̘a�̂Q����v�Z 
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
