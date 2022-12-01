#include "Lector.h"
#include "Puntos.h"
#include "puntosControl.h"


namespace std
{ 
	float mBezier[4][4];

	float t;

	float p1x = 1.5, p1y = 1.5, p1z = 0.0; //Punto Inicial
	float p2x = 6.5, p2y = 3.25, p2z = 0.0; //Punto control 1
	float p3x = 10.5, p3y = 3.25, p3z = 0.0; //Punto control 2
	float p4x = 8.25, p4y = 1.25, p4z = 0.0; //Punto Final

	puntosControl puntosCont[] = { {p1x, p1y, p1z},
							  {p2x, p2y, p2z},
							  {p3x, p3y, p3z},
							  {p4x, p4y, p4z} };

	Puntos posicion; //Puntos
	Puntos traslacion; //Puntos

	float grados = 0;

	float matrizRotacion[4][4]; //Matriz de Rotacion
	float mTransform[4][4]; //Matriz de Transformacion
	float mMov[4]; //Matriz de movimiento de vertices


	void Bezier()
	{
		float a, b, c, d;

		if (t < 1)
		{
			//Fórmula : B(t) = (1-t)^3 * (P0) + 3(1-t)^2 t(P1) + 3(1-t)t^2(P2) + t^3(P3);
			a = pow((1 - t), 3);
			b = 3 * t * pow((1 - t), 2);
			c = 3 * pow(t, 2) * (1 - t);
			d = pow(t, 3);

			posicion.setX(a * puntosCont[0].x + b * puntosCont[1].x + c * puntosCont[2].x + d * puntosCont[3].x);
			posicion.setY(a * puntosCont[0].y + b * puntosCont[1].y + c * puntosCont[2].y + d * puntosCont[3].y);
			posicion.setZ(a * puntosCont[0].z + b * puntosCont[1].z + c * puntosCont[2].z + d * puntosCont[3].z);

			t += 0.001;
			if (t >= 1)
			{
				t = 0; //Regresa a 0 
			}
		}
	}

	void Transformacion()
	{
		//Matriz auxiliar para guardar las posiciones
		float aux[4][4]{ {0, 0, 0, 0},
						  {0, 0, 0, 0},
						  {0, 0, 0, 0},
						  {0, 0, 0, 0} };

		aux[0][0] = mBezier[0][0] * matrizRotacion[0][0] + mBezier[0][1] * matrizRotacion[1][0] + mBezier[0][2] * matrizRotacion[2][0] + mBezier[0][3] * matrizRotacion[3][0];
		aux[0][1] = mBezier[0][0] * matrizRotacion[0][1] + mBezier[0][1] * matrizRotacion[1][1] + mBezier[0][2] * matrizRotacion[2][1] + mBezier[0][3] * matrizRotacion[3][1];
		aux[0][2] = mBezier[0][0] * matrizRotacion[0][2] + mBezier[0][1] * matrizRotacion[1][2] + mBezier[0][2] * matrizRotacion[2][2] + mBezier[0][3] * matrizRotacion[3][2];
		aux[0][3] = mBezier[0][0] * matrizRotacion[0][3] + mBezier[0][1] * matrizRotacion[1][3] + mBezier[0][2] * matrizRotacion[2][3] + mBezier[0][3] * matrizRotacion[3][3];

		aux[1][0] = mBezier[1][0] * matrizRotacion[0][0] + mBezier[1][1] * matrizRotacion[1][0] + mBezier[1][2] * matrizRotacion[2][0] + mBezier[1][3] * matrizRotacion[3][0];
		aux[1][1] = mBezier[1][0] * matrizRotacion[0][1] + mBezier[1][1] * matrizRotacion[1][1] + mBezier[1][2] * matrizRotacion[2][1] + mBezier[1][3] * matrizRotacion[3][1];
		aux[1][2] = mBezier[1][0] * matrizRotacion[0][2] + mBezier[1][1] * matrizRotacion[1][2] + mBezier[1][2] * matrizRotacion[2][2] + mBezier[1][3] * matrizRotacion[3][2];
		aux[1][3] = mBezier[1][0] * matrizRotacion[0][3] + mBezier[1][1] * matrizRotacion[1][3] + mBezier[1][2] * matrizRotacion[2][3] + mBezier[1][3] * matrizRotacion[3][3];

		aux[2][0] = mBezier[2][0] * matrizRotacion[0][0] + mBezier[2][1] * matrizRotacion[1][0] + mBezier[2][2] * matrizRotacion[2][0] + mBezier[2][3] * matrizRotacion[3][0];
		aux[2][1] = mBezier[2][0] * matrizRotacion[0][1] + mBezier[2][1] * matrizRotacion[1][1] + mBezier[2][2] * matrizRotacion[2][1] + mBezier[2][3] * matrizRotacion[3][1];
		aux[2][2] = mBezier[2][0] * matrizRotacion[0][2] + mBezier[2][1] * matrizRotacion[1][2] + mBezier[2][2] * matrizRotacion[2][2] + mBezier[2][3] * matrizRotacion[3][2];
		aux[2][3] = mBezier[2][0] * matrizRotacion[0][3] + mBezier[2][1] * matrizRotacion[1][3] + mBezier[2][2] * matrizRotacion[2][3] + mBezier[2][3] * matrizRotacion[3][3];

		aux[3][0] = mBezier[3][0] * matrizRotacion[0][0] + mBezier[3][1] * matrizRotacion[1][0] + mBezier[3][2] * matrizRotacion[2][0] + mBezier[3][3] * matrizRotacion[3][0];
		aux[3][1] = mBezier[3][0] * matrizRotacion[0][1] + mBezier[3][1] * matrizRotacion[1][1] + mBezier[3][2] * matrizRotacion[2][1] + mBezier[3][3] * matrizRotacion[3][1];
		aux[3][2] = mBezier[3][0] * matrizRotacion[0][2] + mBezier[3][1] * matrizRotacion[1][2] + mBezier[3][2] * matrizRotacion[2][2] + mBezier[3][3] * matrizRotacion[3][2];
		aux[3][3] = mBezier[3][0] * matrizRotacion[0][3] + mBezier[3][1] * matrizRotacion[1][3] + mBezier[3][2] * matrizRotacion[2][3] + mBezier[3][3] * matrizRotacion[3][3];

		mTransform[0][0] = aux[0][0];
		mTransform[0][1] = aux[0][1];
		mTransform[0][2] = aux[0][2];
		mTransform[0][3] = aux[0][3];
		mTransform[1][0] = aux[1][0];
		mTransform[1][1] = aux[1][1];
		mTransform[1][2] = aux[1][2];
		mTransform[1][3] = aux[1][3];
		mTransform[2][0] = aux[2][0];
		mTransform[2][1] = aux[2][1];
		mTransform[2][2] = aux[2][2];
		mTransform[2][3] = aux[2][3];
		mTransform[3][0] = aux[3][0];
		mTransform[3][1] = aux[3][1];
		mTransform[3][2] = aux[3][2];
		mTransform[3][3] = aux[3][3];
	}

	void matrizBezier()
	{
		float x, y, z;

		x = posicion.getX();//Posiciones sacadas de los puntos de control
		y = posicion.getY();
		z = posicion.getZ();

		//Guardar posiciones que iran a la matriz de bezier
		float aux[4][4]{ {1, 0, 0, x},
						{0, 1, 0, y},
						{0, 0, 1, z},
						{0, 0, 0, 1} };

		mBezier[0][0] = aux[0][0];
		mBezier[0][1] = aux[0][1];
		mBezier[0][2] = aux[0][2];
		mBezier[0][3] = aux[0][3];
		mBezier[1][0] = aux[1][0];
		mBezier[1][1] = aux[1][1];
		mBezier[1][2] = aux[1][2];
		mBezier[1][3] = aux[1][3];
		mBezier[2][0] = aux[2][0];
		mBezier[2][1] = aux[2][1];
		mBezier[2][2] = aux[2][2];
		mBezier[2][3] = aux[2][3];
		mBezier[3][0] = aux[3][0];
		mBezier[3][1] = aux[3][1];
		mBezier[3][2] = aux[3][2];
		mBezier[3][3] = aux[3][3];
	}

	//Escalación, está no te la revisa
	void Escalacion(float* x, float* y, float* z, float escala)
	{
		*x *= escala;
		*y *= escala;
		*z *= escala;
	}

	void Rotacion()
	{

		float mRotacionX[4][4]{ {1,   0   ,	 0   ,  0},
						   {0, cos(grados), sin(-grados) ,  0},
						   {0, sin(grados) , cos(grados), 0},
						   {0,   0   ,   0   ,  1} };
		//No los ocupas
		float mRotacionY[4][4]{ {cos(grados),   0   ,	 sin(grados) ,  0},
						  {0,      cos(grados), sin(-grados) ,  0},
						  {0,      1 ,    0,   0},
						  {sin(-grados),  0 , cos(grados), 1}};
		//No los ocupas
		float mRotacionZ[4][4]{ {cos(grados),  sin(-grados) ,	0 ,  0},
						  {sin(grados),     cos(grados),  0 ,   0},
						  {0,      0 ,    1,        0},
						  {0,      0 ,   1      ,   1} };

		//Solo necesito rotar en el eje x
		matrizRotacion[0][0] = mRotacionX[0][0];
		matrizRotacion[0][1] = mRotacionX[0][1];
		matrizRotacion[0][2] = mRotacionX[0][2];
		matrizRotacion[0][3] = mRotacionX[0][3];
		matrizRotacion[1][0] = mRotacionX[1][0];
		matrizRotacion[1][1] = mRotacionX[1][1];
		matrizRotacion[1][2] = mRotacionX[1][2];
		matrizRotacion[1][3] = mRotacionX[1][3];
		matrizRotacion[2][0] = mRotacionX[2][0];
		matrizRotacion[2][1] = mRotacionX[2][1];
		matrizRotacion[2][2] = mRotacionX[2][2];
		matrizRotacion[2][3] = mRotacionX[2][3];
		matrizRotacion[3][0] = mRotacionX[3][0];
		matrizRotacion[3][1] = mRotacionX[3][1];
		matrizRotacion[3][2] = mRotacionX[3][2];
		matrizRotacion[3][3] = mRotacionX[3][3];
	}



	void Movimiento(float x, float y, float z)
	{
		//Añadimos los valores a mover extraidos en el dibujado
		mMov[0] = x;
		mMov[1] = y;
		mMov[2] = z;
		mMov[3] = 1;
		//Vector auxiliar para la multipliacion
		float aux[4] = {0,0,0,0};

		//Multiplicacion de matriz transformacion por vertice
		aux[0] = mTransform[0][0] * mMov[0] + mTransform[0][1] * mMov[1] + mTransform[0][2] * mMov[2] + mTransform[0][3] * mMov[3];
		aux[1] = mTransform[1][0] * mMov[0] + mTransform[1][1] * mMov[1] + mTransform[1][2] * mMov[2] + mTransform[1][3] * mMov[3];
		aux[2] = mTransform[2][0] * mMov[0] + mTransform[2][1] * mMov[1] + mTransform[2][2] * mMov[2] + mTransform[2][3] * mMov[3];
		aux[3] = mTransform[3][0] * mMov[0] + mTransform[3][1] * mMov[1] + mTransform[3][2] * mMov[2] + mTransform[3][3] * mMov[3];

		traslacion.setX(aux[0]);
		traslacion.setY(aux[1]);
		traslacion.setZ(aux[2]);
	}
}