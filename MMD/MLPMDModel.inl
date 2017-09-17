#pragma once

namespace ML::Data::PMD {
	//情報取得用関数
	template<typename T> T Model::_LocalTakeOrder(int seek_size, size_t read_size) {
		//ファイルの読み込み場所を先頭から見て、目的情報位置までシーク
		if (!filer->Seek(seek_size, Filer::SeekMode::FRONT))return false;
		T orderData = {};
		//データの読み込み
		if (filer->Read(&orderData, read_size, 1) == SIZE_T_MAX)	return T();
		//読み込み位置を先頭に戻す
		if (!filer->Rewind())STRICT_THROW("初期位置に戻せませんでした、ファイルが開かれていない可能性があります");
		return orderData;
	}
	//std::stringのための特殊化
	template<> std::string Model::_LocalTakeOrder(int seek_size, size_t read_size) {
		//ファイルの読み込み場所を先頭から見て、バージョン情報が載っている位置までシーク
		if (!filer->Seek(seek_size, Filer::SeekMode::FRONT))return false;
		std::unique_ptr<char[]> orderData = {};
		orderData = std::make_unique<char[]>(read_size + 1);
		if (filer->Read(orderData.get(), read_size, 1) == SIZE_T_MAX)return std::string("読み込みエラー");
		orderData.get()[read_size] = '\0';
		if (!filer->Rewind())STRICT_THROW("初期位置に戻せませんでした、ファイルが開かれていない可能性があります");
		return std::string(orderData.get()) + "\0";
	}
	//ヘッダー情報チェック
	__forceinline bool Model::CheckHeader() { return (_LocalTakeOrder<std::string>(0, static_cast<size_t>(3)) == "Pmd"); }
	//バージョン情報取得
	__forceinline float Model::TakeVersion() { return _LocalTakeOrder<float>(3, static_cast<size_t>(4)); }
	//モデル名取得
	__forceinline std::string Model::TakeModelName() { return _LocalTakeOrder<std::string>(7, static_cast<size_t>(20)); }
	//コメント取得
	__forceinline std::string Model::TakeComment() { return _LocalTakeOrder<std::string>(27, static_cast<size_t>(256)); }
	//Mesh数取得だけど、PMDにはおそらく1つしか無いという前提
	__forceinline DWORD Model::TakeMeshCount() { return MAX_MESH_COUNT; }

	__forceinline MeshBase* Model::TakeMeshOrder(UINT order_index) {
		if (order_index >= MAX_MESH_COUNT)STRICT_THROW("範囲外の値です");
		Utility::ResourceManager<PMD::Mesh, UINT>::Factory(order_index, filer);
		return Utility::ResourceManager<PMD::Mesh, UINT>::Get(order_index);
	}

	Model::Model(std::string file_path) :filer(std::make_shared<Filer>()) {
		TRY{
			//ファイルが開かれているかどうか試して、開かれていなければ開く
			if (!filer->IsOpen())filer->Open(file_path, Filer::OpenMode::ReadBinary);
			//ヘッダーチェック
			if (!CheckHeader())STRICT_THROW("ヘッダー情報が一致しませんでした、ファイル形式が違う可能性があります");
			//バージョンチェック
			if (TakeVersion() != 1.0f)STRICT_THROW("バージョン情報が一致しません、ファイルが壊れている可能性があります");
		}
		CATCH(...) { THROW; }
	}

}