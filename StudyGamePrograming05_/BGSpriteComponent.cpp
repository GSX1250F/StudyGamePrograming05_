#include "BGSpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{	
	for (auto& bg : mBGTextures)
	{
		// xのオフセット更新
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// もし画面から完全に出たら、オフセットを
		// 最後の背景テクスチャの右にリセットする
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(Shader* shader)
{
	for (auto& bg : mBGTextures)
	{
		// テクスチャの幅と高さで短径をスケーリング
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mScreenSize.x),
			static_cast<float>(mScreenSize.y),
			1.0f);
		Matrix4 offsetMat = Matrix4::CreateTranslation(
			Vector3(static_cast<int>(mOwner->GetPosition().x - mScreenSize.x / 2 + bg.mOffset.x),
					static_cast<int>(mOwner->GetPosition().y - mScreenSize.y / 2 + bg.mOffset.y),
					0.0f)
		);
		
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();
		
		// ワールド変換の設定
		shader->SetMatrixUniform("uWorldTransform", world);

		bg.mTexture->SetActive();
	
		// 短径を描画
		glDrawElements(
			GL_TRIANGLES,		// 描画するポリゴン／プリミティブの種類
			6,					// インデックスバッファにあるインデックスの数
			GL_UNSIGNED_INT,	// インデックスの型
			nullptr				// 通常はnullptr
			);
	}
}
	

void BGSpriteComponent::SetBGTextures(const std::vector<Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// それぞれのテクスチャは画面幅分のオフセットを持つ
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
