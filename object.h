#include <vector>
using namespace std;

class Object{
public:

	enum ObjectType{
		Sphere,
		Cube,
		Cone,
		Teapot,
		Torus
	};



	Object();

	Object(float pX,float pY,float pZ, float rX, float rY, float rZ, float sX, float sY, float sZ, int type);

	
	
	

	void setMaterial(int mat);
	int getMaterial();
	void drawMaterial();

	void setObject(int object);
	int getObject();
	
	void translate(float pX, float pY, float pZ);
	void scaleObject(float scale);
	void rotate(float rX, float rY, float rZ);

	float getPX();
	float getPY();
	float getPZ();

	float getRX();
	float getRY();
	float getRZ();

	float getScale();
	
	//void drawObject(bool cObject);

private:
	ObjectType objectType;

	int materialType;

	float m_amb[3];
	float m_diff[3];
	float m_spec[3];
	float shiny;

	float pX;
	float pY;
	float pZ;

	float rX;
	float rY;
	float rZ;

	float scale;


};