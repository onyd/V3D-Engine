#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "Object.h"

Object::Object()
{
}

Object::Object(Vector<float, 3>& pos, Mesh& mesh, size_t id)
	: Movable(pos), _mesh(mesh), Directable(), _id(id)
{
}

Object::Object(Vector<float, 3>& pos, const string& obj_file_name, size_t id)
	: Movable(pos), Directable(), _id(id)
{
	_mesh = Mesh::load_from_file(obj_file_name);
}

void Object::setId(size_t id)
{
	_id = id;
}

size_t Object::getId()
{
	return _id;
}

vector<Triangle> Object::processed_triangle(Camera& cam, vector<Light*>& lights)
{
	vector<Triangle> rendered;
	Matrix<float, 4, 4> model_matrix = getModelMatrix();
	for (Triangle t : _mesh.getTriangles()) {
		// Triangle in world space
		t.matmul(model_matrix);

		Vector<float, 3> normal = t.get_normal().normalized();
		if (this->isVisible(t, normal, cam)) {
			this->applyLights(t, lights, normal);
			// Triangle is now in view space
			t.matmul(cam.getViewMatrix());
			rendered.push_back(t);
		}
	}

	return rendered;
}

Matrix<float, 4, 4> Object::getModelMatrix()
{
	Matrix<float, 4, 4> rotation = getRotationMatrix();
	Matrix<float, 4, 4> translation = identityMatrix<float, 4>();
	translation(3, 0) = _pos[0];
	translation(3, 1) = _pos[1];
	translation(3, 2) = _pos[2];
	return rotation.matmul(translation);
}

bool Object::isVisible(const Triangle& t, Vector<float, 3>&normal, Camera& cam) const
{
	return normal.inner_product(t.p[0] - cam.getPos()) < 0.0f;
}

void Object::applyLights(Triangle& t, vector<Light*>& lights, Vector<float, 3>& normal)
{
	float grayScale = 0.0f;
	for (Light* l : lights) {
		grayScale += normal.inner_product(l->getForward());
	}
	grayScale /= lights.size();
	t.c = t.c + olc::Pixel(255*grayScale, 255*grayScale, 255*grayScale);
}

#endif