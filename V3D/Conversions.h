#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#pragma once

#include "Constants.h"

template<class dtype>
dtype radian(dtype angle) {
	return angle / static_cast<dtype>(180) * static_cast<dtype>(PI);
}

#endif // !CONVERSIONS_H
