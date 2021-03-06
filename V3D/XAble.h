#ifndef XABLE_H
#define XABLE_H
#pragma once

#include "Vector.h"
#include "Quaternion.h"

class Movable
{
public:
	Movable();
	Movable(Vector<float, 3>& pos);

	Vector<float, 3> getPos() const;
	void setPos(const Vector<float, 3>& pos);

	void move(const Vector<float, 3>& translation);

	void moveX(float translation);
	void moveY(float translation);
	void moveZ(float translation);


protected:
	Vector<float, 3> _pos;

};

class Directable
{
public:
	Directable();
	Directable(float pitch, float yaw, float roll);

	void lookAt(Vector<float, 3>& dir);

	Vector<float, 3> getForward() const;
	Vector<float, 3> getRight() const;
	Vector<float, 3> getDown() const;

	void updateLocalAxes();

	void setPitch(float pitch);
	void setYaw(float yaw);
	void setRoll(float roll);

	void offsetPitch(float pitch);
	void offsetYaw(float yaw);
	void offsetRoll(float roll);

	float pitch() const;
	float yaw() const;
	float roll() const;

	Quaternion<float> getRotationQuat() const;
	Matrix<float, 4, 4> getRotationMatrix() const;
protected:
	float _pitch, _yaw, _roll;
	Vector<float, 3> _forward, _right, _down;
};
#endif // !XABLE_H

