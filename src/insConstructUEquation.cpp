#include "mesh.h"
void insConstructUEquation(mesh_t *mesh){

	for(int i=0;i<mesh->ncells*mesh->ndimension;++i){
		mesh->AP[i] = 0.0;
		mesh->R[i]  = 0.0;
		mesh->R1[i] = 0.0;
	}
	for(int i=0;i<mesh->ncells*mesh->ncellFaces*mesh->ndimension;++i){
		mesh->AN[i] = 0.0;
	}


	double Ueqn=0.0;


	double GammaLaplacian  	= -0.01;   // Constant Coefficient for viscous terms
	double GammaDivergence 	=  1.0;   // Constant Coefficient for divergence terms



	Ueqn =	ddteulerbackward(mesh->rho,mesh->U0, mesh->U00, mesh)
		+  fvcLaplacianOfVector (GammaLaplacian, mesh->mu, mu, mesh->U,U,mesh)
		+  fvcDivergenceOfVector (GammaDivergence, mesh->rho, rho,mesh->U,U,mesh->phiU,mesh);


}
