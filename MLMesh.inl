#pragma once
namespace ML::Data {
	__forceinline MeshBase::MeshBase() = default;
	__forceinline MeshBase::~MeshBase() = default;

	template<typename T> __forceinline std::vector<T> MeshBase::_CollectData() {
		std::vector<T> _data = {};
		DWORD _count = TakeOrderCount<T>();
		for (DWORD _index = 0; _index < _count; _index++) {
			_data.push_back(TakeOrder<T>(_index));
		}
		return _data;
	}
	template<typename T, typename U> __forceinline std::vector<U> MeshBase::_CollectData(std::vector<T>& _input_data) {
		DWORD _count = static_cast<DWORD>(_input_data.size());
		std::vector<U> _data = {};
		for (DWORD _index = 0; _index < _count; _index++) {
			_data.push_back(_input_data[_index].GetOrder<U>());
		}
		return _data;
	}

	template<typename T> __forceinline DWORD MeshBase::TakeOrderCount() { COMPILE_ERROR_FOR_TEMPLATE; }
	template<> __forceinline DWORD MeshBase::TakeOrderCount<Vertex>() { return TakeOrderVertexCount(); }
	template<> __forceinline DWORD MeshBase::TakeOrderCount<Vertex::Position>() { return TakeOrderVertexCount(); }
	template<> __forceinline DWORD MeshBase::TakeOrderCount<Vertex::Normal>() { return TakeOrderVertexCount(); }
	template<> __forceinline DWORD MeshBase::TakeOrderCount<Vertex::UV>() { return TakeOrderVertexCount(); }

	template<> __forceinline DWORD MeshBase::TakeOrderCount<Material>() { return TakeOrderMaterialCount(); }
	template<> __forceinline DWORD MeshBase::TakeOrderCount<Material::TexturePath>() { return TakeOrderMaterialCount(); }
	template<> __forceinline DWORD MeshBase::TakeOrderCount<Material::VertexColor>() { return TakeOrderMaterialCount(); }
	
	template<> __forceinline DWORD MeshBase::TakeOrderCount<IndexRow>() { return TakeOrderIndexCount(); }

	template<typename T> __forceinline T MeshBase::TakeOrder(UINT order_index) { COMPILE_ERROR_FOR_TEMPLATE; }
	template<> __forceinline Vertex MeshBase::TakeOrder(UINT order_index) { return TakeOrderVertex(order_index); }
	template<> __forceinline Vertex::Position MeshBase::TakeOrder(UINT order_index) { return TakeOrderVertex(order_index).GetOrder<Vertex::Position>(); }
	template<> __forceinline Vertex::Normal MeshBase::TakeOrder(UINT order_index) { return TakeOrderVertex(order_index).GetOrder<Vertex::Normal>(); }
	template<> __forceinline Vertex::UV MeshBase::TakeOrder(UINT order_index) { return TakeOrderVertex(order_index).GetOrder<Vertex::UV>(); }

	template<> __forceinline Material MeshBase::TakeOrder(UINT order_index) { return TakeOrderMaterial(order_index); }
	template<> __forceinline Material::TexturePath MeshBase::TakeOrder(UINT order_index) { return TakeOrderMaterial(order_index).GetOrder<Material::TexturePath>(); }
	template<> __forceinline Material::VertexColor MeshBase::TakeOrder(UINT order_index) { return TakeOrderMaterial(order_index).GetOrder<Material::VertexColor>(); }
	
	template<> __forceinline IndexRow MeshBase::TakeOrder(UINT order_index) { return TakeOrderIndex(order_index); }

	template<typename T> std::vector<T> MeshBase::TakeOrder() { COMPILE_ERROR_FOR_TEMPLATE; }
	template<> std::vector<Vertex> MeshBase::TakeOrder() { return _CollectData<Vertex>(); }
	template<> std::vector<Vertex::Position> MeshBase::TakeOrder() { return _CollectData<Vertex, Vertex::Position>(TakeOrder<Vertex>()); }
	template<> std::vector<Vertex::Normal> MeshBase::TakeOrder() { return _CollectData<Vertex, Vertex::Normal>(TakeOrder<Vertex>()); }
	template<> std::vector<Vertex::UV> MeshBase::TakeOrder() { return _CollectData<Vertex, Vertex::UV>(TakeOrder<Vertex>()); }

	template<> std::vector<Material> MeshBase::TakeOrder() { return _CollectData<Material>(); }
	template<> std::vector<Material::TexturePath> MeshBase::TakeOrder() { return _CollectData<Material, Material::TexturePath>(TakeOrder<Material>()); }
	template<> std::vector<Material::VertexColor> MeshBase::TakeOrder() { return _CollectData<Material, Material::VertexColor>(TakeOrder<Material>()); }

	template<> std::vector<IndexRow> MeshBase::TakeOrder() { return _CollectData<IndexRow>(); }
}
