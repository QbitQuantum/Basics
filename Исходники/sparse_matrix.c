long BiCGSTAB_LU_SSOR(double w, double tol_rel, double tol_min, double tol_max, DOUBLEVECTOR *x, DOUBLEVECTOR *b, 
					LONGVECTOR *Li, LONGVECTOR *Lp, DOUBLEVECTOR *Lx, LONGVECTOR *Ui, LONGVECTOR *Up, DOUBLEVECTOR *Ux){
	
	DOUBLEVECTOR *r0, *r, *p, *v, *s, *t, *y, *z, *ss, *tt;
	double rho, rho1, alpha, omeg, beta, norm_r0;
	long i=0, j;
	
	r0 = new_doublevector(x->nh);
	r = new_doublevector(x->nh);
	p = new_doublevector(x->nh);
	v = new_doublevector(x->nh);
	s = new_doublevector(x->nh);
	t = new_doublevector(x->nh);
	y = new_doublevector(x->nh);
	z = new_doublevector(x->nh);
	ss = new_doublevector(x->nh);
	tt = new_doublevector(x->nh);
		
	product_using_only_upper_diagonal_part(r, x, Ui, Up, Ux);
	
    for (j=x->nl;j<=x->nh;j++ ) {	
    	r->co[j] = b->co[j] - r->co[j];
		r0->co[j] = r->co[j];
		p->co[j] = 0.;
		v->co[j] = 0.;
    }
	
	norm_r0 = norm_2(r0,r0->nh);
	
	rho = 1.;
	alpha = 1.;
	omeg = 1.;
	
	while ( i<=x->nh && norm_2(r,r->nh) > Fmax( tol_min , Fmin( tol_max , tol_rel*norm_r0) ) ) {
		
		rho1 = product(r0, r);
		
		beta = (rho1/rho)*(alpha/omeg);
		
		rho = rho1;
		
		for (j=x->nl;j<=x->nh;j++ ) {		
			p->co[j] = r->co[j] + beta*(p->co[j] - omeg*v->co[j]);
		}
		
		solve_SSOR_preconditioning(w, y, p, Li, Lp, Lx, Ui, Up, Ux);
		product_using_only_upper_diagonal_part(v, y, Ui, Up, Ux);
		
		alpha = rho/product(r0, v);
		
		for (j=x->nl;j<=x->nh;j++ ) {		
			s->co[j] = r->co[j] - alpha*v->co[j];
		}
		
		solve_SSOR_preconditioning(w, z, s, Li, Lp, Lx, Ui, Up, Ux);
		product_using_only_upper_diagonal_part(t, z, Ui, Up, Ux);
		
		solve_lower_diagonal_system(tt, t, Ui, Up, Ux);
		solve_lower_diagonal_system(ss, s, Ui, Up, Ux);
		omeg = product(tt, ss)/product(tt, tt);
		
		for (j=x->nl;j<=x->nh;j++ ) {		
			x->co[j] += (alpha*y->co[j] + omeg*z->co[j]);
			r->co[j] = s->co[j] - omeg*t->co[j];
		}
		
		i++;
		
		printf("i:%ld normr0:%e normr:%e\n",i,norm_r0,norm_2(r,r->nh));
		
	}
	
	
	free_doublevector(r0);
	free_doublevector(r);
	free_doublevector(p);
	free_doublevector(v);
	free_doublevector(s);
	free_doublevector(t);

	free_doublevector(y);
	free_doublevector(z);
	free_doublevector(ss);
	free_doublevector(tt);
	
	return i;
	
}