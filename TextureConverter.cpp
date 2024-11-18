#include "TextureConverter.h"

// �ȗ�
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	// �e�N�X�`���t�@�C���̓ǂݍ���
	LoadWICTextureFromFile(filePath);
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	// �t�@�C���p�X�����C�h������ɕϊ�����
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

	// WIC�e�N�X�`���̃��[�h
	HRESULT hr = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	// �����m�F
	assert(SUCCEEDED(hr));
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	// �ꎞ�ϐ��Q
	size_t pos1{};
	std::wstring exceptExt{};

	// ��؂蕶�� . ���łĂ����ԍŌ�̕�������������
	pos1 = filePath.rfind('.');
	// �����q�b�g��
	if (pos1 != std::wstring::npos) {
		// ��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		// ��؂蕶���̑O�܂ł𔲂��o��
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}

	// ��؂蕶�� \\ ���łĂ����ԍŌ�̕�������������
	pos1 = filePath.rfind('\\');
	// �����q�b�g��
	if (pos1 != std::wstring::npos) {
		// ��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		// ��؂蕶���̑O�܂ł𔲂��o��
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	// �������擾
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	// ���C�h������𐶐�
	std::wstring ws;
	ws.resize(filePathBufferSize);

	// �ϊ�
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &ws[0], filePathBufferSize);

	// �Ԋ҂���
	return ws;
}
