#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	//コンストラクタ。Update Orderは早め。
	MoveComponent(class Actor* owner , int updateOrder = 10);
	~MoveComponent();

	//Updateをオーバーライド
	void Update(float deltatime) override;

	// 古典物理を実装。重心にかかる力と回転にかかる力のセッターを用意
	void SetMoveForce(Vector2 forceVector) { mMoveForce = forceVector; }
	void SetRotForce(float force) { mRotForce = force; }
	void SetMoveResist(float resist) { mMoveResist = resist; }
	void SetRotResist(float resist) { mRotResist = resist; }

protected:


private:
	// 重心にかかる力
	Vector2 mMoveForce;
	// 回転方向の力F　 トルク=RotForce * Radius = Imoment * RotAccel
	float mRotForce;
	// 重心加速度
	Vector2 mMoveAccel;
	// 回転加速度
	float mRotAccel;
	
	// 重心速度抵抗率(%)
	float mMoveResist;
	// 回転速度抵抗率(%)
	float mRotResist;


};

