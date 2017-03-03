#pragma once

#include <glut.h>
#include "Bullet.h"
#include "Vector3.h"

class HealthPacket {
public:
	Vector3 P;
	Vector3 V;

	float HealthValue;

	HealthPacket(const Vector3 &pos, float healthVal ,const Vector3 &vel) {
		P = pos;
		HealthValue = healthVal;
		V = vel;
	}

	void Update_pos(float dtTSec) {
		P += dtTSec * V;
	}

	void Render() const;

	AABoundingBox GetAABB() const;

};