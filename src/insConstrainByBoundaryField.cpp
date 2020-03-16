
#include "mesh.h"

void insConstrainByBoundaryFieldVector(double* Uf, double* U, int U_name,mesh_t *mesh){



	for (int face = 0; face < mesh->nBoundaryFaces; face++) {

		int fid 	=  mesh->boundaryFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];


		insGetBoundaryCondition(U_name,fid,mesh);


		if (mesh->bctype==fixedValue){

			for (int dim = 0; dim < mesh->ndimension; dim++) {
				int fid_dim = dim+ fid*mesh->ndimension;

				Uf[fid_dim] = mesh->bcvalueVector[dim];
			}

		}


		if (mesh->bctype==fixedNormalGradient){
			for (int dim = 0; dim < mesh->ndimension; dim++) {

				int fid_dim  = dim+ fid*mesh->ndimension;
				int cell_dim = dim + cell*mesh->ndimension;

				Uf[fid_dim] = U[cell_dim];
			}
		}

	}

}


void insConstrainByBoundaryFieldScalar(double* pf,double* pcell,int p_name,mesh_t *mesh){


	for (int face = 0; face < mesh->nBoundaryFaces; face++) {

		int fid 	=  mesh->boundaryFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];

		insGetBoundaryCondition(p_name,fid,mesh);

		if (mesh->bctype==fixedValue){
			pf[fid] = mesh->bcvalueScalar[0];
		}

		if (mesh->bctype==fixedNormalGradient){
			pf[fid] = pcell[cell];
		}

	}



}
