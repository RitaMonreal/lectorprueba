#include <iostream>

using namespace std;

class Vertice
{
	//Atributos
private:
	float x;
	float y;
	float z;
public:
	//Constructor
	Vertice();
	//Setters - estable valor de x, y y z del vertice
	void setX(float);
	void setY(float);
	void setZ(float);
	//Getters - acceden al valor de x, y y z del vertice
	float getX();
	float getY();
	float getZ();
};