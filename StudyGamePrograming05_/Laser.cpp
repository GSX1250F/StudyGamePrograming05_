#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"	
#include "Game.h"
#include "Asteroid.h"
#include "CircleComponent.h"

Laser::Laser(Game* game) : Actor(game),mDeathTime(2.0f)
{

	//スプライトコンポーネント作成、テクスチャ設定
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));
	
	//初期位置,速度,角度はShipで設定

	//CircleComponent作成
	mCircle = new CircleComponent(this);
}

void Laser::UpdateActor(float deltaTime)
{
	//位置はMoveComponentで更新される。
	//画面外にでるか、DeathTimeが0になったら消去する。
	mDeathTime -= deltaTime;
	if(mDeathTime <= 0.0f ||
	   GetPosition().x < 0.0f ||
	   GetPosition().x > GetGame()->mWindowWidth ||
	   GetPosition().y < 0.0f ||
	   GetPosition().y > GetGame()->mWindowHeight)
	{
		SetState(EDead);
	}
	else
	{
		//小惑星と衝突したとき
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//レーザーも消去するなら次を実行
				SetState(EDead);

				//小惑星を消去
				ast->SetState(EPaused);

				break;
			}
		}
	}



}

