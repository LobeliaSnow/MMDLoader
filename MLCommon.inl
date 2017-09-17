#pragma once

namespace ML {
	namespace Error {
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//					Exception
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//private:
		__forceinline std::string Exception::CreateMessage()const noexcept {
			std::stringstream error;
			error << "\n======! begin exception message !======\n\n" << "\n[source : " << _filename << "]\n\n[function : " << _functionName << "]\n\n[line : " << _executeLine << "]\n\n";
			if (!_msg.empty())error << "[cause : " << _msg << "]\n\n";
			error << "\n======! end exception message !======\n\n";
			return error.str();
		}
		//TODO: ファイル出力にする
		__forceinline void Exception::OutputLog()const noexcept { std::cout << CreateMessage() << std::endl; }

		//public:
		__forceinline Exception::Exception(std::string filename, std::string func_name, int exe_line) noexcept :Exception(filename, func_name, exe_line, "") {}

		__forceinline Exception::Exception(std::string filename, std::string func_name, int exe_line, std::string msg) noexcept : _filename(filename), _functionName(func_name), _executeLine(exe_line), _msg(msg) {}

		__forceinline void Exception::BoxMessage()const noexcept {
#if (defined(__EXCEPTION_ON__)||defined(__STRICT_EXCEPTION_ON__))&&!defined(__NO_EXCEPTION__)
			MessageBox(nullptr, CreateMessage().c_str(), "exception!", MB_OK | MB_ICONERROR);
#endif
			OutputLog();
		}

		__forceinline const std::string Exception::CreateExceptionMessage()const noexcept { return CreateMessage(); }


	}
	namespace Utility {
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//					Filer
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//public:
		enum class Filer::OpenMode { NoOpen = -1, AppendBinaryPlus, WriteBinaryPlus, ReadBinaryPlus, AppendBinary, WriteBinary, ReadBinary, AppendPlus, WritePlus, ReadPlus, Append, Write, Read, };

		enum class Filer::SeekMode { FRONT, CURRENT, BACK };

		//private:
		std::string Filer::ModePurse(Filer::OpenMode m) {
			switch (m) {
			case OpenMode::AppendBinaryPlus:	return "ab+";
			case OpenMode::WriteBinaryPlus:		return "wb+";
			case OpenMode::ReadBinaryPlus:		return "rb+";
			case OpenMode::AppendBinary:		return "ab";
			case OpenMode::WriteBinary:			return "wb";
			case OpenMode::ReadBinary:			return "rb";
			case OpenMode::AppendPlus:			return "a+";
			case OpenMode::WritePlus:				return "w+";
			case OpenMode::ReadPlus:				return "r+";
			case OpenMode::Append:					return "a";
			case OpenMode::Write:					return "w";
			case OpenMode::Read:						return "r";
			default: STRICT_THROW("範囲外の値です");
			}
		}

		//public:
		__forceinline Filer::Filer()noexcept : fp(nullptr), mode(Filer::OpenMode::NoOpen) {}

		__forceinline Filer::~Filer()noexcept { if (IsOpen())Close(); }

		__forceinline bool Filer::IsAppendMode()const noexcept { return (mode == OpenMode::AppendBinaryPlus || mode == OpenMode::AppendBinary || mode == OpenMode::AppendPlus || mode == OpenMode::Append); }

		__forceinline bool Filer::IsWriteMode()const noexcept { return (mode == OpenMode::WriteBinaryPlus || mode == OpenMode::WriteBinary || mode == OpenMode::WritePlus || mode == OpenMode::Write); }

		__forceinline bool Filer::IsReadMode()const noexcept { return (mode == OpenMode::ReadBinaryPlus || mode == OpenMode::ReadBinary || mode == OpenMode::ReadPlus || mode == OpenMode::Read); }

		__forceinline bool Filer::IsBinaryMode()const noexcept { return (mode == OpenMode::ReadBinaryPlus || mode == OpenMode::ReadBinary || mode == OpenMode::WriteBinaryPlus || mode == OpenMode::WriteBinary || mode == OpenMode::ReadBinaryPlus || mode == OpenMode::ReadBinary); }

		__forceinline bool Filer::IsTextMode()const noexcept { return (mode == OpenMode::ReadPlus || mode == OpenMode::Read || mode == OpenMode::WritePlus || mode == OpenMode::Write || mode == OpenMode::ReadPlus || mode == OpenMode::Read); }

		__forceinline bool Filer::IsOpen()const noexcept { return (fp != nullptr); }

		__forceinline Filer::OpenMode Filer::GetMode()const noexcept { return mode; }

		__forceinline void Filer::Open(std::string filename, Filer::OpenMode m) {
			if (IsOpen())STRICT_THROW("既に開かれているファイルが存在します");
			mode = m;
			fopen_s(&fp, filename.c_str(), ModePurse(m).c_str());
			if (!fp)	STRICT_THROW("ファイルを開けませんでした");
		}

		__forceinline void Filer::Close()noexcept {
			if (IsOpen()) {
				fclose(fp);
				fp = nullptr;
				mode = OpenMode::NoOpen;
			}
		}

		template<typename T>
		__forceinline size_t Filer::Write(T* pointer, size_t count) noexcept {
			if (!IsOpen() || !(IsWriteMode() && IsAppendMode()))return SIZE_T_MAX;
			return fwrite(pointer, sizeof T, count, fp);
		}

		template<typename T>
		__forceinline size_t Filer::Read(T* pointer, size_t buffer_size, size_t count) noexcept {
			if (!IsOpen() || !IsReadMode())return SIZE_T_MAX;
			return fread_s(pointer, buffer_size, buffer_size, count, fp);
		}

		template <typename ... Args>
		__forceinline size_t Filer::Print(const char *format, Args const & ... args) noexcept {
			if (!IsOpen() || !(IsWriteMode() && IsAppendMode()))return SIZE_T_MAX;
			return fprintf_s(fp, format, args...);
		}

		template <typename ... Args>
		__forceinline size_t Filer::Scan(const char* format, Args const & ... args) noexcept {
			if (!IsOpen() || !IsReadMode())return SIZE_T_MAX;
			return fscanf_s(fp, format, args...);
		}

		__forceinline bool Filer::Seek(int offset, SeekMode mode) {
			if (!IsOpen())return false;
			int origin = -1;
			switch (mode) {
			case SeekMode::FRONT:		origin = SEEK_SET;	break;
			case SeekMode::CURRENT:	origin = SEEK_CUR;	break;
			case SeekMode::BACK:			origin = SEEK_END;	break;
			default:	STRICT_THROW("範囲外の値です");
			}
			return (fseek(fp, offset, origin) == 0);
		}

		__forceinline bool Filer::Rewind() {
			if (!IsOpen())return false;
			rewind(fp);
			return true;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//					ResourceManager
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename Key>
		__forceinline ResourceManager<T, Key>::ResourceManager() noexcept = default;
		
		template<typename T, typename Key>
		__forceinline ResourceManager<T, Key>::~ResourceManager() noexcept = default;

		template<typename T, typename Key>
		template<typename U, typename... Args>
		__forceinline T* ResourceManager<T, Key>::Factory(Key key, Args... args)noexcept {
			if (IsExist(key)) 	return resource[key].get();
			resource[key] = std::make_shared<U>(args...);
			return resource[key].get();
		}
		template<typename T, typename Key>
		__forceinline void ResourceManager<T, Key>::Register(Key key, std::shared_ptr<T> p)noexcept { if (!IsExist(key))	resource[key].swap(p); }
		template<typename T, typename Key>
		__forceinline bool ResourceManager<T, Key>::IsExist(Key key) noexcept { return ((resource.find(key) != resource.end()) && (resource[key].use_count() != 0)); }
		template<typename T, typename Key>
		__forceinline void ResourceManager<T, Key>::Clear() noexcept { resource.clear(); }
		template<typename T, typename Key>
		__forceinline T* ResourceManager<T, Key>::Get(Key key) noexcept { return resource[key].get(); }
		//static変数
		template<typename T, typename Key>
		std::unordered_map<Key, std::shared_ptr<T>> ResourceManager<T, Key>::resource;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//					Singleton
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		__forceinline Singleton<T>::Singleton()noexcept = default;
		template<typename T>
		__forceinline Singleton<T>::~Singleton()noexcept = default;
		template<typename T>
		__forceinline T* Singleton<T>::GetInstance() {
			static T inst;
			return &inst;
		}

	}
}