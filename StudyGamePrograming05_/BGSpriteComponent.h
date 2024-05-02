#pragma once
#include "SpriteComponent.h"
#include "Texture.h"
#include <vector>
#include "Math.h"
class BGSpriteComponent : public SpriteComponent
{
public:
	// �`�揇���̏����l�͉�����(�����炱���w�i�ƂȂ�)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	// �w�i�p�̃e�N�X�`����ݒ肷��
	void SetBGTextures(const std::vector<Texture*>& textures);

private:
	// �X�̔w�i�摜�ƃI�t�Z�b�g���J�v�Z��������\����
	struct BGTexture
	{
		Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
};