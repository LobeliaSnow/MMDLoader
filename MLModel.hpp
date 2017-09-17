#pragma once
namespace ML::Data {
	class ModelBase abstract {
	private:
		template<typename T>
		std::vector<T> _CollectData(UINT mesh_index);
	private:
		//MeshBaseの数を取得するための関数
		//MeshBaseの数はどうしてもここでとる必要があるため苦肉の策
		virtual DWORD TakeMeshCount() = 0;
		virtual MeshBase* TakeMeshOrder(UINT order_index) = 0;
	public:
		/**@brief コンストラクタ*/
		ModelBase();
		/**@brief デストラクタ*/
		virtual ~ModelBase();
		//以下メッシュ以外の関連取得
		/**
		*@brief 対象情報の存在する数を返す
		*@param[in] template 欲しい情報の型
		*@param[in] 対象メッシュのインデックス
		*@return DWORD その型の数
		*@attention ML::Data::MeshBaseの場合は引数は無視されます
		*/
		template<typename T> DWORD TakeOrderCount(UINT mesh_index);
		/**
		*@brief 情報が単一でほしい場合に使用される
		*@param[in] template 欲しい情報の型
		*@param[in] 対象メッシュのインデックス
		*@param[in] 取得対象の情報のインデックス
		*@return template引数の型
		*@attention ML::Data::MeshBaseの場合は第二引数は無視されます
		*/
		template<typename T> T TakeOrder(UINT mesh_index, UINT order_index);
		/**
		*@brief 情報が纏めてほしい場合に使用される
		*@param[in] template 欲しい情報の型
		*@param[in] 対象メッシュのインデックス
		*@return std::vector<template引数の型>
		*@attention ML::Data::MeshBaseの場合は引数は無視されます
		*@attention ML::Data::MeshBaseが欲しい場合は、ML::Data::MeshBase*をtemplate引数に渡してください
		*/
		template<typename T> std::vector<T> TakeOrder(UINT mesh_index);
	};
}
#define NO_USE_ARGUMENT 0

#include "MLModel.inl"