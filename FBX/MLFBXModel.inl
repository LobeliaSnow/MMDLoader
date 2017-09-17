#pragma once
namespace ML::Data::FBX {
	__forceinline DWORD Model::TakeMeshCount() { return scene->GetSrcObjectCount<FbxMesh>(); }
	__forceinline MeshBase* Model::TakeMeshOrder(UINT order_index) {
		if (order_index >= TakeMeshCount())STRICT_THROW("範囲外の値です");
		Utility::ResourceManager<FBX::Mesh, UINT>::Factory(order_index, scene->GetSrcObject<FbxMesh>(order_index));
		return Utility::ResourceManager<FBX::Mesh, UINT>::Get(order_index);
	}

	__forceinline Model::Model(std::string file_path) {
		TRY{
			manager = fbxsdk::FbxManager::Create();

			fbxsdk::FbxImporter* importer = fbxsdk::FbxImporter::Create(manager, "Importer");
			scene = fbxsdk::FbxScene::Create(manager, "Scene");
			//Fbxファイルを開く
			if (!importer->Initialize(file_path.c_str()))	STRICT_THROW("Fbxファイルが開けませんでした");
			//シーンを取り出す
			if (!importer->Import(scene))STRICT_THROW("シーンの取り出しに失敗");
			importer->Destroy();
			fbxsdk::FbxGeometryConverter converter(manager);

			//全て三角化
			if (!converter.Triangulate(scene, true))	STRICT_THROW("三角化に失敗");
			converter.RemoveBadPolygonsFromMeshes(scene);
			//マテリアルごとにメッシュを分離
			if (!converter.SplitMeshesPerMaterial(scene, true))STRICT_THROW("メッシュの分離に失敗");
		}CATCH(...) { 
			manager->Destroy();
			THROW;
		}
	}
	__forceinline Model::~Model() { manager->Destroy(); }
}