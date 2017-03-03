#pragma once

#include "Vector3.h"
#include "AABoundingBox.h"
#include "glut.h"




class wall {
public:
	Vector3 P;

	
	

	EnemyBody(const Vector3 &pos) {
		P = pos;
		
	}

	
	
	AABoundingBox GetAABB() const {
		Vector3 dims=P;
		return AABoundingBox(P, 2*dims);
	}

	void Render() const {
		glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(P.x, P.y, P.z);
			glutSolidCone(5,20,10,10);
		glPopMatrix();
	}

	
};