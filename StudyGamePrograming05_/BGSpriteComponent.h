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
	/// �X�V�ƕ`��͐e����I�[�o�[���C�h����
	void Update(float deltaTime) override;
	void Draw(class Shader* shader) override;
	// �w�i�p�̃e�N�X�`����ݒ肷��
	void SetBGTextures(const std::vector<Texture*>& textures);
	// ��ʃT�C�Y�ƃX�N���[�����x�̐ݒ�/�擾
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	// �X�̔w�i�摜�ƃI�t�Z�b�g���J�v�Z��������\����
	struct BGTexture
	{
		Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};