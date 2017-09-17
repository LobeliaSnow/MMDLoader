#pragma once
#include <math.h>

#ifndef PI
#define PI 3.141592653589793f
#endif

namespace ML::Math {
	/**
	*@brief floatの等値判定
	*@param[in] 左辺値
	*@param[in] 右辺値
	*@param[in] 許容値 デフォルトではものすごく小さい値が設定される
	*/
	__forceinline bool FloatEqual(float x, float y, float threshold = FLT_EPSILON) noexcept { return  (fabsf(x - y) <= threshold); };

	/**
	*@brief 度数法から弧度法に変換
	*@param[in] 度数法での角度
	*@return 弧度法での角度
	*/
	__forceinline float DegreeToRadian(float degree) { return degree* PI / 180; }

	/**
	*@brief 弧度法から度数法に変換
	*@param[in] 弧度法での角度
	*@return 度数法での角度
	*/
	__forceinline float RadianToDegree(float radian) { return radian * (180 / PI); }


	class Vector2 {
	public:
		union {
			struct { float x, y; };
			float v[2];
		};
		/**
		*@brief 型がintのVector2<br>
		*値を取る為のみ使用なので、メンバ関数は提供しない
		*/
		struct IVector2 {
			union {
				struct { int x, y; };
				int v[2];
			};
			__forceinline IVector2(int x, int y) :x(x), y(y) {}
		};
		__forceinline constexpr Vector2(float x, float y) noexcept : x(x), y(y) {}
		__forceinline Vector2(const IVector2& v) noexcept : Vector2(static_cast<float>(v.x), static_cast<float>(v.y)) {}
		__forceinline constexpr Vector2()noexcept : Vector2(0.0f, 0.0f) {}
		/**
		*@brief 値をint型で取得する関数
		*/
		__forceinline IVector2 Get()const  noexcept { return IVector2(static_cast<int>(x), static_cast<int>(y)); }
		/**
		*@brief int型のIVector2からの直接Vector2に代入
		*/
		__forceinline void Set(const IVector2& temp)noexcept {
			for (int i = 0; i < 2; i++) {
				this->v[i] = static_cast<float>(temp.v[i]);
			}
		}
		/**@brief 距離(平方根あり)*/
		__forceinline float Length() { return sqrtf(x*x + y*y); }
		/**@brief 距離(平方根なし)*/
		__forceinline float LengthSq() { return (x*x + y*y); }
		/**@brief 正規化*/
		__forceinline void Normalize() {
			float l = Length();
			if (l != 0.0f) { x /= l;	y /= l; }
		}
		__forceinline bool IsEqual(const Vector2& v) { return (FloatEqual(x, v.x) && FloatEqual(y, v.y)); }
		/**@brief 内積*/
		__forceinline static float Dot(const Vector2& v1, const Vector2& v2) { return (v1.x*v2.x + v1.y*v2.y); }
		__forceinline Vector2 operator +(const Vector2& v) { return Vector2(x + v.x, y + v.y); }
		__forceinline Vector2 operator -(const Vector2& v) { return Vector2(x - v.x, y - v.y); }
		__forceinline Vector2 operator *(const Vector2& v) { return Vector2(x * v.x, y * v.y); }
		__forceinline Vector2 operator /(const Vector2& v) { return Vector2(x / v.x, y / v.y); }
		__forceinline Vector2 operator +(float temp) { return Vector2(x + temp, y + temp); }
		__forceinline Vector2 operator -(float temp) { return Vector2(x - temp, y - temp); }
		__forceinline Vector2 operator *(float temp) { return Vector2(x * temp, y * temp); }
		__forceinline Vector2 operator /(float temp) { return Vector2(x / temp, y / temp); }
		__forceinline Vector2& operator +=(const Vector2& v) { x += v.x;	y += v.y; return *this; }
		__forceinline Vector2& operator -=(const Vector2& v) { x -= v.x;	y -= v.y; return *this; }
		__forceinline Vector2& operator *=(const Vector2& v) { x *= v.x;	y *= v.y; return *this; }
		__forceinline Vector2& operator /=(const Vector2& v) { x /= v.x;	y /= v.y; return *this; }
		__forceinline Vector2& operator +=(float temp) { x += temp;	y += temp; return *this; }
		__forceinline Vector2& operator -=(float temp) { x -= temp;	y -= temp; return *this; }
		__forceinline Vector2& operator *=(float temp) { x *= temp;	y *= temp; return *this; }
		__forceinline Vector2& operator /=(float temp) { x /= temp;	y /= temp; return *this; }
		__forceinline bool operator ==(const Vector2& v) { return IsEqual(v); }
		__forceinline bool operator !=(const Vector2& v) { return !IsEqual(v); }
	};
	__forceinline Vector2 operator +(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x + v2.x, v1.y + v2.y); }
	__forceinline Vector2 operator -(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x - v2.x, v1.y - v2.y); }
	__forceinline Vector2 operator *(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x * v2.x, v1.y * v2.y); }
	__forceinline Vector2 operator /(const Vector2& v1, const Vector2& v2) { return Vector2(v1.x / v2.x, v1.y / v2.y); }
	__forceinline Vector2 operator +(const Vector2& v1, float temp) { return Vector2(v1.x + temp, v1.y + temp); }
	__forceinline Vector2 operator -(const Vector2& v1, float temp) { return Vector2(v1.x - temp, v1.y - temp); }
	__forceinline Vector2 operator *(const Vector2& v1, float temp) { return Vector2(v1.x * temp, v1.y * temp); }
	__forceinline Vector2 operator /(const Vector2& v1, float temp) { return Vector2(v1.x / temp, v1.y / temp); }

	class Vector3 {
	public:
		union {
			struct { float x, y, z; };
			float v[3];
		};
		/**
		*@brief 型がintのVector3<br>
		*値を取る為のみ使用なので、メンバ関数は提供しない
		*/
		struct IVector3 {
			union {
				struct { int x, y, z; };
				int v[3];
			};
			__forceinline IVector3(int x, int y, int z) :x(x), y(y), z(z) {}
		};
		__forceinline constexpr Vector3(float x, float y, float z) noexcept : x(x), y(y), z(z) {}
		__forceinline Vector3(const IVector3& v) noexcept : Vector3(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z)) {}
		__forceinline constexpr Vector3()noexcept : Vector3(0.0f, 0.0f, 0.0f) {}
		/**
		*@brief 値をint型で取得する関数
		*/
		__forceinline IVector3 Get()const  noexcept { return IVector3(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z)); }
		/**
		*@brief int型のIVector3からの直接Vector3に代入
		*/
		__forceinline void Set(const IVector3& v)noexcept {
			for (int i = 0; i < 3; i++) {
				this->v[i] = static_cast<float>(v.v[i]);
			}
		}
		/**@brief 距離(平方根あり)*/
		__forceinline float Length() { return sqrtf(x*x + y*y + z*z); }
		/**@brief 距離(平方根なし)*/
		__forceinline float LengthSq() { return (x*x + y*y + z*z); }
		/**@brief 正規化*/
		__forceinline void Normalize() {
			float l = Length();
			if (l != 0.0f) { x /= l;	y /= l; z /= l; }
		}
		__forceinline bool IsEqual(const Vector3& v) { return (FloatEqual(x, v.x) && FloatEqual(y, v.y) && FloatEqual(z, v.z)); }
		/**@brief 内積*/
		__forceinline static float Dot(const Vector3& v1, const Vector3& v2) { return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z); }
		/**@brief 外積*/
		__forceinline static Vector3 Cross(const Vector3& v1, const Vector3& v2) {
			Vector3 ret = {};
			ret.x = v1.y*v2.z - v1.z*v2.y;
			ret.y = v1.z*v2.x - v1.x*v2.z;
			ret.z = v1.x*v2.y - v1.y*v2.x;
			return ret;
		}
		__forceinline Vector3 operator +(const Vector3& v) { return Vector3(x + v.x, y + v.y, z + v.z); }
		__forceinline Vector3 operator -(const Vector3& v) { return Vector3(x - v.x, y - v.y, z - v.z); }
		__forceinline Vector3 operator *(const Vector3& v) { return Vector3(x * v.x, y * v.y, z * v.z); }
		__forceinline Vector3 operator /(const Vector3& v) { return Vector3(x / v.x, y / v.y, z / v.z); }
		__forceinline Vector3 operator +(float temp) { return Vector3(x + temp, y + temp, z + temp); }
		__forceinline Vector3 operator -(float temp) { return Vector3(x - temp, y - temp, z - temp); }
		__forceinline Vector3 operator *(float temp) { return Vector3(x * temp, y * temp, z * temp); }
		__forceinline Vector3 operator /(float temp) { return Vector3(x / temp, y / temp, z / temp); }
		__forceinline Vector3& operator +=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		__forceinline Vector3& operator -=(const Vector3& v) { x -= v.x;	y -= v.y;	z -= v.z; return *this; }
		__forceinline Vector3& operator *=(const Vector3& v) { x *= v.x;	y *= v.y;	z *= v.z; return *this; }
		__forceinline Vector3& operator /=(const Vector3& v) { x /= v.x;	y /= v.y;	z /= v.z; return *this; }
		__forceinline Vector3& operator +=(float temp) { x += temp;	y += temp;	z += temp; return *this; }
		__forceinline Vector3& operator -=(float temp) { x -= temp;	y -= temp;	z -= temp; return *this; }
		__forceinline Vector3& operator *=(float temp) { x *= temp;	y *= temp;	z *= temp; return *this; }
		__forceinline Vector3& operator /=(float temp) { x /= temp;	y /= temp;	z /= temp; return *this; }
		__forceinline bool operator ==(const Vector3& v) { return IsEqual(v); }
		__forceinline bool operator !=(const Vector3& v) { return !IsEqual(v); }
	};
	__forceinline Vector3 operator +(const Vector3& v1, const Vector3& v2) { return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
	__forceinline Vector3 operator -(const Vector3& v1, const Vector3& v2) { return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
	__forceinline Vector3 operator *(const Vector3& v1, const Vector3& v2) { return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
	__forceinline Vector3 operator /(const Vector3& v1, const Vector3& v2) { return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); }
	__forceinline Vector3 operator +(const Vector3& v1, float temp) { return Vector3(v1.x + temp, v1.y + temp, v1.z + temp); }
	__forceinline Vector3 operator -(const Vector3& v1, float temp) { return Vector3(v1.x - temp, v1.y - temp, v1.z - temp); }
	__forceinline Vector3 operator *(const Vector3& v1, float temp) { return Vector3(v1.x * temp, v1.y * temp, v1.z * temp); }
	__forceinline Vector3 operator /(const Vector3& v1, float temp) { return Vector3(v1.x / temp, v1.y / temp, v1.z / temp); }


	class Vector4 {
	public:
		union {
			struct { float x, y, z, w; };
			float v[4];
		};
		/**
		*@brief 型がintのVector4<br>
		*値を取る為のみ使用なので、メンバ関数は提供しない
		*/
		struct IVector4 {
			union {
				struct { int x, y, z, w; };
				int v[4];
			};
			__forceinline IVector4(int x, int y, int z, int w) :x(x), y(y), z(z), w(w) {}
		};
		__forceinline constexpr Vector4(float x, float y, float z, float w) noexcept :x(x), y(y), z(z), w(w) {}
		__forceinline Vector4(const IVector4& v) noexcept : Vector4(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z), static_cast<float>(v.w)) {}
		__forceinline constexpr Vector4()noexcept : Vector4(0.0f, 0.0f, 0.0f, 0.0f) {}
		/**
		*@brief 値をint型で取得する関数
		*/
		__forceinline IVector4 Get()const  noexcept { return IVector4(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z), static_cast<int>(w)); }
		/**
		*@brief int型のIVector4からの直接Vector4に代入
		*/
		__forceinline void Set(const IVector4& v)noexcept {
			for (int i = 0; i < 4; i++) {
				this->v[i] = static_cast<float>(v.v[i]);
			}
		}
		/**@brief 距離(平方根あり)*/
		__forceinline float Length() { return sqrtf(x*x + y*y + z*z + w*w); }
		/**@brief 距離(平方根なし)*/
		__forceinline float LengthSq() { return (x*x + y*y + z*z + w*w); }
		/**@brief 正規化*/
		__forceinline void Normalize() {
			float l = Length();
			if (l != 0.0f) { x /= l;	y /= l; z /= l; }
		}
		__forceinline bool IsEqual(const Vector4& v) { return (FloatEqual(x, v.x) && FloatEqual(y, v.y) && FloatEqual(z, v.z) && FloatEqual(w, v.w)); }
		/**@brief 内積*/
		__forceinline static float Dot(const Vector4& v1, const Vector4& v2) { return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w); }
		__forceinline Vector4 operator +(const Vector4& v) { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
		__forceinline Vector4 operator -(const Vector4& v) { return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
		__forceinline Vector4 operator *(const Vector4& v) { return Vector4(x * v.x, y * v.y, z * v.z, w * v.w); }
		__forceinline Vector4 operator /(const Vector4& v) { return Vector4(x / v.x, y / v.y, z / v.z, w / v.w); }
		__forceinline Vector4 operator +(float temp) { return Vector4(x + temp, y + temp, z + temp, w + temp); }
		__forceinline Vector4 operator -(float temp) { return Vector4(x - temp, y - temp, z - temp, w - temp); }
		__forceinline Vector4 operator *(float temp) { return Vector4(x * temp, y * temp, z * temp, w * temp); }
		__forceinline Vector4 operator /(float temp) { return Vector4(x / temp, y / temp, z / temp, w / temp); }
		__forceinline Vector4& operator +=(const Vector4& v) { x += v.x;	y += v.y;	z += v.z; w += v.w; return *this; }
		__forceinline Vector4& operator -=(const Vector4& v) { x -= v.x;	y -= v.y;	z -= v.z; w -= v.w; return *this; }
		__forceinline Vector4& operator *=(const Vector4& v) { x *= v.x;	y *= v.y;	z *= v.z; w *= v.w; return *this; }
		__forceinline Vector4& operator /=(const Vector4& v) { x /= v.x;	y /= v.y;	z /= v.z; w /= v.w; return *this; }
		__forceinline Vector4& operator +=(float temp) { x += temp;	y += temp;	z += temp; z += temp; return *this; }
		__forceinline Vector4& operator -=(float temp) { x -= temp;	y -= temp;	z -= temp; z -= temp; return *this; }
		__forceinline Vector4& operator *=(float temp) { x *= temp;	y *= temp;	z *= temp; z *= temp; return *this; }
		__forceinline Vector4& operator /=(float temp) { x /= temp;	y /= temp;	z /= temp; z /= temp; return *this; }
		__forceinline bool operator ==(const Vector4& v) { return IsEqual(v); }
		__forceinline bool operator !=(const Vector4& v) { return !IsEqual(v); }
	};
	__forceinline Vector4 operator +(const Vector4& v1, const Vector4& v2) { return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w); }
	__forceinline Vector4 operator -(const Vector4& v1, const Vector4& v2) { return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w); }
	__forceinline Vector4 operator *(const Vector4& v1, const Vector4& v2) { return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w); }
	__forceinline Vector4 operator /(const Vector4& v1, const Vector4& v2) { return Vector4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w); }
	__forceinline Vector4 operator +(const Vector4& v1, float temp) { return Vector4(v1.x + temp, v1.y + temp, v1.z + temp, v1.w + temp); }
	__forceinline Vector4 operator -(const Vector4& v1, float temp) { return Vector4(v1.x - temp, v1.y - temp, v1.z - temp, v1.w + temp); }
	__forceinline Vector4 operator *(const Vector4& v1, float temp) { return Vector4(v1.x * temp, v1.y * temp, v1.z * temp, v1.w + temp); }
	__forceinline Vector4 operator /(const Vector4& v1, float temp) { return Vector4(v1.x / temp, v1.y / temp, v1.z / temp, v1.w + temp); }

}