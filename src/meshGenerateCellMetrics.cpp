
#include "mesh.h"

void generateCellCenters(mesh_t *mesh);
void generateFaceCenters(mesh_t *mesh);
void generateFaceAreas(mesh_t *mesh);
void generateCellVolumes(mesh_t *mesh);
void generateCellFaceInterpolationFactor(mesh_t *mesh);
void generateCellFaceExtrapolationFactor(mesh_t *mesh);
void generateCellToCellDistanceVectors(mesh_t *mesh);
void writeMeshMetrics(mesh_t *mesh);

void meshGenerateCellMetrics(mesh_t *mesh){

	generateCellCenters(mesh);
	generateFaceCenters(mesh);
	generateFaceAreas(mesh);
	generateCellVolumes(mesh);

	generateCellFaceInterpolationFactor(mesh);
	generateCellFaceExtrapolationFactor(mesh);
	generateCellToCellDistanceVectors(mesh);

	writeMeshMetrics(mesh);

}

void generateCellCenters(mesh_t *mesh){

	dfloat *sum;
	sum = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));

	for( int cell = 0; cell < mesh->ncells;cell++){

		// Clear container
		for (int i = 0; i < (mesh->ndimension); i++) {sum[i] = 0;}


		for(int vertex=0;vertex<mesh->ncellVertices;vertex++){
			for(int dimension=0;dimension<mesh->ndimension;dimension++){

				int vid_s 		= vertex + cell*mesh->ncellVertices;
				int vid 		= mesh->cellToVertex[vid_s];
				int vid_dim		= dimension + vid*mesh->ndimension;


				sum[dimension] = sum[dimension] + mesh->vertices[vid_dim];

			}
		}

		for(int dimension=0;dimension<mesh->ndimension;dimension++){
			int cell_dim		= dimension + cell*mesh->ndimension;
			mesh->C[cell_dim] 	= sum[dimension]/mesh->ncellVertices;
		}



	}

	free(sum);

}

void generateFaceCenters(mesh_t *mesh){


	dfloat *sum;
	sum = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));


	for( int cell = 0; cell < mesh->ncells;cell++){
		for (int face = 0; face < mesh->ncellFaces; ++face) {

			// Clear container
			for (int i = 0; i < (mesh->ndimension); i++) {sum[i] = 0;}


			for (int facevertex = 0; facevertex < mesh->nfaceVertices; facevertex++){

				int vid_ss = facevertex+face*mesh->nfaceVertices;
				int vertex = mesh->faceToVertices[vid_ss];
				int vid_s  = vertex + cell*mesh->ncellVertices;
				int vid    = mesh->cellToVertex[vid_s];

				for(int dimension=0;dimension<mesh->ndimension;dimension++){

					int vid_dim  = dimension + vid*mesh->ndimension;
					sum[dimension] = sum[dimension] + mesh->vertices[vid_dim];

				}
			}

			int fid  = face + cell*mesh->ncellFaces;

			for(int dimension=0;dimension<mesh->ndimension;dimension++){
				int fid_dim  = dimension + fid*mesh->ndimension;
				mesh->Cf[fid_dim] = sum[dimension]/mesh->nfaceVertices;
			}

		}
	}

	free(sum);
}

void generateFaceAreas(mesh_t *mesh){


	/* Face area in 2D = dl X k */
	/* compute component of length vector of each face, dl = dx i + dy j */
	/* Face area in 2D = dy i -dx j */

	for( int cell = 0; cell < mesh->ncells;cell++){
		for (int face = 0; face < mesh->ncellFaces; ++face) {

			dfloat *dl;
			dl = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
			for (int i = 0; i < (mesh->ndimension); i++) { dl[i] = 0;}

			int facevertex,vid_ss1,vid_ss2,vertex1,vertex2;
			int vid_s1, vid_s2,vid1,vid2,vid_dim1,vid_dim2;

			facevertex = 0;
			vid_ss1 = facevertex+face*mesh->nfaceVertices;
			vertex1 = mesh->faceToVertices[vid_ss1]; // Get Local vertex ID
			vid_s1  = vertex1 + cell*mesh->ncellVertices;
			vid1    = mesh->cellToVertex[vid_s1]; // Get Global vertex ID

			facevertex = 1;
			vid_ss2 = facevertex+face*mesh->nfaceVertices;
			vertex2 = mesh->faceToVertices[vid_ss2];
			vid_s2  = vertex2 + cell*mesh->ncellVertices;
			vid2    = mesh->cellToVertex[vid_s2];


			for (int dimension = 0; dimension < mesh->ndimension; dimension++) {
				vid_dim1  = dimension + vid1*mesh->ndimension;
				vid_dim2  = dimension + vid2*mesh->ndimension;

				// calculate length vector, dx = x2-x1 , dy= y2-y1;
				dl[dimension] =  mesh->vertices[vid_dim2]-mesh->vertices[vid_dim1];
			}

			int dimension,fidx,fidy,fidz;
			dimension =0;
			fidx = dimension + face*mesh->ndimension+cell*mesh->ndimension*mesh->ncellFaces;
			dimension =1;
			fidy = dimension + face*mesh->ndimension+cell*mesh->ndimension*mesh->ncellFaces;
			dimension =2;
			fidz = dimension + face*mesh->ndimension+cell*mesh->ndimension*mesh->ncellFaces;

			mesh->Sf[fidx] =  dl[1];  // dy
			mesh->Sf[fidy] = -dl[0];  // -dx
			mesh->Sf[fidz] =  0.0;    // 0

			free(dl);

		}
	}



	dfloat *area;
	area = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));

	// Compute the magnitude of the face areas
	for( int cell = 0; cell < mesh->ncells;cell++){
		for (int face = 0; face < mesh->ncellFaces; ++face) {
			int fid = face + cell*mesh->ncellFaces;

			for (int dimension = 0; dimension < mesh->ndimension; dimension++) {
				int fid_dim = dimension + fid*mesh->ndimension;
				area[dimension] = mesh->Sf[fid_dim];
			}

			mesh->magSf[fid] = sqrt(pow(area[0],2) + pow(area[1],2) + pow(area[2],2));
		}
	}

	free(area);

}

void generateCellVolumes(mesh_t *mesh){
	/* Volume in 2D is cell Area */
	/* Cell area in 2D = one half of cross product of its diagonals */
	/* a->northwest , b->southwest , c->southeast , d->northeast  corners of cell*/
	/* area = 0.5* (r_bd X r_ca), where r is diagonal vector */


	dfloat *a; a = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
	dfloat *b; b = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
	dfloat *c; c = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
	dfloat *d; d = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));

	dfloat *r_bd; r_bd = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
	dfloat *r_ca; r_ca = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));

	int vertex_a,vertex_b,vertex_c,vertex_d;
	int vid_a,vid_b,vid_c,vid_d;

	for (int cell = 0; cell < mesh->ncells; cell++) {

		vertex_a = 0 + cell * mesh->ncellVertices;
		vertex_b = 1 + cell * mesh->ncellVertices;
		vertex_c = 2 + cell * mesh->ncellVertices;
		vertex_d = 3 + cell * mesh->ncellVertices;

		vid_a = mesh->cellToVertex[vertex_a];
		vid_b = mesh->cellToVertex[vertex_b];
		vid_c = mesh->cellToVertex[vertex_c];
		vid_d = mesh->cellToVertex[vertex_d];


		for (int dimension = 0; dimension < mesh->ndimension; dimension++) {

			a[dimension] = mesh->vertices[dimension+vid_a*mesh->ndimension];
			b[dimension] = mesh->vertices[dimension+vid_b*mesh->ndimension];
			c[dimension] = mesh->vertices[dimension+vid_c*mesh->ndimension];
			d[dimension] = mesh->vertices[dimension+vid_d*mesh->ndimension];

			r_bd[dimension] = d[dimension]-b[dimension];
			r_ca[dimension] = a[dimension]-c[dimension];
		}

		mesh->V[cell] = 0.5*(r_bd[0]*r_ca[1]-r_bd[1]*r_ca[0]) ; // cross product of r_bd and r_ca


	}

	free(a);
	free(b);
	free(c);
	free(d);

	free(r_bd);
	free(r_ca);

}

void generateCellFaceInterpolationFactor(mesh_t *mesh){


	dfloat *f;
	dfloat *N;
	dfloat *P;

	f = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
	N = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
	P = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));

	for (size_t i = 0; i < mesh->ndimension; i++) {
		f[i] = 0;
		N[i] = 0;
		P[i] = 0;
	}

	for (int face = 0; face < mesh->nInnerFaces; face++) {

		int fid 	=  mesh->innerFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int cell_n	=  mesh->faceToNeighborCell[fid];

		for (int dim = 0; dim < mesh->ndimension; dim++) {

			int fid_dim   = dim + fid*mesh->ndimension;
			int cell_dim  = dim + cell*mesh->ndimension;
			int cell_ndim = dim + cell_n*mesh->ndimension;

			f[dim] = mesh->Cf[fid_dim];
			N[dim] = mesh->C[cell_ndim];
			P[dim] = mesh->C[cell_dim];
		}

		dfloat fN = distance(f,N);
		dfloat PN = distance(P,N);

		mesh->fx[fid] = fN/PN;


	}


	free(f);
	free(N);
	free(P);
}

void generateCellFaceExtrapolationFactor(mesh_t *mesh){


	dfloat *f;
	dfloat *b;
	dfloat *P;

	f = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
	b = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));
	P = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));

	for (size_t i = 0; i < mesh->ndimension; i++) {
		f[i] = 0;
		b[i] = 0;
		P[i] = 0;
	}


	for (int face = 0; face < mesh->nBoundaryFaces; face++) {

		int fid 	=  mesh->boundaryFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int oface	=  mesh->faceToOppositeFace[fid]; // local face ID

		int ofid	=	oface  + cell*mesh->ncellFaces; // Global face ID

		for (int dim = 0; dim < mesh->ndimension; dim++) {

			int fid_dim    = dim + fid*mesh->ndimension;
			int ofid_dim   = dim + ofid*mesh->ndimension;
			int cell_dim   = dim + cell*mesh->ndimension;

			f[dim] = mesh->Cf[ofid_dim];
			b[dim] = mesh->Cf[fid_dim];
			P[dim] = mesh->C[cell_dim];


		}

		dfloat fb = distance(f,b);
		dfloat fP = distance(f,P);

		mesh->fx[fid] = fb/fP;


	}


	free(f);
	free(b);
	free(P);

}

void generateCellToCellDistanceVectors(mesh_t *mesh){


	for (int face = 0; face < mesh->nInnerFaces; face++) {

		int fid 	=  mesh->innerFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];
		int cell_n	=  mesh->faceToNeighborCell[fid];

		for (int dim = 0; dim < mesh->ndimension; dim++) {

			int cell_dim  = dim + cell*mesh->ndimension;
			int cell_ndim = dim + cell_n*mesh->ndimension;
			int fid_dim   = dim + fid*mesh->ndimension;

			mesh->d[fid_dim] = mesh->C[cell_ndim]-mesh->C[cell_dim];
		}

	}




	for (int face = 0; face < mesh->nBoundaryFaces; face++) {

		int fid 	=  mesh->boundaryFaces[face];
		int cell	=  mesh->faceToOwnerCell[fid];

		for (int dim = 0; dim < mesh->ndimension; dim++) {

			int fid_dim   = dim + fid*mesh->ndimension;
			int cell_dim  = dim + cell*mesh->ndimension;

			mesh->d[fid_dim] = mesh->Cf[fid_dim]-mesh->C[cell_dim];
		}
	}



	// Compute the magnitude of the distance vector

	dfloat *dl;
	dl = (dfloat*) calloc(mesh->ndimension, sizeof(dfloat));

	for (int cell = 0; cell < mesh->ncells; ++cell) {
		for (int face = 0; face < mesh->ncellFaces; ++face) {

			int fid		=  face  + cell*mesh->ncellFaces;

			for (int dim = 0; dim < mesh->ndimension; dim++) {
				int fid_dim   = dim + fid*mesh->ndimension;
				dl[dim] = mesh->d[fid_dim];
			}

			mesh->magd[fid] = sqrt(pow(dl[0],2) + pow(dl[1],2) + pow(dl[2],2));
		}
	}

	free(dl);




}

void writeMeshMetrics(mesh_t *mesh){

	int n = 50;
    char *variableName ;
    variableName	= (char*) calloc(n, sizeof(char));


	strcpy(variableName, "V");
	printMeshVertexVector(mesh->vertices, variableName,mesh);

	strcpy(variableName, "C");
	printMeshVolumeVector(mesh->C, variableName, mesh);

	strcpy(variableName, "Cf");
	printMeshSurfaceVector(mesh->Cf, variableName, mesh);

	strcpy(variableName, "Sf");
	printMeshSurfaceVector(mesh->Sf, variableName, mesh);

	strcpy(variableName, "magSf");
	printMeshSurfaceScalar(mesh->magSf, variableName, mesh);


	strcpy(variableName, "V");
	printMeshVolumeScalar(mesh->V, variableName, mesh);

	strcpy(variableName, "fx");
	printMeshSurfaceScalar(mesh->fx, variableName, mesh);

	strcpy(variableName, "d");
	printMeshSurfaceVector(mesh->d, variableName, mesh);

	strcpy(variableName, "magd");
	printMeshSurfaceScalar(mesh->magd, variableName, mesh);

	free(variableName);

}
