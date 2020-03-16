#include "mesh.h"
void insConstructFlux(double* VectorField, double* FluxField, int UName, mesh_t *mesh){

	dfloat *VectorField_f; // Face value of vector field
	createField(&VectorField_f,surfaceVector,mesh);

	interpolateVectorCellToFace(VectorField,VectorField_f,mesh);
	insConstrainByBoundaryFieldVector(VectorField_f,VectorField,UName,mesh);

	insConstructFluxofSurfaceVector(VectorField_f,FluxField,mesh);

	free(VectorField_f);



	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Flux of Vector \n" );
	//	printf ( " --------------------------------- \n" );
	//	printf ( " Cell ID :    West  South  East  North \n" );
	//
	//	for (int cell = 0; cell < mesh->ncells; cell++) {
	//
	//		printf ( " Cell%3i : ", cell );
	//
	//		for (int face = 0; face < mesh->ncellFaces; face++) {
	//
	//			int fid = face 	+ cell*mesh->ncellFaces;
	//
	//			printf ( " %5lf", FluxField[fid] );
	//		}
	//
	//		printf ( "\n" );
	//	}

}


void insConstructFluxofSurfaceVector(double* VectorField_f, double* FluxField, mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;

			double sum=0.0;

			for (int dim = 0; dim < mesh->ndimension; dim++) {

				int fid_dim = dim+ fid*mesh->ndimension;

				sum	=	sum+VectorField_f[fid_dim]*mesh->Sf[fid_dim];

			}

			FluxField[fid] = sum;
		}
	}

}
