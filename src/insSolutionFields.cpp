#include "mesh.h"
void insConstructSolutionFields(mesh_t *mesh){


	createField(&mesh->U,volumeVector,mesh);
	createField(&mesh->p,volumeScalar,mesh);
	createField(&mesh->rho,volumeScalar,mesh);
	createField(&mesh->mu,volumeScalar,mesh);

	createField(&mesh->phiU,surfaceScalar,mesh);
	createField(&mesh->divphiU,volumeScalar,mesh);

	createField(&mesh->U0,volumeVector,mesh);
	createField(&mesh->U00,volumeVector,mesh);



	mesh->bcvalueScalar	= (dfloat*) calloc(1, sizeof(dfloat));
	mesh->bcvalueVector	= (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));


	mesh->bcvalueScalar[0]=0.0;
	for (int i = 0; i < mesh->ndimension; i++) {
		mesh->bcvalueVector[i]=0.0;
	}

}

void insDestructSolutionFields(mesh_t *mesh){

	free(mesh->U);
	free(mesh->p);
	free(mesh->rho);
	free(mesh->mu);

	free(mesh->phiU);
	free(mesh->divphiU);

	free(mesh->U0);
	free(mesh->U00);


	free(mesh->bcvalueScalar);
	free(mesh->bcvalueVector);

}

