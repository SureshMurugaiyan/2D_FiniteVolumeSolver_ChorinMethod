#include "mesh.h"

double distance(double *X1,double *X2){

	double Distance = 0.0;

	double a = X2[0]-X1[0];
	double b = X2[1]-X1[1];
	double c = X2[2]-X1[2];

	Distance = sqrt(pow(a,2)+pow(b,2) +pow(c,2));

	return Distance;
}



double magnitude(double a){
double c = 0;
	if(a>0){c= a;}
	if(a<0){c=-a;}

	return c;
}

void copyDataToFrom(double* copyTo, double* copyFrom, int variableType, mesh_t *mesh){

	int n=0;

	switch (variableType)
	{

	case vertexScalar:	n = mesh->ncells*mesh->ncellVertices;break;
	case vertexVector:	n = mesh->ncells*mesh->ncellVertices*mesh->ndimension;break;
	case volumeScalar:	n = mesh->ncells;break;
	case volumeVector:	n = mesh->ncells*mesh->ndimension;break;
	case surfaceScalar:	n = mesh->ncells*mesh->ncellFaces;break;
	case surfaceVector:	n = mesh->ncells*mesh->ncellFaces*mesh->ndimension;break;
	}

	for (int i = 0; i< n; i++){
		copyTo[i]= copyFrom[i];
	}
}


double max(double a, double b){

	if (a>b) {
		return a;
	}

	return b;
}

double min(double a, double b){

	if (a<b) {
		return a;
	}

	return b;
}


double sgn(double F){


	if (F<0.0) {
		return -1.0;
	}

	return 1.0;

}
