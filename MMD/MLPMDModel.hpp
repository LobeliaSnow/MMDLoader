#pragma once
namespace ML::Data::PMD {
	class Model :public ModelBase {
		using Filer = Utility::Filer;
	private:
		static const int MAX_MESH_COUNT = 1;
	private:
		std::shared_ptr<Filer> filer;
	private:
		bool CheckHeader();
		template<typename T> T _LocalTakeOrder(int seek_size, size_t read_size);
		float TakeVersion();
		std::string TakeModelName();
		std::string TakeComment();
		DWORD TakeMeshCount()override;
		MeshBase* TakeMeshOrder(UINT order_index)override;
	public:
		Model(std::string file_path);
	};
}

#include "MLPMDModel.inl"