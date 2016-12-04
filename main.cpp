

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#  include <GL/glut.h>
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

int mX;
int mY;

int width = 0;
int height = 0;
int k;

GLubyte *image;

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
void drawTex()
{
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


GLubyte* LoadPPM(char* file, int* width, int* height, int* max)
{
	GLubyte* img;
	FILE *fd;
	int n, m;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;
	
	/* first open file and check if it's an ASCII PPM (indicated by P3 at the start) */
	fd = fopen(file, "r");
	fscanf(fd,"%[^\n] ",b);
	if(b[0]!='P'|| b[1] != '3')
	{
		printf("%s is not a PPM file!\n",file); 
		exit(0);
	}
	printf("%s is a PPM file\n", file);
	fscanf(fd, "%c",&c);

	/* next, skip past the comments - any line starting with #*/
	while(c == '#') 
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd); 

	/* now get the dimensions and max colour value from the image */
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	/* calculate number of pixels and allocate storage for this */
	nm = n*m;
	img = (GLubyte*) malloc(3*sizeof(GLuint)*nm);
	s=255.0/k;

	/* for every pixel, grab the read green and blue values, storing them in the image data array */
	for(i=0;i<nm;i++) 
	{
		fscanf(fd,"%d %d %d",&red, &green, &blue );
		img[3*nm-3*i-3]=red*s;
		img[3*nm-3*i-2]=green*s;
		img[3*nm-3*i-1]=blue*s;
	}

	/* finally, set the "return parameters" (width, height, max) and return the image array */
	*width = n;
	*height = m;
	*max = k;

	return img;
}
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
			//camPos[0] += 1;
			camPos[0] += 1;
			break;

		case 'w':
		case 'W':
				camPos[2] -= 0.2;
			break;

		case 'd':
		case 'D':
			//camPos[0] -= 1;
			camPos[0] -=1;
			break;

		case 's':
		case 'S':
				camPos[2] += 0.2;
			break;

		case 't':
			image = LoadPPM("interface.ppm", &width, &height, &k);
			drawTex();
			break;
		case 'y':
			glDisable(GL_TEXTURE_2D);
			
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

bool CalcIntersections(Object* object) //Literally all of this was from the lecture code
{									   //Except for the extra X and Y arrays needed for the ray
									   //THANK YOU BASED THOMAS FOR MAKING IT MUCH EASIER THAN IT HAS TO BE
	GLdouble R0[3], R1[3], Rd[3]; 
	GLdouble modelMat[16], projMat[16];
	GLint viewMat[4];

	glGetDoublev( GL_MODELVIEW_MATRIX, modelMat);
	glGetDoublev(GL_PROJECTION_MATRIX, projMat);
	glGetIntegerv(GL_VIEWPORT, viewMat);

	//double winX = (double)mX;
	//double winY = viewport[3] - double(mY);

	gluUnProject(mX, mY, 0.0, modelMat, projMat, 
				viewMat, &R0[0], &R0[1], &R0[2]);
			
	gluUnProject(mX, mY, 1.0, modelMat, projMat,
				viewMat, &R1[0], &R1[1], &R1[2]);

	Rd[0] = R1[0] - R0[0];
	Rd[1] = R1[1] - R0[1];
	Rd[2] = R1[2] - R0[2];

	GLdouble m = sqrt(Rd[0]*Rd[0] + Rd[1]*Rd[1] + Rd[2]*Rd[2]);
	Rd[0] /=m;
	Rd[1] /=m;
	Rd[2] /=m;

	float tX = (((double)object->getPX()) - R0[0]/Rd[0]);
	float tY = (((double)object->getPY()) - R0[1]/Rd[1]);
	float tZ = (((double)object->getPZ()) - R0[2]/Rd[2]);

	double ptX[3];
	double ptY[3];
	double ptZ[3];

	ptX[0] = object->getPX();
	ptX[1] = R0[1] + tX*Rd[1];
	ptX[2] = R0[2] + tX*Rd[2];

	ptY[0] = R0[0] + tY*Rd[0];
	ptY[1] = object->getPY();
	ptY[2] = R0[2] + tY*Rd[2];

	ptZ[0] = R0[0] + tZ*Rd[0];
	ptZ[1] = R0[1] + tZ*Rd[1];
	ptZ[2] = object->getPZ();

	double pX = (double)object->getPX();
	double pY = (double)object->getPY();
	double pZ = (double)object->getPZ();
	double offset = (double)object->getScale()/1.5;

	if(ptX[0] > pX - offset && ptX[0] < pX + offset &&
		ptX[1] > pY - offset && ptX[1] < pY + offset &&
		ptX[2] > pZ - offset && ptX[2] < pZ + offset)
		{
			return true;
		}
	if(ptY[0] > pX - offset && ptY[0] < pX + offset &&
		ptY[1] > pY - offset && ptY[1] < pY + offset &&
		ptY[2] > pZ - offset && ptY[2] < pZ + offset)
		{
			return true;
		}
	if(ptZ[0] > pX - offset && ptZ[0] < pX + offset &&
		ptZ[1] > pY - offset && ptZ[1] < pY + offset &&
		ptZ[2] > pZ - offset && ptZ[2] < pZ + offset)
		{
			return true;
		}
	return false;
}

void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mX = x;
		mY = 800 - y;
		for(vector<Object*>::iterator current=objects.begin(); current!=objects.end(); ++current)
		{
			if (CalcIntersections(*current))
			{
				currentObject = *current;
			}
		}
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mX = x;
		mY = 800-y;
		
		for(vector<Object*>::iterator current=objects.begin(); current!=objects.end();++current)
		{
			if (CalcIntersections(*current))
			{
				currentObject =*current;
				//objects.erase();
			}
			
		}
		objects.erase(std::remove(objects.begin(), objects.end(), currentObject), objects.end());	
	}
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
    
    glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	
	glRasterPos2i(width,0);
	glPixelZoom(-1, 1);
	glDrawPixels(width,height,GL_RGB, GL_UNSIGNED_BYTE, image);

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
		float scale = objD.getScale();
		switch(objD.getObject())
		{
			case 0:
				glutSolidCube(scale);
				break;
			case 1:
				glutSolidSphere(scale/2, 100,100);
				break;
			case 2:
				glPushMatrix();
				glTranslatef(0, 0, -scale/2);
				glutSolidCone(scale/2, scale, 32,32);
				glPopMatrix();
				break;
			case 3:
				glPushMatrix();
				glScalef(1,1,3);
				glutSolidTorus(scale/3 - scale/6,scale/3, 32, 32);
				glPopMatrix();
				break;
			case 4:
				glutSolidTeapot(scale);
				break;
		}
		if(objDraw == currentObject)
		{
			glColor3f(1,0,0);
			if(objD.getObject()== 4)
				glutWireCube(scale*2);
			else 	
				glutWireCube(scale);
			
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


    float diff0[4] = {1, 1, 1, 1};            
    float amb0[4] = {0.8f, 0.1f, 0.2f, 1};
	float spec0[4] = {0.1f, 0.1f, 0.2f, 1};
	
	float diff1[4] = {1, 0.1, 0, 1};  
    float amb1[4] = {0.3f, 0.5f, 0.1f, 1};
    float spec1[4] = {0.7f, 0.1f, 0.1f, 1};

   
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
	 glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);

    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(light0Pos[0], light0Pos[1], light0Pos[2]);
    glutWireSphere(0.1, 16, 16);
    glPopMatrix();


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

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	drawObject();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
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

