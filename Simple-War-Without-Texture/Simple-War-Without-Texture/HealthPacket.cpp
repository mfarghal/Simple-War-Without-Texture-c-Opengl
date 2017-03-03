#pragma once

#include "HealthPacket.h"


	void HealthPacket::Render() const {
		glPushMatrix();
			glTranslatef(P.x, P.y, P.z);
			glColor3f(1, 1, 0);
			//glutSolidCube(10);
			glutSolidSphere(2,1000 ,10);
		glPopMatrix();
	}

	AABoundingBox HealthPacket::GetAABB() const {
		return AABoundingBox(P, Vector3(10, 10, 10));
	}
	