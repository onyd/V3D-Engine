#include "PlaneObject.h"

PlaneObject::PlaneObject(const Vector<float, 3>& normal, const Vector<float, 3>& pos, const Vector<float, 3>& up, float width, float height, size_t id)
{
	Vector<float, 3> ortho = up.cross_product(normal);
	Vector<float, 3> points1[3] = { pos, pos + up * height, pos + up * height + ortho * width };
	Vector<float, 3> points2[3] = { pos, pos + up * height + ortho * width , pos + ortho * width};

	std::vector<Triangle> triangles = { Triangle(points1), Triangle(points2) };

	_mesh = Mesh(triangles);
	_id = id;
	_normal = normal;
	_pos = pos;
}

PlaneObject::PlaneObject(const Plane<float>& p, const Vector<float, 3>& pos, const Vector<float, 3>& up, float width, float height, size_t id)
	: PlaneObject(p.getNormal(), pos, up, width, height, id)
{
}

vector<Triangle> PlaneObject::processed_triangle(Camera& cam, vector<Light*>& lights)
{
	vector<Triangle> rendered;
	

	return rendered;
}
