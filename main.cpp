#include "cista.h"
#include <cstdio>

struct vec3 {
	float x, y, z;
};

struct mat4 {
	float d[16];
};

struct Vertex {
	vec3 position;
	vec3 normal;
};

struct Mesh {
	cista::raw::vector<mat4> transforms;
	cista::raw::vector<Vertex> vertices;
};

using Meshes = cista::raw::vector<Mesh>;

//template <typename Ctx>
//void serialize(Ctx& c, vec3 const* v, cista::offset_t const pos) {
//	c.write(pos, v->x);
//	c.write(pos, v->y);
//	c.write(pos, v->z);
//}
//
//template <typename Ctx>
//void serialize(Ctx& c, mat4 const* m, cista::offset_t const pos) {
//	for(int i = 0; i < 16; += i) {
//		c.write(pos, m->d[i]);
//	}
//}

template <typename Ctx>
void serialize(Ctx& c, Mesh const* mesh, cista::offset_t const pos) {
	for(auto const& t : mesh->transforms) {
		c.write(pos, t);
	}
	for(auto const& v : mesh->vertices) {
		c.write(pos, v);
	}
}

template <typename Ctx>
void serialize(Ctx& c, Meshes const* meshes, cista::offset_t const pos) {
	for(auto const& mesh : *meshes) {
		c.write(pos, mesh);
	}
}

int main() {
	Meshes meshes;
	for(int i = 0; i < 10; ++i) {
		Mesh mesh;
		for(int i = 0; i < 10; ++i) {
			mat4 m;
			mesh.transforms.emplace_back(m);
		}
		for(int i = 0; i < 10; ++i) {
			Vertex v;
			mesh.vertices.emplace_back(v);
		}
		meshes.emplace_back(std::move(mesh));
	}
	cista::byte_buf buffer;
	buffer = cista::serialize(meshes);

	// write buffer to file
	if(std::FILE* f1 = std::fopen("file.bin", "wb")) {
		assert(!buffer.empty());
		std::fwrite(buffer.data(), sizeof(buffer[0]), buffer.size(), f1);
		std::fclose(f1);
	}
}