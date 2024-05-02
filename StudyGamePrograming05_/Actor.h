#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	enum State
	{
		EActive,		//�ғ���
		EPaused,		//�X�V��~��
		EDead			//�폜�Ώ�
	};

	Actor(class Game* game);
	virtual ~Actor();

	// �Q�[������Ăяo�����X�V�֐�(�I�[�o�[���C�h�s��)
	void Update(float deltaTime);
	// �A�N�^�[�����S�R���|�[�l���g���X�V(�I�[�o�[���C�h�s��)
	void UpdateComponents(float deltaTime);
	// �A�N�^�[�Ǝ��̍X�V����(�I�[�o�[���C�h�\)
	virtual void UpdateActor(float deltaTime);
	// �Q�[������Ăяo�����Process Input(�I�[�o�[���C�h�s��)
	void ProcessInput(const uint8_t* keyState);
	// �A�N�^�[�Ǝ��̓��͏���(�I�[�o�[���C�h�\)
	virtual void ActorInput(const uint8_t* keyState);

	// �Q�b�^�[�E�Z�b�^�[
	// �ʒu
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true;}
	// ���x
	const Vector2& GetVelocity() const { return mVelocity; }
	void SetVelocity(const Vector2& vel) { mVelocity = vel; mRecomputeWorldTransform = true;	}
	// �g�嗦�i���ʂ͕ς��Ȃ��B���a�ɉe������j
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true;}
	// ��]
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; mRecomputeWorldTransform = true;}
	// ���a
	float GetRadius() const { return mRadius * mScale; }	//�g�嗦���l��
	void SetRadius(float radius) { mRadius = radius; mRecomputeWorldTransform = true;}
	// ��]���x
	float GetRotSpeed() const { return mRotSpeed; }
	void SetRotSpeed(float rotspeed) { mRotSpeed = rotspeed; mRecomputeWorldTransform = true;}
	// ����
	float GetMass() const { return mMass; }
	void SetMass(float mass) { mMass = mass; mRecomputeWorldTransform = true;}
	// �������[�����g
	float GetImoment() const;

	// ���[���h�ϊ�
	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	// �����̒P�ʃx�N�g��
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }		//�����̒P�ʃx�N�g��

	// ���
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// �A�N�^�[�̏��
	State mState;

	// �ړ�
	Vector2 mPosition;		//��ʏ�̈ʒu
	Vector2 mVelocity;		//���xx,y
	float mScale;			//�g�嗦
	float mRotation;		//��]
	float mRotSpeed;		//��]���x
	float mMass;			//����
	float mRadius;			//���a�i�g�嗦�͖����j
	
	// �ϊ�
	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};
