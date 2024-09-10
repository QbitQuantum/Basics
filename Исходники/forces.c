void Compute_AMD_Force(reax_system *system, control_params *control,
		simulation_data *data, static_storage *workspace, list **lists) {
	/**
	 * compute the AMD energy and force.
	 */
	int i, type_i;
	real q;
	real E_Pol, E_Pot;
	real delta_Pot, fscale;
	real s1, s2, s3, s4;
    // initiate parameters
    delta_Pot = 0.0;
    fscale = 0.0;
	/* Compute Potential Energy */
	E_Pol = 0.0;
	for (i = 0; i < system->N; i++) {
		q = system->atoms[i].q;
		type_i = system->atoms[i].type;

		E_Pol += (system->reaxprm.sbp[type_i].chi * q
				+ (system->reaxprm.sbp[type_i].eta / 2.0) * SQR(q))
				* KCALpMOL_to_EV;
	}

	E_Pot = data->E_BE + data->E_Ov + data->E_Un + data->E_Lp + data->E_Ang
			+ data->E_Pen + data->E_Coa + data->E_HB + data->E_Tor
			+ data->E_Con + data->E_vdW + data->E_Ele + data->E_Pol;
	/* compute delta V and Force scaling factor
	 * reference: JCTC 2011, 7, 890–897
	 */
	data->E_amd = control->amd_energy - data->Fragment_wat*120.0;
	if (data->E_amd > E_Pot) {
		if (control->amd_func == 1){
		/* s1 = Eb -V(r) */
		s1 = data->E_amd - E_Pot;
		/* s2 = (Eb -V(r))^p + a */
		s2 = POW(s1, control->amd_power) + control->amd_alpha;
		s3 = s1/s2/s2;
		s4 = control->amd_power*POW(s1, control->amd_power)-2*s2;
		delta_Pot = s1 * s1 / s2;
		fscale = 1 + s3*s4;
		}
		else if (control->amd_func == 2){
			s1 = data->E_amd - E_Pot;
			s2 = s1*s1;
			s3 = s2 + 2*s1;
			s4 = control->amd_alpha*(s3+1);
			delta_Pot = s2*(s1+1)/s4;
			fscale = 1-(s2+2*s1)/s4;
		}

		data->E_amd_delta = delta_Pot;
		data->F_amd_scale = fscale;
		/* scale the force */
		for (i = 0; i < system->N; ++i)
			rvec_Scale(system->atoms[i].f, fscale, system->atoms[i].f);
	}
	else
	{
		data->E_amd_delta = 0;
		data->F_amd_scale = 1;
	}
	//printf("in AMD no of water is %12.4f\n", data->F_amd_scale);
	//printf("in AMD no of water is %d\n", data->Fragment_wat);
}