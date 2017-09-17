#pragma once
namespace ML::Data {
	Material::Material(TexturePath file_path, VertexColor vertex_color) :filePath(file_path), vertexColor(vertex_color) {}
	Material::~Material() = default;
	Material::TexturePath Material::GetTexturePath() { return filePath; }
	Material::VertexColor Material::GetVertexColor() { return vertexColor; }

	template<typename T> T Material::GetOrder() { COMPILE_ERROR_FOR_TEMPLATE; }
	template<> Material::TexturePath Material::GetOrder() { return GetTexturePath(); }
	template<> Material::VertexColor Material::GetOrder() { return GetVertexColor(); }

}