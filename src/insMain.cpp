/******************************************************************************
                     2 Dimensional Finite Volume Numerical Solver.
                Chorin Projection Algorithm to solve Navier Stokes Equations.
*******************************************************************************/

// valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./main

#include "mesh.h"

int main(int argc, char **argv){



	clock_t t;
	t = clock();


	mesh_t *mesh = (mesh_t*) calloc(1, sizeof(mesh_t));

	meshReadInput(mesh);

	meshConstructFields(mesh);
	meshGenerateCellConnectivity(mesh);

	meshRead(mesh);
	meshGenerateCellMetrics(mesh);

	meshGenerateBoundaryName(mesh);

	printf("\nStarting time marching loop \n");

	solverConstructFields(mesh);

	solverSetControls(mesh);

	insConstructSolutionFields(mesh);

	insSetInitialConditions(mesh);

	insWriteSolutionField(mesh);


	while (mesh->stopCriterion==false){

		copyDataToFrom(mesh->U0,mesh->U,volumeVector,mesh);
		copyDataToFrom(mesh->U00,mesh->U0,volumeVector,mesh);


		insConstructFlux(mesh->U,mesh->phiU, U, mesh);

		insConstructUEquation(mesh);

		solveVector(mesh->U,mesh);

		insConstructFlux(mesh->U,mesh->phiU, U, mesh);


		insConstructPEquation(mesh);

		int refCell  = 0;
		int refValue = 0;
		setReferenceValueScalar(mesh->p,p, refCell,refValue,mesh);

		solveScalar(mesh->p,mesh);

		insCorrectU(mesh);
		insConstructFlux(mesh->U,mesh->phiU, U, mesh);



		fvdDivergenceOfSurfaceScalar(mesh->phiU, mesh->divphiU, mesh);


		//=========================================!
		mesh->timeStep++;
		mesh->time = mesh->timeStep*mesh->deltatime;

		insWriteSolutionField(mesh);

		solverUpdateStoppingCriterion(mesh);
		//=========================================!
	}













	insDestructSolutionFields(mesh);
	solverDestructFields(mesh);
	meshDestructFields(mesh);

	free(mesh);

	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

	printf("Solver took %f seconds to execute \n", time_taken);

}






