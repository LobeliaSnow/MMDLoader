#pragma once
namespace ML {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					Information
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//private:
	__forceinline Information::Information() = default;
	__forceinline Information::~Information() = default;
	//public:
	__forceinline const std::string& Information::GetAPIName() { return apiName; }
	__forceinline std::string Information::GetAPIVersion() {
		std::stringstream _stream;
		_stream << mainVersion << "." << subVersion << type;
		return _stream.str();
	}
	__forceinline const std::string& Information::GetAPIComment() {
		static std::string comment = "現状スタティックメッシュ(ボーン無し)のみ対応、ボーンも適宜対応する。\nとりあえずコメントつけるのを急ぐ。\n";
		return comment;
	}
	__forceinline const int Information::GetAPIMainVersion() { return mainVersion; }
	__forceinline const int Information::GetAPISubVersion() { return subVersion; }
	__forceinline const std::string& Information::GetType() { return type; }

}