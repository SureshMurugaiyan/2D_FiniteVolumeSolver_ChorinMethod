#include "mesh.h"


double ddteulerbackward(dfloat* rho, dfloat* U0, dfloat* U00,mesh_t *mesh){



// For First time step , use First Order Euler

	if (mesh->timeStep==0){

		for (int cell = 0; cell < mesh->ncells; cell++) {
			for (int dimension = 0; dimension < mesh->ndimension; dimension++) {

				int cell_dim = dimension + cell*mesh->ndimension;

				dfloat AP_new = rho[cell]/mesh->deltatime;
				dfloat R_new  = - rho[cell]*U0[cell_dim]/mesh->deltatime;

				mesh->AP[cell_dim] = mesh->AP[cell_dim] + AP_new;
				mesh->R[cell_dim]  = mesh->R[cell_dim]  + R_new;

			}
		}

	}

	// From second time step , use euler backward

	if (mesh->timeStep> 0){

		for (int cell = 0; cell < mesh->ncells; cell++) {
			for (int dim = 0; dim < mesh->ndimension; dim++) {

				int cell_dim = dim + cell*mesh->ndimension;

				dfloat AP_new = 3.0*rho[cell]/(2.0*mesh->deltatime);
				dfloat R_new  = - (4.0*rho[cell]*U0[cell_dim]-rho[cell]*U00[cell_dim])/(2.0*mesh->deltatime);

				mesh->AP[cell_dim] = mesh->AP[cell_dim] + AP_new;
				mesh->R[cell_dim]  = mesh->R[cell_dim]  + R_new;
			}
		}

	}



	return 0.0;

}
