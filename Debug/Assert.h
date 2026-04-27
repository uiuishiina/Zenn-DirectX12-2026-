#pragma once
// Assert.h

#include<string>

// アサートマクロ
#if _DEBUG
#define ASSERT(var) Assert::Assert::handle_assert_failure(Assert::AssertValue(var, #var))
#else
#define ASSERT(var) ((void)0)
#endif // _DEBUG

namespace Assert {
	
	// チェック値の種類を表す列挙型
	enum class Check_Value_Type {
		integer,
		floating_point,
		double_precision,
		boolean,
		long_integer,
		pointer,
		hresult,
	};

	// HRESULT型のエイリアス...Windows APIで使用されるエラーコードを表す型
	using HResult = long;

	// チェック値を格納する構造体
	struct AssertValue {
		Check_Value_Type type;
		//	値を格納するための共用体...異なる型の値を同じメモリ領域に格納できるようにするための構造体
		//	テンプレート使用でもよかったが、今回は共用体を使用して実装...テンプレートを使用する際は,HRESULT型の特殊な処理が必要になるため注意
		union {
			int intValue;		// 整数値
			float floatValue;	// 浮動小数点値
			bool boolValue;		// ブール値
			void* pointerValue;	// ポインタ値
			HResult hresultValue;	// HRESULT値
		}value;

		std::string value_name;	// 値の名前

		// コンストラクタ
		AssertValue(int val,std::string name)		: type(Check_Value_Type::integer), value_name(name)				{ value.intValue = val; }
		AssertValue(float val,std::string name)		: type(Check_Value_Type::floating_point), value_name(name)		{ value.floatValue = val; }
		AssertValue(bool val,std::string name)		: type(Check_Value_Type::boolean), value_name(name)				{ value.boolValue = val; }
		AssertValue(void* val,std::string name)		: type(Check_Value_Type::pointer), value_name(name)				{ value.pointerValue = val; }
		AssertValue(HResult val,std::string name)	: type(Check_Value_Type::hresult), value_name(name)				{ value.hresultValue = val; }
	};


	// アサートクラス
	class Assert final
	{
		static bool is_valid(const AssertValue& value);
		//@brief	アサート失敗時の処理関数
		//@param	value チェック対象の値
		static void is_error(const AssertValue& value);
	public:
		Assert() = default;
		~Assert() = default;

		// コピー禁止,ムーブ禁止
		Assert(const Assert&) = delete;
		Assert& operator=(const Assert&) = delete;
		Assert(const Assert&&) = delete;
		Assert&& operator=(const Assert&&) = delete;

		//@brief	アサート失敗時の処理関数
		//@param	value チェック対象の値
		static void handle_assert_failure(const AssertValue& value);
	};
}