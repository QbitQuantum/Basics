int Matrix_T::transposeTest(void)
{
	TestUtil testFramework("Matrix", "Transpose", __FILE__, __LINE__);

	gpstk::Matrix<double> A1T(2,2),A2T(3,3),A3T(4,4),A4T(4,5);
	gpstk::Matrix<double> CompareA1T(2,2),CompareA2T(3,3),CompareA3T(4,4),CompareA4T(5,4);
	A1T = gpstk::transpose(A1);
	A2T = gpstk::transpose(A2);
	A3T = gpstk::transpose(A3);
	A4T = gpstk::transpose(A4);

	double temp4[4] = {2,-3,5,-7};
	double temp5[9] = {1,3,-5,0,1,-1,-2,-2,9};
	double temp6[16] = {2,1,0,0,3,0,2,2,1,3,-3,3,5,1,2,1};
	double temp7[20] = {8,7,1,-78,5,-9,7,24,18,5,10,20,-2,0,11,-68,1.5,7,47,0};		

	CompareA1T = temp4;
	CompareA2T = temp5;
	CompareA3T = temp6;
	CompareA4T = temp7;

	int badCount = 0;

	//testFramework.assert(AT == CompareAT, testMesg, __LINE__);
	for(int i = 0; i < A1T.rows(); i++)
		for(int j = 0; j < A1T.cols(); j++)
     			if (A1T(i,j) != CompareA1T(i,j)) {badCount++;}
	failDescriptionStream << "Check if gpstk::transpose(A1) returns the right matrix. " << badCount << " of the elements are incorrect.";
	failDescriptionString = failDescriptionStream.str(); failDescriptionStream.str("");
    testFramework.assert(badCount==0, failDescriptionString, __LINE__);
  	badCount = 0; // Reset error counter

	for(int i = 0; i < A2T.rows(); i++)
		for(int j = 0; j < A2T.cols(); j++)
     			if (A2T(i,j) != CompareA2T(i,j)) {badCount++;}
	failDescriptionStream << "Check if gpstk::transpose(A2) returns the right matrix. " << badCount << " of the elements are incorrect.";
	failDescriptionString = failDescriptionStream.str(); failDescriptionStream.str("");
    testFramework.assert(badCount==0, failDescriptionString, __LINE__);
  	badCount = 0; // Reset error counter

	for(int i = 0; i < A3T.rows(); i++)
		for(int j = 0; j < A3T.cols(); j++)
     			if (A3T(i,j) != CompareA3T(i,j)) {badCount++;}
	failDescriptionStream << "Check if gpstk::transpose(A3) returns the right matrix. " << badCount << " of the elements are incorrect.";
	failDescriptionString = failDescriptionStream.str(); failDescriptionStream.str("");
    testFramework.assert(badCount==0, failDescriptionString, __LINE__);
  	badCount = 0; // Reset error counter

	for(int i = 0; i < A4T.rows(); i++)
		for(int j = 0; j < A4T.cols(); j++)
     			if (A4T(i,j) != CompareA4T(i,j)) {badCount++;}
	failDescriptionStream << "Check if gpstk::transpose(A4) returns the right matrix. " << badCount << " of the elements are incorrect.";
	failDescriptionString = failDescriptionStream.str(); failDescriptionStream.str("");
    testFramework.assert(badCount==0, failDescriptionString, __LINE__);
  	badCount = 0; // Reset error counter      	

  	return testFramework.countFails();
  }