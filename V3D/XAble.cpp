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

void Movable::setPos(Vector<float, 3>& pos)
{
	_pos = pos;
}

void Movable::move(Vector<float, 3>& translation)
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
	: _pitch(0.0f), _yaw(0.0f), _roll(0.0f)
{
}

Directable::Directable(float pitch, float yaw, float roll)
	: _pitch(pitch), _yaw(yaw), _roll(roll)
{
}

void Directable::lookAt(Vector<float, 3>& dir)
{
	Vector<float, 3> up(0.0f, 1.0f, 0.0f);
	Quaternion<float> rot = Quaternion<float>::lookAtQuaternion(dir, up);

	_pitch = rot.pitch();
	_yaw = rot.yaw();
	_roll = rot.roll();
}

Vector<float, 3> Directable::getDirection() const
{
	return Vector<float, 3>(
		-sin(_pitch),
		sin(_yaw) * cos(_pitch),
		-cos(_yaw) * cos(_pitch));
}

void Directable::setPitch(float pitch)
{
	_pitch = fmod(pitch, 2*PI);
}

void Directable::setYaw(float yaw)
{
	_yaw = fmod(yaw, 2*PI);
}

void Directable::setRoll(float roll)
{
	_roll = fmod(roll, 2*PI);
}

void Directable::offsetPitch(float pitch)
{
	_pitch += pitch;
	_pitch = fmod(_pitch, 2*PI);
}

void Directable::offsetYaw(float yaw)
{
	_yaw += yaw;
	_yaw = fmod(_yaw, 2*PI);
}

void Directable::offsetRoll(float roll)
{
	_roll += roll;
	_roll = fmod(_roll, 2*PI);
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
	return Quaternion<float>::getRotationMatrix(_pitch, _yaw, _roll);
}
