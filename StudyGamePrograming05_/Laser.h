#pragma once
#include "Actor.h"

class Laser : public Actor
{
public:
	Laser(Game* game);

	void UpdateActor(float deltaTime) override;

private:
	float mDeathTime;
	float mLaserSpeed;
	class CircleComponent* mCircle;		//衝突チェックのためのアクセスポインタ。他のオブジェクトから参照するため。
};

