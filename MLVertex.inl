#pragma once
namespace ML::Data {
	__forceinline Vertex::Vertex() = default;
	__forceinline Vertex::Vertex(Position position, Normal normal, UV uv) :position(position), normal(normal), uv(uv) {	}
	__forceinline Vertex::~Vertex() = default;

	__forceinline Vertex::Position Vertex::GetOrderPosition() { return position; }
	__forceinline Vertex::Normal Vertex::GetOrderNormal() { return normal; }
	__forceinline Vertex::UV Vertex::GetOrderUV() { return uv; }

	template<typename T> __forceinline T Vertex::GetOrder() { COMPILE_ERROR_FOR_TEMPLATE; }
	template<> __forceinline Vertex::Position Vertex::GetOrder() { return GetOrderPosition(); }
	template<> __forceinline Vertex::Normal Vertex::GetOrder() { return GetOrderNormal(); }
	template<> __forceinline Vertex::UV Vertex::GetOrder() { return GetOrderUV(); }

}