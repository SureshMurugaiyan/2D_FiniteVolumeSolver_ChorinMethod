#include "mesh.h"

void solverConstructFields(mesh_t *mesh){

	createField(&mesh->AP,volumeVector,mesh);
	createField(&mesh->AN,surfaceVector,mesh);
	createField(&mesh->R,volumeVector,mesh);
	createField(&mesh->R1,volumeVector,mesh);

	createField(&mesh->aP,volumeScalar,mesh);
	createField(&mesh->aN,surfaceScalar,mesh);
	createField(&mesh->r,volumeScalar,mesh);

}

void solverDestructFields(mesh_t *mesh){

	free(mesh->AP);
	free(mesh->AN);
	free(mesh->R);
	free(mesh->R1);

	free(mesh->aP);
	free(mesh->aN);
	free(mesh->r);

}
