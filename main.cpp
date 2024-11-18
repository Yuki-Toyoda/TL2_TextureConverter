#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <d3d12.h>
#include "TextureConverter.h"

/// <summary>
/// コマンドライン引数列挙子
/// </summary>
enum Argument {
	kApplicationPath,	// アプリケーションまでのパス
	kFilePath,			// テクスチャのパス
	NumArgument			// カウント用
};

int main(int argc, char* argv[]) {
	// 異常な数の場合停止
	assert(argc >= NumArgument);
	
	// COMライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	// 初期化出来なかった場合停止
	assert(SUCCEEDED(hr));

	// コンバーター生成
	TextureConverter converter;
	// 変換を開始する
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	// COMライブラリの終了
	CoUninitialize();

	// ウィンドウが勝手に閉じるのを防ぐ
	system("pause");
	// 終了
	return 0;
}