#ifndef GEOMETRICS_CPP
#define GEOMETRICS_CPP

#include "Geometrics.h"


// Mesh
Mesh::Mesh()
	: _t(std::vector<Triangle>())
{
}

Mesh::Mesh(const std::vector<Triangle>& t)
	: _t(t)
{
}

std::vector<Triangle>& Mesh::getTriangles()
{
	return _t;
}

Triangle& Mesh::operator[](size_t i)
{
	return _t[i];
}

Mesh Mesh::load_from_file(const std::string& file_name)
{
	std::ifstream obj_stream(file_name);
	if (!obj_stream.is_open()) {
		throw std::invalid_argument("Mesh loading from file: " + file_name + " has failed.");
	}

	std::vector<Vector<float, 3>> verticies;
	std::vector<Triangle> triangles;

	while (!obj_stream.eof()) {
		char line[128];
		obj_stream.getline(line, 128);

		std::stringstream s;
		s << line;
		
		char symbol;

		if (line[0] == 'v') {
			Vector<float, 3> v;
			s >> symbol >> v[0] >> v[1] >> v[2];
			verticies.push_back(v);
		}

		if (line[0] == 'f') {
			int f[3];
			s >> symbol >> f[0] >> f[1] >> f[2];
			Vector<float, 3> v[3] = { verticies[f[0] - 1], verticies[f[1] - 1] , verticies[f[2] - 1] };
			triangles.push_back(Triangle(v));
		}
	}

	return Mesh(triangles);
}
#endif 
