#pragma once
//	ShaderCompiler.h

#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

//	シェーダーコンパイラークラス
class ShaderCompiler final
{
	ComPtr<ID3DBlob> shader_blob_;	//	シェーダーバイトコード
public:
	//	コンストラクタとデストラクタ
	ShaderCompiler() = default;
	~ShaderCompiler() = default;
	//	コピー禁止,ムーブ禁止
	ShaderCompiler(const ShaderCompiler&) = delete;
	ShaderCompiler& operator=(const ShaderCompiler&) = delete;
	ShaderCompiler(const ShaderCompiler&&) = delete;
	ShaderCompiler&& operator=(const ShaderCompiler&&) = delete;

	//@brief	HLSLシェーダーのコンパイル
	//@param	filename			HLSLシェーダーファイルのパス
	//@param	entry_point_name	HLSLシェーダーのエントリーポイント名
	//@param	target_profile		HLSLシェーダーのターゲットプロファイル
	//@return	コンパイルの成否
	[[nodiscard]] bool compile_shader(const wchar_t* filename, const char* entry_point_name, const char* target_profile);

	//@brief	シェーダーバイトコードの取得
	//@return	シェーダーバイトコード
	[[nodiscard]] ID3DBlob* get_shader_blob() const noexcept;
};