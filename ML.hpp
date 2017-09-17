#pragma once

/**
*@brief MLライブラリは主にTake***,Get***から成り立ちます。<br>
*@brief Get自体は読み込みせずに返すだけですが、Takeは読み込みから始めるので実行速度を気にする場合は気を付けてください
*@attention このライブラリの例外はML::Error::Exception型で投げます
*@author Lobelia.Snow
*/

//TODO: コメントちゃんと書くこと
//TODO: 情報取得のためのヘルパー関数を用意する 
//TODO: 情報を追加していくための備忘録作成
//TODO: ヘッダーのロケーション整理
//TODO: constや、noexcept等の追加
//TODO: 下の実装でレンジチェックをしているが、それを上で行う
//TODO: (できれば)キャッシュ的なのを用いて一度ロードした物は次から再ロードなしにする
//TODO: (できれば)重複する情報を削り、渡す際にあたかもあるかのようにふるまわせる

#define ML_FBX_SUPPORT

#include "MLCommon.hpp"
#include "MLInformation.hpp"
#include "MLDeveloper.hpp"
#include "MLMath.hpp"
#include "MLVertex.hpp"
#include "MLMaterial.hpp"
#include "MLIndexRow.hpp"
#include "MLMesh.hpp"
#include "MLModel.hpp"
#include "MMD\MLPMDMesh.hpp"
#include "MMD\MLPMDModel.hpp"

