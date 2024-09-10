bool CorrespondTemplates::computeRigidAlignment(TriangleMesh * originalMesh, TriangleMesh * alignedMesh, g_NodeContainer contToBeAligned)
{
	long int i, numberOfNodes, dimension, dimensionH, lwork, info, determinant;
	double alpha, beta;
	char job, trans;
	bool returnval;
	numberOfNodes = originalMesh->getNumberOfNodes();
	dimension = 3;
	dimensionH = 4;
	job = 'A';
	trans = 'N';
	alpha = 1.0;
	beta = 0.0;
	lwork = 2*numberOfNodes;
	double * work = new double[lwork];
	double * A = new double[numberOfNodes * dimensionH];
	double * b = new double[numberOfNodes * dimension];
	double * S = new double[dimension];
	double * U = new double[dimension*dimension];
	double * VT = new double[dimension*dimension];
	double * R = new double[dimensionH*dimension];

	returnval = true;

	//populate the arrays A and b:
	for(i = 0; i < numberOfNodes; i++)
	{
		A[i] = originalMesh->nodes()[i]->coordinate().x();
		A[numberOfNodes + i] = originalMesh->nodes()[i]->coordinate().y();
		A[2*numberOfNodes + i] = originalMesh->nodes()[i]->coordinate().z();
		A[3*numberOfNodes + i] = 1.0;
		b[i] = alignedMesh->nodes()[i]->coordinate().x();
		b[numberOfNodes + i] = alignedMesh->nodes()[i]->coordinate().y();
		b[2*numberOfNodes + i] = alignedMesh->nodes()[i]->coordinate().z();
	}
	//compute an estimate of R:
	clapack::dgels_(&trans, &numberOfNodes, &dimensionH, &dimension, A, &numberOfNodes, b, &numberOfNodes, work, &lwork, &info);
	if(info != 0)
	{
		cout<<"Problem with estimating R "<<info<<endl;
		goto align_EXIT;
	}
	//make sure that R is a valid matrix (orthonormal): b contains R
	delete [] work;
	lwork = max(3 * min(dimension, dimensionH) + max(dimension, dimensionH), 5*min(dimension, dimensionH));
	work = new double[lwork];
	//only copy 3 by 3 submatrix to R:
	for(i = 0; i < dimension; i++)
	{
		R[i] = b[i];
		R[dimension + i] = b[numberOfNodes + i];
		R[2*dimension + i] = b[2*numberOfNodes + i];
	}
	//copy the modified version back to b (as help storage) and then to R in the correct order
	R[10] = R[8]; R[9] = R[7]; R[8] = R[6];
	R[6] = R[5]; R[5] = R[4]; R[4] = R[3];
	R[3] = b[3]; R[7] = b[numberOfNodes+3]; R[11] = b[2*numberOfNodes+3];

	//transform the coordinates:
	numberOfNodes = contToBeAligned.numberOfItems();
	delete [] A;
	A = new double[numberOfNodes * dimensionH];
	//populate the array A:
	for(i = 0; i < numberOfNodes; i++)
	{
		A[i] = contToBeAligned[i]->coordinate().x();
		A[numberOfNodes + i] = contToBeAligned[i]->coordinate().y();
		A[2*numberOfNodes + i] = contToBeAligned[i]->coordinate().z();
		A[3*numberOfNodes + i] = 1.0;
	}
	//do the rigid transformation and set it to part:
	clapack::dgemm_(&trans, &trans, &numberOfNodes, &dimension, &dimensionH, &alpha, A, &numberOfNodes, R, &dimensionH, &beta,
		b, &numberOfNodes);
	for(i = 0; i < numberOfNodes; i++)
	{
		contToBeAligned[i]->coordinate(g_Vector(b[i], b[numberOfNodes + i], b[2*numberOfNodes + i]));
	}

align_EXIT:
	delete [] work;
	delete [] A;
	delete [] b;
	delete [] S;
	delete [] U;
	delete [] VT;
	delete [] R;

	return returnval;
}