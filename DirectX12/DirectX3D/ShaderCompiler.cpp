//	ShaderCompiler.cpp

#include"ShaderCompiler.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"
#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

[[nodiscard]] bool ShaderCompiler::compile_shader(const wchar_t* filename, const char* entry_point_name, const char* target_profile) {
	UINT compile_flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
	compile_flags |= D3DCOMPILE_DEBUG;
#endif
	ComPtr<ID3DBlob> error_blob;
	const auto hr = D3DCompileFromFile(filename, nullptr, nullptr, entry_point_name, target_profile, compile_flags, 0, &shader_blob_, &error_blob);
	if (FAILED(hr)) {
		if (error_blob) {
			LOG_ERROR(static_cast<const char*>(error_blob.Get()->GetBufferPointer()));
		}
		LOG_HRESULT(hr);
		return false;
	}
	return true;
}


[[nodiscard]] ID3DBlob* ShaderCompiler::get_shader_blob() const noexcept {
	ASSERT(shader_blob_ != nullptr);
	return shader_blob_.Get();
}