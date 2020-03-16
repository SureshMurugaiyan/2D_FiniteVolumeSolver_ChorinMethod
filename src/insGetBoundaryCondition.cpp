#include "mesh.h"

void insGetBoundaryCondition( int variable_name, int fid, mesh_t *mesh){

	int patchID=mesh->patchID[fid];

	int dimx = 0;
	int dimy = 1;
	int dimz = 2;

	double x = mesh->Cf[dimx+fid*mesh->ndimension];
	double y = mesh->Cf[dimy+fid*mesh->ndimension];
	double z = mesh->Cf[dimz+fid*mesh->ndimension];

	switch (patchID)
	{

	case topBoundary:
		switch (variable_name)
		{
		case U:
			mesh->bctype 	= fixedValue;
			mesh->bcvalueVector[0]	= 1.00;
			mesh->bcvalueVector[1]	= 0.00;
			mesh->bcvalueVector[2]	= 0.00;
			break;
		case p:
			mesh->bctype			= fixedNormalGradient;
			mesh->bcvalueScalar[0]	= 0.0;
			break;
		case rho:
			mesh->bctype 	= fixedValue;
			mesh->bcvalueScalar[0]	= 1.0;
			break;
		case mu:
			mesh->bctype 	= fixedValue;
			mesh->bcvalueScalar[0]	= 1.0;
			break;
		default:
			mesh->bctype 	= none;
		}
		break;
		/*******************************************************/
	case bottomBoundary:
		switch (variable_name)
		{
		case U:
			mesh->bctype 			= fixedValue;
			mesh->bcvalueVector[0]	= 0.00;
			mesh->bcvalueVector[1]	= 0.00;
			mesh->bcvalueVector[2]	= 0.00;
			break;
		case p:
			mesh->bctype			= fixedNormalGradient;
			mesh->bcvalueScalar[0]	= 0.0;
			break;
		case rho:
			mesh->bctype 			= fixedValue;
			mesh->bcvalueScalar[0]	= 1.0;
			break;
		case mu:
			mesh->bctype 			= fixedValue;
			mesh->bcvalueScalar[0]	= 1.0;
			break;
		default:
			mesh->bctype 	= none;
		}
		break;
		/*******************************************************/
	case leftBoundary:
		switch (variable_name)
		{
		case U:
			mesh->bctype 			= fixedValue;
			mesh->bcvalueVector[0]	= 0.00;
			mesh->bcvalueVector[1]	= 0.00;
			mesh->bcvalueVector[2]	= 0.00;
			break;
		case p:
			mesh->bctype			= fixedNormalGradient;
			mesh->bcvalueScalar[0]	= 0.0;
			break;
		case rho:
			mesh->bctype 			= fixedValue;
			mesh->bcvalueScalar[0]	= 1.0;
			break;
		case mu:
			mesh->bctype 	= fixedValue;
			mesh->bcvalueScalar[0]	= 1.0;
			break;
		default:
			mesh->bctype 	= none;
		}
		break;
		/*******************************************************/
	case rightBoundary:
		switch (variable_name)
		{
		case U:
			mesh->bctype 			= fixedValue;
			mesh->bcvalueVector[0]	= 0.00;
			mesh->bcvalueVector[1]	= 0.00;
			mesh->bcvalueVector[2]	= 0.00;
			break;
		case p:
			mesh->bctype			= fixedNormalGradient;
			mesh->bcvalueScalar[0]	= 0.0;
			break;
		case rho:
			mesh->bctype 			= fixedValue;
			mesh->bcvalueScalar[0]	= 1.0;
			break;
		case mu:
			mesh->bctype 	= fixedValue;
			mesh->bcvalueScalar[0]	= 1.0;
			break;

		default:
			mesh->bctype 	= none;
		}
		break;

		/*******************************************************/
	}

}



// Properties of water
//mu = 0.00089;
//rho = 997.0;
// re = 10=> ux = 0.0000089
//
//void insGetBoundaryCondition( int variable_name, int fid, mesh_t *mesh){
//
//	int patchID=mesh->patchID[fid];
//
//	int dimx = 0;
//	int dimy = 1;
//
//	double x = mesh->Cf[dimx+fid*mesh->nmeshdimension];
//	double y = mesh->Cf[dimy+fid*mesh->nmeshdimension];
//
//	switch (patchID)
//	{
//
//	case topBoundary:
//		switch (variable_name)
//		{
//		case U:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueVector[0]	= 0.0000089;
//			mesh->bcvalueVector[1]	= 0.00;
//			mesh->bcvalueVector[2]	= 0.00;
//			break;
//		case p:
//			mesh->bctype			= fixedNormalGradient;
//			mesh->bcvalueScalar[0]	= 0.0;
//			break;
//		case rho:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueScalar[0]	= 997.0;
//			break;
//		case mu:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueScalar[0]	= 0.00089;
//			break;
//		default:
//			mesh->bctype 	= none;
//		}
//		break;
//		/*******************************************************/
//	case bottomBoundary:
//		switch (variable_name)
//		{
//		case U:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueVector[0]	= 0.0;
//			mesh->bcvalueVector[1]	= 0.0;
//			mesh->bcvalueVector[2]	= 0.0;
//			break;
//		case p:
//			mesh->bctype			= fixedNormalGradient;
//			mesh->bcvalueScalar[0]	= 0.0;
//			break;
//		case rho:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueScalar[0]	= 997.0;
//			break;
//		case mu:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueScalar[0]	= 0.00089;
//			break;
//		default:
//			mesh->bctype 	= none;
//		}
//		break;
//		/*******************************************************/
//	case leftBoundary:
//		switch (variable_name)
//		{
//		case U:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueVector[0]	= 0.0;
//			mesh->bcvalueVector[1]	= 0.0;
//			mesh->bcvalueVector[2]	= 0.0;
//			break;
//		case p:
//			mesh->bctype			= fixedNormalGradient;
//			mesh->bcvalueScalar[0]	= 0.0;
//			break;
//		case rho:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueScalar[0]	= 997.0;
//			break;
//		case mu:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueScalar[0]	= 0.00089;
//			break;
//		default:
//			mesh->bctype 	= none;
//		}
//		break;
//		/*******************************************************/
//	case rightBoundary:
//		switch (variable_name)
//		{
//		case U:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueVector[0]	= 0.0;
//			mesh->bcvalueVector[1]	= 0.0;
//			mesh->bcvalueVector[2]	= 0.0;
//			break;
//		case p:
//			mesh->bctype			= fixedNormalGradient;
//			mesh->bcvalueScalar[0]	= 0.0;
//			break;
//		case rho:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueScalar[0]	= 997.0;
//			break;
//		case mu:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueScalar[0]	= 0.00089;
//			break;
//
//		default:
//			mesh->bctype 	= none;
//		}
//		break;
//
//		/*******************************************************/
//	}
//
//}







































////
//void insGetBoundaryCondition( int variable_name, int fid, mesh_t *mesh){
//
//	int patchID=mesh->patchID[fid];
//
//	int dimx = 0;
//	int dimy = 1;
//
//	double x = mesh->Cf[dimx+fid*mesh->nmeshdimension];
//	double y = mesh->Cf[dimy+fid*mesh->nmeshdimension];
//
//	switch (patchID)
//	{
//
//	case topBoundary:
//		switch (variable_name)
//		{
//		case U:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueVector[0]	= 1.0;
//			mesh->bcvalueVector[1]	= 0.00;
//			mesh->bcvalueVector[2]	= 0.00;
//			break;
//		case p:
//			mesh->bctype			= fixedNormalGradient;
//			mesh->bcvalueScalar[0]	= 0.0;
//			break;
//		case rho:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueScalar[0]	= 1.0;
//			break;
//		case mu:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueScalar[0]	= 1.0;
//			break;
//		default:
//			mesh->bctype 	= none;
//		}
//		break;
//		/*******************************************************/
//	case bottomBoundary:
//		switch (variable_name)
//		{
//		case U:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueVector[0]	= 0.0;
//			mesh->bcvalueVector[1]	= 0.0;
//			mesh->bcvalueVector[2]	= 0.0;
//			break;
//		case p:
//			mesh->bctype			= fixedNormalGradient;
//			mesh->bcvalueScalar[0]	= 0.0;
//			break;
//		case rho:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueScalar[0]	= 1.0;
//			break;
//		case mu:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueScalar[0]	= 1.0;
//			break;
//		default:
//			mesh->bctype 	= none;
//		}
//		break;
//		/*******************************************************/
//	case leftBoundary:
//		switch (variable_name)
//		{
//		case U:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueVector[0]	= 0.0;
//			mesh->bcvalueVector[1]	= 0.0;
//			mesh->bcvalueVector[2]	= 0.0;
//			break;
//		case p:
//			mesh->bctype			= fixedNormalGradient;
//			mesh->bcvalueScalar[0]	= 0.0;
//			break;
//		case rho:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueScalar[0]	= 1.0;
//			break;
//		case mu:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueScalar[0]	= 1.0;
//			break;
//		default:
//			mesh->bctype 	= none;
//		}
//		break;
//		/*******************************************************/
//	case rightBoundary:
//		switch (variable_name)
//		{
//		case U:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueVector[0]	= 0.0;
//			mesh->bcvalueVector[1]	= 0.0;
//			mesh->bcvalueVector[2]	= 0.0;
//			break;
//		case p:
//			mesh->bctype			= fixedNormalGradient;
//			mesh->bcvalueScalar[0]	= 0.0;
//			break;
//		case rho:
//			mesh->bctype 			= fixedValue;
//			mesh->bcvalueScalar[0]	= 1.0;
//			break;
//		case mu:
//			mesh->bctype 	= fixedValue;
//			mesh->bcvalueScalar[0]	= 1.0;
//			break;
//
//		default:
//			mesh->bctype 	= none;
//		}
//		break;
//
//		/*******************************************************/
//	}
//
//}
