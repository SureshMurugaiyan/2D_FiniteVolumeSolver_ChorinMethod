#include "mesh.h"

void printSolutionVolumeVector(dfloat* phi, char *fileName,int timeStep,mesh_t *mesh){

	//=================================================================================!
	int dimension;

	int n = 50;

    char *directory ;
    char *subdirectory ;
    char *newFilelName ;


    directory		= (char*) calloc(n, sizeof(char));
    subdirectory	= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    sprintf(subdirectory,"%d",timeStep);
    strcat(directory, subdirectory);
    mkdir(directory, 0777);
    strcat(directory, "/");


	FILE * fptr;

	//=================================================================================!
	dimension = 0;
	strcpy(newFilelName, directory);
	strcat(newFilelName, fileName);
	strcat(newFilelName, "X.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

			int cell_dim = dimension + cell*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[cell_dim]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	//=================================================================================!
	dimension = 1;
	strcpy(newFilelName, directory);
	strcat(newFilelName, fileName);
	strcat(newFilelName, "Y.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){


			int cell_dim = dimension + cell*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[cell_dim]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);


	//=================================================================================!
	dimension = 2;
	strcpy(newFilelName, directory);
	strcat(newFilelName, fileName);
	strcat(newFilelName, "Z.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

			int cell_dim = dimension + cell*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[cell_dim]);


		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);


	//=================================================================================!
	free(directory);
	free(subdirectory);
	free(newFilelName);


}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!


void printSolutionVolumeScalar(dfloat* phi, char *fileName,int timeStep,mesh_t *mesh){

	//=================================================================================!
	int n = 50;

    char *directory ;
    char *subdirectory ;
    char *newFilelName ;


    directory		= (char*) calloc(n, sizeof(char));
    subdirectory	= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    sprintf(subdirectory,"%d",timeStep);
    strcat(directory, subdirectory);
    mkdir(directory, 0777);
    strcat(directory, "/");
	strcpy(newFilelName, directory);
	strcat(newFilelName, fileName);

	FILE * fptr;

	//=================================================================================!

	strcat(newFilelName, ".txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

			fprintf(fptr,"%6.10f \t",phi[cell]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	//=================================================================================!
	free(directory);
	free(subdirectory);
	free(newFilelName);


}
