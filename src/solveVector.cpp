#include "mesh.h"
void solveVector(double* U, mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int dim = 0; dim < mesh->ndimension; dim++) {
			int cell_dim = dim+cell*mesh->ndimension;

			U[cell_dim] = -mesh->R[cell_dim]/mesh->AP[cell_dim];
		}
	}

}
