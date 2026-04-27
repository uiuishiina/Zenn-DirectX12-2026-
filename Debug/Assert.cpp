// Assert.cpp

#include"Assert.h"
#include"Log.h"
#include<Windows.h>
#include<sstream>

#define WIN32_LEAN_AND_MEAN	//	Windowsヘッダの軽量化


bool Assert::Assert::is_valid(const AssertValue& value) {
	switch (value.type) {
	case Check_Value_Type::integer:
		return value.value.intValue != 0;
	case Check_Value_Type::floating_point:
		return value.value.floatValue != 0.0f;
	case Check_Value_Type::boolean:
		return value.value.boolValue;
	case Check_Value_Type::pointer:
		return value.value.pointerValue != nullptr;
	case Check_Value_Type::hresult:
		return SUCCEEDED(value.value.hresultValue);
	default:
		return false; // 不明な型は無効とみなす
	}
}

void Assert::Assert::is_error(const AssertValue& value) {
	// エラーメッセージの構築...値の名前と値を含むメッセージを作成
	std::ostringstream error_message;
	error_message << "Assertion failed: " + value.value_name + " = ";
	char* msgBuf = nullptr;
	// 値の種類に応じて適切な形式で値を文字列に変換してエラーメッセージに追加
	switch (value.type) {
	case Check_Value_Type::integer:
		error_message << std::to_string(value.value.intValue);
		break;
	case Check_Value_Type::floating_point:
		error_message << std::to_string(value.value.floatValue);
		break;
	case Check_Value_Type::boolean:
		error_message << (value.value.boolValue ? "true" : "false");
		break;
	case Check_Value_Type::pointer:
		error_message << "0x" << std::to_string(reinterpret_cast<std::uintptr_t>(value.value.pointerValue));
		break;
	case Check_Value_Type::hresult:
		error_message << "0x" << std::hex << value.value.hresultValue << " : " << Log::Log::HRESULT_to_string(value.value.hresultValue);
		break;
	default:
		error_message << "Unknown type";
		break;
	}
	// ログにエラーメッセージを出力
	LOG_ERROR(error_message.str());
}

void Assert::Assert::handle_assert_failure(const AssertValue& value) {
	if (Assert::is_valid(value)) {
		return;
	}
	Assert::is_error(value);
	std::abort(); // プログラムを強制終了
}