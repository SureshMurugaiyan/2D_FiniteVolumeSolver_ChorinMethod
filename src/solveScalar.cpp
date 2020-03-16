#include "mesh.h"
void solveScalar(double* P, mesh_t *mesh){

	dfloat maxNorm 	=	mesh->maxNorm;
	dfloat lambda 	=	mesh->lambda;
	int	maxitrEqn	=	mesh->maxitrEqn;


	int itrEqn = 0;
	bool stopCriterionUEqn=false;



	dfloat delPhi=0.0;
	dfloat* sum;
	createField(&sum,volumeScalar,mesh);



	while (stopCriterionUEqn==false){

		dfloat residual=0.0;


		//---------

//		for (int cell = 0; cell < mesh->ncells; cell++) {
//			sum =0.0;
//			delPhi=0.0;
//			for (int face = 0; face < mesh->ncellFaces; face++) {
//
//				int fid = face+cell*mesh->ncellFaces;
//				int cell_n = mesh->cellToCells[fid];
//
//
//				if (cell_n>(-1)){
//
//				sum = sum + mesh->aN[fid]*P[cell_n];
//				}
//
//			}
//
//			sum = sum+ mesh->r[cell]+mesh->aP[cell]*P[cell];
//			delPhi = -sum/mesh->aP[cell];
//			P[cell] = P[cell]+lambda*delPhi;
//
//			residual = residual + sum*sum ;
//
//		}




		//---------


			for (int face = 0; face < mesh->nInnerFaces; face++){

				int fid 	= mesh->innerFaces[face];
				int cell    = mesh->faceToOwnerCell[fid];
				int cell_n  = mesh->faceToNeighborCell[fid];

				sum[cell] = sum[cell] + mesh->aN[fid]*P[cell_n];

			}

			for (int cell = 0; cell < mesh->ncells; cell++) {

				sum[cell] = sum[cell]+mesh->r[cell]+mesh->aP[cell]*P[cell];
				delPhi = -sum[cell]/mesh->aP[cell];
				P[cell] = P[cell]+lambda*delPhi;
				residual = residual + sum[cell]*sum[cell] ;
				sum[cell] = 0.0;
			}

			//---------



		residual = sqrt(residual)/mesh->ncells;


		if (residual<mesh->maxNorm) {stopCriterionUEqn=true;}


		if (itrEqn==maxitrEqn) {stopCriterionUEqn=true;}

		itrEqn++;

	}

	free(sum);

//		printf(" Maximum number of Inner Iterations P Pressure, N= %d\t \n", itrEqn);


}
