#include "mesh.h"
double fvcLaplacianOfVector(double alpha, dfloat* mu, int mu_name, dfloat* U,int U_name,mesh_t *mesh){

	/**********************Calculate the face values ************************************/
	dfloat *mu_f;
	createField(&mu_f,surfaceScalar,mesh);

	interpolateScalarCellToFace(mu,mu_f,mesh);
	insConstrainByBoundaryFieldScalar(mu_f,mu,mu_name,mesh);


	/**********************Calculate the Coefficients of Matrix ************************************/

	for (int face = 0; face < mesh->nInnerFaces; face++) {

		int fid 	=  mesh->innerFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int cell_n	=  mesh->faceToNeighborCell[fid];

		for (int dim = 0; dim < mesh->ndimension; dim++) {
			int cell_dim = dim+cell*mesh->ndimension;
			int cell_ndim = dim+cell_n*mesh->ndimension;

			dfloat R_new  = (mu_f[fid]*mesh->magSf[fid]/mesh->magd[fid])*(U[cell_ndim]-U[cell_dim]);
			R_new  		  = (alpha/mesh->V[cell])*R_new;

			mesh->R[cell_dim]  = mesh->R[cell_dim]  + R_new;


		}
	}

	for (int face = 0; face < mesh->nBoundaryFaces; face++) {

		int fid 	=  mesh->boundaryFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];


		insGetBoundaryCondition(U_name,fid,mesh);

		if (mesh->bctype==fixedValue){


			for (int dim = 0; dim < mesh->ndimension; dim++) {

				int cell_dim = dim+cell*mesh->ndimension;

				dfloat R_new  = (mu_f[fid]*mesh->magSf[fid]/mesh->magd[fid])*(mesh->bcvalueVector[dim]-U[cell_dim]);
				R_new  		  = (alpha/mesh->V[cell])*R_new;
				mesh->R[cell_dim]	=	mesh->R[cell_dim] + R_new;

			}

		}

		if (mesh->bctype==fixedNormalGradient){

			for (int dim = 0; dim < mesh->ndimension; dim++) {
				int cell_dim = dim+cell*mesh->ndimension;

				dfloat R_new  =	(mu_f[fid]*mesh->bcvalueVector[dim]*mesh->magSf[fid]);
				R_new  		  = (alpha/mesh->V[cell])*R_new;
				mesh->R[cell_dim]	=	mesh->R[cell_dim] + R_new;
			}

		}


	}





	free(mu_f);
	return 0.0;
}
