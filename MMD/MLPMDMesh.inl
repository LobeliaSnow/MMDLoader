#pragma once
namespace ML::Data::PMD {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//					PMD::Mesh
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//private:
	__forceinline bool Mesh::ModelLinkCheck() { return filer.expired(); }
	//TODO: この下最適化の余地あり、頭が冷えているときに直すこと
	DWORD Mesh::_LocalTakeOrderCount(int seek_size, int read_size) {
		if (ModelLinkCheck())STRICT_THROW("Modelとのリンクが切れています");
		DWORD _count = 0;
		if (std::shared_ptr<Filer> _filer = filer.lock()) {
			if (!_filer->Seek(seek_size, Filer::SeekMode::FRONT))return 0;
			if (_filer->Read(&_count, read_size, 1) == SIZE_T_MAX)return 0;
			_filer->Rewind();
		}
		return _count;
	}
	template<typename T> __forceinline T Mesh::_LocalTakeOrder(UINT index, int seek_size, int read_size) {
		if (index >= TakeOrderCount<T>())STRICT_THROW("データ数を超えたインデックスが指定されています");
		if (ModelLinkCheck())STRICT_THROW("Modelとのリンクが切れています");
		T _ret = {};
		if (std::shared_ptr<Filer> _filer = filer.lock()) {
			if (!_filer->Seek(seek_size, Filer::SeekMode::FRONT))STRICT_THROW("シークに失敗しました");
			if (_filer->Read(&_ret, read_size, 1) == SIZE_T_MAX)STRICT_THROW("読み込みに失敗しました");
			_filer->Rewind();
		}
		return _ret;
	}
	//std::stringのための特殊化
	template<> std::string Mesh::_LocalTakeOrder(UINT index, int seek_size, int read_size) {
		if (ModelLinkCheck())STRICT_THROW("Modelとのリンクが切れています");
		std::unique_ptr<char[]> _orderData = {};
		if (std::shared_ptr<Filer> _filer = filer.lock()) {
			//ファイルの読み込み場所を先頭から見て、情報が載っている位置までシーク
			if (!_filer->Seek(seek_size, Filer::SeekMode::FRONT))return false;
			//読み取りサイズ+'\0'分のメモリ確保
			_orderData = std::make_unique<char[]>(read_size + 1);
			if (_filer->Read(_orderData.get(), read_size, 1) == SIZE_T_MAX)return std::string("読み込みエラー");
			_orderData.get()[read_size] = '\0';
			if (!_filer->Rewind())STRICT_THROW("初期位置に戻せませんでした、ファイルが開かれていない可能性があります");
		}
		return std::string(_orderData.get()) + "\0";
	}
	//IndexRowのための特殊化
	template<> __forceinline IndexRow Mesh::_LocalTakeOrder(UINT index, int seek_size, int read_size) {
		if (index >= TakeOrderCount<IndexRow>())STRICT_THROW("データ数を超えたインデックスが指定されています");
		if (ModelLinkCheck())STRICT_THROW("Modelとのリンクが切れています");
		WORD _ret = {};
		if (std::shared_ptr<Filer> _filer = filer.lock()) {
			if (!_filer->Seek(seek_size, Filer::SeekMode::FRONT))STRICT_THROW("シークに失敗しました");
			if (_filer->Read(&_ret, read_size, 1) == SIZE_T_MAX)STRICT_THROW("読み込みに失敗しました");
			_filer->Rewind();
		}
		return IndexRow(static_cast<UINT>(_ret));
	}

	template<typename T> __forceinline std::vector<T> Mesh::_LocalTakeOrder() {
		std::vector<T> ret = {};
		if (ModelLinkCheck())STRICT_THROW("Modelとのリンクが切れています");
		DWORD count = TakeOrderCount<T>();
		if (count == 0)STRICT_THROW("データが見つかりません");
		for (UINT index = 0; index < count; index++) {
			ret.push_back(TakeOrderSingle<T>(index));
		}
		return ret;
	}
	//private:
	__forceinline DWORD Mesh::TakeOrderVertexCount() { return _LocalTakeOrderCount(283, 4); }
	__forceinline DWORD Mesh::TakeOrderMaterialCount() { return _LocalTakeOrderCount(287 + 38 * TakeOrderCount<Vertex>() + 4 + 2 * TakeOrderCount<IndexRow>(), 4); }
	__forceinline DWORD Mesh::TakeOrderIndexCount() { return _LocalTakeOrderCount(287 + 38 * TakeOrderCount<Vertex>(), 4); }

	__forceinline Vertex Mesh::TakeOrderVertex(UINT order_index) {
		Vertex::Position _p = _LocalTakeOrder<Vertex::Position>(order_index, 287 + 38 * order_index, 12);
		Vertex::Normal _n = _LocalTakeOrder<Vertex::Normal>(order_index, 287 + 38 * order_index + 12, 12);
		Vertex::UV _u = _LocalTakeOrder<Vertex::UV>(order_index, 287 + 38 * order_index + 12 + 12, 8);
		return Vertex(_p, _n, _u);
	}
	__forceinline Material Mesh::TakeOrderMaterial(UINT order_index) {
		Material::TexturePath _path = _LocalTakeOrder<std::string>(order_index, 287 + 38 * TakeOrderCount<Vertex>() + 4 + 2 * TakeOrderCount<IndexRow>() + 4 + 70 * order_index + 50, 20);
		Material::VertexColor _vc = _LocalTakeOrder<Material::VertexColor>(order_index, 287 + 38 * TakeOrderCount<Vertex>() + 4 + 2 * TakeOrderCount<IndexRow>() + 4 + 70 * order_index, 12);
		return Material(_path, _vc);
	}
	__forceinline IndexRow Mesh::TakeOrderIndex(UINT order_index) { return _LocalTakeOrder<IndexRow>(order_index, 287 + 38 * TakeOrderCount<Vertex>() + 4 + 2 * order_index, 2); }
	//public:
	__forceinline Mesh::Mesh(std::weak_ptr<Utility::Filer> filer) :filer(filer) {}
	__forceinline Mesh::~Mesh() = default;

}