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
	class CircleComponent* mCircle;		//衝突チェックのためのアクセスポインタ。他のオブジェクトから参照するため。

};

