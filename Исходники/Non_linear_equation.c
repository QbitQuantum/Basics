double *Nonlinear_equation(double *magnitude, double *phase)
  { 
    extern int ngin();
    int m,n,i,ka;
    double eps1,eps2;
    void nginf(int,int,double [],double []);
    void ngins(int,int,double [],double [][4]);
    double *x;
   
    x = Calloc(4 , sizeof(double));   
    x[0] = 5400.0;
    x[1] = 340.0;
    x[2] = 0.5;
    x[3] = 0.4;
    
    m=In_vect_n*In_vect_n; n=4; ka=m+1; eps1=0.0000000001; eps2=0.00000001;
    i=ngin(m,n,eps1,eps2,x,ka,nginf,ngins,magnitude,phase);
    printf("\n");
    printf("i=%d\n",i);
    printf("\n");
    for (i=0; i<=3; i++)
      printf("x[%d]=%13.7e\n",i,x[i]);
    printf("\n");
	return x;
  }