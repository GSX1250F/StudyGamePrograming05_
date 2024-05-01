#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(EActive),
	mPosition(Vector2::Zero),
	mVelocity(Vector2::Zero),
	mScale(1.0f),
	mRotation(0.0f),
	mRotSpeed(0.0f),
	mMass(1.0f),
	mRadius(0.0f),
	mImoment(0.0f),
	mGame(game),
	mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	// ~ComponentではRemoveActorが呼び出されるので、別の種類のループを使う
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState != EDead)	// EPausedのときも更新するよう修正。
	{
		// ワールド変換
		ComputeWorldTransform();

		// 位置情報を更新
 		SetPosition(GetPosition() + mVelocity * deltaTime);
		SetRotation(GetRotation() + mRotSpeed * deltaTime);
		
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		// ワールド変換（再変換）
		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

//新しく追加されたインプット用関数
void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

//機能追加するときオーバーライドするインプット用関数
void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// まずスケーリング、次に回転、最後に平行移動
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));

		// ワールド変換の更新をコンポーネントに通知する
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}


void Actor::AddComponent(Component* component)
{
	// ソート済みの配列で挿入点を見つける
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// イテレータの位置の前に要素を挿入する
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}