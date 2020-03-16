#include "mesh.h"
double fvcDivergenceOfVector(double alpha, dfloat* rho, int rho_name, dfloat* U,int U_name,
		dfloat* phiU, mesh_t *mesh){

	/**********************Calculate the face values ************************************/
	dfloat *rho_f;
	createField(&rho_f,surfaceScalar,mesh);
	interpolateScalarCellToFace(rho,rho_f,mesh);
	insConstrainByBoundaryFieldScalar(rho_f,rho,rho_name,mesh);


	/**********************Calculate the Coefficients of Matrix ************************************/

	for (int face = 0; face < mesh->nInnerFaces; face++) {

		int fid 	=  mesh->innerFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int cell_n	=  mesh->faceToNeighborCell[fid];


		for (int dim = 0; dim < mesh->ndimension; dim++) {
			int cell_dim = dim+cell*mesh->ndimension;
			int cell_ndim = dim+cell_n*mesh->ndimension;

			dfloat R_new  = rho_f[fid]*mesh->phiU[fid]*(mesh->fx[fid]*U[cell_dim] + (1.0-mesh->fx[fid])*U[cell_ndim] );
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

				dfloat R_new  = rho_f[fid]*mesh->phiU[fid]*mesh->bcvalueVector[dim];
				R_new  		  = (alpha/mesh->V[cell])*R_new;
				mesh->R[cell_dim]  = mesh->R[cell_dim]  + R_new;
			}
		}

		if (mesh->bctype==fixedNormalGradient){

			for (int dim = 0; dim < mesh->ndimension; dim++) {
				int cell_dim = dim+cell*mesh->ndimension;
				dfloat R_new  = rho_f[fid]*mesh->phiU[fid]*U[cell_dim]
							  + rho_f[fid]*mesh->phiU[fid]*mesh->magd[fid]*mesh->bcvalueVector[dim];

				R_new  		  = (alpha/mesh->V[cell])*R_new;
				mesh->R[cell_dim]  = mesh->R[cell_dim]  + R_new;
			}

		}
	}









	free(rho_f);
	return 0.0;
}
