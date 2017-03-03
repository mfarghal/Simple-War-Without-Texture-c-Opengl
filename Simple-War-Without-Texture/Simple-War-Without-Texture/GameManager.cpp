#include <cstdlib>

#include "GameManager.h"
using namespace std;


void GameManager::Reset(const Vector3 &heroPos, int teapotSize, size_t numEnemies, const Vector3 &minPos, const Vector3 &maxPos, const Vector3 &minV, const Vector3 &maxV) {
	hero.P = heroPos;
	
	//calling enemyBodies.reserve(numEnemies); increases efficiency
	for(int i=0; i<numEnemies; i++) {
		Vector3 enemyPos(RandFloat(minPos.x, maxPos.x),
						 0,
						 RandFloat(minPos.z, maxPos.z));
	//	Vector3 enemyvel;
		Vector3 enemyV(RandFloat(minV.x, maxV.x),  RandFloat(minV.x, maxV.x), RandFloat(minV.z, maxV.z));
		enemyBodies.push_back(EnemyBody(enemyPos,enemyV ));
	}
	gameOver = false;
	heroScore = 0;
	heroHealth = 100;
	heroBullets.clear();
	//enemyBullets.clear();
	healthPCs.clear();
}

////////////////////////////////////////
void GameManager::regenerate(EnemyBody &EB)
{
	//TODO: Check the collision between boxes and the walls.
	
			EB.P.Set(RandFloat(-10,10),0,RandFloat(-300,0));
	}

/////////////////////////////////////////////

void GameManager::HandleCollisions() {
		AABoundingBox heroBox(GetHeroPos(), Vector3(10, 10, 10));
	//check hero collision with health packets
	size_t numPCs = healthPCs.size();
	for(int i=numPCs-1; i>=0; i--) {
		AABoundingBox hpBox = healthPCs[i].GetAABB();
		if(hpBox.IntersectsWith(heroBox)) {
			heroHealth = min(heroHealth + healthPCs[i].HealthValue, 100);
			healthPCs.erase(healthPCs.begin() + i);
		}
	}




	//check collision: hero bullets with enemies
	size_t nEnems = enemyBodies.size();
	for(int enemInd = nEnems-1; enemInd>=0; enemInd--) {
		AABoundingBox enemBox = enemyBodies[enemInd].GetAABB();
		size_t nBulls = heroBullets.size();
		for(int bullInd = nBulls-1; bullInd>=0; bullInd--) {
			if(heroBullets[bullInd].GetAABB().IntersectsWith(enemBox)) {
				healthPCs.push_back(HealthPacket(enemBox.Center, 20,enemyBodies[enemInd].V));
				heroBullets.erase(heroBullets.begin() + bullInd);
				//enemyBodies.erase(enemyBodies.begin() + enemInd);
				regenerate(enemyBodies[enemInd]);
				heroScore += 100;
				break;
			}
		}
	}

	//////////////////
	AABoundingBox hero_box=hero.GetAABB();
	for(int i=0;i<enemyBodies.size();i++)
	{
		if(enemyBodies[i].GetAABB().IntersectsWith(hero_box))
		{
			heroHealth-=20;
			regenerate(enemyBodies[i]);

		}
	}


	for(int i=0;i<enemyBodies.size();i++)
	{
		if (enemyBodies[i].P.z>hero.P.z+30)
		{
			regenerate(enemyBodies[i]);
			

		}
	}
	
	/////////////////
/*	//check collision: enemy bullets with hero
	size_t enemyBullCount = enemyBullets.size();
	for(int bInd = enemyBullCount-1; bInd>=0; bInd--) 
		if(enemyBullets[bInd].GetAABB().IntersectsWith(heroBox)) {
			heroHealth = max(heroHealth - 20, 0);
			enemyBullets.erase(enemyBullets.begin() + bInd);
			//if(heroHealth == 0) gameOver = true;
		}
}*/
}
  void GameManager::Update(float dtSec) {
	if(gameOver) return;
	HandleCollisions();
	//update bullets
	size_t nb = heroBullets.size();
	for(int b=nb-1; b>=0; b--) {
		heroBullets[b].Update(dtSec);
		if(heroBullets[b].HasExpired())
			heroBullets.erase(heroBullets.begin() + b);
	}
	for(int i=0; i<healthPCs.size(); i++) {
		healthPCs[i].Update_pos(dtSec);
	
	}
	for(int e=0; e<enemyBodies.size(); e++) {
		enemyBodies[e].Update_pos(dtSec);
		
	} 
}


	/*
	nb = enemyBullets.size();
	for(int b=nb-1; b>=0; b--) {
		enemyBullets[b].Update(dtSec);
		if(enemyBullets[b].HasExpired())
			enemyBullets.erase(enemyBullets.begin() + b);
	}
	*/
	//let EBs fire bullets
/*	size_t ne = enemyBodies.size();
	for(int e=0; e<ne; e++) {
		enemyBodies[e].Update(dtSec);
		if(enemyBodies[e].FireReady())
			enemyBullets.push_back(enemyBodies[e].ShootAt(hero.P));
	}


}*/


void GameManager::Render() const {
	//draw Hero
	hero.Render();

	//draw enemies
	size_t ne = enemyBodies.size();
	for(int e=0; e<ne; e++)
		enemyBodies[e].Render();

	size_t nb = heroBullets.size();
	for(int b=0; b<nb; b++)
		heroBullets[b].Render();

	nb = enemyBullets.size();
	for(int b=0; b<nb; b++)
	 enemyBullets[b].Render();

	//draw health pcs
	size_t nh = healthPCs.size();
	for(int h=0; h<nh; h++)
		healthPCs[h].Render();
}

