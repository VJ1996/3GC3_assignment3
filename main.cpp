

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "object.h"

float verts[8][3] = { {-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
float cols[6][3] = { {1,0,0}, {0,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };

float camPos[] = {10, 10, 10};	            //initial camera location
float camUp[] = {0, 1, 0};                  //up vector of the camera
float camTarget[] = {0, 0, 0};	            //point camera is looking at

float light0Pos[] = {5, 5, 5 , 1};          //initial light0 position
float light1Pos[] = {0, 5, 5, 1};           //initial light1 positon


vector<Object*> objects;
Object* currentObject;



int materialType;



 enum ObjectType{ 
	Cube,
	Sphere,
	Cone,
	Torus,
	Teapot
};


/*** 
 EYE LOCATION
 ***/



void keyboard(unsigned char key, int x, int y)
{

	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;
		case '1':
			materialType = 0;
			break;
		case'2':
			materialType = 1;
			break;
		case'3':
			materialType = 2;
			break;
		case'4':
			materialType = 3;
			break;
		case'5':
			materialType = 4;
			break;
		case'6':
		{
			currentObject = new Object();
			currentObject->setObject(0);
			currentObject->setMaterial(materialType);
			objects.push_back(currentObject);
		}
		break;
		case'7':
		{
			currentObject = new Object();
			currentObject->setObject(1);
			currentObject->setMaterial(materialType);
			objects.push_back(currentObject);
			
		}
		break;
		case'8':
		{
			currentObject = new Object();
			currentObject->setObject(2);
			currentObject->setMaterial(materialType);
			objects.push_back(currentObject);
			
		}
		break;
		case'9':
		{
			currentObject = new Object();
			currentObject->setObject(3);
			currentObject->setMaterial(materialType);
			objects.push_back(currentObject);
			
		}
		break;
		case'0':
		{
			currentObject = new Object();
			currentObject->setObject(4);
			currentObject->setMaterial(materialType);
			objects.push_back(currentObject);
			
		}
		break;
		case 'r':
		case 'R':
			objects.clear();

		case 'm':
			currentObject->setMaterial(materialType);
			break;
		case 'a':
		case 'A':
			camPos[0] = camPos[0]*cos(0.03)-camPos[2]*sin(0.03);
			camPos[2] = camPos[0]*sin(0.03)+camPos[2]*cos(0.03);
			break;

		case 'w':
		case 'W':
				camPos[0] -= 0.2;
			break;

		case 'd':
		case 'D':
			camPos[0] = camPos[0]*cos(-0.03)-camPos[2]*sin(-0.03);
			camPos[2] = camPos[0]*sin(-0.03)+camPos[2]*cos(-0.03);
			break;

		case 's':
		case 'S':
				camPos[0] += 0.2;
			break;

			
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{

	

	if(key == GLUT_KEY_LEFT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		light1Pos[0]-=1;
	}
	else if(key == GLUT_KEY_RIGHT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		light1Pos[0]+=1;
	}
	else if(key == GLUT_KEY_UP && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		light1Pos[1] +=1;
	}
	else if(key == GLUT_KEY_DOWN && glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		light1Pos[1]-=1; 
	}

	//Translations
	else if(key == GLUT_KEY_LEFT && glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		if(currentObject!=0)
		{
			currentObject->translate(currentObject->getPX()-0.3,
									currentObject->getPY(), currentObject->getPZ());
		}
	}
	else if(key == GLUT_KEY_RIGHT && glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		if(currentObject!=0)
		{
			currentObject->translate(currentObject->getPX()+0.3,
									currentObject->getPY(), currentObject->getPZ());
		}
	}
	else if(key == GLUT_KEY_UP && glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		if(currentObject!=0){
			currentObject->translate(currentObject->getPX(),
									currentObject->getPY()+0.03, currentObject->getPZ());
		}
	}
	else if(key == GLUT_KEY_DOWN && glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		if(currentObject!=0){
			currentObject->translate(currentObject->getPX(),
									currentObject->getPY()-0.03, currentObject->getPZ());
		}
	}
	else if(key == GLUT_KEY_END && glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		if(currentObject!=0){
			currentObject->translate(currentObject->getPX(),
									currentObject->getPY(), currentObject->getPZ()-0.03);
		}
	}
	else if(key == GLUT_KEY_HOME && glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		if(currentObject!=0){
			currentObject->translate(currentObject->getPX(),
									currentObject->getPY(), currentObject->getPZ()+0.03);
		}
	}

	//Rotations

	else if(key == GLUT_KEY_LEFT && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		if(currentObject!=0)
		{
			currentObject->rotate(currentObject->getRX()-1,currentObject->getRY(), currentObject->getRZ());
		}
	}
	else if(key == GLUT_KEY_RIGHT && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		if(currentObject!=0)
		{
			currentObject->rotate(currentObject->getRX()+1,currentObject->getRY(), currentObject->getRZ());
		}
	}
	else if(key == GLUT_KEY_UP && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		if(currentObject!=0)
		{
			currentObject->rotate(currentObject->getRX(),currentObject->getRY()+1, currentObject->getRZ());
		}
	}
	else if(key == GLUT_KEY_DOWN && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		if(currentObject!=0)
		{
			currentObject->rotate(currentObject->getRX(),currentObject->getRY()-1, currentObject->getRZ());
		}
	}
	else if(key == GLUT_KEY_END && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		if(currentObject!=0)
		{
			currentObject->rotate(currentObject->getRX(),currentObject->getRY(), currentObject->getRZ()-1);
		}
	}
	else if(key == GLUT_KEY_HOME && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		if(currentObject!=0)
		{
			currentObject->rotate(currentObject->getRX(),currentObject->getRY(), currentObject->getRZ()+2);
		}
	}

	//scaling

	else if(key == GLUT_KEY_PAGE_UP)
	{
		if(currentObject!=0 && currentObject->getScale()<30)
		{
			currentObject->scaleObject(currentObject->getScale()+0.2); //scale up
		}
	}
	else if(key == GLUT_KEY_PAGE_DOWN)
	{
		if(currentObject!=0 && currentObject->getScale()>0.05)
		{
			currentObject->scaleObject(currentObject->getScale()-0.2); //scale down
		}
	}

	//Light controls
	else if (key == GLUT_KEY_LEFT)
	{
		light0Pos[0]-=1;
	}
	else if(key == GLUT_KEY_RIGHT)
	{
		light0Pos[0]+=1;
	}
	else if(key == GLUT_KEY_UP)
	{
		light0Pos[1] +=1;
	}
	else if(key == GLUT_KEY_DOWN)
	{
		light0Pos[1] -= 1;
	}

	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{

}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    
    glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	

	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,1,1000);
    /************************************************************************
     
                            PERSPECTIVE SET UP!
     
     modelview moves the eye and objects, projection is for camera type
     frustum / ortho left, right, bottom, top, nearVal, farVal
     
     ************************************************************************/
   materialType = 0;

   glFrontFace(GL_CCW);
   glCullFace(GL_BACK);
   glEnable(GL_CULL_FACE);
}

void drawObject()
{
	for(vector<Object*>::iterator draw=objects.begin(); draw != objects.end(); ++draw)
	{
		Object* objDraw = *draw;
		Object objD = *objDraw;
		objD.drawMaterial();
		glPushMatrix();
		glTranslatef(objD.getPX(), objD.getPY(), objD.getPZ());
		glRotatef(objD.getRY(), 0, 1 , 0);
		glRotatef(objD.getRX(), 1, 0, 0);
		
		glRotatef(objD.getRZ(), 0, 0, 1);
		glColor3f(0.25,0.25,0.25);

		switch(objD.getObject())
		{
			case 0:
				glutSolidCube(objD.getScale());
				break;
			case 1:
				glutSolidSphere(objD.getScale()/2, 100,100);
				break;
			case 2:
				glPushMatrix();
				glTranslatef(0, 0, -objD.getScale()/2);
				glutSolidCone(objD.getScale()/2, objD.getScale(), 32,32);
				glPopMatrix();
				break;
			case 3:
				glPushMatrix();
				glScalef(1,1,3);
				glutSolidTorus(objD.getScale()/3 - objD.getScale()/6, objD.getScale()/3, 32, 32);
				glPopMatrix();
				break;
			case 4:
				glutSolidTeapot(objD.getScale());
				break;
		}
		if(objDraw == currentObject)
		{
			glColor3f(1,0,0);
			if(objD.getObject()== 4)
				glutWireCube(objD.getScale()*2);
			else 	
				glutWireCube(objD.getScale());
			
		}	
		glPopMatrix();
		}
}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	//float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], camTarget[0],camTarget[1],camTarget[2],camUp[0], camUp[1], camUp[2]);

	//set light colours
    float diff0[4] = {1, 1, 1, 1};            //blue light (light0)
    float diff1[4] = {1, 0.1, 0, 1};            //amber light (light1)
    float amb0[4] = {0.2f, 0.2f, 0.2f, 1};
    float amb1[4] = {0.2f, 0.2f, 0.2f, 1};
    float spec0[4] = {0.2f, 0.2f, 0.2f, 1};
    float spec1[4] = {0.2f, 0.2f, 0.2f, 1};

    //set light position and properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);

    //draw sphere for light0
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(light0Pos[0], light0Pos[1], light0Pos[2]);
    glutWireSphere(0.1, 16, 16);
    glPopMatrix();

    //draw sphere for light1
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(light1Pos[0], light1Pos[1], light1Pos[2]);
    glutWireSphere(0.1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0,-1,0);
    glScalef(1,0.01,1);
    glutSolidCube(100);     //draws plane
    glPopMatrix();

   
	glFrontFace(GL_CCW);
	drawObject();
	glFrontFace(GL_CCW);
	 
	
	
	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Modeller.x");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	glEnable(GL_DEPTH_TEST);
	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
