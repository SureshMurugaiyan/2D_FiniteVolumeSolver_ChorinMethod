#include "mesh.h"
void fvdGradientOfScalar(dfloat* gradCell,dfloat *phiCell, int P_Name, mesh_t *mesh){

	dfloat *pf;
	createField(&pf,surfaceScalar,mesh);
	interpolateScalarCellToFace(mesh->p,pf,mesh);

	insConstrainByBoundaryFieldScalar(pf,mesh->p,p,mesh);


	double *sum;
	sum		= (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));


	for (int cell = 0; cell < mesh->ncells; cell++) {

		for (int i = 0; i < mesh->ndimension; i++) {
			sum[i]=0.0;
		}


		for (int face = 0; face < mesh->ncellFaces; face++) {
			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];



			for (int dim = 0; dim < mesh->ndimension; dim++) {
				int fid_dim = dim+ fid*mesh->ndimension;
				sum[dim]	=	sum[dim]+pf[fid]*mesh->Sf[fid_dim];
			}

		}

		for (int dim = 0; dim < mesh->ndimension; dim++) {
			int cell_dim = dim+ cell*mesh->ndimension;
			gradCell[cell_dim]  = sum[dim]/mesh->V[cell];
		}


	}



	free(pf);
	free(sum);
}
