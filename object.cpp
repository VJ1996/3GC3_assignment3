#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "object.h"
#include <vector>


int id;
int type;


Object::Object()
{

	this->pX = 0;
	this->pY = 0;
	this->pZ = 0;

	this->rX = 0;
	this->rY = 0;
	this->rZ = 0;

	scale=1;

	float m_amb[3];
	float m_diff[3];
	float m_spec[3];
	float shiny;
	
}

Object::Object(float pX,float pY,float pZ, float rX, float rY, float rZ, float sX, float sY, float sZ, int type)
{
	this->pX = pX;
	this->pY = pY;
	this->pZ = pZ;

	this->rX = rX;
	this->rY = rY;
	this->rZ = rZ;

	this->scale = scale;
}

void Object::translate(float pX, float pY, float pZ)
{
	this->pX += pX;
	this->pY += pY;
	this->pZ += pZ;
}

void Object::rotate(float rX, float rY, float rZ)
{
	this->rX = rX;
	this->rY = rY;
	this->rZ = rZ;

}

void Object::scaleObject(float scale)
{
	
	this->scale = scale;
}

float Object::getScale()
{
	return scale;
}

float Object::getRX()
{
	return rX;
}

float Object::getRY()
{
	return rY;
}

float Object::getRZ()
{
	return rZ;
}

float Object::getPX()
{
	return pX;
}

float Object::getPY()
{
	return pY;
}

float Object::getPZ()
{
	return pZ;
}

void Object::setMaterial(int mat)
{
	switch(mat)
	{
	case 0:		
		m_amb[0] = 0.24725;
		m_amb[1] = 0.1995;
		m_amb[2] = 0.0745;
		m_diff[0] = 0.75164;
		m_diff[1] = 0.60648;
		m_diff[2] = 0.22648;
		m_spec[0] = 0.628281;
		m_spec[1] = 0.555802;
		m_spec[2] = 0.366065;
		shiny = 04;
		break;
	case 1:
		m_amb[0]  = 0.19225;
		m_amb[1] = 0.19225;
		m_amb[2] = 0.19225;
		m_diff[0] = 0.50754;
		m_diff[1] = 0.50754;
		m_diff[2] = 0.50754;
		m_spec[0] = 0.508273;
		m_spec[1] = 0.508273;
		m_spec[2] = 0.508273;
		shiny = 0.4;
	case 2:
		m_amb[0] = 0.25;
		m_amb[1] = 0.25;
		m_amb[2] = 0.25;
		m_diff[0] = 0.4;
		m_diff[1] = 0.4;
		m_diff[2] = 0.4;
		m_spec[0] = 0.774597;
		m_spec[1] = 0.774597;
		m_spec[2] = 0.774597;
		shiny = 0.6;
		break;
	case 3:
		m_amb[0] = 0.2125;
		m_amb[1] = 0.2125;
		m_amb[2] = 0.2125;
		m_diff[0] = 0.714;
		m_diff[1] = 0.714;
		m_diff[2] = 0.714;
		m_spec[0] = 0.393548;
		m_spec[1] = 0.393548;
		m_spec[2] = 0.393548;
		shiny = 0.2;
		break;
	case 4:
		m_amb[0] = 0.1745;
		m_amb[1] = 0.1745;
		m_amb[2] = 0.1745;
		m_diff[0] = 0.61424;
		m_diff[1] = 0.61424;
		m_diff[2] = 0.61424;
		m_spec[0] = 0.727811;
		m_spec[1] = 0.727811;
		m_spec[2] = 0.727811;
		shiny = 0.6;
		break;
	}
}

void Object::drawMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
}

int Object::getMaterial()
{
	return materialType;
}


void Object::setObject(int object)
{
	switch(object)
	{
		case 0:
			objectType = Cube;
			break;
		case 1:
			objectType = Sphere;
			break;
		case 2:
			objectType = Cone;
			break;
		case 3:
			objectType = Torus;
			break;
		case 4:
			objectType = Teapot;
			break;
	}
	
}

int Object::getObject()
{
	if (objectType == Cube)
		return 0;
	else if(objectType == Sphere)
		return 1;
	else if(objectType == Cone)
		return 2;
	else if(objectType == Torus)
		return 3;
	else if(objectType == Teapot)
		return 4;
}