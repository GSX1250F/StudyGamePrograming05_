#include "Farback.h"
#include "Game.h"
#include "SpriteComponent.h"

Farback::Farback(Game* game , int id) : Actor(game),scrollspeed(-10.0f),offset_x(0.0f),offset_y(0.0f)
{
	BGfiles.emplace_back("Assets/Farback01.png");
	BGfiles.emplace_back("Assets/Farback02.png");
	
	//�X�v���C�g�R���|�[�l���g�쐬�A�e�N�X�`���ݒ�
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture(BGfiles[id]));
}

void Farback::UpdateActor(float deltaTime)
{
	// �w�i�̃��b�s���O����
	if(GetPosition().x < offset_x * (-0.5f) ||
	   GetPosition().x > offset_x * 0.5f)
	{
		 SetPosition(Vector2(-GetPosition().x, GetPosition().y));
	}
	if (GetPosition().y < offset_y * (-0.5f) ||
		GetPosition().y > offset_y * 0.5f)
	{
		 SetPosition(Vector2(GetPosition().x, -GetPosition().y));
	}
}