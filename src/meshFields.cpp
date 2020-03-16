#include "mesh.h"


void meshConstructFields(mesh_t *mesh){

	createField(&mesh->vertices,vertexVector, mesh);
	createField(&mesh->C,volumeVector,mesh);
	createField(&mesh->Cf,surfaceVector,mesh);
	createField(&mesh->Sf,surfaceVector,mesh);
	createField(&mesh->magSf,surfaceScalar,mesh);
	createField(&mesh->V,volumeScalar,mesh);
	createField(&mesh->fx,surfaceScalar,mesh);
	createField(&mesh->d,surfaceVector,mesh);
	createField(&mesh->magd,surfaceScalar,mesh);


	mesh->cellToVertex 			= (dint*) calloc(mesh->ncells*mesh->ncellVertices, sizeof(dint));
	mesh->cellToCells 			= (dint*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(dint));
	mesh->cellToFaces 			= (dint*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(dint));
	mesh->faceToOppositeFace 	= (dint*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(dint));
	mesh->faceToVertices		= (dint*) calloc(mesh->ncellFaces*mesh->nfaceVertices, sizeof(dint));
	mesh->faceToLocalFaces		= (dint*) calloc(mesh->ncellFaces*2, sizeof(dint));
	mesh->faceToOwnerCell 	 	= (dint*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(dint));
	mesh->faceToNeighborCell 	= (dint*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(dint));
	mesh->patchID 				= (dint*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(dint));

	for (int i = 0; i < (mesh->ncells*mesh->ncellVertices); i++) {
		mesh->cellToVertex[i] = 0;
	}

	for (int i = 0; i < (mesh->ncells*mesh->ncellFaces); i++) {
		mesh->cellToCells[i] = 0;
		mesh->cellToFaces[i] = 0;
		mesh->faceToOppositeFace[i] = 0;
	}

	for (int i = 0; i < (mesh->ncellFaces*mesh->nfaceVertices); i++) {
		mesh->faceToVertices[i] = 0;
	}

	for (int i = 0; i < (mesh->ncellFaces*2); i++) {
		mesh->faceToLocalFaces[i] = 0;
	}


	for (int i = 0; i < (mesh->ncells*mesh->ncellFaces); i++) {
		mesh->faceToOwnerCell[i] = 0;
		mesh->faceToNeighborCell[i] = 0;
		mesh->patchID[i] = 0;
	}

}

void meshDestructFields(mesh_t *mesh){

	free(mesh->vertices);


	free(mesh->C);
	free(mesh->Cf);
	free(mesh->Sf);
	free(mesh->magSf);

	free(mesh->V);
	free(mesh->fx);

	free(mesh->d);
	free(mesh->magd);

	free(mesh->cellToVertex);
	free(mesh->cellToCells);
	free(mesh->cellToFaces);
	free(mesh->faceToOppositeFace);
	free(mesh->faceToVertices);
	free(mesh->faceToLocalFaces);
	free(mesh->faceToOwnerCell);
	free(mesh->faceToNeighborCell);

	free(mesh->innerCells);
	free(mesh->boundaryCells);
	free(mesh->innerFaces);
	free(mesh->boundaryFaces);

	free(mesh->patchID);
}
