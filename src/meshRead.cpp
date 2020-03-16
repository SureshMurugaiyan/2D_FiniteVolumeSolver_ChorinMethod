
#include "mesh.h"
#include "../input/input.h"

void writeMesh(mesh_t *mesh);


void meshRead(mesh_t *mesh){

	FILE *myFile;
	myFile = fopen("meshGenerator/finiteVolumeMesh.txt", "r");

    if (myFile == NULL){
        printf("Error Reading File 'meshGenerator/finiteVolumeMesh.txt' \n");
        exit (0);
    }



    for (int i = 0; i < mesh->nvertices*mesh->ndimension; i++){
        fscanf(myFile, "%lf",&mesh->vertices[i] );
    }


    fclose(myFile);


    writeMesh(mesh);
}


void writeMesh(mesh_t *mesh){

	int n = 50;
    char *variableName ;
    variableName	= (char*) calloc(n, sizeof(char));

	int dimension;
	strcpy(variableName, "V");
	printMeshVertexVector(mesh->vertices, variableName, mesh);


	free(variableName);
}
