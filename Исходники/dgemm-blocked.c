/* Copy new_matirx back to the old_matrix. */
void copy_padding_back(int old_size, double* old_matrix, int new_size, double* new_matrix) {
    if(old_size%2 == 1) {
	 	for(int i=0; i<old_size; i++) {
	     	double* addr_new = new_matrix + i * new_size;
	     	double* addr_old = old_matrix + i * old_size;
			for(int j=0; j<old_size - 1; j+=2) {
				__m128d v1 = _mm_load_pd(addr_new + j);
				_mm_storeu_pd(addr_old + j, v1);
	    		}
			old_matrix[(i+1)*old_size-1]=new_matrix[i*new_size+old_size-1];
		}
    }else {
		for(int i=0; i<old_size; i++) {
			double* addr_new = new_matrix + i * new_size;
			double* addr_old = old_matrix + i * old_size;
			for(int j=0; j<old_size; j+=2) {
				__m128d v1 = _mm_load_pd(addr_new + j);
				_mm_storeu_pd(addr_old + j, v1);
			 }
		}
    }
    free(new_matrix);
}