#include "TextureConverter.h"

// �ȗ�
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	// �e�N�X�`���t�@�C���̓ǂݍ���
	LoadWICTextureFromFile(filePath);

	// DDS�t�@�C���Ƃ��ď����o��
	SaveDDSTextureToFile();
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	// �t�@�C���p�X�����C�h������ɕϊ�����
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

	// WIC�e�N�X�`���̃��[�h
	HRESULT hr = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	// �����m�F
	assert(SUCCEEDED(hr));

	// �ǂݍ��񂾃e�N�X�`���̃t�@�C���p�X�𕪉�����
	SeparateFilePath(wFilePath);
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
		// ��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�����
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		// ��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		// �������^�[��
		return;
	}
	// ��؂蕶�� / ���łĂ����ԍŌ�̕�������������
	pos1 = filePath.rfind('/');
	// �����q�b�g��
	if (pos1 != std::wstring::npos) {
		// ��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�����
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		// ��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		// �������^�[��
		return;
	}
	
	// ��؂蕶�������݂��Ȃ��ꍇ�A�t�@�C���݂̂Ƃ��Ĉ���
	directoryPath_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFile()
{
	// �ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata_.format = MakeSRGB(metadata_.format);

	// ���ʊm�F�p
	HRESULT result = S_FALSE;

	// �o�̓t�@�C������ݒ�
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	// DDS�t�@�C�������o��
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));
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
