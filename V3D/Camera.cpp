#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "Camera.h"

Camera::Camera(Vector<float, 3>& pos, float Zn, float Zf, float fov, float width, float height)
	: Movable(pos), Directable(), _width(width), _height(height)
{
	this->setup(Zn, Zf, fov, height / width);
}

Matrix<float, 4, 4> Camera::getViewMatrix() const
{
	Matrix<float, 4, 4> rotation = this->getRotationMatrix();
	rotation.transpose();

	Matrix<float, 4, 4> translation = identityMatrix<float, 4>();
	translation(3, 0) = -_pos[0];
	translation(3, 1) = -_pos[1];
	translation(3, 2) = -_pos[2];
	return translation.matmul(rotation);
}

Matrix<float, 4, 4> Camera::getProjectionMatrix() const
{
	return _projection_mat;
}

Vector<float, 3> Camera::getScale() const
{
	return Vector<float, 3>(0.5f*_width, 0.5f*_height, 1.0f);
}

Plane<float> Camera::getEyePlane() const
{
	return _eyePlane;
}

float Camera::getHeight() const
{
	return _height;
}

float Camera::getWidth() const
{
	return _width;
}

Plane<float> Camera::getTopPlane() const
{
	return _topPlane;
}

Plane<float> Camera::getBotPlane() const
{
	return _botPlane;
}

Plane<float> Camera::getLeftPlane() const
{
	return _leftPlane;
}

Plane<float> Camera::getRightPlane() const
{
	return _rightPlane;
}

void Camera::setup(float Zn, float Zf, float fov, float aspect_ratio)
{
	// Build projection matrix
	float F = 1.0f / tanf(radian(fov / 2.0f));
	float q = Zn / (Zf - Zn);

	Matrix<float, 4, 4> projection_mat;

	projection_mat(0, 0) = aspect_ratio * F;
	projection_mat(1, 1) = F;
	projection_mat(2, 2) = q;
	projection_mat(2, 3) = 1.0f;
	projection_mat(3, 2) = -Zf * q;

	_projection_mat = projection_mat;

	float c = cosf(fov / 2.0f);
	float s = sinf(fov / 2.0f);
	// Build boundaries	
	_topPlane = Plane<float>(Vector<float, 3>(0.0f, c, s), Vector<float, 3>(0.0f, -Zn / F, 0.0f));
	_botPlane = Plane<float>(Vector<float, 3>(0.0f, -c, s), Vector<float, 3>(0.0f, Zn / F, 0.0f));
	_leftPlane = Plane<float>(Vector<float, 3>(c, 0.0f, s), Vector<float, 3>(-Zn / (aspect_ratio * F), 0.0f, 0.0f));
	_rightPlane = Plane<float>(Vector<float, 3>(-c, 0.0f, s), Vector<float, 3>(Zn / (aspect_ratio * F), 0.0f, 0.0f));
	_eyePlane = Plane<float>(Vector<float, 3>(0.0f, 0.0f, 1.0f), Vector<float, 3>(0.0f, 0.0f, Zn));

}

#endif