void varinit(void)
{
	int i;
	/*
	 * Resetting all flags
	 */
	Intr1_Cnt=0;
	Intr2_Cnt=0;
	IRQ1Flag = 1;
	IRQ2Flag = 1;

	WSZ = 34;
	TA_cnt =0;


	count = 0;
	qcnt = 0;

	velcnt = 0;
	rtime = 0.0;
	rcnt = 0;
	cnt_10ms = 0;




	latm = MasterLat;
	longm = MasterLon;

	epsilon = 0.0;
	four_delt = 4.0 * del_t;
	eight_delt = 8.0 * del_t;
	cdr_delt = cdr * del_t;
	cdr_delt_ms = cdr_delt / 3600;

	for(i=0;i<32;i++){
		Array_SA[i] = 0;
	}

	for(i=0;i<3;i++)
	{
		velo_ref_y[i] = 0.0;
		velo_ref_yold[i] = 0.0;;
		velo_ref_x[i] = 0.0;
		velo_ref_xold[i] = 0.0;

		pure_vel[i] = 0.0;

		p_velo_20ms[i] = 0.0;
		p_velo[i] = 0.0;

		pure_v_old[i] = 0.0;
		p_Ang[i] = 0.0;

		pure_gyro_drift[i] = 0.0;
		pure_acc_residu[i] = 0.0;

	}

#if 0

	/* these are known misalignment angles between M and S -
	 * Measured w.r.t Master to give DCM from slave to Master.
	 * Beware they are not between slave to NED */
	known_si    =  0.0 * cdr;
	known_theta =  0.0 * cdr;
	known_phi   =  0.0 * cdr;

	euler2dcm_stp(0, 0, 0, (double*)CSkew_est);
	transpose(3, 3, (double*)CSkew_est, (double*)CSkew_est_T);

	euler2dcm_stp(known_si, known_theta, known_phi, (double*)CS2M_K);
	transpose(3, 3, (double*)CS2M_K, (double*)CM2S_K);

	euler2dcm_stp(THDG, PITCH, ROLL, (double*)Cb2ned_M);
	matmul(3, 3, (double*)Cb2ned_M, 3, 3, (double*)CS2M_K, (double*)Cb2ned_S);

	if(ta_flag==1 && nav_flag==1)

	{
		dcm2quat((double*)Cb2ned_S, (double *)p_q_body2ned);

	}

	else if(ta_flag ==0 && level_flag==1)
#endif
	{

		euler2quat_spt(mdl_si,mdl_phi,mdl_theta,(double *)p_q_body2ned);


		p_si = mdl_si;
		p_phi = mdl_phi;
		p_theta = mdl_theta;



	}

	ned2ecef_q(latm, longm,(double*) q_ned2ecef);
	quat_mult((double*)q_ned2ecef,(double*)p_q_body2ned, (double*)p_q_body2ecef);


	/*
	 * Modification after Manjit discussion
	 */
	quat2dcm((double *)p_q_body2ecef,(double*)p_dcm);


	quat2dcm((double *)q_ned2ecef,(double*)p_dcm_n);
	matmul(3,3, (double*)p_dcm_n,3,1,(double*)MasterVel,(double*)pure_vel);




	pure_v_old[0] = pure_vel[0];
	pure_v_old[1] = pure_vel[1];
	pure_v_old[2] = pure_vel[2];

	init(0.0, 0.0, 0.0, p_velo_20ms);

	init(0.0, 0.0, 0.0, p_velo);


	init(0.0,0.0,0.0,pure_gyro_drift);
	init(0.0,0.0,0.0,pure_acc_residu);



	for (i = 0; i < 3; i++)
	{
		p_alp1[i] = 0.0;    p_alp2[i] = 0.0;    p_alp3[i] = 0.0;    p_alp4[i] = 0.0;

	}

	for (i = 0; i < 3; i++)
		Delta_Angle[i] = 0.0;

	for (i = 0; i < 6; i++)
		accum1[i] = 0.0;

	init(0.0, 0.0, earth_rate, omega);	 //earth rate vector ECEF

	//used in levelling
	Ned_omega[0] = earth_rate * cos(latm);
	Ned_omega[1] = 0.0;
	Ned_omega[2] = -earth_rate *sin(latm);

	for (i = 0; i < 3; i++)
		omg_dub[i] = 2.0 * omega[i];

	r_init = r0 * (1.0 - eccen * (sin(latm) * sin(latm)));


	pure_R = r_init + MasterAlt; // altitude;


	lla2ecef(latm,longm,MasterAlt,(double *)pure_ecef_pos); //input is geodetic



	pure_g_ecef();

	/****  for epsilon estimation   ****/

	init(0.0, 0.0, -pure_g_ecef_mag, Ned_gravity_detic);

}								 //end of varinit()