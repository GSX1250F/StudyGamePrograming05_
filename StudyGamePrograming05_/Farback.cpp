#include "Farback.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Actor.h"


Farback::Farback(Game* game) : Actor(game),scrollspeed(-10.0f)
{
	// ‚P‚Â‚ß‚Ì”wŒi
	Actor* bg1 = new Actor(game);
	SpriteComponent* sc1 = new SpriteComponent(bg1 , 10);
	sc1->SetTexture(game->GetTexture("Assets/Farback01.png"));
	Farbacks.emplace_back(bg1);
	offset = sc1->GetTexWidth();

	// ‚Q‚Â‚ß‚Ì”wŒi
	Actor* bg2 = new Actor(game);
	SpriteComponent* sc2 = new SpriteComponent(bg2, 10);
	sc2->SetTexture(game->GetTexture("Assets/Farback02.png"));
	Farbacks.emplace_back(bg2);

	for (int i = 0; i < Farbacks.size(); i++)
	{
		Farbacks[i].SetPosition(Vector2(0.0f + i * offset , 0.0f));
		Farbacks[i].SetVelocity(Vector2(-scrollspeed, 0.0f));
	}

}

void Farback::UpdateActor(float deltaTime)
{
	// ”wŒi‚Ìƒ‰ƒbƒsƒ“ƒOˆ—
	for (auto i:Farbacks)
	{

	}
}
