
#include "mesh.h"

void meshCellToVerticesConnectivity(mesh_t *mesh);
void meshCellToCellsConnectivity(mesh_t *mesh);
void meshCellToFacesConnectivity(mesh_t *mesh);
void meshFaceToOppositeFacesConnectivity(mesh_t *mesh);
void meshFaceToVerticesConnectivity(mesh_t *mesh);
void meshFaceToLocalFaceConnectivity(mesh_t *mesh);
void meshFaceToOwnerCellConnectivity(mesh_t *mesh);
void meshFaceToNeighborCellConnectivity(mesh_t *mesh);
void meshCalculateNoOfBoundaryandInnerCells(mesh_t *mesh);
void meshCalculateNoOfBoundaryandInnerFaces(mesh_t *mesh);
void meshCalculateInnerandBoundaryCellID(mesh_t *mesh);
void meshCalculateInnerandBoundaryFaceID(mesh_t *mesh);

void meshGenerateCellConnectivity(mesh_t *mesh){

	meshCellToVerticesConnectivity(mesh);
	meshCellToCellsConnectivity(mesh);
	meshCellToFacesConnectivity(mesh);
	meshFaceToOppositeFacesConnectivity(mesh);
	meshFaceToVerticesConnectivity(mesh);
	meshFaceToLocalFaceConnectivity(mesh);
	meshFaceToOwnerCellConnectivity(mesh);
	meshFaceToNeighborCellConnectivity(mesh);
	meshCalculateNoOfBoundaryandInnerCells(mesh);
	meshCalculateNoOfBoundaryandInnerFaces(mesh);

	meshCalculateInnerandBoundaryCellID(mesh);
	meshCalculateInnerandBoundaryFaceID(mesh);

}


void meshCellToCellsConnectivity(mesh_t *mesh){


	// This is Hard Coded for 2D
	if (mesh->ncellFaces !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellFaces should be set to %i!\n", 4 );
		exit ( 1 );
	}

	int *cells;
	cells	= (int*) calloc(mesh->ncellFaces, sizeof(int));


		for (int row = 0; row < mesh->ncellsy; row++) {
			for (int col = 0; col < mesh->ncellsx; col++) {

				int cellID = col + row*mesh->ncellsx;

				cells[0] =  (col-1) + (row+0)*mesh->ncellsx; // West
				cells[1] =  (col+0) + (row+1)*mesh->ncellsx; // south
				cells[2] =  (col+1) + (row+0)*mesh->ncellsx; // east
				cells[3] =  (col+0) + (row-1)*mesh->ncellsx; // north

				for (int face = 0; face < mesh->ncellFaces; face++) {

					int fid = face 	+ cellID*mesh->ncellFaces;

					mesh->cellToCells[fid] = cells[face];


					// Correct for north boundary
					if ((row ==0) && (face==3)){
						mesh->cellToCells[fid] = -1;
					}

					// Correct for south boundary
					if ((row ==(mesh->ncellsy-1)) && (face==1)){
						mesh->cellToCells[fid] = -1;
					}


		            // Correct for West boundary
					if ((col==0) && (face==0)){
						mesh->cellToCells[fid] = -1;
					}


		            // Correct for East boundary
					if ((col==(mesh->ncellsx-1)) && (face==2)){
						mesh->cellToCells[fid] = -1;
					}

				}
			}
		}


		free(cells);


		/*************************************************************/
		/* UNIT TEST                                                 */
		/*************************************************************/
		//		printf ( " \n Cell To Cell Connectivity \n" );
		//		printf ( " --------------------------------- \n" );
		//		printf ( " Cell ID :    West  South  East  North \n" );
		//
		//		for (int cell = 0; cell < mesh->ncells; cell++) {
		//
		//			printf ( " Cell%3i : ", cell );
		//
		//			for (int face = 0; face < mesh->ncellFaces; face++) {
		//
		//				int fid = face 	+ cell*mesh->ncellFaces;
		//
		//				printf ( " %5i", mesh->cellToCells[fid] );
		//			}
		//
		//			printf ( "\n" );
		//		}


}


void meshCellToFacesConnectivity(mesh_t *mesh){


	// This is Hard Coded for 2D
	if (mesh->ncellFaces !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellFaces should be set to %i!\n", 4 );
		exit ( 1 );
	}

	int *neighborfaces;
	neighborfaces	= (int*) calloc(mesh->ncellFaces, sizeof(int));

		for (int row = 0; row < mesh->ncellsy; row++) {
			for (int col = 0; col <  mesh->ncellsx; col++) {

				int cellID = col + row*mesh->ncellsx;

				neighborfaces[0] =  2;
				neighborfaces[1] =  3;
				neighborfaces[2] =  0;
				neighborfaces[3] =  1;


				for (int face = 0; face < mesh->ncellFaces; face++) {

					int fid = face 	+ cellID*mesh->ncellFaces;

					mesh->cellToFaces[fid] = neighborfaces[face];

					// Correct for north boundary
					if ((row ==0) && (face==3)){
						mesh->cellToFaces[fid] = -1;
					}

					// Correct for south boundary
					if ((row ==(mesh->ncellsy-1)) && (face==1)){
						mesh->cellToFaces[fid] = -1;
					}


		            // Correct for West boundary
					if ((col==0) && (face==0)){
						mesh->cellToFaces[fid] = -1;
					}


		            // Correct for East boundary
					if ((col==( mesh->ncellsx-1)) && (face==2)){
						mesh->cellToFaces[fid] = -1;
					}
				}

			}

		}


	free(neighborfaces);


	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Cell To Face Connectivity \n" );
	//	printf ( " --------------------------------- \n" );
	//	printf ( " Cell ID :    West  South  East  North \n" );
	//
	//	for (int cell = 0; cell < mesh->ncells; cell++) {
	//
	//		printf ( " Cell%3i : ", cell );
	//
	//		for (int face = 0; face < mesh->ncellFaces; face++) {
	//
	//			int fid = face 	+ cell*mesh->ncellFaces;
	//
	//			printf ( " %5i", mesh->cellToFaces[fid] );
	//		}
	//
	//		printf ( "\n" );
	//	}

}


void meshCellToVerticesConnectivity(mesh_t *mesh){

	// This is Hard Coded for 2D
	if (mesh->ncellVertices !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellVertices should be set to %i!\n", 4 );
		exit ( 1 );
	}

	int *localvertices;
	localvertices	= (int*) calloc(mesh->ncellVertices, sizeof(int));

	for(int cell=0;cell<mesh->ncells; cell++){
		for(int vert=0;vert<mesh->ncellVertices; vert++){

			int vid = vert+cell*mesh->ncellVertices;
			mesh->cellToVertex[vid]=vid;
		}
	}

	free(localvertices);


	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/

	//	printf ( " \n Cell To Vertex Connectivity \n" );
	//	printf ( " --------------------------- \n" );
	//	printf ( " Vert ID :    NWest  SWest  SEast  NEast \n" );
	//
	//	for (int cell = 0; cell < mesh->ncells; cell++) {
	//
	//		printf ( " Cell%3i : ", cell );
	//
	//		for (int vert = 0; vert < mesh->ncellVertices; vert++) {
	//
	//			int vid = vert 	+ cell*mesh->ncellVertices;
	//
	//			printf ( " %5i", mesh->cellToVertex[vid] );
	//		}
	//
	//		printf ( "\n" );
	//	}

}

void meshFaceToOppositeFacesConnectivity(mesh_t *mesh){


	// This is Hard Coded for 2D
	if (mesh->ncellFaces !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellFaces should be set to %i!\n", 4 );
		exit ( 1 );
	}

	int *oppositeFaces;
	oppositeFaces	= (int*) calloc(mesh->ncellFaces, sizeof(int));

	for(int cell=0;cell<mesh->ncells; cell++){

		oppositeFaces[0] =  2;
		oppositeFaces[1] =  3;
		oppositeFaces[2] =  0;
		oppositeFaces[3] =  1;


		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face 	+ cell*mesh->ncellFaces;

			mesh->faceToOppositeFace[fid] = oppositeFaces[face];


		}

	}


	free(oppositeFaces);


	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Cell To OppositeFace Connectivity \n" );
	//	printf ( " --------------------------------- \n" );
	//	printf ( " Cell ID :    West  South  East  North \n" );
	//
	//	for (int cell = 0; cell < mesh->ncells; cell++) {
	//
	//		printf ( " Cell%3i : ", cell );
	//
	//		for (int face = 0; face < mesh->ncellFaces; face++) {
	//
	//			int fid = face 	+ cell*mesh->ncellFaces;
	//
	//			printf ( " %5i", mesh->faceToOppositeFace[fid] );
	//		}
	//
	//		printf ( "\n" );
	//	}

}

void meshFaceToVerticesConnectivity(mesh_t *mesh){


	// This is Hard Coded for 2D
	if (mesh->nfaceVertices !=2) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->nfaceVertices should be set to %i!\n", 2 );
		exit ( 1 );
	}


	mesh->faceToVertices[0] = 0;
	mesh->faceToVertices[1] = 1;
	mesh->faceToVertices[2] = 1;
	mesh->faceToVertices[3] = 2;
	mesh->faceToVertices[4] = 2;
	mesh->faceToVertices[5] = 3;
	mesh->faceToVertices[6] = 3;
	mesh->faceToVertices[7] = 0;


	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Face To Vertices Connectivity \n" );
	//	printf ( " --------------------------------- \n" );
	//	printf ( " Face ID :   Vertex1 Vertex 2 \n" );
	//
	//	for (int face = 0; face < mesh->ncellFaces; face++) {
	//
	//		printf ( " Face%3i : ", face );
	//
	//		for (int vertex = 0; vertex < mesh->nfaceVertices; vertex++) {
	//
	//			int vid = vertex 	+ face*mesh->nfaceVertices;
	//
	//			printf ( " %6i", mesh->faceToVertices[vid] );
	//		}
	//
	//		printf ( "\n" );
	//	}

}

void meshFaceToLocalFaceConnectivity(mesh_t *mesh){

	// This is Hard Coded for 2D
	if (mesh->ncellFaces !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellFaces should be set to %i!\n", 4 );
		exit ( 1 );
	}

	mesh->faceToLocalFaces[0] = 0;
	mesh->faceToLocalFaces[1] = 1;
	mesh->faceToLocalFaces[2] = 2;
	mesh->faceToLocalFaces[3] = 3;
	mesh->faceToLocalFaces[4] = 0;
	mesh->faceToLocalFaces[5] = 1;
	mesh->faceToLocalFaces[6] = 2;
	mesh->faceToLocalFaces[7] = 3;

	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Face To LocalFace Connectivity \n" );
	//	printf ( " --------------------------------- \n" );
	//	printf ( " Face ID :   Face1 Face2 \n" );
	//
	//	for (int face = 0; face < mesh->ncellFaces; face++) {
	//
	//		printf ( " Face%3i : ", face );
	//
	//		for (int lface = 0; lface < 2; lface++) {
	//
	//			int fid = lface 	+ face*2;
	//
	//			printf ( " %4i", mesh->faceToLocalFaces[fid] );
	//		}
	//
	//		printf ( "\n" );
	//	}

}

void meshFaceToOwnerCellConnectivity(mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;

			mesh->faceToOwnerCell[fid] = cell;


		}
	}

	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Face to Owner Cell Connectivity \n" );
	//	printf ( " --------------------------------- \n" );
	//	printf ( " Cell ID :    West  South  East  North \n" );
	//
	//	for (int cell = 0; cell < mesh->ncells; cell++) {
	//
	//		printf ( " Cell%3i : ", cell );
	//
	//		for (int face = 0; face < mesh->ncellFaces; face++) {
	//
	//			int fid = face 	+ cell*mesh->ncellFaces;
	//
	//			printf ( " %5i", mesh->faceToOwnerCell[fid] );
	//		}
	//
	//		printf ( "\n" );
	//	}

}

void meshFaceToNeighborCellConnectivity(mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];

			mesh->faceToNeighborCell[fid] = cell_n;
		}
	}

	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Face to Neighbor Cell Connectivity \n" );
	//	printf ( " --------------------------------- \n" );
	//	printf ( " Cell ID :    West  South  East  North \n" );
	//
	//	for (int cell = 0; cell < mesh->ncells; cell++) {
	//
	//		printf ( " Cell%3i : ", cell );
	//
	//		for (int face = 0; face < mesh->ncellFaces; face++) {
	//
	//			int fid = face 	+ cell*mesh->ncellFaces;
	//
	//			printf ( " %5i", mesh->faceToNeighborCell[fid] );
	//		}
	//
	//		printf ( "\n" );
	//	}
}

void meshCalculateNoOfBoundaryandInnerCells(mesh_t *mesh){

	mesh->nBoundaryCells = 0;
	mesh->nInnerCells	 = 0;

	bool boundaryCell;

	for (int cell = 0; cell < mesh->ncells; cell++) {

		boundaryCell = false;

		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];

			if (cell_n==(-1)){  boundaryCell = true; }
		}


		if(boundaryCell==true){mesh->nBoundaryCells = mesh->nBoundaryCells +1;}
		if(boundaryCell==false){mesh->nInnerCells   = mesh->nInnerCells +1;}

	}


	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf(" No of BoundaryCells, N = %d\t \n", mesh->nBoundaryCells);
	//	printf(" No of Actual BoundaryCells, N = %d\t \n", mesh->ncells-(mesh->ncellsx-2)*(mesh->ncellsy-2));
	//
	//	if(mesh->nBoundaryCells==(mesh->ncells-(mesh->ncellsx-2)*(mesh->ncellsy-2))) {printf(" Test passed \n\n");}
	//
	//	printf(" No of InnerCells, N = %d\t \n", mesh->nInnerCells);
	//	printf(" No of Actual InnerCells, N = %d\t \n", (mesh->ncellsx-2)*(mesh->ncellsy-2));
	//
	//	if(mesh->nInnerCells==(mesh->ncellsx-2)*(mesh->ncellsy-2)) {printf(" Test passed \n\n");}

}

void meshCalculateNoOfBoundaryandInnerFaces(mesh_t *mesh){

	mesh->nBoundaryFaces = 0;
	mesh->nInnerFaces	 = 0;

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];

			if (cell_n>(-1)){

				mesh->nInnerFaces = mesh->nInnerFaces+1;
			}

			if (cell_n==(-1)){
				mesh->nBoundaryFaces = mesh->nBoundaryFaces+1;
			}
		}
	}

	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf(" No of Boundary Faces, N= %d\t \n", mesh->nBoundaryFaces);
	//	printf(" No of Actual Boundary Faces, N= %d\t \n", mesh->nBoundaryCells+4);
	//
	//	if(mesh->nBoundaryFaces==(mesh->nBoundaryCells+4)) {printf(" Test passed \n\n");}
	//
	//	printf(" No of Inner Faces, N= %d\t \n",mesh->nInnerFaces );
	//	printf(" No of Actual Inner Faces, N= %d\t \n", mesh->ncells*mesh->ncellFaces -(mesh->nBoundaryCells+4));
	//	if(mesh->nInnerFaces== (mesh->ncells*mesh->ncellFaces -(mesh->nBoundaryCells+4))) {printf(" Test passed \n\n");}
}

void meshCalculateInnerandBoundaryCellID(mesh_t *mesh){
	mesh->innerCells 	= (dint*) calloc(mesh->nInnerCells, sizeof(dint));
	mesh->boundaryCells = (dint*) calloc(mesh->nBoundaryCells, sizeof(dint));

	bool boundaryCell= false;
	int i=0,j=0; // counters

	for (int cell = 0; cell < mesh->ncells; cell++) {

		boundaryCell = false;

		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];

			if (cell_n==(-1)){  boundaryCell = true; }
		}


		if(boundaryCell==true){
			mesh->boundaryCells[i] = cell;
			i++;
		}

		if(boundaryCell==false){
			mesh->innerCells[j] = cell;
			j++;
		}

	}

	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Boundary cell ID \n" );
	//	printf ( " --------------------------------- \n" );
	//
	//	for (int cell = 0; cell < mesh->nBoundaryCells; cell++) {
	//
	//		printf ( " %5i \n", mesh->boundaryCells[cell] );
	//
	//	}
	//
	//	printf ( " \n Inner cell ID \n" );
	//	printf ( " --------------------------------- \n" );
	//
	//	for (int cell = 0; cell < mesh->nInnerCells; cell++) {
	//
	//		printf ( " %5i \n", mesh->innerCells[cell] );
	//
	//	}
}

void meshCalculateInnerandBoundaryFaceID(mesh_t *mesh){

	mesh->innerFaces 	= (dint*) calloc(mesh->nInnerFaces, sizeof(dint));
	mesh->boundaryFaces = (dint*) calloc(mesh->nBoundaryFaces, sizeof(dint));

	int i = 0;
	int j = 0;

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];

			if (cell_n>(-1)){

				mesh->innerFaces[i] = fid;

				i++;
			}

			if (cell_n==(-1)){
				mesh->boundaryFaces[j] = fid;
				j++;
			}
		}
	}

	/*************************************************************/
	/* UNIT TEST                                                 */
	/*************************************************************/
	//	printf ( " \n Boundary Face ID \n" );
	//	printf ( " --------------------------------- \n" );
	//
	//	for (int face = 0; face < mesh->nBoundaryFaces; face++) {
	//
	//		printf ( " %5i \n", mesh->boundaryFaces[face] );
	//
	//	}
	//
	//	printf ( " \n Inner Face ID \n" );
	//	printf ( " --------------------------------- \n" );
	//
	//	for (int face = 0; face < mesh->nInnerFaces; face++) {
	//
	//		printf ( " %5i \n", mesh->innerFaces[face] );
	//
	//	}
}
