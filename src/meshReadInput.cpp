
#include "mesh.h"

void meshReadInput(mesh_t *mesh){

	mesh->ncellVertices	 = 4;
	mesh->ncellFaces  	 = 4;
	mesh->nfaceVertices  = 2;
	mesh->ndimension 	 = 3;




	dint * meshStats;
	meshStats = (dint*) calloc(2, sizeof(dint));


	FILE *myFile;
	myFile = fopen("meshGenerator/finiteVolumeMeshStatistics.txt", "r");


    if (myFile == NULL){
        printf("Error Reading File 'meshGenerator/finiteVolumeMeshStatistics.txt' \n");
        exit (0);
    }


    for (int i = 0; i < 2; i++){
        fscanf(myFile, "%d", &meshStats[i] );
    }


    fclose(myFile);



	mesh->ncellsx = meshStats[0];
	mesh->ncellsy = meshStats[1];
	mesh->ncells  = mesh->ncellsx*mesh->ncellsy;

	mesh->nvertices  = mesh->ncells*mesh->ncellVertices;


	 free(meshStats);


}
