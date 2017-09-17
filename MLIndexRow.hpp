#pragma once
namespace ML::Data {
	/**
	*@brief 情報用の型、実際にこれを読み込むのはMeshクラス
	*/
	class IndexRow {
	private:
		UINT index;
	public:
		/**
		*@brief この型そのものをUINTとして扱う為のキャスト演算子
		*@return UINT
		*/
		__forceinline operator UINT()const noexcept { return index; }
		/**@brief コンストラクタ*/
		IndexRow();
		/**
		*@brief コンストラクタ
		*@param[in] 実データ
		*/
		IndexRow(UINT index);
		/**@brief デストラクタ*/
		~IndexRow();
	};
}
#include "MLIndexRow.inl"