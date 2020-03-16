#include "mesh.h"

dfloat insComputeL2Norm(dfloat* delU,int n);

void insWriteSolutionField(mesh_t *mesh){

	int n = 50;
    char *variableName ;
    variableName	= (char*) calloc(n, sizeof(char));

	if (mesh->timeStep % mesh->WriteFrequency == 0) {

		//---> to terminal monitoring
		printf("Time Step: %d\t Time: %.8e\t \n",mesh->timeStep, mesh->time);



		strcpy(variableName, "U");
		printSolutionVolumeVector(mesh->U, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "p");
		printSolutionVolumeScalar(mesh->p, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "rho");
		printSolutionVolumeScalar(mesh->rho, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "mu");
		printSolutionVolumeScalar(mesh->mu, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "divphiU");
		printSolutionVolumeScalar(mesh->divphiU, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "U0");
		printSolutionVolumeVector(mesh->U0, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "U00");
		printSolutionVolumeVector(mesh->U00, variableName, mesh->timeStep, mesh);

	}





	//===========================================================================!

    strcpy(variableName, "testCase/residual.txt");

    if (mesh->timeStep == 0){remove("testCase/residual.txt");}

	dfloat *delU; // change in U
	createField(&delU,volumeVector,mesh);

	for(int i=0;i<mesh->ncells*mesh->ndimension;i++){
		delU[i] = (mesh->U[i]-mesh->U0[i])/mesh->deltatime;
	}

	dfloat L2NormU = insComputeL2Norm(delU,mesh->ncells*mesh->ndimension);



	free(delU);


	FILE * fptr;

	fptr = fopen (variableName, "a");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}


	if (mesh->timeStep > 0){
	fprintf(fptr,"%d\t %6.10f \n",mesh->timeStep, L2NormU);}
	fclose(fptr);


	if (mesh->timeStep % mesh->WriteFrequency == 0) {
		printf("UMomentum: %.8e\t \n\n", L2NormU);
	}


    free(variableName);
}



dfloat insComputeL2Norm(dfloat* delU,int n){

	dfloat L2Norm = 0.0;

	dfloat sum = 0.0;
	for (int i=0;i<n;i++){
		sum = sum + delU[i]*delU[i];
	}

	L2Norm = sqrt(sum/n);

	return L2Norm;
}
