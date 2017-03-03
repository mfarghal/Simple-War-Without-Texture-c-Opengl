#pragma once

#include "Vector3.h"
#include "AABoundingBox.h"
#include "Bullet.h"
#include "glut.h"

const float EnemySize = 10;

class EnemyBody {

public:
	Vector3 P;
	Vector3 V;
	//float TimeSinceLastFire;
	//float InterBulletTime;
	

	EnemyBody (const Vector3 &pos ,const Vector3 &Vel) {
		P = pos;
		V = Vel;
	
		//TimeSinceLastFire = 0;
		//InterBulletTime = 4;
	}
	/*EnemyBody(const Vector3 &vel ) {
		V = vel;
		
	
		TimeSinceLastFire = 0;
		InterBulletTime = 4;
	}*/


	void Update_pos(float dtTSec) {
		//TimeSinceLastFire += dtSec;
		//v = vel;
		//P.z -= dtSec * V.z;
	   //	enemy[i].p.z-- ;
		P += dtTSec * V;
	}

	AABoundingBox GetAABB() const {
		Vector3 dims(4, 4, 4);
		return AABoundingBox(P, 2*dims);
	}

	void Render() const {
		glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslatef(P.x, P.y, P.z);
			glutWireCone(1,15,15,15);
			//glutWireTeapot(EnemySize);
		glPopMatrix();
	}
	/*
	bool FireReady() const { return TimeSinceLastFire >= InterBulletTime; }

	Bullet ShootAt(const Vector3 &target) {
		Vector3 bulDir = (target - P);
		bulDir.Normalize();
		Bullet bul(P, 40 * bulDir);
		TimeSinceLastFire = 0;
		return bul;
	}*/
};