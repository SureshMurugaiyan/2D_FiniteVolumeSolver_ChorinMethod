#include "mesh.h"
void printMeshVertexVector(double* phi, char *fileName,mesh_t *mesh){

	//=================================================================================!
	int dimension;

	int n = 50;

    char *directory ;
    char *newFilelName ;

    directory		= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);

	FILE * fptr;

	//=================================================================================!
	dimension = 0;

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, "X.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellVertices;vertex++){

			int vid 	= vertex + cell*mesh->ncellVertices;
			int vid_dim = dimension + vid*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[vid_dim]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	//=================================================================================!
	dimension = 1;

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, "Y.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellVertices;vertex++){

			int vid 	= vertex + cell*mesh->ncellVertices;
			int vid_dim = dimension + vid*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[vid_dim]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);


	//=================================================================================!
	dimension = 2;

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, "Z.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellVertices;vertex++){

			int vid 	= vertex + cell*mesh->ncellVertices;
			int vid_dim = dimension + vid*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[vid_dim]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);


	//=================================================================================!
	free(directory);
	free(newFilelName);


}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!


void printMeshSurfaceVector(double* phi, char *fileName,mesh_t *mesh){

	//=================================================================================!
	int dimension;

	int n = 50;

    char *directory ;
    char *newFilelName ;

    directory		= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);

	FILE * fptr;

	//=================================================================================!
	dimension = 0;

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, "X.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellFaces;vertex++){

			int fid 	= vertex + cell*mesh->ncellVertices;
			int fid_dim = dimension + fid*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[fid_dim]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	//=================================================================================!
	dimension = 1;

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, "Y.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellFaces;vertex++){

			int fid 	= vertex + cell*mesh->ncellVertices;
			int fid_dim = dimension + fid*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[fid_dim]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);


	//=================================================================================!
	dimension = 2;

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, "Z.txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellFaces;vertex++){

			int fid 	= vertex + cell*mesh->ncellVertices;
			int fid_dim = dimension + fid*mesh->ndimension;

			fprintf(fptr,"%6.10f \t",phi[fid_dim]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);


	//=================================================================================!
	free(directory);
	free(newFilelName);


}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!


void printMeshVolumeVector(double* phi, char *fileName,mesh_t *mesh){

	//=================================================================================!
	int dimension;

	int n = 50;

    char *directory ;
    char *newFilelName ;

    directory		= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);

	FILE * fptr;

	//=================================================================================!
	dimension = 0;

	strcpy(newFilelName, "testCase/Mesh/");
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

	strcpy(newFilelName, "testCase/Mesh/");
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

	strcpy(newFilelName, "testCase/Mesh/");
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
	free(newFilelName);


}



void printMeshVertexScalar(double* phi, char *fileName,mesh_t *mesh){

	//=================================================================================!
	int n = 50;

    char *directory ;
    char *newFilelName ;

    directory		= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);

	FILE * fptr;

	//=================================================================================!

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, ".txt");

	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellVertices;vertex++){
			int vid 	= vertex + cell*mesh->ncellVertices;
			fprintf(fptr,"%6.10f \t",phi[vid]);
		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	//=================================================================================!
	free(directory);
	free(newFilelName);


}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!


void printMeshSurfaceScalar(double* phi, char *fileName,mesh_t *mesh){

	//=================================================================================!
	int n = 50;

    char *directory ;
    char *newFilelName ;

    directory		= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);

	FILE * fptr;

	//=================================================================================!

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, ".txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellFaces;vertex++){

			int fid 	= vertex + cell*mesh->ncellVertices;

			fprintf(fptr,"%6.10f \t",phi[fid]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	//=================================================================================!
	free(directory);
	free(newFilelName);


}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!


void printMeshVolumeScalar(double* phi, char *fileName,mesh_t *mesh){

	//=================================================================================!
	int n = 50;

    char *directory ;
    char *newFilelName ;

    directory		= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);

	FILE * fptr;

	//=================================================================================!

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
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
	free(newFilelName);


}



//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$!

// For integer dataType

void printMeshSurfaceScalar(dint* phi, char *fileName,mesh_t *mesh){

	//=================================================================================!
	int n = 50;

    char *directory ;
    char *newFilelName ;

    directory		= (char*) calloc(n, sizeof(char));
    newFilelName	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);

	FILE * fptr;

	//=================================================================================!

	strcpy(newFilelName, "testCase/Mesh/");
	strcat(newFilelName, fileName);
	strcat(newFilelName, ".txt");


	fptr = fopen (newFilelName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellFaces;vertex++){

			int fid 	= vertex + cell*mesh->ncellVertices;

			fprintf(fptr,"%d \t",phi[fid]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	//=================================================================================!
	free(directory);
	free(newFilelName);


}

