#include "mesh.h"
#include "../meshGenerator/meshInput.h"

void meshGenerateBoundaryName(mesh_t *mesh){


	for (int face = 0; face < mesh->nBoundaryFaces; face++) {

		int fid 		= mesh->boundaryFaces[face];
		int localFace 	= fid % mesh->ncellFaces;

		if (localFace ==0) {mesh->patchID[fid] = leftBoundary ;}
		if (localFace ==1) {mesh->patchID[fid] = bottomBoundary;}
		if (localFace ==2) {mesh->patchID[fid] = rightBoundary;}
		if (localFace ==3) {mesh->patchID[fid] = topBoundary;}
	}

	for (int face = 0; face < mesh->nInnerFaces; face++) {

		int fid 	=  mesh->innerFaces[face];
		mesh->patchID[fid] = innerDomain ;
	}



	int n = 50;
	char *variableName ;
	variableName	= (char*) calloc(n, sizeof(char));

	strcpy(variableName, "patchID");
	printMeshSurfaceScalar(mesh->patchID, variableName, mesh);


	free(variableName);
}











//void meshGenerateBoundaryName(mesh_t *mesh){
//
//	int dimx,dimy,dimz;
//	int fid_dimx,fid_dimy,fid_dimz;
//	int fid;
//
//	dimx = 0; // dim = 0 gives x component
//	dimy = 1; // dim = 1 gives y component
//	dimz = 2; // dim = 2 gives z component
//
//	for (int face = 0; face < mesh->nBoundaryFaces; face++) {
//
//		fid 		=  mesh->boundaryFaces[face];
//		fid_dimx   	=  dimx + fid*mesh->ndimension;
//		fid_dimy   	=  dimy + fid*mesh->ndimension;
//		fid_dimz   	=  dimz + fid*mesh->ndimension;
//
//
//		if (magnitude(mesh->Cf[fid_dimy]-input_y1)<1e-14) {mesh->patchID[fid] = topBoundary;}
//		if (magnitude(mesh->Cf[fid_dimy]-input_y2)<1e-14) {mesh->patchID[fid] = bottomBoundary;}
//		if (magnitude(mesh->Cf[fid_dimx]-input_x4)<1e-14) {mesh->patchID[fid] = rightBoundary;}
//		if (magnitude(mesh->Cf[fid_dimx]-input_x1)<1e-14) {mesh->patchID[fid] = leftBoundary ;}
//
//	}
//
//	for (int face = 0; face < mesh->nInnerFaces; face++) {
//
//		int fid 	=  mesh->innerFaces[face];
//		mesh->patchID[fid] = innerDomain ;
//	}
//
//
//
//	int n = 50;
//	char *variableName ;
//	variableName	= (char*) calloc(n, sizeof(char));
//
//	strcpy(variableName, "patchID");
//	printMeshSurfaceScalar(mesh->patchID, variableName, mesh);
//
//
//	free(variableName);
//}
