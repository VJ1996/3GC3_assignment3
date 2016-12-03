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
	

private:
	ObjectType objectType;

	int materialType;

	float pX;
	float pY;
	float pZ;

	float rX;
	float rY;
	float rZ;

	float scale;


};