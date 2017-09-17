#pragma once
namespace ML::Data {
	/**
	*@brief 情報用の型、実際にこれを読み込むのはMeshクラス
	*/
	class Material {
	public:
		//TODO: 情報取得方法を多く提供
		/**@brief テクスチャファイルパス*/
		class TexturePath final{
		private:
			/**@brief 本体*/
			std::string path;
		public:
			/**
			*@brief コンストラクタ
			*@param[in] 実データ
			*/
			TexturePath(std::string path) :path(path) {}
			/**@brief この型をstd::stringとして扱うためのキャスト演算子*/
			operator std::string() { return path; }
		};
		/**@brief 頂点色*/
		class VertexColor :public Math::Vector3 { 
		public:
			/**@brief この型をMath::Vector3として扱うためのキャスト演算子*/
			operator Math::Vector3() { return *this; } 
		};
	private:
		/**@brief テクスチャパス*/
		TexturePath filePath;
		/**@brief 頂点色*/
		VertexColor vertexColor;
	public:
		/**
		*@brief コンストラクタ
		*@param[in] テクスチャパス
		*@param[in] 頂点色
		*/
		Material(TexturePath file_path, VertexColor vertex_color);
		/**@brief デストラクタ*/
		~Material();
		/**
		*@brief テクスチャパス取得
		*@return テクスチャパス
		*/
		TexturePath GetTexturePath();
		/**
		*@brief 頂点色取得
		*@return 頂点色
		*/
		VertexColor GetVertexColor();
		/**
		*@brief ML::Data::Material::TexturePathでテクスチャパス<br>
		*@brief ML::Data::Material::VertexColorで頂点色<br>
		*@param[in] template ML::Data::Material::TexturePath or ML::Data::Material::VertexColor
		*@return template引数の型
		*/
		template<typename T> T GetOrder();
	};
}
#include "MLMaterial.inl"