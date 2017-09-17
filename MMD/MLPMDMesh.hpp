#pragma once
/**
*@attention PMDモデルにメッシュインデックスは必要ないため参照されない。
*/
namespace ML::Data::PMD {
	class Mesh final :public MeshBase {
		using Filer = Utility::Filer;
	private:
		std::weak_ptr<Utility::Filer> filer;
	private:
		bool ModelLinkCheck();
		DWORD _LocalTakeOrderCount(int seek_size, int read_size);
		template<typename T> T _LocalTakeOrder(UINT index, int seek_size, int read_size);
		template<typename T> std::vector<T> _LocalTakeOrder();
	private:
		DWORD TakeOrderVertexCount()override;
		DWORD TakeOrderMaterialCount()override;
		DWORD TakeOrderIndexCount()override;
		Vertex TakeOrderVertex(UINT order_index)override;
		Material TakeOrderMaterial(UINT order_index)override;
		IndexRow TakeOrderIndex(UINT order_index)override;
	public:
		Mesh(std::weak_ptr<Utility::Filer> filer);
		~Mesh();
	};
}

#include "MLPMDMesh.inl"