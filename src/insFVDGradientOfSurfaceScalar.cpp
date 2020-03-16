#include "mesh.h"

void fvdSnGradientOfScalar(dfloat* gradFace,dfloat *phiCell, int P_Name, mesh_t *mesh){



	for (int face = 0; face < mesh->nInnerFaces; face++){

		int fid 	= mesh->innerFaces[face];
		int cell 	= mesh->faceToOwnerCell[fid];
		int cell_n 	= mesh->faceToNeighborCell[fid];

		for (int dim = 0; dim < mesh->ndimension; dim++) {

			int fid_dim   = dim + fid*mesh->ndimension;
			int cell_dim  = dim + cell*mesh->ndimension;
			int cell_ndim = dim + cell_n*mesh->ndimension;

			dfloat denominator = (mesh->C[cell_ndim]-mesh->C[cell_dim]);


			if ((denominator > 0.001) ||  (denominator < 0.001)){

				gradFace[fid_dim] = (phiCell[cell_n]-phiCell[cell])/denominator;
			}

		}

	}


	for (int face = 0; face < mesh->nBoundaryFaces; face++){

		int fid 	= mesh->boundaryFaces[face];
		int cell 	= mesh->faceToOwnerCell[fid];

		insGetBoundaryCondition(P_Name,fid,mesh);

		for (int dim = 0; dim < mesh->ndimension; dim++) {

			int fid_dim   = dim + fid*mesh->ndimension;
			int cell_dim  = dim + cell*mesh->ndimension;

			dfloat denominator = (mesh->Cf[fid_dim]-mesh->C[cell_dim]);

			if ((denominator >0.0) ||  (denominator < 0.0)){

				gradFace[fid_dim] = (mesh->bcvalueScalar[0]-phiCell[cell])/denominator;
			}

		}

	}

}
