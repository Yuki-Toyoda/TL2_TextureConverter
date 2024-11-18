#pragma once
#include <string>
#include <Windows.h>
#include "Externals/DirectXTex/DirectXTex.h"

/// <summary>
/// �e�N�X�`���̌`����ύX����R���o�[�^�[
/// </summary>
class TextureConverter
{
public: // �R���X�g���N�^��

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TextureConverter() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TextureConverter() = default;

public: // �����o�֐�

	/// <summary>
	/// WIC�e�N�X�`����DDS�e�N�X�`���ɕϊ�����
	/// </summary>
	/// <param name="filePath">�e�N�X�`���܂ł̃t�@�C���p�X</param>
	void ConvertTextureWICToDDS(const std::string& filePath);

private: // �@�\�֐��Q

	/// <summary>
	/// WIC�e�N�X�`���t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="filePath">�e�N�X�`���܂ł̃t�@�C���p�X</param>
	void LoadWICTextureFromFile(const std::string& filePath);

	/// <summary>
	/// �n���ꂽ�t�@�C���p�X���t�@�C���p�X / �t�@�C�����ɕ�������
	/// </summary>
	/// <param name="filePath">�������s���t�@�C���p�X</param>
	void SeparateFilePath(const std::wstring& filePath);

private: // �ÓI�@�\�֐��Q

	/// <summary>
	/// �}���`�o�C�g����������C�h������ɕϊ�����
	/// </summary>
	/// <param name="mString">�ύX���镶����</param>
	/// <returns></returns>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

private: // �����o�ϐ�

	// �e�N�X�`���̃��^�f�[�^
	DirectX::TexMetadata metadata_{};
	// �C���[�W
	DirectX::ScratchImage scratchImage_{};

	// �f�B���N�g���p�X
	std::wstring directoryPath_{};
	// �t�@�C����
	std::wstring fileName_{};
	// �t�@�C���g���q
	std::wstring fileExt_{};

};

