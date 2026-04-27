// Log.cpp
#include"Log.h"
#include<Windows.h>

#define WIN32_LEAN_AND_MEAN	//	Windowsヘッダの軽量化

void Log::Log::output(const LogMessage& message) {
	std::string logText;
	// ログレベルに応じたプレフィックスを追加
	switch (message.level) {
	case LogLevel::None:
		logText = message.message;
		break;
	case LogLevel::Info:
		logText = "[INFO] " + message.message;
		break;
	case LogLevel::Error:
		logText = "[ERROR] " + message.message;
		break;
	}
	// ログをコンソールに出力
	OutputDebugStringA(logText.c_str());
	line_break();
}

void Log::Log::line_break() {
	OutputDebugStringA("\n");
}

std::string Log::Log::HRESULT_to_string(long hresult) {
	char* msgBuf = nullptr;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		hresult,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&msgBuf,
		0,
		NULL
	);
	std::string result = msgBuf ? std::string(msgBuf) : "Unknown error";
	if (msgBuf) {
		LocalFree(msgBuf);
	}
	return result;
}