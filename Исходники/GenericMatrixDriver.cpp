void unaryOperation(const int operatorChoice)
{
	std::cout << "Operation " << OPERATIONS[operatorChoice-1] 
		  << " requires 1 operand matrix." << std::endl;

	// Read the matrix information:
	int rows, cols;
	std::vector<T> cells;
	readMatrixInfo(rows, cols, cells);
	Matrix<T> m;
	try
	{
		m = Matrix<T>(rows, cols, cells);
	}
	catch (std::exception& exception)
	{
		std::cout << "Got Exception from Matrix with message: "
			<< std::endl << exception.what() << std::endl;
		doExit();
	}
	
	std::cout << MAT_LINE << std::endl << "got matrix:" << std::endl;
	std::cout << m;

	Matrix<T> resultMat;

	switch (operatorChoice)
	{
	 case TRANSPOSE:
		 resultMat = m.trans();
		 //assert(m(0,0)==resultMat(0,0));
		 printResultMatrix(resultMat);
		 break;
	 case TRACE:
		 try
		 {
			 std::cout << "The matrix is square and its trace is " << m.trace() << std::endl;
		 }
		 catch (std::exception& exception)
		 {
			 std::cout << "Got Exception from Matrix with message: "
				 << std::endl << exception.what() << std::endl;
			 doExit();
		 }
		 break;
/*	 case SCALAR_TIMES_MATRIX:
		 resultMat = scalar * m;
		 printResultMatrix(resultMat);
		 break;
	 case MATRIX_TIMES_SCALAR:
		 resultMat = m * scalar;
		 printResultMatrix(resultMat);
		 break;
		 */
	}
	checkIterators(resultMat);
}