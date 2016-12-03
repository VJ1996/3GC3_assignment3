
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
	materialType = mat;
}

int Object::getMaterial()
{
	return materialType;
}

void Object::setObject(int object)
{
	if(object == 0)
		objectType = Cube;
	else if(object == 1)
		objectType = Sphere;
	else if(object == 2)
		objectType == Cone;
	else if(object == 3)
		objectType == Torus;
	else if(object == 4)
		objectType == Teapot;
	
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