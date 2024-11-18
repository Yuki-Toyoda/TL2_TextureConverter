#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <d3d12.h>
#include "TextureConverter.h"

/// <summary>
/// �R�}���h���C�������񋓎q
/// </summary>
enum Argument {
	kApplicationPath,	// �A�v���P�[�V�����܂ł̃p�X
	kFilePath,			// �e�N�X�`���̃p�X
	NumArgument			// �J�E���g�p
};

int main(int argc, char* argv[]) {
	// �ُ�Ȑ��̏ꍇ��~
	assert(argc >= NumArgument);
	
	// COM���C�u�����̏�����
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	// �������o���Ȃ������ꍇ��~
	assert(SUCCEEDED(hr));

	// �R���o�[�^�[����
	TextureConverter converter;
	// �ϊ����J�n����
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	// COM���C�u�����̏I��
	CoUninitialize();

	// �E�B���h�E������ɕ���̂�h��
	system("pause");
	// �I��
	return 0;
}