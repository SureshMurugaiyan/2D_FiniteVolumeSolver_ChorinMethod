
#include "mesh.h"

void setReferenceValueScalar(double* p,int P_name, int refCell,double refValue, mesh_t *mesh){

	for (int face = 0; face < mesh->nBoundaryFaces; face++){

		int fid 	= mesh->boundaryFaces[face];
		int cell 	= mesh->faceToOwnerCell[fid];

		insGetBoundaryCondition(P_name,fid,mesh);


		if (mesh->bctype == fixedValue){
			return;

		}
	}



	mesh->aP[refCell] = 1.00;

	for (int face = 0; face < mesh->ncellFaces; face++) {

		int fid = face+refCell*mesh->ncellFaces;

		mesh->aN[fid] = 0;

	}

	mesh->r[refCell]  = - refValue;

}
