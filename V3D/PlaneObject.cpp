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

vector<Triangle*> PlaneObject::render(Camera& cam, vector<Light*>& lights)
{
	vector<Triangle*> rendered;
	for (Triangle t : _mesh.getTriangles()) {
		t.matmul(cam.getViewMatrix());
		applyLights(t, lights, _normal);
		//t.c = olc::Pixel(255, 255, 255);

		// Clipping
		Triangle* output[2] = { new Triangle, new Triangle };
		size_t nClipped = this->clip(t, cam.getEyePlane(), output[0], output[1]);
		if (nClipped == 1) {
			project(output[0], cam);
			rendered.push_back(output[0]);
			delete output[1];
		}
		else if (nClipped == 2) {
			project(output[0], cam);
			project(output[1], cam);

			rendered.push_back(output[0]);
			rendered.push_back(output[1]);
		}
		else {
			delete output[0];
			delete output[1];
		}

	}
	return rendered;
}
