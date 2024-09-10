void matrix_fmt(char *fmt,matrix a) {

	int i,j;
	double *p;

	if(transpose) a=a.transpose();
	p=a.data();
	for(i=0;i<a.ncols();i++) {
		for(j=0;j<a.nrows();j++) {
			fprintf(stdout,fmt,*(p++));
			if(j<a.nrows()-1) fprintf(stdout," ");
		}
		fprintf(stdout,"\n");
	}
}