#pragma once
// Log.h

#include<string>

#if _DEBUG
#define LOG_NONE(msg)	Log::Log::output(Log::LogMessage(Log::LogLevel::None, msg))
#define LOG_INFO(msg)	Log::Log::output(Log::LogMessage(Log::LogLevel::Info, msg))
#define LOG_ERROR(msg)	Log::Log::output(Log::LogMessage(Log::LogLevel::Error, msg))
#define LOG_VARIABLE(var) Log::Log::output(Log::LogMessage(Log::LogLevel::Info, #var " = " + std::to_string(var)))
#define LOG_HRESULT(hr) Log::Log::output(Log::LogMessage(Log::LogLevel::Error, std::to_string(hr) + " : " + Log::Log::HRESULT_to_string(hr)))
#else
#define LOG_NONE(msg) ((void)0)
#define LOG_INFO(msg) ((void)0)
#define LOG_ERROR(msg) ((void)0)
#define LOG_VARIABLE(var) ((void)0)
#define LOG_HRESULT(hr) ((void)0)
#endif // _DEBUG

namespace Log {
	// ログレベル列挙型
	enum class LogLevel {
		None,
		Info,
		Error,
	};

	// ログメッセージ構造体
	struct LogMessage {
		LogLevel level;
		std::string message;

		LogMessage(LogLevel lvl, std::string_view msg) : level(lvl), message(msg) {}
	};

	// ログ出力クラス
	class Log final
	{
	public:
		Log() = default;
		~Log() = default;
		// コピー禁止,ムーブ禁止
		Log(const Log&) = delete;
		Log& operator=(const Log&) = delete;
		Log(const Log&&) = delete;
		Log&& operator=(const Log&&) = delete;

		//@brief	ログ出力関数
		//@param	message ログメッセージ構造体
		static void output(const LogMessage& message);

		//@brief	ログに改行を追加する関数
		static void line_break();

		//@brief	HRESULTコードを文字列に変換する関数
		//@param	hresult HRESULTコード
		//@return	HRESULTコードに対応するエラーメッセージ文字列
		static std::string HRESULT_to_string(long hresult);
	};
}