#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Random.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Texture.h"

//OpenGL用に、画面中央が(0,0)、上方向に+,右方向に+の座標系に修正

Ship::Ship(Game* game) : Actor(game) , mLaserCooldown(0.0f)
{
	Init();
	/*
	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));
	*/

	// アニメーションのスプライトコンポーネントを作成
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
		game->GetTexture("Assets/Ship05.png")
	};
	asc->SetAnimTextures(anims,1,1,true);
	mAnimComponent = asc;


	//InputComponent作成
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_UP);
	ic->SetBackwardKey(SDL_SCANCODE_DOWN);
	ic->SetClockwiseKey(SDL_SCANCODE_RIGHT);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_LEFT);
	ic->SetMaxForwardForce(300.0f);
	ic->SetMaxRotForce(150.0f);
	ic->SetMoveResist(30.0f);
	ic->SetRotResist(30.0f);

	//CircleComponent作成
	mCircle = new CircleComponent(this);
	
}

void Ship::Init()
{
	
	SetPosition(Vector2(0.0f, 0.0f));
	//ランダムな向きで初期化
	float rot = Random::GetFloatRange(0.0f, Math::TwoPi);
	SetRotation(rot);
	SetScale(1.0f);
	SetMass(1.0f);

	crash = false;
	crashTime = 1.5f;
	crashPos.x = 0.0f;
	crashPos.y = 0.0f;
	deactiveTime = 1.5f;
	SetState(EActive);
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (crash == false) 
	{
		if (keyState[SDL_SCANCODE_LEFT])
		{
			mAnimComponent->SetAnimNum(2, 2, false); 
		}
		else if (keyState[SDL_SCANCODE_RIGHT])
		{
			mAnimComponent->SetAnimNum(3, 3, false); 
		}
		else if (keyState[SDL_SCANCODE_UP])
		{
			mAnimComponent->SetAnimNum(4, 4, false); 
		}
		else if (keyState[SDL_SCANCODE_DOWN])
		{
			mAnimComponent->SetAnimNum(5, 5, false); 
		}
		else if (mAnimComponent->mIsAnimating == false)
		{
			// アニメーション中が終わっていたら元のループに戻る。
			mAnimComponent->SetAnimNum(1, 1, true);
		}


		if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
		{
			// レーザーオブジェクトを作成、位置と回転角を宇宙船とあわせる。
			Laser* laser = new Laser(GetGame());
			laser->SetPosition(GetPosition() + 35.0f * GetScale() * Vector2(Math::Cos(GetRotation()), Math::Sin(GetRotation())));
			laser->SetRotation(GetRotation());
			laser->SetVelocity(1000.0f * Vector2(Math::Cos(GetRotation()), Math::Sin(GetRotation())));

			// レーザー冷却期間リセット
			mLaserCooldown = 0.5f;
		}
	}
	
}

void Ship::UpdateActor(float deltaTime)
{
	if (crash == false)
	{
		//画面外にでたら反対の位置に移動（ラッピング処理）
		if (GetPosition().x < GetGame()->mWindowWidth * (-0.5f) - 1.0f * GetRadius() ||
			GetPosition().x > GetGame()->mWindowWidth * 0.5f + 1.0f * GetRadius())
		{
			SetPosition(Vector2(-1.0f * GetPosition().x, GetPosition().y));
		}
		if (GetPosition().y < GetGame()->mWindowHeight * (-0.5f) - 1 * GetRadius() ||
			GetPosition().y > GetGame()->mWindowHeight * 0.5f + 1 * GetRadius())
		{
			SetPosition(Vector2(GetPosition().x, -1.0f * GetPosition().y));
		}

		mLaserCooldown -= deltaTime;	//レーザーを次に撃てるまでの時間

		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//小惑星と衝突したとき
				crashPos = GetPosition();
				crashRot = GetRotation();

				//ゲーム自体を終了する場合
				//GetGame()->SetRunning(false);

				crash = true;
				break;
			}
		}
	}
	else
	{
		if (crashTime >= 0.0f && deactiveTime >= 0.0f)
		{
			SetPosition(crashPos);		// MoveComponentが更新されても衝突したときの位置に置きなおし
			crashRot -= 3.0f * Math::TwoPi * deltaTime;
			SetRotation(crashRot);		// MoveComponentが更新されても衝突してからの回転角度に置きなおし
			crashTime -= deltaTime;
		}
		else if (crashTime < 0.0f && deactiveTime >= 0.0f)
		{
			SetState(EPaused);
			deactiveTime -= deltaTime;
			
		}
		else
		{
			//初期位置へリセット
			Init();
		}
	}


}



