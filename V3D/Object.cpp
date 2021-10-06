#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "Object.h"

Object::Object()
{
}

Object::Object(Vector<float, 3>& pos, Mesh& mesh, unsigned int id)
	: Movable(pos), _mesh(mesh), Directable(), _id(id)
{
}

Object::Object(Vector<float, 3>& pos, const string& obj_file_name, unsigned int id)
	: Movable(pos), Directable(), _id(id)
{
	_mesh = Mesh::load_from_file(obj_file_name);
}

void Object::setId(unsigned int id)
{
	_id = id;
}

unsigned int Object::getId()
{
	return _id;
}

vector<Triangle*> Object::render(Camera& cam, vector<Light*>& lights)
{
	vector<Triangle*> rendered;
	Matrix<float, 4, 4> model_matrix = getModelMatrix();
	for (Triangle t : _mesh.getTriangles()) {
		// Triangle in world space
		t.matmul(model_matrix);

		Vector<float, 3> normal = t.get_normal().normalized();
		if (isVisible(t, normal, cam)) {
			// Triangle is now in view space
			t.matmul(cam.getViewMatrix());
			applyLights(t, lights, normal);
			if (isInView(t, cam)) {

				// Clipping
				Triangle* output[2] = { new Triangle, new Triangle };
				unsigned int nClipped = this->clip(t, cam.getEyePlane(), output[0], output[1]);
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
		}
	}
	if (rendered.size() > 0) {
		cout << rendered.size() << endl;
	}
	return rendered;
}

unsigned int Object::countOutsidePoints(const Triangle& t, const Plane<float>& p) const
{
	unsigned int nOutside = 0;

	if (p.getNormal().inner_product(t.p[0]) + p.getD() < 0) { nOutside++; }
	if (p.getNormal().inner_product(t.p[1]) + p.getD() < 0) { nOutside++; }
	if (p.getNormal().inner_product(t.p[2]) + p.getD() < 0) { nOutside++; }
	return nOutside;
}

unsigned int Object::clip(Triangle& t, const Plane<float>& p, Triangle* out1, Triangle* out2)
{
	Vector<float, 3>* insides[3];
	Vector<float, 3>* outsides[3];
	unsigned int nInside = 0;
	unsigned int nOutside = 0;

	// Count and sort inside and outside points according to the plane
	if (p.getNormal().inner_product(t.p[0]) + p.getD() >= 0) { insides[nInside++] = &t.p[0]; }
	else { outsides[nOutside++] = &t.p[0]; }
	if (p.getNormal().inner_product(t.p[1]) + p.getD() >= 0) { insides[nInside++] = &t.p[1]; }
	else { outsides[nOutside++] = &t.p[1]; }
	if (p.getNormal().inner_product(t.p[2]) + p.getD() >= 0) { insides[nInside++] = &t.p[2]; }
	else { outsides[nOutside++] = &t.p[2]; }

	if (nInside == 0) {
		return 0;
	}
	if (nInside == 3) {
		out1->c = t.c;
		out1->p[0] = t.p[0];
		out1->p[1] = t.p[1];
		out1->p[2] = t.p[2];

		return 1;
	}
	if (nInside == 1) {
		out1->c = olc::Pixel(0, 0, 255);
		out1->p[0] = *insides[0];
		out1->p[1] = p.getIntersection(Line(*insides[0], *outsides[0]));
		out1->p[2] = p.getIntersection(Line(*insides[0], *outsides[1]));
		return 1;

	}
	if (nInside == 2) {
		out1->c = olc::Pixel(255, 0, 0);//t.c;
		out1->p[0] = *insides[0];
		out1->p[1] = *insides[1];
		out1->p[2] = p.getIntersection(Line(*insides[0], *outsides[0]));

		out2->c = olc::Pixel(0, 255, 0);
		out2->p[0] = *insides[1];
		out2->p[1] = out1->p[2];
		out2->p[2] = p.getIntersection(Line(*insides[1], *outsides[0]));
		return 2;
	}
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

bool Object::isInView(const Triangle& t, Camera& cam) const
{
	
	if (countOutsidePoints(t, cam.getTopPlane()) == 3)
		return false;
	if (countOutsidePoints(t, cam.getBotPlane()) == 3)
		return false;
	if (countOutsidePoints(t, cam.getLeftPlane()) == 3)
		return false;
	if (countOutsidePoints(t, cam.getRightPlane()) == 3)
		return false;

	return true;	
}

bool Object::isVisible(const Triangle& t, Vector<float, 3>&normal, Camera& cam) const
{
	return normal.inner_product(t.p[0] - cam.getPos()) < 0.0f;
}

void Object::project(Triangle* t, Camera& cam)
{
	// Projects
	for (unsigned int i = 0; i < 3; i++) {
		Vector<float, 4> projected = vector4_cast(t->p[i]) * cam.getProjectionMatrix();
		if (projected[3] != 0.0f) {
			t->p[i] = vector3_cast(projected) / projected[3];
		}
	}
	(*t) += Vector<float, 3>(1.0f, 1.0f, 0.0f);
	(*t) *= cam.getScale();
}

void Object::applyLights(Triangle& t, vector<Light*>& lights, Vector<float, 3>& normal)
{
	float grayScale = 0.0f;
	for (Light* l : lights) {
		grayScale += normal.inner_product(l->getDirection());
	}
	grayScale /= lights.size();
	t.c = t.c + olc::Pixel(255*grayScale, 255*grayScale, 255*grayScale);
}

#endif