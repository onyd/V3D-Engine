//#ifndef ENGINE_H
//#define ENGINE_H
//#pragma once
//
//#include "Vector.h"
//#include "Matrix.h"
//#include "Quaternion.h"
//
//struct Triangle {
//	Vector<float, 4> p[3];
//}; 
//
//struct Mesh {
//	vector<Triangle> t;
//};
//
//
//class V3DEngine : public olc::PixelGameEngine
//{
//public:
//	V3DEngine();
//	bool OnUserCreate() override;
//	bool OnUserUpdate(float fElapsedTime) override;
//private:
//	void projectVector(Vector<float, 4>& v, Vector<float, 4>& output);
//
//
//	Matrix<float, 4, 4> getRotationX(float thetaX);
//
//	Matrix<float, 4, 4> getRotationY(float thetaY);
//
//	Matrix<float, 4, 4> getRotationZ(float thetaZ);
//
//
//private:
//	Mesh cube;
//	Matrix<float, 4, 4> projection_matrix;
//	float theta;
//
//	Vector<float, 4> translation;
//	Vector<float, 4> offset;
//	Vector<float, 4> scale;
//
//};
//
//#endif 
