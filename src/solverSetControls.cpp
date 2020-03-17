
#include "mesh.h"

void solverSetControls(mesh_t *mesh){

	mesh->timeStepMax		= 10000;
	mesh->finalTime  		= 10000*0.01;
	mesh->deltatime  		= 0.01;
	mesh->WriteFrequency	= 1000;
	mesh->nCorrMax  		= 1;
	mesh->time  			= 0.0; // start time
	mesh->timeStep  		= 0; // start time step
	mesh->stopCriterion  	= false;


	mesh->lambda  	=	1.0;	// relaxation parameter
	mesh->maxNorm 	=	1e-6;	// max norm of solution
	mesh->maxitrEqn	=	2000;	// max number of iterations

}
