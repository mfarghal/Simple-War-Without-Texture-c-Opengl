#pragma once

#include "Vector3.h"
#include "AABoundingBox.h"
#include "Bullet.h"
#include "glut.h"

class HeroTeapot {
public:
	Vector3 P;
	int teapotSize;

    HeroTeapot(const Vector3 &pos, int size) {
		P = pos;
		teapotSize = size;
	}

	AABoundingBox GetAABB() const {
		Vector3 dims(teapotSize, teapotSize, teapotSize);
		return AABoundingBox(P, 2*dims);
	}

	void Render() const {
		glPushMatrix();
			glColor3f(0, 0, 1);
			glTranslatef(P.x, P.y, P.z);
			glutWireTeapot(teapotSize);
		glPopMatrix();
	}

	Bullet ShootAt(const Vector3 &target) {
		Vector3 bulDir = (target - P);
		bulDir.Normalize();
		Bullet bul(P, 40 * bulDir);
		return bul;
	}
};