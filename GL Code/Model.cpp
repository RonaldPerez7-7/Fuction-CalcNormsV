#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include <time.h> //libreria de tiempo
#include <GL/glut.h>


#include "Model.h"


double vert_[5][3] = { { 0.5, 0.0, -0.5},
					  {-0.5, 0.0, -0.5},
					  {-0.5, 0.0,  0.5},
					  { 0.5, 0.0,  0.5},
					  { 0.0, 1.0,  0.0} };

int face_[6][3] = { {0, 1, 4},
				   {1, 2, 4},
				   {2, 3, 4},
				   {3, 0, 4},
				   {3, 2, 0},
				   {2, 1, 0} };


Model::Model()
{
	nvert = 5;
	nface = 6;

	V = new vertex[nvert];
	for (int i = 0; i < nvert; i++)
		for (int j = 0; j < 3; j++)
			V[i].ver[j] = vert_[i][j];

	F = new face[nface];
	for (int i = 0; i < nface; i++)
		for (int j = 0; j < 3; j++)
			F[i].tri[j] = face_[i][j];

	CalcNormsV();
	CalcNormsF();
}

Model::Model(std::string name) {
	ReadM3D(name);
}


Model::~Model()
{
	if (V != NULL)
		delete V;

	if (F != NULL)
		delete F;
}

void Model::DrawM(float diff[4]) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	DrawM();
}

void Model::DrawM() {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nface; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			glNormal3dv(V[F[i].tri[j]].N); // Asignar las normales de los vértices
			glVertex3dv(V[F[i].tri[j]].ver); // Dibuja el vértice
		}
	}
	glEnd();
}

void Model::CalcNorm(double a[3], double b[3], double c[3], double N[3]) //Funcion "GENERAL" para calcular las normales
{
	double Vab[3], Vac[3], norm;

	for (int i = 0; i < 3; i++)
	{
		Vab[i] = b[i] - a[i];
		Vac[i] = c[i] - a[i];
	}

	N[0] = Vab[1] * Vac[2] - Vab[2] * Vac[1];
	N[1] = Vab[2] * Vac[0] - Vab[0] * Vac[2];
	N[2] = Vab[0] * Vac[1] - Vab[1] * Vac[0];

	norm = sqrt(N[0] * N[0] + N[1] * N[1] + N[2] * N[2]);

	for (int i = 0; i < 3; i++)
		N[i] = N[i] / norm;
}

void Model::CalcNormsV()  //Funcion para calcular normales de los vertices.
{
	
	for (int i = 0; i < nvert; i++) 
	{
		for (int j = 0; j < 3; j++)
		{
			V[i].N[j] = 0;
		}
	}


	for (int i = 0; i < nface; i++) //Cálculo de las normales de las caras y acumulación en las normales de los vértices.
	{
		CalcNorm(V[F[i].tri[0]].ver, V[F[i].tri[1]].ver, V[F[i].tri[2]].ver, F[i].N);//Reutilizamos la función CalcNorm
		for (int j = 0; j < 3; j++)
		{
			V[F[i].tri[j]].N[0] += F[i].N[0];
			V[F[i].tri[j]].N[1] += F[i].N[1];
			V[F[i].tri[j]].N[2] += F[i].N[2];
		}
	}
	
	for (int i = 0; i < nvert; i++) // Normalizar  los vértices.
	{
		double norm = sqrt(V[i].N[0] * V[i].N[0] + V[i].N[1] * V[i].N[1] + V[i].N[2] * V[i].N[2]);
		for (int j = 0; j < 3; j++)
		{
			V[i].N[j] /= norm;
		}
	}
}

void Model::CalcNormsF() //Funcion para calcular normales de las caras.
{
	for (int i = 0; i < nface; i++)
	{
		CalcNorm(V[F[i].tri[0]].ver, V[F[i].tri[1]].ver, V[F[i].tri[2]].ver, F[i].N); //Reutilizamos la función CalcNorm
	}
}

void Model::ReadM3D(std::string name)
{
	std::ifstream infile;
	infile.open(name);

	infile >> nvert;
	V = new vertex[nvert];
	for (int i = 0; i < nvert; i++)
		infile >> V[i].ver[0] >> V[i].ver[1] >> V[i].ver[2];

	infile >> nface;
	F = new face[nface];
	for (int i = 0; i < nface; i++)
		infile >> F[i].tri[0] >> F[i].tri[1] >> F[i].tri[2];

	infile.close();
	CalcNormsV();
	CalcNormsF();
}
