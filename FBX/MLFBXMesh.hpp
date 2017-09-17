#pragma once
namespace ML::Data::FBX {
	class Mesh :public MeshBase {
	private:
		fbxsdk::FbxMesh* mesh;
		std::vector<Vertex::Position> vertexPoints;
		std::vector<Vertex::Normal> normalDirections;
		std::vector<Vertex::UV> uvPositions;
		//vector
		std::unique_ptr<Material::TexturePath> texturePath;
		std::unique_ptr<Material::VertexColor> vertexColor;
	private:
		Vertex::Position LocalTakeOrderVertex(UINT order_index);
		Vertex::Normal LocalTakeOrderNormal(UINT order_index);
		Vertex::UV LocalTakeOrderUV(UINT order_index);
		Material::TexturePath LocalTakeOrderTexturePath(UINT order_index);
		Material::VertexColor LocalTakeOrderVertexColor(UINT order_index);
	public:
		Mesh(FbxMesh* mesh);
		~Mesh();
		/**
		*@brief 頂点数取得
		*@param[in] 対象メッシュのインデックス
		*@return 頂点数
		*/
		DWORD TakeOrderVertexCount()override;
		/**
		*@brief マテリアル数取得
		*@param[in] 対象メッシュのインデックス
		*@return マテリアル数
		*/
		DWORD TakeOrderMaterialCount()override;
		/**
		*@brief インデックス数取得
		*@param[in] 対象メッシュのインデックス
		*@return インデックス数
		*/
		DWORD TakeOrderIndexCount()override;
		/**
		*@brief 頂点取得
		*@param[in] 対象メッシュのインデックス
		*@param[in] ほしい情報へのインデックス
		*@return 頂点
		*/
		Vertex TakeOrderVertex(UINT order_index)override;
		/**
		*@brief マテリアル取得
		*@param[in] 対象メッシュのインデックス
		*@param[in] ほしい情報へのインデックス
		*@return マテリアル
		*/
		Material TakeOrderMaterial(UINT order_index)override;
		/**
		*@brief インデックス取得
		*@param[in] 対象メッシュのインデックス
		*@param[in] ほしい情報へのインデックス
		*@return インデックス
		*/
		IndexRow TakeOrderIndex(UINT order_index)override;

	};
}
#include "MLFBXMesh.inl"