#include "mesh.h"


double fvmLaplacianOfScalar(double alpha, dfloat* p,int P_name,mesh_t *mesh){

	/**********************Calculate the Coefficients of Matrix ************************************/

	for (int face = 0; face < mesh->nInnerFaces; face++){

		int fid 	= mesh->innerFaces[face];
		int cell 	= mesh->faceToOwnerCell[fid];

		dfloat aP_new  = - (alpha/mesh->V[cell])*mesh->magSf[fid]/mesh->magd[fid];
		dfloat aN_new  =   (alpha/mesh->V[cell])*mesh->magSf[fid]/mesh->magd[fid];

		mesh->aP[cell]	=	mesh->aP[cell] + aP_new;
		mesh->aN[fid]	=	mesh->aN[fid]  + aN_new;

	}

	for (int face = 0; face < mesh->nBoundaryFaces; face++){

		int fid 	= mesh->boundaryFaces[face];
		int cell 	= mesh->faceToOwnerCell[fid];

		insGetBoundaryCondition(P_name,fid,mesh);

		if (mesh->bctype==fixedValue){

			dfloat aP_new  =  - (alpha/mesh->V[cell])*(mesh->magSf[fid]/mesh->magd[fid]);
			dfloat r_new   =    (alpha/mesh->V[cell])*(mesh->magSf[fid]/mesh->magd[fid])*mesh->bcvalueScalar[0];

			mesh->aP[cell]	=	mesh->aP[cell] + aP_new;
			mesh->r[cell]	=	mesh->r[cell]  + r_new;
		}

		if (mesh->bctype==fixedNormalGradient){

			double g_b = mesh->bcvalueScalar[0];
			dfloat r_new  = (alpha/mesh->V[cell])*(g_b*mesh->magSf[fid]);
			mesh->r[cell] =	mesh->r[cell]  + r_new;

		}

	}

	return 0.0;
}
