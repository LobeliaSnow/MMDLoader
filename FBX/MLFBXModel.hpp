#pragma once
namespace ML::Data::FBX {
	class Model :public ModelBase{
	private:
		/**@brief fbxマネージャー*/
		fbxsdk::FbxManager* manager;
		/**@brief fbxシーン*/
		fbxsdk::FbxScene* scene;
	private:
		DWORD TakeMeshCount()override;
		MeshBase* TakeMeshOrder(UINT order_index)override;
	public:
		Model(std::string file_path);
		~Model();
	};
}
#include "MLFBXModel.inl"