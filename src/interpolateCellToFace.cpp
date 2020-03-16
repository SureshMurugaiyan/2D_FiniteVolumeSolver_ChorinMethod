#include "mesh.h"

void interpolateScalarCellToFace(dfloat* phiCell, dfloat* phiFace,mesh_t *mesh){


	for (int face = 0; face < mesh->nInnerFaces; face++) {

		int fid 	=  mesh->innerFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int cell_n	=  mesh->faceToNeighborCell[fid];

		phiFace[fid] = mesh->fx[fid]*phiCell[cell]+(1-mesh->fx[fid])*phiCell[cell_n];

	}


	for (int face = 0; face < mesh->nBoundaryFaces; face++) {

		int fid 	=  mesh->boundaryFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int oface	=  mesh->faceToOppositeFace[fid]; // local face ID

		int ofid	=	oface  + cell*mesh->ncellFaces; // Global face ID

		phiFace[fid] = mesh->fx[fid]*phiCell[cell]+(1-mesh->fx[fid])*phiFace[ofid];

	}


}
/*********************************************************************************/
void interpolateVectorCellToFace(dfloat* phiCell, dfloat* phiFace,mesh_t *mesh){

	for (int face = 0; face < mesh->nInnerFaces; face++) {

		int fid 	=  mesh->innerFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int cell_n	=  mesh->faceToNeighborCell[fid];

		for (int dim = 0; dim < mesh->ndimension; dim++) {

			int fid_dim   = dim + fid*mesh->ndimension;
			int cell_dim  = dim + cell*mesh->ndimension;
			int cell_ndim = dim + cell_n*mesh->ndimension;

			phiFace[fid_dim] = mesh->fx[fid]*phiCell[cell_dim]+(1-mesh->fx[fid])*phiCell[cell_ndim];
		}
	}



	for (int face = 0; face < mesh->nBoundaryFaces; face++) {

		int fid 	=  mesh->boundaryFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int oface	=  mesh->faceToOppositeFace[fid]; // local face ID

		int ofid	=	oface  + cell*mesh->ncellFaces; // Global face ID

		for (int dim = 0; dim < mesh->ndimension; dim++) {

			int fid_dim    = dim + fid*mesh->ndimension;
			int ofid_dim   = dim + ofid*mesh->ndimension;
			int cell_dim   = dim + cell*mesh->ndimension;

			phiFace[fid_dim] = mesh->fx[fid]*phiCell[cell_dim]+(1-mesh->fx[fid])*phiFace[ofid_dim];
		}



	}


}
