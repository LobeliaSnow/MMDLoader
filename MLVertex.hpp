#pragma once
namespace ML::Data {
	/**
	*@brief 情報用の型、実際にこれを読み込むのはMeshクラス
	*/
	class Vertex final {
	public:
		//TODO: 情報取得方法を多く提供
		class Position :public Math::Vector3 { public:	operator Math::Vector3() { return *this; } };
		class Normal :public Math::Vector3 { public:	operator Math::Vector3() { return *this; } };
		class UV :public Math::Vector2 { public:	operator Math::Vector2() { return *this; } };
	private:
		/**@brief 頂点位置*/
		Position position;
		/**@brief 法線方向*/
		Normal normal;
		/**@brief UV座標*/
		UV uv;
	public:
		/**@brief コンストラクタ*/
		Vertex();
		/**
		*@breif コンストラクタ
		*@param[in] 位置
		*@param[in] 法線
		*@param[in] ＵＶ
		*@attention Mesh用。実際にこの情報を入手したいときは、各Model又はMeshから入手。
		*/
		Vertex(Position position, Normal normal, UV uv);
		/**@brief デストラクタ*/
		~Vertex();
		/**
		*@brief 頂点位置を取得
		*@return 頂点位置
		*/
		Position GetOrderPosition();
		/**
		*@brief 法線方向を取得
		*@return 法線方向
		*/
		Normal GetOrderNormal();
		/**
		*@brief UV座標を取得
		*@return UV座標
		*/
		UV GetOrderUV();
		/**
		*@brief ML::Data::Vertex::Positionで頂点位置<br>
		*@brief ML::Data::Vertex::Normalで法線方向<br>
		*@brief ML::Data::Vertex::UVでUV座標<br>
		*@param[in] template ML::Data::Vertex::Position or ML::Data::Vertex::Normal or ML::Data::Vertex::UV
		*@return template引数の型
		*/
		template<typename T> T GetOrder();
	};
}

#include "MLVertex.inl"