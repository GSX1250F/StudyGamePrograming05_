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
		// x�̃I�t�Z�b�g�X�V
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// ������ʂ��犮�S�ɏo����A�I�t�Z�b�g��
		// �Ō�̔w�i�e�N�X�`���̉E�Ƀ��Z�b�g����
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
		// �e�N�X�`���̕��ƍ����ŒZ�a���X�P�[�����O
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mScreenSize.x),
			static_cast<float>(mScreenSize.y),
			1.0f);
		// �e�N�X�`���̃I�t�Z�b�g�i���s�ړ��j
		Matrix4 offsetMat = Matrix4::CreateTranslation(
			Vector3(static_cast<int>(mOwner->GetPosition().x - mScreenSize.x / 2 + bg.mOffset.x),
					static_cast<int>(mOwner->GetPosition().y - mScreenSize.y / 2 + bg.mOffset.y),
					0.0f)
		);
		
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();
		
		// ���[���h�ϊ��̐ݒ�
		shader->SetMatrixUniform("uWorldTransform", world);

		bg.mTexture->SetActive();
	
		// �Z�a��`��
		glDrawElements(
			GL_TRIANGLES,		// �`�悷��|���S���^�v���~�e�B�u�̎��
			6,					// �C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
			GL_UNSIGNED_INT,	// �C���f�b�N�X�̌^
			nullptr				// �ʏ��nullptr
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
		// ���ꂼ��̃e�N�X�`���͉�ʕ����̃I�t�Z�b�g������
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
