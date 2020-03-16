#include "mesh.h"
double fvcDivergenceOfSurfaceScalar(dfloat alpha, dfloat* phiU,mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {

		double sum = 0.0;

		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			sum = sum + phiU[fid];

		}

		dfloat r_new = alpha*sum/mesh->V[cell];

		mesh->r[cell] = mesh->r[cell]+ r_new;
	}

	return 0.0;
}
