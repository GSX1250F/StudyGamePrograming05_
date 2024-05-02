#pragma once
#include "SpriteComponent.h"
#include "Texture.h"
#include <vector>
#include "Math.h"
class BGSpriteComponent : public SpriteComponent
{
public:
	// 描画順序の初期値は下げる(だからこそ背景となる)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	// 背景用のテクスチャを設定する
	void SetBGTextures(const std::vector<Texture*>& textures);

private:
	// 個々の背景画像とオフセットをカプセル化する構造体
	struct BGTexture
	{
		Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
};