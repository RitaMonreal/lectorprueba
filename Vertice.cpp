#include <iostream>
#include "Vertice.h"

using namespace std;

	//Cosntructor
	Vertice::Vertice()
	{

	}
	//Getter
	float Vertice::getX()
	{
		return x;
	}

	float Vertice::getY()
	{
		return y;
	}

	float Vertice::getZ()
	{
		return z;
	}
	//Setter
	void Vertice::setX(float x)
	{
		this->x = x;
	}

	void Vertice::setY(float y)
	{
		this->y = y;
	}

	void Vertice::setZ(float z)
	{
		this->z = z;
	}