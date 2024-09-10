void prox(prob_vars * vars, all_data * data, prox_data * p_data)
{
	double v[data->m*(data->T+1)];
	memcpy(v,vars->u,sizeof(double)*data->m*(data->T+1));
	subArray(v,vars->y,data->m*(data->T+1));

	memcpy(vars->x_t,vars->x,sizeof(double)*data->n*(data->T+1));
	subArray(vars->x_t,vars->z,data->n*(data->T+1));

	double nm,fac;
//	#pragma omp parallel for private(nm,fac)
	for(int i=0;i<data->T+1;i++){
		nm = nrm(&v[i*data->m],data->m);
		fac = 1-fminl(1/(1+data->rho),p_data->M/(data->rho*nm));
		for(int j=0;j<data->m;j++){
			vars->u_t[i*data->m+j]=fac*v[i*data->m+j];
		}
	}
}