#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/stat.h>

#include "math.h"

#define dfloat double
#define dint size_t


typedef enum {
	U					=	0,
	p					=	1,
	rho					=	2,
	mu					=	3,

	topBoundary			=	100,
	bottomBoundary		=	101,
	leftBoundary		=	102,
	rightBoundary		=	103,
	innerDomain			=	104,

	fixedValue			=	201,
	fixedNormalGradient	=	202,
	slip				=	203,
	none				=	204,

	vertexScalar		=	301,
	vertexVector		=	302,
	volumeScalar		=	303,
	volumeVector		=	304,
	surfaceScalar		=	305,
	surfaceVector		=	306,

} variable_name;

typedef struct{

	dint ncellVertices; /* number of vertices per cell */
	dint ncellFaces; /* number of faces per cell */
	dint nfaceVertices; /* number of vertices per Face */
	dint ndimension; /* nmeshdimension = x,y,z stored for 2D Mesh */

	dint ncellsx; /* number of cells along each row = colmax*/
	dint ncellsy; /* number of cells along each col = rowmax */
	dint ncells; /* number of cells in mesh */
	dint nvertices; /* number of vertices in mesh */

	dint *cellToVertex; /* Global to Global Vertex connectivity */
	dint *cellToCells; /* Global cell to Global cell connectivity */
	dint *cellToFaces; /* Global cell to adjacent Global cell Face connectivity */ // @suppress("Type cannot be resolved")
	dint *faceToOppositeFace; /* Global cell to Opposite Local cell Face connectivity */ // @suppress("Type cannot be resolved")
	dint *faceToVertices; /* local face to Local vertices connectivity */
	dint *faceToLocalFaces; /* Face to adjacent Local Face connectivity */

	dint *faceToOwnerCell; /* Face to Opposite Local Face connectivity */
	dint *faceToNeighborCell; /* Face to Opposite Local Face connectivity */ // @suppress("Type cannot be resolved")

	dint nInnerCells; // @suppress("Type cannot be resolved")
	dint nBoundaryCells; // @suppress("Type cannot be resolved")
	dint nInnerFaces;
	dint nBoundaryFaces;

	dint *innerCells;
	dint *boundaryCells;
	dint *innerFaces;
	dint *boundaryFaces;


	dfloat *vertices; /* coordinates of vertices */
	dfloat *C; /* coordinates of cell centers */
	dfloat *Cf; /* coordinates of cell face centers */

	dfloat *Sf; /* vector values of outward cell normal face Areas */
	dfloat *magSf; /* Magnitude of Face areas */

	dfloat *V; /* cell volumes (in 2D Cell Area) */

	dfloat *fx; /* Cell Face interpolation Factor */

	dfloat *d; /* Vector from from cell P to cell N  */
	dfloat *magd; /* distance from P to N */

	dint *patchID; /* Name the patches inlet, outlet, top wall, bottom wall */

	/*************************************************************/
	/* Solver Fields                                             */
	/*************************************************************/
	// Vector Equation Momentum
	dfloat *AP; // diagonal coefficients
	dfloat *AN; // neighbor cell coefficients
	dfloat *R;  // source term
	dfloat *R1; // additional source term

	// Scalar Equation Pressure Equation
	dfloat *aP; // diagonal coefficients
	dfloat *aN; // neighbor cell coefficients
	dfloat *r;  // source term for scalar eqn


	/*************************************************************/
	/* Solver Control                                			 */
	/*************************************************************/
	dint timeStepMax;
	dfloat finalTime;
	dfloat deltatime;
	dint WriteFrequency;
	dint nCorrMax; // number of corrector loops in predictor corrector
	dfloat time;
	dint timeStep;
	bool stopCriterion;

	dfloat lambda;  // relaxation parameter
	dfloat maxNorm; // max norm of solution
	dint maxitrEqn; // max number of iterations

	/*************************************************************/
	/* Solution Field                                            */
	/*************************************************************/

	dfloat *U;
	dfloat *p;
	dfloat *rho;
	dfloat *mu;

	dfloat *phiU;
	dfloat *divphiU;

	dfloat *U0;
	dfloat *U00;

	/*************************************************************/
	/* Boundary condition type and value                         */
	/*************************************************************/
	int bctype;
	dfloat* bcvalueScalar;
	dfloat* bcvalueVector;
}mesh_t;

void meshReadInput(mesh_t *mesh);

void createField(dfloat** phi, int variableType, mesh_t *mesh);
void meshConstructFields(mesh_t *mesh);
void meshDestructFields(mesh_t *mesh);

void meshGenerateCellConnectivity(mesh_t *mesh);
void meshRead(mesh_t *mesh);
void printMeshVertexVector(dfloat* phi, char *fileName,mesh_t *mesh);
void printMeshSurfaceVector(dfloat* phi, char *fileName,mesh_t *mesh);
void printMeshVolumeVector(dfloat* phi, char *fileName,mesh_t *mesh);
void printMeshVertexScalar(dfloat* phi, char *fileName,mesh_t *mesh);
void printMeshSurfaceScalar(dfloat* phi, char *fileName,mesh_t *mesh);
void printMeshVolumeScalar(dfloat* phi, char *fileName,mesh_t *mesh);
void printMeshSurfaceScalar(dint* phi, char *fileName,mesh_t *mesh);

dfloat distance(dfloat *X1,dfloat *X2);
dfloat magnitude(dfloat a);

void meshGenerateCellMetrics(mesh_t *mesh);

void meshGenerateBoundaryName(mesh_t *mesh);

void solverConstructFields(mesh_t *mesh);
void solverDestructFields(mesh_t *mesh);

void solverSetControls(mesh_t *mesh);

void insConstructSolutionFields(mesh_t *mesh);
void insDestructSolutionFields(mesh_t *mesh);
void insSetInitialConditions(mesh_t *mesh);
void insWriteSolutionField(mesh_t *mesh);

void printSolutionVolumeScalar(dfloat* phi, char *fileName,int timeStep,mesh_t *mesh);
void printSolutionVolumeVector(dfloat* phi, char *fileName,int timeStep,mesh_t *mesh);

void solverUpdateStoppingCriterion(mesh_t *mesh);

void copyDataToFrom(dfloat* copyTo, dfloat* copyFrom,int varName, mesh_t *mesh);
void insConstructUEquation(mesh_t *mesh);

void interpolateScalarCellToFace(dfloat* phiCell, dfloat* phiFace,mesh_t *mesh);
void interpolateVectorCellToFace(dfloat* phiCell, dfloat* phiFace,mesh_t *mesh);

void insGetBoundaryCondition( int variable_name, int fid, mesh_t *mesh);

void insConstrainByBoundaryFieldVector(double* Uf, double* U, int U_name,mesh_t *mesh);
void insConstrainByBoundaryFieldScalar(double* pf,double* pcell,int p_name,mesh_t *mesh);



double ddteulerbackward(dfloat* rho, dfloat* U0, dfloat* U00,mesh_t *mesh);
double fvcLaplacianOfVector(double alpha, dfloat* mu, int mu_name, dfloat* U,int U_name,mesh_t *mesh);
double fvcDivergenceOfVector(double alpha, dfloat* rho, int rho_name, dfloat* U,int U_name,
		dfloat* phiU, mesh_t *mesh);

void fvdDivergenceOfSurfaceScalar(double* phiU, double* divphiU, mesh_t *mesh);

void insConstructFlux(double* Uvec, double* phiU, int UName, mesh_t *mesh);
void insConstructFluxofSurfaceVector(double* HbyAf, double* phiHbyA, mesh_t *mesh);

void insConstructPEquation(mesh_t *mesh);
double fvcDivergenceOfSurfaceScalar(dfloat alpha, dfloat* phiHbyA,mesh_t *mesh);
double fvmLaplacianOfScalar(double alpha, dfloat* p,int P_name,mesh_t *mesh);
void setReferenceValueScalar(double* p,int P_name, int refCell,double refValue, mesh_t *mesh);

void solveVector(double* U, mesh_t *mesh);
void solveScalar(double* P, mesh_t *mesh);

void fvdGradientOfScalar(dfloat* gradCell,dfloat *phiCell, int P_Name, mesh_t *mesh);
void insCorrectU(mesh_t *mesh);

void fvdSnGradientOfScalar(dfloat* gradCell,dfloat *phiCell, int P_Name, mesh_t *mesh);

//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);
//void functiontest(mesh_t *mesh);

