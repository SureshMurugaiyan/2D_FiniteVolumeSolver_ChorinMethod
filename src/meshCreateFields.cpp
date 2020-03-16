#include "mesh.h"

void createField(dfloat** phi, int variableType, mesh_t *mesh){

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

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (int i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}


}
