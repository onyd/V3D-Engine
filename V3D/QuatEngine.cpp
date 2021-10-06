#define OLC_PGE_APPLICATION
#include "QuatEngine.h"


V3DQEngine::V3DQEngine()
{
	sAppName = "V3D";
}

bool V3DQEngine::OnUserCreate()
{
	// Load objects
	Vector<float, 3> obj_pos = Vector<float, 3>(1.0f, 0.0f, 5.1f);
	o = Object(obj_pos, "teapot.obj");
	
	// Scene
	Vector<float, 3> c_pos(0.0f, 0.0f, 0.0f);
	float Zn = 0.01f;
	float Zf = 1000.0f;
	float fov = 90.0f;
	float w = (float)ScreenWidth();
	float h = (float)ScreenHeight();
	Camera camera = Camera(c_pos, Zn, Zf, fov, w, h);

	Vector<float, 3> light_dir(0.0f, 0.0f, -1.0f);
	l = Light(light_dir);

	scene = Scene(camera);
	scene.add_object(&o);
	scene.add_light(&l);

	// Debug planes
	float F = 1.0f / tanf(radian(fov / 2.0f));
	float a = h / w;
	float c = cosf(fov / 2.0f);
	float s = sinf(fov / 2.0f);
	Plane<float> topPlane(Vector<float, 3>(0.0f, c, s), Vector<float, 3>(0.0f, -Zn / F, 0.0f));
	Plane<float> botPlane(Vector<float, 3>(0.0f, -c, s), Vector<float, 3>(0.0f, Zn / F, 0.0f));
	Plane<float> leftPlane(Vector<float, 3>(c, 0.0f, s), Vector<float, 3>(-Zn / (a * F), 0.0f, 0.0f));
	Plane<float> rightPlane(Vector<float, 3>(-c, 0.0f, s), Vector<float, 3>(Zn / (a * F), 0.0f, 0.0f));
	
	Vector<float, 3> up(0.0f, -1.0f, 0.0f);
	scene.add_object(new PlaneObject(topPlane, Vector<float, 3>(0.0f, -Zn / F, 0.0f), up, 5.0f, 5.0f));
	scene.add_object(new PlaneObject(leftPlane, Vector<float, 3>(-Zn / (a * F), 0.0f, 0.0f), up, 5.0f, 5.0f));

	//o.offsetPitch(PI / 4);
	//o.offsetRoll(PI / 4);
	
	return true;
}

bool V3DQEngine::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::BLACK);
	
	if (GetKey(olc::Key::UP).bHeld) 
		scene.getCamera().offsetPitch(-2.0f * fElapsedTime);
	if (GetKey(olc::Key::DOWN).bHeld)
		scene.getCamera().offsetPitch(2.0f * fElapsedTime);
	if (GetKey(olc::Key::LEFT).bHeld)
		scene.getCamera().offsetYaw(2.0f * fElapsedTime);
	if (GetKey(olc::Key::RIGHT).bHeld)
		scene.getCamera().offsetYaw(-2.0f * fElapsedTime);

	if (GetKey(olc::Key::Z).bHeld)
		scene.getCamera().moveZ(2.0f * fElapsedTime);
	if (GetKey(olc::Key::S).bHeld)
		scene.getCamera().moveZ(-2.0f * fElapsedTime);
	if (GetKey(olc::Key::Q).bHeld)
		scene.getCamera().moveX(-2.0f * fElapsedTime);
	if (GetKey(olc::Key::D).bHeld)
		scene.getCamera().moveX(2.0f * fElapsedTime);

	//o.offsetYaw(0.001f);
	//o.offsetRoll(0.005f);

	for (Triangle* t : scene.render()) {
		FillTriangle(t->p[0][0], t->p[0][1],
			t->p[1][0], t->p[1][1],
			t->p[2][0], t->p[2][1], t->c);
		delete t;
	}
	return true;
}

