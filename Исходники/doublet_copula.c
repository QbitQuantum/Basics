void			init_cdf_doublet(const double rho,
					   const double t1,
					   const double t2,
					   int n,
					   int m)
{
//  double 		**cdf_doublet;
    double		coef1;			//coef pour la cdf
    double		coef2;			//coef pour la deuxieme integrale
    int 		i=0;
    int			j=0;
    double		a1;			//borne inf de la cdf
    double		b1;			//borne sup de la cdf
    double		a2;			//borne inf de la deuxieme integrale
    double		b2;			//borne sup de la deuxieme integrale
    double		s1;			//variable de stockage
    double		s2;			//autre variable de stockage
    
    
    cdf=malloc(2*sizeof(double*));		//on declare le tableau pour la cdf
    cdf[0]=malloc((n+1)*sizeof(double));	//on declare la colonne des points
    cdf[1]=malloc((n+1)*sizeof(double));	//on declare la colonne des valeurs aux points
    coef1 = (tgamma((t1+1)/2) * tgamma((t2+1)/2));
    coef1 = coef1 / (tgamma(t1/2) * tgamma(t2/2) * M_PI * rho * sqrt((1 - rho*rho) * (t1 - 2) * (t2 - 2))); 
    a1=dp[0];
    b1=dp[1];
    a2=dp[2];
    b2=dp[3];
    coef1 = coef1*(b1 - a1)/n;			//methode des trapezes
    coef2 = (b2 - a2)/m;				//methode des trapezes
    printf("test : f_cdf = %f \n",pow(a1,2));
    s2=0;    
    printf("avant boucle\n");
    for(i=0;i<n+1;i++){
    cdf[0][i]= a1 + (b1 - a1)*i/( (double )n); 		//point considere = x1;
    s1=0;
    s1+=f_cdf(rho,t1,t2,cdf[0][i],a2)/2;
    s1+=f_cdf(rho,t1,t2,cdf[0][i],b2)/2;
    	for(j=1;j<m;j++)
	s1+=f_cdf(rho,t1,t2,cdf[0][i],a2 + (b2 - a2)*j/((double) m));	//methode des trapezes
    if (i>0) {
  //  printf("s1 = %f, s2= %f ,\n",s1,s2);
    cdf[1][i]=(s1+s2)/2*coef1*coef2+cdf[1][i-1];		//methode des trapezes
  //  printf("X=%g, Y=%g, i=%f\n", cdf[1][i], cdf[1][i-1], cdf[0][i]);
    }
    else
    cdf[1][i]=0;						//premiere boucle, initialisation
    
    s2=s1;
    }	
  //  printf("ok %f, %f, %f\n",cdf[0][n],cdf[1][n],cdf[1][50]);
    return;
}