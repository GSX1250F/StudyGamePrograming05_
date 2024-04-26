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
	class CircleComponent* mCircle;		//衝突チェックのためのアクセスポインタ。他のオブジェクトから参照するため。
	Vector2 crashPos;		//衝突したときの位置
	float crashRot;		//衝突したときの向き
	bool crash;				//衝突検知
	float crashTime;		//衝突演出時間
	float deactiveTime;		//衝突演出後、リセットされるまでスプライトを消す時間

	class AnimSpriteComponent* mAnimComponent;

};

