/**
@file Bullet.cpp

Implementation of the Bullet class.

Created on: March 2010
*/

#include <windows.h>
#include <gl/gl.h>
#include <glut.h>
#include "Bullet.h"

const float Bullet::DefaultLifeTime = 3;

/**
	Moves the bullet and updates its lifetime.
	*/
void Bullet::Update(float dtSec) {
	//Has the bullet died?
	if(LifeTime < dtSec) {
		LifeTime = 0;
		//don't update
		return; 
	}
	P += dtSec * V;
	LifeTime -= dtSec;
}

/**
Renders the bullet as a sphere whose color changes according to lifetime
(r: 1 -> 0,
 g: 0, 
 b: 0 -> 1).
*/
void Bullet::Render() const {
	glPushMatrix();
		glTranslatef(P.x, P.y, P.z);
		glColor3f(LifeTime/DefaultLifeTime, 0, 1 - LifeTime/DefaultLifeTime);
		glutWireSphere(1, 20, 20);
	glPopMatrix();
}