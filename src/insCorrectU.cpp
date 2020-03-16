#include "mesh.h"
void insCorrectU(mesh_t *mesh){

	dfloat *gradP; // cell center Pressure gradient
	createField(&gradP,volumeVector,mesh);

	fvdGradientOfScalar(gradP,mesh->p,p,mesh);

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int dim = 0; dim < mesh->ndimension; dim++) {
			int cell_dim = dim+ cell*mesh->ndimension;

			mesh->U[cell_dim] = mesh->U[cell_dim]-gradP[cell_dim];
		}

	}


	free(gradP);


}
