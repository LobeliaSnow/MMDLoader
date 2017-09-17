#pragma once

namespace ML::Data {
	//TODO: 何番目のメッシュとかいらなくね？
	/**
	*@brief メッシュ、実際に情報を読み込むのは大体こいつ
	*/
	class MeshBase abstract {
	private:
		/**
		@brief 単一の情報を集めてstd::vectorにする
		*@param[in] template 集める対象の型
		*@return std::vector<指定した型>
		*/
		template<typename T>  std::vector<T> _CollectData();
		/**
		@brief 単一の情報を集めてstd::vectorにする
		*@param[in] template 情報源の型の型
		*@param[in] template 集める対象の型
		*@param[in] 情報源
		*@return std::vector<指定した型>
		*/
		template<typename T, typename U> __forceinline std::vector<U> _CollectData(std::vector<T>& _input_data);
	protected:
	public:
		/**
		*@brief コンストラクタ
		*@param[in] 対象メッシュのインデックス
		*/
		MeshBase();
		/**@brief デストラクタ*/
		~MeshBase();
		/**
		*@brief 頂点数取得
		*@param[in] 対象メッシュのインデックス
		*@return 頂点数
		*/
		virtual DWORD TakeOrderVertexCount() = 0;
		/**
		*@brief マテリアル数取得
		*@param[in] 対象メッシュのインデックス
		*@return マテリアル数
		*/
		virtual DWORD TakeOrderMaterialCount() = 0;
		/**
		*@brief インデックス数取得
		*@param[in] 対象メッシュのインデックス
		*@return インデックス数
		*/
		virtual DWORD TakeOrderIndexCount() = 0;
		/**
		*@brief 頂点取得
		*@param[in] 対象メッシュのインデックス
		*@param[in] ほしい情報へのインデックス
		*@return 頂点
		*/
		virtual Vertex TakeOrderVertex(UINT order_index) = 0;
		/**
		*@brief マテリアル取得
		*@param[in] 対象メッシュのインデックス
		*@param[in] ほしい情報へのインデックス
		*@return マテリアル
		*/
		virtual Material TakeOrderMaterial(UINT order_index) = 0;
		/**
		*@brief インデックス取得
		*@param[in] 対象メッシュのインデックス
		*@param[in] ほしい情報へのインデックス
		*@return インデックス
		*/
		virtual IndexRow TakeOrderIndex(UINT order_index) = 0;
		/**
		*@brief 指定された型の存在数を取得
		*@param[in] template 数を入手したい情報の型
		*@return 指定された型の存在数
		*/
		template<typename T> DWORD TakeOrderCount();
		/**
		*@brief 指定された型の存在数を取得
		*@param[in] template 入手したい情報の型
		*@return 指定された型情報
		*/
		template<typename T> T TakeOrder(UINT order_index);
		/**
		*@brief 指定された型の存在数をまとめて取得
		*@param[in] template 入手したい情報の型
		*@return 指定された型情報をまとめたもの
		*/
		template<typename T> std::vector<T> TakeOrder();
	};
}

#include "MLMesh.inl"