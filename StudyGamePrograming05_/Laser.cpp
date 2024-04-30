#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"	
#include "Game.h"
#include "Asteroid.h"
#include "CircleComponent.h"

Laser::Laser(Game* game) : Actor(game),mDeathTime(2.0f)
{

	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));
	
	//�����ʒu,���x,�p�x��Ship�Őݒ�

	//CircleComponent�쐬
	mCircle = new CircleComponent(this);
}

void Laser::UpdateActor(float deltaTime)
{
	//DeathTime��0�ɂȂ������������B
	mDeathTime -= deltaTime;
	if(mDeathTime <= 0.0f) 
	{
		SetState(EDead);
	}
	else
	{
		//���f���ƏՓ˂����Ƃ�
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				//���[�U�[����������Ȃ玟�����s
				SetState(EDead);

				//���f��������
				ast->SetState(EPaused);

				break;
			}
		}
	}



}

