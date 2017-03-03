#include <windows.h>
#include <gl/gl.h>
#include "glut.h"
#include <ctime>
#include <cstdio>
#include <vector>

#include "GameManager.h"

using namespace std;
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

/*** Global Variables ***/
UINT prevFrameTime = 0;

GameManager game;

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char *argv[]);

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 800.0/800, 0.25, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //CT <- I
	//CT <- V
	gluLookAt( 
		//eye position
		1, 20, 100,
		//look at point
		0, 0, 0,
		//up dir
		0, 1, 0);
}

void OnKeyboard(unsigned char c, int x, int y) {
	float step = 2;
	switch(toupper(c))
	{
	case ' ':
		//bullets.push_back(Bullet(camera.P, 25 * camera.GetLookDirection()));
		game.HeroShoot();
		break;
	}
}

void OnSpecial(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP: //move forward
			game.hero.P.z--;
		break;
		case GLUT_KEY_DOWN: //move backward
			game.hero.P.z++;
		break;
		case GLUT_KEY_LEFT: //move left
			game.hero.P.x--;
		break;
		case GLUT_KEY_RIGHT: //move right
			game.hero.P.x++;
		break;
	}
}

void Update()
{
	UINT currTime = timeGetTime();
	//the first update?
	if(prevFrameTime == 0) {
		prevFrameTime = currTime;
		return;
	}
	//interframe time (in seconds)
	float dt = (currTime - prevFrameTime)/1000.0;

	//Write all update code here.	
	prevFrameTime = currTime;
	game.Update(dt);

	//Display health, score, fps
	char titleStr[512];
	sprintf(titleStr, "Health: %d, Score: %d, fps: %f", game.heroHealth, game.heroScore, 1/dt);
	glutSetWindowTitle(titleStr);
}
float spotAngle = 0;
void SetLights() 
{
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0); 
	//color properties 
	float light0_diffuse[4] = { 1, 1, 1, 1 }; 
	float light0_ambient[4] = { 0.15f, 0.15f, 0.15f, 1 }; 
	float light0_specular[4] = { 1, 1, 1, 1 }; 
	//other properties 
	float light0_pos[4] = { -25, 5, 60, 1 }; 
	//w=1 --> not directional
	float light0_spot_cutoff = 30;
	float light0_spot_direction[3] = { 1, 0, -1 }; 
	float light0_spot_exponent = 5; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0_ambient); 
	//pass OpenGL the light source color values 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	//spot light properties 
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light0_spot_cutoff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, light0_spot_exponent);
	//Similar to primitive rendering, the light positions and 
	//directions are multiplied by the model-view transformation
	//(but no projection). So, we can animate light sources as well!
	glPushMatrix(); 
	{
		//let the spot light source "yaw" about itself 
		glRotatef(spotAngle, 0, 1, 0);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_pos); 
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_spot_direction);
	}
	glPopMatrix(); 
}
void SetMaterial() 
{ 
	/** * We want to make objects to look red. So, 
	the diffuse of the material must be * set to red. 
	We want the objects to be shiny. 
	So, we set the material's specular * 
	color to r = g = b = high value, and set its shininess to a high value less * than or equal to 128. 
	We do not want emission. So, we set to black. **/ 
	//red material -> diffuse = red 
	float mat0_diffuse[4] = { 1, 1, 0, 1 }; 
	//Naturally, the material reflects the same amount of incident light, either it is 
	//direct light (diffuse) or background light (ambient). So, we usually take 
	//the ambient = the diffuse of the material 
	float mat0_ambient[4] = { 1, 1, 0, 1 }; 
	//Naturally, the specular of the material is a shade(scale) of white. r = g = b = const 
	//If the material is shiny, const -> 1. If the material is dull, const -> 0. 
	float mat0_specular[4] = { 0, 1, 0, 1 }; 
	float mat0_shininess = 100; 
	float mat0_emission[4] = { 0, 0, 0, 1 }; 
	//ambient of the material usually equals its diffuse 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat0_diffuse); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat0_diffuse); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0_ambient); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat0_specular); 
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat0_shininess); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat0_emission);
}
void RenderScene() 
{ 
	SetMaterial(); 
	//render solid teapot: far left corner 
	glPushMatrix(); 
	game.Render();
	glPopMatrix(); 
}

void OnDisplay() {
	//set the background color to white
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SetTransformations();
	SetLights(); 
	RenderScene();
	//drawing code geos here
	game.Render();

	glFlush();
	glutSwapBuffers();
	Update();
	glutPostRedisplay();
}


int main(int argc, char* argv[]) {
	timeBeginPeriod(1);
	InitGraphics(argc, argv);
	timeEndPeriod(1);
	return 0;
}

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(800, 800);
	glutCreateWindow("OpenGL Lab");
	glutKeyboardFunc(OnKeyboard);
	glutSpecialFunc(OnSpecial);
	glutDisplayFunc(OnDisplay);

	glEnable(GL_DEPTH_TEST);

	//Reset the hero position, hero size, number of enemies, minimum position for enemies and maximum position for enemies
	game.Reset(Vector3(0,0,0) , 10, 5, Vector3(-50, 0, -30), Vector3(50, 0, -150),Vector3(0,0 , 30), Vector3(0, 0, 50));
	glutMainLoop();
}

