/*! @return Vector */
Vector<double> SparseMatrix::operator * (Vector<double> vec){
	Vector<double> C;
	int row,col;
	C.set_size(number_of_rows);
	C.initialize();
	for(int i = 0; i < number_of_rows; i++){
		row = i;
		for(int j = I[i]; j < I[i + 1]; j++){
			col = J[j];
			C[row] += Elements[j]*vec[col];
		}
	}
	return C;
}