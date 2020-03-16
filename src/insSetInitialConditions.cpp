#include "mesh.h"
#include "../input/input.h"

void insSetInitialConditions(mesh_t *mesh){



	int dimx = 0; // dim = 0 gives x component
	int dimy = 1; // dim = 1 gives y component
	int dimz = 2; // dim = 2 gives z component

	int idx,idy,idz;

	for(int cell=0;cell<mesh->ncells;++cell){

		idx	= dimx+cell*mesh->ndimension;
		idy	= dimy+cell*mesh->ndimension;
		idz	= dimz+cell*mesh->ndimension;

		mesh->mu[cell]  = input_mu_initial;
		mesh->rho[cell] = input_rho_initial;

		mesh->U[idx]	= input_Ux_initial;
		mesh->U[idy]	= input_Uy_initial;
		mesh->U[idz]	= input_Uz_initial;

		mesh->p[cell]	= input_P_initial;

	}


}
