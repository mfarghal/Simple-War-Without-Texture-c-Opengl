#pragma once

#include "EnemyBody.h"
#include "Bullet.h"
#include <windows.h>
#include <vector>
#include "HealthPacket.h"
#include <math.h>
#include "HeroTeapot.h"

using namespace std;

class GameManager {
public:
	vector<Bullet> heroBullets;
	vector<Bullet> enemyBullets;
	
	vector<EnemyBody> enemyBodies;
	vector<HealthPacket> healthPCs;
	
	HeroTeapot hero;

	int heroHealth; //0 -> 100
	int heroScore;
	bool gameOver;
	
	GameManager() : hero(Vector3(0,0,10), 10)
	{}
	/**
	Returns a random real number betn min and max.
	*/
	static float RandFloat(float min, float max) {
		return rand()/((double)RAND_MAX + 1) * (max - min) + min;
	}

	void Reset(const Vector3 &heroPos, int teapotSize, size_t numEnemies, const Vector3 &minPos, const Vector3 &maxPos, const Vector3 &minV, const Vector3 &maxV);

	Vector3 GetHeroPos() const {
		return hero.P;
	}

	
	void HandleCollisions();

	void Update(float dtSec);


	
	////////////////////////////////////////////////////////////////////////////
    void regenerate(EnemyBody &EB);
	
	void HeroShoot() {
		if(gameOver) return;
		Bullet hb(hero.P, Vector3(0,0,-30)); //hero bullet will go over the -ve z axis
		
		heroBullets.push_back(hb);
	}

	void Render() const;
	
};
