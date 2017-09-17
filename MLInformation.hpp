#pragma once
namespace ML {
	/**@brief ML APIについての情報格納場所*/
	class Information :public Utility::Singleton<Information> {
		friend class Utility::Singleton<Information>;
	private:
		/**@brief APIの名前の定数*/
		const std::string apiName = "ML API";
		/**@brief APIのメインバージョン*/
		const int mainVersion = 0;
		/**@brief APIのサブバージョン*/
		const int subVersion = 1;
		/**@brief 現在のAPIの状態を表す*/
		std::string type = "α";
	private:
		/**@brief コンストラクタ*/
		Information();
		/**@brief デストラクタ*/
		~Information();
	public:
		/**
		*@brief APIの名前を返します
		*@return API名
		*/
		const std::string& GetAPIName();
		/**
		*@brief APIのバージョンを返します
		*@return APIのバージョン
		*/
		std::string GetAPIVersion();
		/**
		*@brief APIのコメントを返します
		*@return APIのコメント
		*/
		const std::string& GetAPIComment();
		/**
		*@brief APIのメインバージョンを返します
		*@return APIメインバージョン
		*/
		const int GetAPIMainVersion();
		/**
		*@brief APIのサブバージョンを返します
		*@return APIサブバージョン
		*/
		const int GetAPISubVersion();
		/**
		*@brief APIの状態を返します
		*@return APIの状態(β等)
		*/
		const std::string& GetType();
	};
}
#include "MLInformation.inl"