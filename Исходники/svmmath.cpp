//
// TODO 3: ComputeHomography()
//		Computes the homography H from the plane specified by "points" to the image plane,
//		and its inverse Hinv.
//		If the plane is the reference plane (isRefPlane == true), don't convert the
//		coordinate system to the plane. Only do this for polygon patches where
//		texture mapping is necessary.
//		Coordinate system conversion is to be implemented in a separate routine
//		ConvertToPlaneCoordinate.
//		For more detailed explaination, see
//		http://www.cs.cornell.edu/courses/cs4670/2012fa/projects/p4/homography.pdf.
//
void ComputeHomography(CTransform3x3 &H, CTransform3x3 &Hinv, const vector<SVMPoint> &points, vector<Vec3d> &basisPts, bool isRefPlane)
{
	int i,j;
	int numPoints = (int) points.size();
	printf("pts:%d",numPoints);
	assert( numPoints >= 4 );

	basisPts.clear();
	if (isRefPlane) // reference plane
	{
		printf("ref plane\n");
		for (i=0; i < numPoints; i++)
		{
			Vec3d tmp = Vec3d(points[i].X, points[i].Y, points[i].W); // was Z, not W
			basisPts.push_back(tmp);
		}
	} 
	else // arbitrary polygon
	{
			printf("polygon\n");
        double uScale, vScale; // unused in this function
		ConvertToPlaneCoordinate(points, basisPts, uScale, vScale);
	}

	// A: 2n x 9 matrix where n is the number of points on the plane
	//    as discussed in lecture
	int numRows = 2 * numPoints;
	const int numCols = 9;

	typedef Matrix<double, Dynamic, 9, RowMajor> MatrixType;
	MatrixType A = MatrixType::Zero(numRows, numCols);

	/******** BEGIN TODO ********/
	// fill in the entries of A 
//printf("TODO: svmmath.cpp:187\n"); 
//fl_message("TODO: svmmath.cpp:187\n");
	int n=0;
	for(j=0;j<numRows; j+=2){
		
		A(j,0)=basisPts[n][0]; //x1
		A(j,1)=basisPts[n][1]; //y1
		A(j,2)=1;
		A(j,3)=0;
		A(j,4)=0;
		A(j,5)=0;

		A(j,6)=-points[n].u*basisPts[n][0]; //-x1'*x1
		A(j,7)=-points[n].u*basisPts[n][1]; //-x1'*y1
		A(j,8)=-points[n].u; //-x1'

		//next row
		A(j+1,0)=0;
		A(j+1,1)=0;
		A(j+1,2)=0;
		A(j+1,3)=basisPts[n][0];
		A(j+1,4)=basisPts[n][1];
		A(j+1,5)=1;
		A(j+1,6)=-points[n].v*basisPts[n][0];
		A(j+1,7)=-points[n].v*basisPts[n][1];
		A(j+1,8)=-points[n].v;
		n++;

	}
	

	/******** END TODO ********/

	double eval, h[9];
	MinEig(A, eval, h);

	H[0][0] = h[0];
	H[0][1] = h[1];
	H[0][2] = h[2];

	H[1][0] = h[3];
	H[1][1] = h[4];
	H[1][2] = h[5];

	H[2][0] = h[6];
	H[2][1] = h[7];
	H[2][2] = h[8];

	// compute inverse of H
	if (H.Determinant() == 0)
		fl_alert("Computed homography matrix is uninvertible \n");
	else
		Hinv = H.Inverse();

	int ii;
	printf("\nH=[\n");
	for (ii=0; ii<3; ii++)
		printf("%e\t%e\t%e;\n", H[ii][0]/H[2][2], H[ii][1]/H[2][2], H[ii][2]/H[2][2]);
	printf("]\nHinv=[\n");

	for (ii=0; ii<3; ii++)
		printf("%e\t%e\t%e;\n", Hinv[ii][0]/Hinv[2][2], Hinv[ii][1]/Hinv[2][2], Hinv[ii][2]/Hinv[2][2]);

	printf("]\n\n");
}