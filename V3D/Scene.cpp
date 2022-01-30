#ifndef SCENE_CPP
#define SCENE_CPP

#include "Scene.h"

Scene::Scene(Camera& camera)
	: _camera(camera)
{
}

void Scene::add_object(MeshObject* _objects)
{
	objects.push_back(_objects);
}

void Scene::remove_object(MeshObject* _objects)
{
}

void Scene::add_light(Light* _light)
{
	lights.push_back(_light);
}

void Scene::remove_light(Light* _light)
{
}

Camera& Scene::getCamera()
{
	return _camera;
}

std::vector<Triangle*> Scene::render()
{
	std::vector<Triangle> rendered;
	for (MeshObject* o : objects) {
		for (Triangle& t : o->processed_triangle(_camera, lights)) {
			// Camera front clipping
			Triangle output[2];
			unsigned int nClipped = this->clip(t, _camera.getEyePlane(), &output[0], &output[1]);
			if (nClipped == 1) {
				project(&output[0], _camera);
				rendered.push_back(output[0]);
			}
			else if (nClipped == 2) {
				project(&output[0], _camera);
				project(&output[1], _camera);

				rendered.push_back(output[0]);
				rendered.push_back(output[1]);
			}
		}
	}

	// Sort by z coordinates to keep objects depth ordered
	std::sort(rendered.begin(), rendered.end(), [](Triangle& t1, Triangle& t2) {
		return ((t1.p[0][2] + t1.p[1][2] + t1.p[2][2]) > (t2.p[0][2] + t2.p[1][2] + t2.p[2][2]));
	});

	std::vector<Triangle*> result;

	// Camera edges clipping
	for (Triangle& t : rendered) {
		Triangle output[2];;
		std::list<Triangle> triList;

		triList.push_back(t);
		int nNewTriangles = 1;

		for (int p = 0; p < 4; p++)
		{
			int nTrisToAdd = 0;
			while (nNewTriangles > 0)
			{
				Triangle current = triList.front();
				triList.pop_front();
				nNewTriangles--;

				// Clipping against each edge
				switch (p)
				{
					case 0:	nTrisToAdd = this->clip(current, _camera.getTopPlane(), &output[0], &output[1]); break;
					case 1:	nTrisToAdd = this->clip(current, _camera.getBotPlane(), &output[0], &output[1]); break;
					case 2:	nTrisToAdd = this->clip(current, _camera.getLeftPlane(), &output[0], &output[1]); break;
					case 3:	nTrisToAdd = this->clip(current, _camera.getRightPlane(), &output[0], &output[1]); break;
				}

				// A clipped triangle may be clipped against another plane
				for (int w = 0; w < nTrisToAdd; w++) {
					triList.push_back(output[w]);
				}
			}

			nNewTriangles = triList.size();
			for (Triangle& t : triList)
			{
				result.push_back(new Triangle(t)); 
			}
		}
	}

	return result;
}

void Scene::project(Triangle* t, Camera& cam)
{
	// Projects
	for (unsigned short i = 0; i < 3; i++) {
		Vector<float, 4> projected = vector4_cast(t->p[i]) * cam.getProjectionMatrix();
		if (projected[3] != 0.0f) {
			t->p[i] = vector3_cast(projected) / projected[3];
		}
	}
	(*t) += Vector<float, 3>(1.0f, 1.0f, 0.0f);
	(*t) *= cam.getScale();
}

unsigned int Scene::clip(Triangle& t, const Plane<float>& p, Triangle* out1, Triangle* out2)
{
	Vector<float, 3>* insides[3];
	Vector<float, 3>* outsides[3];
	unsigned int  nInside = 0;
	unsigned int nOutside = 0;

	// Count and sort inside and outside points according to the plane by comparing their signed distance to plane
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
		out1->c = t.c;
		out1->p[0] = *insides[0];
		out1->p[1] = p.getIntersection(Line(*insides[0], *outsides[0]));
		out1->p[2] = p.getIntersection(Line(*insides[0], *outsides[1]));

		return 1;
	}
	if (nInside == 2) {
		out1->c = t.c;
		out1->p[0] = *insides[0];
		out1->p[1] = *insides[1];
		out1->p[2] = p.getIntersection(Line(*insides[0], *outsides[0]));

		out2->c = t.c;
		out2->p[0] = *insides[1];
		out2->p[1] = out1->p[2];
		out2->p[2] = p.getIntersection(Line(*insides[1], *outsides[0]));

		return 2;
	}
}

#endif