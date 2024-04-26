#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	//�R���X�g���N�^�BUpdate Order�͑��߁B
	MoveComponent(class Actor* owner , int updateOrder = 10);
	~MoveComponent();

	//Update���I�[�o�[���C�h
	void Update(float deltatime) override;

	// �ÓT�����������B�d�S�ɂ�����͂Ɖ�]�ɂ�����͂̃Z�b�^�[��p��
	void SetMoveForce(Vector2 forceVector) { mMoveForce = forceVector; }
	void SetRotForce(float force) { mRotForce = force; }
	void SetMoveResist(float resist) { mMoveResist = resist; }
	void SetRotResist(float resist) { mRotResist = resist; }

protected:


private:
	// �d�S�ɂ������
	Vector2 mMoveForce;
	// ��]�����̗�F�@ �g���N=RotForce * Radius = Imoment * RotAccel
	float mRotForce;
	// �d�S�����x
	Vector2 mMoveAccel;
	// ��]�����x
	float mRotAccel;
	
	// �d�S���x��R��(%)
	float mMoveResist;
	// ��]���x��R��(%)
	float mRotResist;


};

