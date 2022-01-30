#include "XAble.h"

Movable::Movable()
	: _pos(Vector<float, 3>())
{
}

Movable::Movable(Vector<float, 3>& pos)
	: _pos(pos)
{
}
Vector<float, 3> Movable::getPos() const
{
	return _pos;
}

void Movable::setPos(const Vector<float, 3>& pos)
{
	_pos = pos;
}

void Movable::move(const Vector<float, 3>& translation)
{
	_pos += translation;
}

void Movable::moveX(float translation)
{
	_pos[0] += translation;
}

void Movable::moveY(float translation)
{
	_pos[1] += translation;
}

void Movable::moveZ(float translation)
{
	_pos[2] += translation;
}



Directable::Directable()
	: _pitch(0.0f), _yaw(0.0f), _roll(0.0f), _forward(Vector<float, 3>(0.0f, 0.0f, 1.0f)), _right(Vector<float, 3>(1.0f, 0.0f, 0.0f)), _down(Vector<float, 3>(0.0f, 1.0f, 0.0f))
{
}

Directable::Directable(float pitch, float yaw, float roll)
	: _pitch(pitch), _yaw(yaw), _roll(roll)
{
	updateLocalAxes();
}

void Directable::lookAt(Vector<float, 3>& dir)
{
	Quaternion<float> rot = Quaternion<float>::setLookAtQuaternion(dir, _down);

	_pitch = rot.pitch();
	_yaw = rot.yaw();
	_roll = rot.roll();
	updateLocalAxes();
}

Vector<float, 3> Directable::getForward() const
{
	return _forward;
}

Vector<float, 3> Directable::getRight() const
{
	return _right;
}

Vector<float, 3> Directable::getDown() const
{
	return _down;
}

void Directable::updateLocalAxes()
{
	// Axes are circularly reversed (x, y, z) -> (z, x, y)
	_forward = Vector<float, 3>(
		-sin(_yaw) * cos(_pitch),
		-sin(_pitch),
		cos(_yaw) * cos(_pitch));

	_right = Vector<float, 3>(
		-sin(_yaw) * sin(_pitch) * sin(_roll) + cos(_yaw) * cos(_roll),
		cos(_pitch) * sin(_roll),
		cos(_yaw) * sin(_pitch) * sin(_roll) + sin(_yaw) * cos(_roll));

	_down = _forward.cross_product(_right);
}


void Directable::setPitch(float pitch)
{
	_pitch = fmod(pitch, 2*PI);
	updateLocalAxes();
}

void Directable::setYaw(float yaw)
{
	_yaw = fmod(yaw, 2*PI);
	updateLocalAxes();
}

void Directable::setRoll(float roll)
{
	_roll = fmod(roll, 2*PI);
	updateLocalAxes();
}

void Directable::offsetPitch(float pitch)
{
	_pitch += pitch;
	_pitch = fmod(_pitch, 2*PI);
	updateLocalAxes();
}

void Directable::offsetYaw(float yaw)
{
	_yaw += yaw;
	_yaw = fmod(_yaw, 2*PI);
	updateLocalAxes();
}

void Directable::offsetRoll(float roll)
{
	_roll += roll;
	_roll = fmod(_roll, 2*PI);
	updateLocalAxes();
}

float Directable::pitch() const
{
	return _pitch;
}

float Directable::yaw() const
{
	return _yaw;

}

float Directable::roll() const
{
	return _roll;

}

Quaternion<float> Directable::getRotationQuat() const
{
	return Quaternion<float>::getRotationQuaternion(_pitch, _yaw, _roll);
}

Matrix<float, 4, 4> Directable::getRotationMatrix() const
{
	Matrix<float, 4, 4> rot;

	rot(0, 0) = _right[0];
	rot(0, 1) = _right[1];
	rot(0, 2) = _right[2];

	rot(1, 0) = _down[0];
	rot(1, 1) = _down[1];
	rot(1, 2) = _down[2];

	rot(2, 0) = _forward[0];
	rot(2, 1) = _forward[1];
	rot(2, 2) = _forward[2];

	rot(3, 3) = 1.0f;

	return rot;
}
