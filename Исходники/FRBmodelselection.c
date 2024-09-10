double R_rlm_rand(double *X, double *y, int *N, int *P,
		int *Boot_Samp, int *Nres,
		int *M, int *size_boot, double *ours, double *full,
		double *Beta_m, double *Beta_s, double *Scale,
		int *Seed, int *calc_full,
		double *C, double *Psi_c, int *max_it,
		int *converged_mm,
		int *groups, int *n_group, int *k_fast_s)
{
void initialize_mat(double **a, int n, int m);
void initialize_vec(double *a, int n);
void R_S_rlm(double *X, double *y, int *n, int *P,
		int *nres, int *max_it,
		double *SCale, double *beta_s, double *beta_m,
		int *converged_mm,
		int *seed_rand, double *C, double *Psi_c,
		int *Groups, int *N_group, int *K_fast_s);
double Psi_reg(double,double);
double Psi_reg_prime(double,double);
double Chi_prime(double,double);
double Chi(double,double);
void sampler_i(int, int, int *);
int inverse(double **,double **, int);
void matias_vec_vec(double **, double *, double *, int);
void scalar_mat(double **, double, double **, int, int);
void scalar_vec(double *, double, double *, int);
void sum_mat(double **,double **, double **, int, int);
void sum_vec(double *, double *, double *, int);
void dif_mat(double **, double **, double **, int , int );
void dif_vec(double *, double *, double *, int);
void mat_vec(double **, double *, double *, int, int);
void mat_mat(double **, double **, double **, int, int, int);
// void disp_vec(double *, int);
// void disp_mat(double **, int, int);
// void disp_mat_i(int **, int, int);
// void disp_vec(double *, int);
/* double **xb; */
double *Xb, **xb;
int **boot_samp;
double **x, **x2, **x3, **x4, *beta_m, *beta_s,*beta_aux;
double *Fi, *res, *res_s, *w, *ww, dummyscale, scale;
double *v, *v2, *v_aux, *yb; // , timefinish, timestart;
double u,u2,s,c,Psi_constant;
// double test_chi=0, test_psi=0;
int n,p,m,seed; // ,*indices;
int nboot=*size_boot;
// int fake_p = 0;
register int i,j,k;
setbuf(stdout,NULL);
c = *C; Psi_constant = *Psi_c;
n = *N; p = *P; m = *M; seed = *Seed;
boot_samp = (int **) malloc(m * sizeof(int*) );
for(i=0;i<m;i++)
	boot_samp[i] = (int*) malloc(nboot *sizeof(int));
// indices = (int *) malloc( n * sizeof(int) );
v = (double *) malloc( p * sizeof(double) );
v2 = (double *) malloc( p * sizeof(double) );
v_aux = (double *) malloc( p * sizeof(double) );
yb = (double *) malloc( n * sizeof(double) );
Xb = (double*) malloc( n * p * sizeof(double) );
x =  (double **) malloc ( n * sizeof(double *) );
xb =  (double **) malloc ( n * sizeof(double *) );
Fi  = (double *) malloc ( n * sizeof(double) );
res = (double *) malloc ( n * sizeof(double) );
res_s = (double *) malloc ( n * sizeof(double) );
ww  = (double *) malloc ( n * sizeof(double) );
w   = (double *) malloc ( n * sizeof(double) );
x2 = (double **) malloc ( p * sizeof(double *) );
x3 = (double **) malloc ( p * sizeof(double *) );
x4 = (double **) malloc ( p * sizeof(double *) );
beta_aux = (double *) malloc( p * sizeof(double) );
beta_m = (double *) malloc( p * sizeof(double) );
beta_s = (double *) malloc( p * sizeof(double) );
for(i=0;i<n;i++) {
	x[i] =  (double*) malloc (p * sizeof(double) );
	xb[i] =  (double*) malloc ((p+1) * sizeof(double) );
	};
for(i=0;i<p;i++) {
	x2[i] = (double*) malloc (p * sizeof(double) );
	x3[i] = (double*) malloc (p * sizeof(double) );
	x4[i] = (double*) malloc (p * sizeof(double) );
};
/* copy X into x for easier handling */
for(i=0;i<n;i++)
        for(j=0;j<p;j++)
                x[i][j]=X[j*n+i];
/* calculate robust regression estimates */

for(i=0;i<m;i++)
	for(j=0;j<nboot;j++)
		boot_samp[i][j]=Boot_Samp[j*m+i]-1;

R_S_rlm(X, y, N, P, Nres, max_it, &scale, Beta_s, Beta_m,
		converged_mm, &seed, &c,
		Psi_c, groups, n_group, k_fast_s);

*Scale = scale;
/* get M-fitted values in Fi */
mat_vec(x,Beta_m,Fi,n,p);
/* get residuals of M-est in res */
dif_vec(y,Fi,res,n);
/* get S-fitted values in res_s */
mat_vec(x,Beta_s,res_s,n,p);
/* get residuals of S-est in res_s */
dif_vec(y,res_s,res_s,n);
/* set auxiliary matrices to zero */

initialize_mat(x3, p, p);
initialize_mat(x4, p, p);
initialize_vec(v, p);
u2 = 0.0;
/* calculate correction matrix */

for(i=0;i<n;i++) {
	u = res[i]/scale ;
	w[i]  = Psi_reg(u,Psi_constant)/res[i];
        matias_vec_vec(x2,x[i],x[i],p);
	scalar_mat(x2,Psi_reg_prime(u,Psi_constant),
                x2,p,p);
        sum_mat(x3,x2,x3,p,p);
        matias_vec_vec(x2,x[i],x[i],p);
        scalar_mat(x2,w[i],x2,p,p);
        sum_mat(x4,x2,x4,p,p);
	scalar_vec(x[i],Psi_reg_prime(u,Psi_constant)*u,v_aux,p);
	sum_vec(v,v_aux,v,p);
	u2 += Chi_prime(u, c) * u;
};

/* scalar_vec(v, .5 * (double) (n-p) * scale / u2 , v, p);  */
scalar_vec(v, .5 * (double) n * scale / u2 , v, p);
inverse(x3,x2,p);
mat_mat(x2,x4,x3,p,p,p);
mat_vec(x2,v,v2,p,p);
scalar_mat(x3,scale,x3,p,p);
/* the correction matrix is now in x3 */
/* the correction vector is now in v2 */

/* start the bootstrap replications */
for(i=0;i<m;i++) {
	/* change the seed! */
	++seed;
	// sampler_i(n,nboot,indices);
	// for(j=0;j<nboot; j++)
	// 	indices[j]=boot_samp[i][j];
	/* get pseudo observed y's */
	for(j=0;j<nboot;j++) /* xb[j][p] = */
			yb[j] = y[boot_samp[i][j]];
	for(j=0;j<nboot;j++)
		for(k=0;k<p;k++) {
			// xb[j][k] = x[boot_samp[i][j]][k];
			// Xb[k*nboot+j] = X[k*n + indices[j]];
			Xb[k*nboot+j] = x[boot_samp[i][j]][k];
			xb[j][k] = Xb[k*nboot+j];
		};

	/* calculate full bootstrap estimate */

	if( *calc_full == 1 )
	R_S_rlm(Xb,yb,&nboot,P,Nres,max_it,&dummyscale,
			beta_s,beta_m,converged_mm,&seed,&c,
			Psi_c, groups, n_group, k_fast_s);

/* void R_S_rlm(double *X, double *y, int *n, int *P,
		int *nres, int *max_it,
		double *SCale, double *beta_s, double *beta_m,
		int *converged_mm,
		int *seed_rand, double *C, double *Psi_c,
		int *Groups, int *N_group, int *K_fast_s) */

	/*	double *C, double *Psi_c, int *max_it,
		int *groups, int *n_group, int *k_fast_s); */

	// HERE

	/* disp_mat(xb, nboot,p); */
	// disp_vec(yb,nboot);
	// Rprintf("\nfull scale: %f", dummyscale);

	/* calculate robust bootsrap */

	scalar_vec(v,0.0,v,p);	 	/* v <- 0 */
	scalar_mat(x2,0.0,x2,p,p);	/* x2 <- 0 */
	s = 0.0;
	for(j=0;j<nboot;j++) {
		scalar_vec(xb[j],yb[j]*w[boot_samp[i][j]],v_aux,p);
		sum_vec(v,v_aux,v,p);
		matias_vec_vec(x4,xb[j],xb[j],p);
		scalar_mat(x4,w[boot_samp[i][j]],x4,p,p);
		sum_mat(x2,x4,x2,p,p);
		s += Chi(res_s[boot_samp[i][j]] / scale , c);
	};
	/* s = s * scale / .5 / (double) (nboot - p)  ;  */
	s = s * scale / .5 / (double) n;
	inverse(x2,x4,p);		/* x4 <- x2^-1 */
	mat_vec(x4,v,v_aux,p,p);	/* v_aux <- x4 * v */
	dif_vec(v_aux,Beta_m,v_aux,p); 	/* v_aux <- v_aux - beta_m */
	/* v has the robust bootstrapped vector, correct it */
	mat_vec(x3,v_aux,v,p,p);	/* v <- x3 * v_aux */
	scalar_vec(v2,s-scale,v_aux,p);
	sum_vec(v_aux,v,v,p);

	/* store the betas (splus-wise!) */
	for(j=0;j<p;j++) {
		ours[j*m+i]=v[j];
		if( *calc_full == 1 )
			// full[j*m+i]=beta_m[j]-Beta_m[j];
			full[j*m+i]=beta_m[j];
	};
};
for(i=0;i<m;i++)
	free(boot_samp[i]);
free(boot_samp);
for(i=0;i<n;i++) {
	free(x[i]);
	free(xb[i]);
	};
for(i=0;i<p;i++) {
	free(x2[i]);
	free(x3[i]);
	free(x4[i]);
	};
free(x) ;free(x2);free(xb);
free(x3);free(x4);
free(beta_aux);free(beta_m);free(beta_s);
free(w);free(ww);free(Fi);free(res);
free(v);free(v2);free(v_aux);free(yb);
free(res_s);
free(Xb);
return(0);
}