#pragma once
#ifndef __ML_UTILITY__
#define __ML_UTILITY__
///////////////////////////////////////////////////
//		汎用include
///////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <intsafe.h>
#include <unordered_map>
///////////////////////////////////////////////////
///////////////////////////////////////////////////

#define Interface abstract
namespace ML {
	namespace Error {
#ifdef _DEBUG
		//これは例外発生時に指定された方式で情報を表示する
#define __EXCEPTION_ON__
#else
		//これはログをはくようにする
#define __EXCEPTION_LOG_ON__
#endif
//指定された例外とログファイルを両方はかせる
//#define __STRICT_EXCEPTION_ON__
//これを定義するとExceptionはログファイルも例外も発さない
//一番優先度が高い ほかのコマンドをすべて無視する
//#define __NO_EXCEPTION__
	/**
	*@brief 例外クラス
	*@brief 一応地震で実体を作って使用することも可能
	*@attention このクラスは自分で実体を生成するのではなく、<br>
	*下で定義されているマクロによって生成させる。<br>
	*メッセージを表示するには、CATCH文でこのクラスを捕まえてメンバ関数によって表示
	*@attention ログ出力等の制御は上にあるコメント参照
	*/
		class Exception {
		private:
			/**@brief ソースファイル名*/
			std::string _filename;
			/**@brief 実行された関数名*/
			std::string _functionName;
			/**@brief 例外が出た行*/
			int _executeLine;
			/**@brief 任意のメッセージ*/
			std::string _msg;
		private:
			/**
			*@brief エラーメッセージ構築
			*@return エラー文章
			*/
			std::string CreateMessage()const noexcept;
			/**
			*@brief ログ出力
			*/
			void OutputLog()const noexcept;
		public:
			/**
			*@brief コンストラクタ
			*@param[in] ソースファイル名
			*@param[in] 関数名
			*@param[in] 実行行番号
			*/
			Exception(std::string filename, std::string func_name, int exe_line) noexcept;
			/**
			*@brief コンストラクタ
			*@param[in] ソースファイル名
			*@param[in] 関数名
			*@param[in] 実行行番号
			*@param[in] 任意のメッセージ
			*/
			Exception(std::string filename, std::string func_name, int exe_line, std::string msg) noexcept;
			/**@brief デストラクタ*/
			virtual ~Exception() noexcept = default;
			/**@brief メッセージボックスにより出力*/
			void BoxMessage()const noexcept;
			/**@brief エラー文章を取得*/
			const std::string CreateExceptionMessage()const noexcept;
		};
		//この先マクロ定義
		/**@def ソースファイル名取得*/
#define FILE_NAME __FILE__
	/**@def 関数名取得*/
#define FUNCTION_NAME __func__
	/**@def 実行している行取得*/
#define EXECUTE_LINE __LINE__
	/**@def 変数名取得*/
#define VARIABLE_NAME(variable) # variable
	/**@def 例外クラス実体生成*/
#define STRICT_EXCEPTION_FACTORY(msg) ML::Error::Exception(FILE_NAME,FUNCTION_NAME,EXECUTE_LINE,msg)
	/**@def 例外クラス実体生成*/
#define EXCEPTION_FACTORY STRICT_EXCEPTION_FACTORY("")
	/**@def try*/
#define TRY try
	/**@def throw Exceptionをメッセージ付きで投げる*/
#define STRICT_THROW(msg) throw STRICT_EXCEPTION_FACTORY(msg)
	/**@def throw Exceptionを投げる*/
#define THROW_E STRICT_THROW("");
	/**@def catch*/
#define CATCH catch
	/**@def throw*/
#define THROW throw
	/**@def アライメント*/
#define ALIGN(n) __declspec(align(n))

	}
	namespace Utility {
		//要実験
		class Filer {
		public:
			enum class OpenMode;
			enum class SeekMode;
		private:
			OpenMode mode;
			FILE* fp;
		private:
			std::string ModePurse(OpenMode m);
		public:
			Filer()noexcept;
			~Filer()noexcept;
			bool IsAppendMode()const noexcept;
			bool IsWriteMode()const noexcept;
			bool IsReadMode()const noexcept;
			bool IsBinaryMode()const noexcept;
			bool IsTextMode()const noexcept;
			bool IsOpen()const noexcept;
			OpenMode GetMode()const noexcept;
			__forceinline void Open(std::string filename, OpenMode m);
			__forceinline void Close()noexcept;
			template<typename T> __forceinline size_t Write(T* pointer, size_t count) noexcept;
			template<typename T> __forceinline size_t Read(T* pointer, size_t buffer_size, size_t count) noexcept;
			template <typename ... Args> __forceinline size_t Print(const char *format, Args const & ... args) noexcept;
			template <typename ... Args> __forceinline size_t Scan(const char* pointer, Args const & ... args) noexcept;
			__forceinline bool Seek(int offset, SeekMode mode);
			__forceinline bool Rewind();
		};
		/**
		*@brief リソースマネージャー
		*@param 管理対象の型
		*@param 鍵となる型 デフォルトではstd::string
		*/
		template<typename T, typename Key = std::string>
		class ResourceManager final {
		protected:
			/**
			*@brief リソース管理用連想配列
			*/
			static std::unordered_map<Key, std::shared_ptr<T>>resource;
		public:
			/**@brief コンストラクタ*/
			ResourceManager() noexcept;
			/**@brief デストラクタ*/
			~ResourceManager() noexcept;
			/**
			*@brief ファクトリ関数
			*@brief インスタンスが作られていれば既存のものを、作られていなければ新規で作成して返します。
			*@param <template>インスタンス作成時に入れた型と継承関係のものを管理したい場合に指定、しなければそのままの型
			*@param <template>インスタンス作成時に使用する引数リスト
			*@param[in] 鍵
			*@param[in] インスタンス生成に必要な引数
			*@return インスタンスへのポインタ
			*/
			template<typename U = T, typename... Args>
			static T* Factory(Key key, Args... args)noexcept;
			/**
			*@brief 登録関数
			*@brief ファクトリを使用せず直接インスタンスを預けたいときに使用
			*@param[in] 鍵
			*@param[in] インスタンスへのポインタ
			*/
			static void Register(Key key, std::shared_ptr<T> p)noexcept;
			/**
			*@brief インスタンスが存在するか返す
			*@param[in] 鍵
			*@return 存在しているか否かのbool値
			*/
			static bool IsExist(Key key) noexcept;
			static void Clear() noexcept;
			static T* Get(Key key) noexcept;
		};
		template<typename T>
		class Singleton {
		protected:
			__forceinline Singleton()noexcept;
			__forceinline virtual ~Singleton()noexcept;
		public:
			static T* GetInstance();
		};
	}
}
#include "MLCommon.inl"
#endif
