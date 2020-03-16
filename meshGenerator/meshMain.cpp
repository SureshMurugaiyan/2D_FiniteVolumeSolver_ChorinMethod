/******************************************************************************
                     2 Dimensional Finite Volume Numerical Solver.
                Chorin Projection Algorithm to solve Navier Stokes Equations.
*******************************************************************************/

// valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./main
// clear && g++ meshMain.cpp -o main && ./main

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "math.h"
#include "meshInput.h"

#define dfloat double
#define dint size_t

#define mymax(a,b) ( ((a)>(b)) ? (a):(b) )
#define mymin(a,b) ( ((a)<(b)) ? (a):(b) )


typedef enum {
	cartesian	=	0,
	polar		=	1,

} inputCoordinate;

typedef struct{

	dint ncellsx; /* number of cells along each row = colmax*/
	dint ncellsy; /* number of cells along each col = rowmax */
	dint ncells; /* number of cells in mesh */

	dint nverticesx; /* number of cells along each row = colmax*/
	dint nverticesy; /* number of cells along each col = rowmax */
	dint nvertices; /* number of cells in mesh */

	dint ndimension; /* nmeshdimension = x,y,z stored for 2D Mesh */

	dfloat *vertices; /* coordinates of vertices */
	dint ncellVertices; /*number of vertices per cell */
	dint *cellToVertex; /* Global to Global Vertex connectivity */

}mesh_t;

void createBoundaryMeshRectangle(mesh_t *mesh);
void createSurfaceMesh(mesh_t *mesh);
void writeMesh(mesh_t *mesh);
void convertPolarToCartesian(mesh_t *mesh);
void writeFiniteVolumeMesh(mesh_t *mesh);
void meshCellToVerticesConnectivity(mesh_t *mesh);
int main(int argc, char **argv){



	clock_t t;
	t = clock();

	dint coordinateSystem = input_coordinate ;

	mesh_t *mesh = (mesh_t*) calloc(1, sizeof(mesh_t));

	mesh->ncellsx = input_ncellsx;
	mesh->ncellsy = input_ncellsy;
	mesh->ncells  = mesh->ncellsx*mesh->ncellsy;

	mesh->nverticesx = mesh->ncellsx+1;
	mesh->nverticesy = mesh->ncellsy+1;
	mesh->nvertices  = mesh->nverticesx*mesh->nverticesy;

	mesh->ndimension 	 = 3;


	mesh->vertices = (dfloat*) calloc(mesh->nvertices*mesh->ndimension, sizeof(dfloat));

	for (int i = 0; i < mesh->nvertices*mesh->ndimension; i++) {
		mesh->vertices[i] = 0.0;
	}


	printf("Generating Boundary Mesh  \n");
	createBoundaryMeshRectangle(mesh);






	printf("Generating Surface Mesh \n");
	createSurfaceMesh(mesh);


	if(coordinateSystem == polar) {

		convertPolarToCartesian(mesh);
	}


	printf("Writing Surface Mesh \n");
	writeMesh(mesh);


	mesh->ncellVertices 	 = 4;

	mesh->cellToVertex 			= (dint*) calloc(mesh->ncells*mesh->ncellVertices, sizeof(dint));
	for (int i = 0; i < (mesh->ncells*mesh->ncellVertices); i++) {
		mesh->cellToVertex[i] = 0;
	}

	meshCellToVerticesConnectivity(mesh);

	printf("Writing Finite Volume Surface Mesh \n");
	writeFiniteVolumeMesh(mesh);


	free(mesh->cellToVertex);
	free(mesh->vertices);
	free(mesh);

	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

	printf("Mesh Generation took %f seconds to execute \n", time_taken);

}

void createBoundaryMeshRectangle(mesh_t *mesh){

	/*
	 * (X1,Y1)*----------------*(X4,Y4)
	 * 		  |                |
	 *        |				   |
	 *        |                |
	 * (X2,Y2)*----------------*(X3,Y3)
	 */


	dfloat x1, y1, z1;   // (x1,y1,z1)--> north west corner
	dfloat x2, y2, z2;   // (x2,y2,z2)--> south west corner
	dfloat x3, y3, z3;   // (x3,y3,z3)--> south east corner
	dfloat x4, y4, z4;   // (x4,y4,z4)--> north east corner

	x1 = input_x1; y1 = input_y1; z1 = input_z1;
	x2 = input_x2; y2 = input_y2; z2 = input_z2;// North Boundary
	x3 = input_x3; y3 = input_y3; z3 = input_z3;
	x4 = input_x4; y4 = input_y4; z4 = input_z4;// South Boundary

	dint northwestVertexID,southwestVertexID,southeastVertexID,northeastVertexID;
	dint dim_x,dim_y,dim_z;
	dint northwestVertexID_x,southwestVertexID_x,southeastVertexID_x,northeastVertexID_x;
	dint northwestVertexID_y,southwestVertexID_y,southeastVertexID_y,northeastVertexID_y;
	dint northwestVertexID_z,southwestVertexID_z,southeastVertexID_z,northeastVertexID_z;

	northwestVertexID=0;
	southwestVertexID=(mesh->nvertices-mesh->nverticesx);
	southeastVertexID=(mesh->nvertices-1);
	northeastVertexID=(mesh->nverticesx-1);

	dim_x=0;
	dim_y=1;
	dim_z=2;


	northwestVertexID_x = dim_x + northwestVertexID*mesh->ndimension ;
	northwestVertexID_y = dim_y + northwestVertexID*mesh->ndimension ;
	northwestVertexID_z = dim_z + northwestVertexID*mesh->ndimension ;

	southwestVertexID_x = dim_x + southwestVertexID*mesh->ndimension ;
	southwestVertexID_y = dim_y + southwestVertexID*mesh->ndimension ;
	southwestVertexID_z = dim_z + southwestVertexID*mesh->ndimension ;


	southeastVertexID_x = dim_x + southeastVertexID*mesh->ndimension ;
	southeastVertexID_y = dim_y + southeastVertexID*mesh->ndimension ;
	southeastVertexID_z = dim_z + southeastVertexID*mesh->ndimension ;

	northeastVertexID_x = dim_x + northeastVertexID*mesh->ndimension ;
	northeastVertexID_y = dim_y + northeastVertexID*mesh->ndimension ;
	northeastVertexID_z = dim_z + northeastVertexID*mesh->ndimension ;

	//========================================================================!
	// Fix the corners vertices of the grid
	mesh->vertices[northwestVertexID_x] = x1;// North west Corner
	mesh->vertices[northwestVertexID_y] = y1;
	mesh->vertices[northwestVertexID_z] = z1;

	mesh->vertices[southwestVertexID_x] = x2;// South west Corner
	mesh->vertices[southwestVertexID_y] = y2;
	mesh->vertices[southwestVertexID_z] = z2;

	mesh->vertices[southeastVertexID_x] = x3;// South east Corner
	mesh->vertices[southeastVertexID_y] = y3;
	mesh->vertices[southeastVertexID_z] = z3;

	mesh->vertices[northeastVertexID_x] = x4;//  North east Corner
	mesh->vertices[northeastVertexID_y] = y4;
	mesh->vertices[northeastVertexID_z] = z4;

	dint count;

	//========================================================================!
	// Generate North Boundary Mesh
	//========================================================================!


	count = 0;  // Initialize counter

	for( dint vertex = northwestVertexID; vertex < (northeastVertexID+1);vertex++){
		for(dint dimension=0;dimension<mesh->ndimension;dimension++){

			dint vid_dim = dimension + vertex*mesh->ndimension ;

			dint northwestVertexID_dim,northeastVertexID_dim;
			dfloat minVal,maxVal;


			northwestVertexID_dim  = dimension + northwestVertexID*mesh->ndimension;
			northeastVertexID_dim  = dimension + northeastVertexID*mesh->ndimension;

			minVal = mesh->vertices[northwestVertexID_dim];
			maxVal = mesh->vertices[northeastVertexID_dim];

			mesh->vertices[vid_dim] =  minVal+(((maxVal-minVal)/(mesh->nverticesx-1)))*count;

		}
		count++;
	}

	//========================================================================!
	// Generate South Boundary Mesh
	//========================================================================!


	count = 0;  // Initialize counter

	for( dint vertex = southwestVertexID; vertex < (southeastVertexID+1);vertex++){
		for(dint dimension=0;dimension<mesh->ndimension;dimension++){

			dint vid_dim = dimension + vertex*mesh->ndimension ;

			dint southwestVertexID_dim,southeastVertexID_dim;
			dfloat minVal,maxVal;


			southwestVertexID_dim  = dimension + southwestVertexID*mesh->ndimension;
			southeastVertexID_dim  = dimension + southeastVertexID*mesh->ndimension;

			minVal = mesh->vertices[southwestVertexID_dim];
			maxVal = mesh->vertices[southeastVertexID_dim];

			mesh->vertices[vid_dim] =  minVal+(((maxVal-minVal)/(mesh->nverticesx-1)))*count;

		}
		count++;
	}


	//========================================================================!
	// Generate West Boundary Mesh
	//========================================================================!


	count = 0;  // Initialize counter

	for( dint vertex = northwestVertexID; vertex < (southwestVertexID+1);vertex=(vertex+mesh->nverticesx)){
		for(dint dimension=0;dimension<mesh->ndimension;dimension++){

			dint vid_dim = dimension + vertex*mesh->ndimension ;

			dint northwestVertexID_dim,southwestVertexID_dim;
			dfloat minVal,maxVal;


			northwestVertexID_dim  = dimension + northwestVertexID*mesh->ndimension;
			southwestVertexID_dim  = dimension + southwestVertexID*mesh->ndimension;

			minVal = mesh->vertices[northwestVertexID_dim];
			maxVal = mesh->vertices[southwestVertexID_dim];

			mesh->vertices[vid_dim] =  minVal+(((maxVal-minVal)/(mesh->nverticesy-1)))*count;

		}
		count++;
	}


	//========================================================================!
	// Generate East Boundary Mesh
	//========================================================================!


	count = 0;  // Initialize counter

	for( dint vertex = northeastVertexID; vertex < (southeastVertexID+1);vertex=(vertex+mesh->nverticesx)){
		for(dint dimension=0;dimension<mesh->ndimension;dimension++){

			dint vid_dim = dimension + vertex*mesh->ndimension ;

			dint northeastVertexID_dim,southeastVertexID_dim;
			dfloat minVal,maxVal;


			northeastVertexID_dim  = dimension + northeastVertexID*mesh->ndimension;
			southeastVertexID_dim  = dimension + southeastVertexID*mesh->ndimension;

			minVal = mesh->vertices[northeastVertexID_dim];
			maxVal = mesh->vertices[southeastVertexID_dim];

			mesh->vertices[vid_dim] =  minVal+(((maxVal-minVal)/(mesh->nverticesy-1)))*count;

		}
		count++;
	}

}


void createSurfaceMesh(mesh_t *mesh){


	// Transfinite Interpolation for creating inner points
	// https://en.wikipedia.org/wiki/Transfinite_interpolation
	double delr = 1.0/(mesh->nverticesx-1); // computational space unit length
	double dels = 1.0/(mesh->nverticesy-1); // computational space unit height
	double r=0.0,s=0.0;

	dint northwestVertexID,southwestVertexID,southeastVertexID,northeastVertexID;

	northwestVertexID=0;
	southwestVertexID=(mesh->nvertices-mesh->nverticesx);
	southeastVertexID=(mesh->nvertices-1);
	northeastVertexID=(mesh->nverticesx-1);

	for(int vertexY=1;vertexY<(mesh->nverticesy-1);vertexY++){
		for(int vertexX=1;vertexX<(mesh->nverticesx-1);vertexX++){
			for(int dimension=0;dimension<mesh->ndimension;dimension++){

				dint vid     = vertexX + vertexY*mesh->nverticesx;
				dint vid_dim = dimension+vid*mesh->ndimension;

				dint northwestVertexID_dim, southwestVertexID_dim;
				dint southeastVertexID_dim, northeastVertexID_dim;

				northwestVertexID_dim  = dimension + northwestVertexID*mesh->ndimension;
				southwestVertexID_dim  = dimension + southwestVertexID*mesh->ndimension;
				southeastVertexID_dim  = dimension + southeastVertexID*mesh->ndimension;
				northeastVertexID_dim  = dimension + northeastVertexID*mesh->ndimension;

				dint northboundaryVertex = vertexX + 0*mesh->nverticesx;
				dint southboundaryVertex = vertexX + (mesh->nverticesy-1)*mesh->nverticesx;
				dint westboundaryVertex  = 0 + vertexY*mesh->nverticesx;
				dint eastboundaryVertex  = (mesh->nverticesx-1) + vertexY*mesh->nverticesx;

				dint northboundaryvertex_dim = dimension + northboundaryVertex*mesh->ndimension;
				dint southboundaryvertex_dim = dimension + southboundaryVertex*mesh->ndimension;
				dint westboundaryvertex_dim  = dimension + westboundaryVertex*mesh->ndimension;
				dint eastboundaryvertex_dim  = dimension + eastboundaryVertex*mesh->ndimension;


				mesh->vertices[vid_dim] =     (1-s)*mesh->vertices[southboundaryvertex_dim]
										+ 	s*mesh->vertices[northboundaryvertex_dim]
										+ 	(1-s)*(mesh->vertices[westboundaryvertex_dim]
										-(1-s)*mesh->vertices[southwestVertexID_dim]
										- s*mesh->vertices[northwestVertexID_dim])
										+	r*(mesh->vertices[eastboundaryvertex_dim]
										-(1-s)*mesh->vertices[southeastVertexID_dim]
										- s*mesh->vertices[northeastVertexID_dim]);

			}
		}
	}


}

void convertPolarToCartesian(mesh_t *mesh){

	for(int vertices=0;vertices<mesh->nvertices;vertices++){

			dint r_dim     = 0 + vertices*mesh->ndimension;
			dint theta_dim = 1 + vertices*mesh->ndimension;

			dfloat r 	 = mesh->vertices[r_dim];
			dfloat theta = mesh->vertices[theta_dim];

			mesh->vertices[r_dim] 		= r*cos(theta);
			mesh->vertices[theta_dim] 	= r*sin(theta);

	}


}

void writeMesh(mesh_t *mesh){

	int dimension;
	char *fileName ;

	int n = 50;
	FILE * fptr;


	//==================================================================!
	// Print X-Component
	//==================================================================!
	fileName	= (char*) calloc(n, sizeof(char));
	dimension = 0;
	strcpy(fileName, "VX.txt");


	fptr = fopen (fileName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int vertex = 0; vertex < mesh->nvertices;vertex++){

		int vid_dim = dimension + vertex*mesh->ndimension ;
		fprintf(fptr,"%lf \t",mesh->vertices[vid_dim]);

		int vertexCol = vertex % mesh->nverticesx;
		if (vertexCol==(mesh->nverticesx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	free(fileName);
	//==================================================================!
	// Print Y-Component
	//==================================================================!
	fileName	= (char*) calloc(n, sizeof(char));
	dimension = 1;
	strcpy(fileName, "VY.txt");


	fptr = fopen (fileName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int vertex = 0; vertex < mesh->nvertices;vertex++){

		int vid_dim = dimension + vertex*mesh->ndimension ;
		fprintf(fptr,"%6.10f \t",mesh->vertices[vid_dim]);

		int vertexCol = vertex % mesh->nverticesx;
		if (vertexCol==(mesh->nverticesx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	free(fileName);

	//==================================================================!
	// Print Z-Component
	//==================================================================!
	fileName	= (char*) calloc(n, sizeof(char));
	dimension = 2;
	strcpy(fileName, "VZ.txt");


	fptr = fopen (fileName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int vertex = 0; vertex < mesh->nvertices;vertex++){

		int vid_dim = dimension + vertex*mesh->ndimension ;
		fprintf(fptr,"%6.10f \t",mesh->vertices[vid_dim]);

		int vertexCol = vertex % mesh->nverticesx;
		if (vertexCol==(mesh->nverticesx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	free(fileName);

}


void meshCellToVerticesConnectivity(mesh_t *mesh){

	// This is Hard Coded for 2D
	if (mesh->ncellVertices !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellVertices should be set to %i!\n", 4 );
		exit ( 1 );
	}

	int *globalvertices;
	globalvertices	= (int*) calloc(mesh->ncellVertices, sizeof(int));

	for(int cell=0;cell<mesh->ncells; cell++){

		dint cellRow,cellCol;
		cellRow = cell / mesh->ncellsx;
		cellCol = cell % mesh->ncellsx;

		globalvertices[0] =  (cellCol+0) + (cellRow+0)*mesh->nverticesx;
		globalvertices[1] =  (cellCol+0) + (cellRow+1)*mesh->nverticesx;
		globalvertices[2] =  (cellCol+1) + (cellRow+1)*mesh->nverticesx;
		globalvertices[3] =  (cellCol+1) + (cellRow+0)*mesh->nverticesx;

		for(int vert=0;vert<mesh->ncellVertices; vert++){

			int vid = vert+cell*mesh->ncellVertices;
			mesh->cellToVertex[vid]=globalvertices[vert];
		}
	}

	free(globalvertices);
}


void writeFiniteVolumeMesh(mesh_t *mesh){


	int dimension;
	int n = 50;
	char *fileName ;
	fileName	= (char*) calloc(n, sizeof(char));
	FILE * fptr;




	// Write Mesh Statistics
	strcpy(fileName, "finiteVolumeMeshStatistics.txt");
	fptr = fopen (fileName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	fprintf(fptr,"%d \n",mesh->ncellsx);
	fprintf(fptr,"%d \n",mesh->ncellsy);
	fclose(fptr);



// Write Mesh

	strcpy(fileName, "finiteVolumeMesh.txt");

	fptr = fopen (fileName, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellVertices;vertex++){
			for(int dimension=0;dimension<mesh->ndimension;dimension++){

				int id 	= vertex + cell*mesh->ncellVertices ;
				int vid = mesh->cellToVertex[id];
				int vid_dim = dimension + vid*mesh->ndimension ;

				fprintf(fptr,"%lf \n",mesh->vertices[vid_dim]);

			}
		}
	}
	fclose(fptr);
	free(fileName);




}
