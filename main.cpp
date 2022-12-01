#include <GL/freeglut.h>
#include <Math.h>
#include "Lector.h"
#include "Puntos.h"
#include "Matrices.h"

using namespace std;

//Objetos
Obj raqueta("Raqueta.obj");
float escalaRaqueta = 0.18;
Obj pelota("Pelota.obj");
float escalaPelota = 0.1;
//0.18, 0.1

//Caras
void CarasRaqueta(Obj obj)
{
	int c, v;

	Vertice vertices; //variable que almacena float x y z 
	
	for (c = 0; c < obj.caras.size(); c++)
	{
		glBegin(GL_TRIANGLES);

		for (v = 0; v < obj.caras[c].index.size(); v++)
		{
			float x = obj.vertices[obj.caras[c].index[v]].getX();
			float y = obj.vertices[obj.caras[c].index[v]].getY();
			float z = obj.vertices[obj.caras[c].index[v]].getZ();

			Escalacion(&x, &y, &z, escalaRaqueta);
			glVertex3f(x, y, z);

		}
		glEnd();
	}
}

void CarasPelota(Obj obj)
{
	int c, v;
	Vertice vertices; 

	//C A R A S 
	for (c = 0; c < obj.caras.size(); c++)
	{
		glBegin(GL_TRIANGLES);
		for (v = 0; v < obj.caras[c].index.size(); v++)
		{
			float x = obj.vertices[obj.caras[c].index[v]].getX();
			float y = obj.vertices[obj.caras[c].index[v]].getY();
			float z = obj.vertices[obj.caras[c].index[v]].getZ();

			Escalacion(&x, &y, &z, escalaPelota);

			//Enviados para el movimento del obj
			Movimiento(x, y, z);

			glVertex3f(traslacion.getX(), traslacion.getY(), traslacion.getZ());

			if (grados >= 360)
			{
				grados = 0;
			}
			grados += 0.0001;
		}

		glEnd();
	}
}

void Matrices()
{
	Bezier();
	matrizBezier();
	Rotacion();
	Transformacion();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(5.5, 0.0, 3.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(1.5, 0.0, 3.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.0, 0.0, 1.0);
	CarasPelota(pelota);

	glColor3f(0.0, 1.0, 0.0);
	CarasRaqueta(raqueta);

	Matrices();
	glutSwapBuffers();
	glFlush();
}

void init()
{
	/*  select clearing (background) color  */
	glClearColor(1.0, 1.0, 1.0, 1.0);//Blanco
	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluPerspective(80, 1280 / 720.0, 0.1f, 40);
	//	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
		//gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	//	glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
	//	gluLookAt(1.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		//gluLookAt(1.5, 0.0, 3.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
		/*
		 *  Declare initial window size, position, and display mode
		 *  (single buffer and RGBA).  Open window with "hello"
		 *  in its title bar.  Call initialization routines.
		 *  Register callback function to display graphics.
		 *  Enter main loop and process events.
		 */
}

int main(int argc, char** argv)
{
	//Instancias de Objetos
	raqueta.leerArchivo();
	pelota.leerArchivo();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Perritos");
	init();
	glutDisplayFunc(display);

	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}