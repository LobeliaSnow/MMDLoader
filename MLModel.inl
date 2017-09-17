#pragma once
namespace ML::Data {
	__forceinline ModelBase::ModelBase() = default;
	__forceinline ModelBase::~ModelBase() = default;

	template<typename T> std::vector<T> ModelBase::_CollectData(UINT mesh_index) {
		DWORD _count = TakeOrderCount<T>(mesh_index);
		std::vector<T> _data;
		for (DWORD _index = 0; _index < _count; _index++) {
			_data.push_back(TakeOrder<T>(mesh_index, _index));
		}
		return _data;
	}

	template<typename T> __forceinline DWORD ModelBase::TakeOrderCount(UINT mesh_index) { COMPILE_ERROR_FOR_TEMPLATE; }
	template<> __forceinline DWORD ModelBase::TakeOrderCount<MeshBase*>(UINT mesh_index) { return TakeMeshCount(); }
	template<> __forceinline DWORD ModelBase::TakeOrderCount<Vertex>(UINT mesh_index) { return TakeMeshCount(); }
	template<> __forceinline DWORD ModelBase::TakeOrderCount<Vertex::Position>(UINT mesh_index) { return TakeMeshCount(); }
	template<> __forceinline DWORD ModelBase::TakeOrderCount<Vertex::Normal>(UINT mesh_index) { return TakeMeshCount(); }
	template<> __forceinline DWORD ModelBase::TakeOrderCount<Vertex::UV>(UINT mesh_index) { return TakeMeshCount(); }

	template<> __forceinline DWORD ModelBase::TakeOrderCount<Material>(UINT mesh_index) { return TakeMeshOrder(mesh_index)->TakeOrderCount<Material>(); }
	template<> __forceinline DWORD ModelBase::TakeOrderCount<Material::TexturePath>(UINT mesh_index) { return  TakeOrderCount<Material>(mesh_index); }
	template<> __forceinline DWORD ModelBase::TakeOrderCount<Material::VertexColor>(UINT mesh_index) { return TakeOrderCount<Material>(mesh_index); }
	
	template<> __forceinline DWORD ModelBase::TakeOrderCount<IndexRow>(UINT mesh_index) { return TakeMeshOrder(mesh_index)->TakeOrderCount<IndexRow>(); }

	template<typename T> __forceinline T ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { COMPILE_ERROR_FOR_TEMPLATE; }
	template<> __forceinline MeshBase* ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeMeshOrder(mesh_index); }
	template<> __forceinline Vertex ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeOrder<MeshBase*>(mesh_index, NO_USE_ARGUMENT)->TakeOrder<Vertex>(order_index); }
	template<> __forceinline Vertex::Position ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeMeshOrder(mesh_index)->TakeOrder<Vertex::Position>(order_index); }
	template<> __forceinline Vertex::Normal ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeMeshOrder(mesh_index)->TakeOrder<Vertex::Normal>(order_index); }
	template<> __forceinline Vertex::UV ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeMeshOrder(mesh_index)->TakeOrder<Vertex::UV>(order_index); }

	template<> __forceinline Material ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeMeshOrder(mesh_index)->TakeOrder<Material>(order_index); }
	template<> __forceinline Material::TexturePath ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeMeshOrder(mesh_index)->TakeOrder<Material::TexturePath>(order_index); }
	template<> __forceinline Material::VertexColor ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeMeshOrder(mesh_index)->TakeOrder<Material::VertexColor>(order_index); }
	
	template<> __forceinline IndexRow ModelBase::TakeOrder(UINT mesh_index, UINT order_index) { return TakeMeshOrder(mesh_index)->TakeOrder<IndexRow>(order_index); }

	template<typename T> __forceinline std::vector<T> ModelBase::TakeOrder(UINT mesh_index) { COMPILE_ERROR_FOR_TEMPLATE; }
	template<> __forceinline std::vector<MeshBase*> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<MeshBase*>(NO_USE_ARGUMENT); }
	template<> __forceinline std::vector<Vertex> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<Vertex>(mesh_index); }
	template<> __forceinline std::vector<Vertex::Position> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<Vertex::Position>(mesh_index); }
	template<> __forceinline std::vector<Vertex::Normal> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<Vertex::Normal>(mesh_index); }
	template<> __forceinline std::vector<Vertex::UV> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<Vertex::UV>(mesh_index); }

	template<> __forceinline std::vector<Material> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<Material>(mesh_index); }
	template<> __forceinline std::vector<Material::TexturePath> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<Material::TexturePath>(mesh_index); }
	template<> __forceinline std::vector<Material::VertexColor> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<Material::VertexColor>(mesh_index); }
	
	template<> __forceinline std::vector<IndexRow> ModelBase::TakeOrder(UINT mesh_index) { return _CollectData<IndexRow>(mesh_index); }

}