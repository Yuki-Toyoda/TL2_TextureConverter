#include "TextureConverter.h"

// 省略
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	// テクスチャファイルの読み込み
	LoadWICTextureFromFile(filePath);
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	// ファイルパスをワイド文字列に変換する
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

	// WICテクスチャのロード
	HRESULT hr = LoadFromWICFile(wFilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	// 成功確認
	assert(SUCCEEDED(hr));
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	// 一時変数群
	size_t pos1{};
	std::wstring exceptExt{};

	// 区切り文字 . がでてくる一番最後の部分を検索する
	pos1 = filePath.rfind('.');
	// 検索ヒット時
	if (pos1 != std::wstring::npos) {
		// 区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		// 区切り文字の前までを抜き出す
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}

	// 区切り文字 \\ がでてくる一番最後の部分を検索する
	pos1 = filePath.rfind('\\');
	// 検索ヒット時
	if (pos1 != std::wstring::npos) {
		// 区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		// 区切り文字の前までを抜き出す
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	// 文字数取得
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	// ワイド文字列を生成
	std::wstring ws;
	ws.resize(filePathBufferSize);

	// 変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &ws[0], filePathBufferSize);

	// 返還する
	return ws;
}
