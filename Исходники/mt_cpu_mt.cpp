void calc_grad_c(		int i1, 		// i index правой молекулы
					int j1,			// j index правой молекулы

					int i2,			// i index левой молекулы

					bit type, 		// dimer type: 0 - 'D', 1 - 'T'
					bit pos,		// monomer position in dimer: 0 - bottom, 1 - top

					float x_1,		// правая молекула		mol1
					float y_1,
					float teta_1,

					float x_2,		// левая молекула		mol2
					float y_2,
					float teta_2,

					float x_3,		// верхняя молекула 	mol3
					float y_3,
					float teta_3,

					float *grad_lat_x_1,			// left component of mol1
					float *grad_lat_y_1,
					float *grad_lat_teta_1,

					float *grad_lat_x_2,			// right component of mol2
					float *grad_lat_y_2,
					float *grad_lat_teta_2,

					float *grad_long_x_1,			// up component of mol1
					float *grad_long_y_1,
					float *grad_long_teta_1,

					float *grad_long_x_3,			// down component of mol3
					float *grad_long_y_3,
					float *grad_long_teta_3

							)


{

	// теперь PE_left - это индекс i2, а PF_right - индекс i1

	float cos_t_A = cosf(teta_2);
	float sin_t_A = sinf(teta_2);
	float cos_t_B = cosf(teta_1);
	float sin_t_B = sinf(teta_1);


	float cos_t_1 = cos_t_B;
	float sin_t_1 = sin_t_B;

	float cos_t_3 = cosf(teta_3);
	float sin_t_3 = sinf(teta_3);

	// swap i1 <=> i2

	float Ax_left = Ax_1[i2]*cos_t_A + Ax_3[i2]*sin_t_A - Ax_2[i2] +
				(x_2 + R_MT) * A_Bx_4[i2];

	float Ay_left = Ay_1[i2]*cos_t_A + Ay_2[i2]*sin_t_A + Ay_3[i2] +
				(x_2 + R_MT) * A_By_4[i2];

	float Az_left = -Az_1*sin_t_A + Az_2*cos_t_A + y_2;


	float Bx_right = Bx_1[i1]*cos_t_B + Bx_3[i1]*sin_t_B - Bx_2[i1] +
				(x_1 + R_MT) * A_Bx_4[i1];

	float By_right = By_1[i1]*cos_t_B + By_2[i1]*sin_t_B + By_3[i1] +
				(x_1 + R_MT) * A_By_4[i1];

	float Bz_right = -Bz_1*sin_t_B + Bz_2*cos_t_B + y_1;

	float Dx = Ax_left - Bx_right;
	float Dy = Ay_left - By_right;
	float Dz = Az_left - Bz_right;


	float dist = sqrtf(( pow(Dx, 2) + pow(Dy, 2) + pow(Dz, 2) ));


	if (dist <=1e-7 ){
		dist = 1e-5;
	}

	float inv_dist = 1/dist;

	float drdAx = Dx * inv_dist;
	float drdAy = Dy * inv_dist;
	float drdAz = Dz * inv_dist;
	float drdBx = -drdAx;
	float drdBy = -drdAy;
	float drdBz = -drdAz;

	float dA_X_dteta = -sin_t_A*Ax_1[i2] + cos_t_A*Ax_3[i2];
	float dA_Y_dteta = -sin_t_A*Ay_1[i2] + cos_t_A*Ay_2[i2];
	float dA_Z_dteta = -cos_t_A*Az_1 - sin_t_A*Az_2;

	float drdx_A = drdAx*A_Bx_4[i2] + drdAy*A_By_4[i2];
	float drdy_A = drdAz;
	float drdteta_A = drdAx*dA_X_dteta + drdAy*dA_Y_dteta + drdAz*dA_Z_dteta;

	//================================================
	float dB_X_dteta = -sin_t_B*Bx_1[i1] + cos_t_B*Bx_3[i1];
	float dB_Y_dteta = -sin_t_B*By_1[i1] + cos_t_B*By_2[i1];
	float dB_Z_dteta = -cos_t_B*Bz_1 - sin_t_B*Bz_2;

	float drdx_B = drdBx*A_Bx_4[i1] + drdBy*A_By_4[i1];
	float drdy_B = drdBz;
	float drdteta_B = drdBx*dB_X_dteta + drdBy*dB_Y_dteta + drdBz*dB_Z_dteta;


	float Grad_U_tmp = (b_lat* dist *expf(-dist*inv_ro0)*(2.0f - dist*inv_ro0) +
				dist* clat_dlat_ro0 * expf( - (dist*dist) * d_lat_ro0 )  ) * A_Koeff;



	if ((i1==12)&&(j1>=(N_d-3))) {

		*grad_lat_x_2 = 0.0f;
		*grad_lat_y_2 = 0.0f;
		*grad_lat_teta_2 = 0.0f;

		*grad_lat_x_1 = 0.0f;
		*grad_lat_y_1 = 0.0f;
		*grad_lat_teta_1 = 0.0f;

	} else {

		*grad_lat_x_2 = Grad_U_tmp * drdx_A;
		*grad_lat_y_2 = Grad_U_tmp * drdy_A;
		*grad_lat_teta_2 = Grad_U_tmp * drdteta_A;

		*grad_lat_x_1 = Grad_U_tmp * drdx_B;
		*grad_lat_y_1 = Grad_U_tmp * drdy_B;
		*grad_lat_teta_1 = Grad_U_tmp * drdteta_B;

	}



	//	[nd] 	- 	mol3
	//	[nd-1] 	- 	mol1


	// longitudinal gradient

	float r_long_x = (x_3 - x_1) - Rad*(sin_t_1 + sin_t_3);
	float r_long_y = (y_3 - y_1) - Rad*(cos_t_1 + cos_t_3);
	float r_long = sqrtf( r_long_x*r_long_x + r_long_y*r_long_y);

	if (r_long <=1e-15 ){
		r_long = 1e-7;
	}

	float drdx_long = - r_long_x/r_long;
	float drdy_long = - r_long_y/r_long;

	float dUdr_C;

	if (pos==0) {		// bottom monomer (interaction inside dimer)
		dUdr_C = C_Koeff*r_long;
	} else {			// top monomer (interaction with upper dimer)

		float tmp1 = r_long *  expf(-r_long*inv_ro0_long)*(2 - r_long*inv_ro0_long);
		float tmp2	= r_long * clong_dlong_ro0 * expf(-(r_long*r_long) * d_long_ro0 );

		if (type==0)	// dimer type 'D'
			dUdr_C = (tmp1*b_long_D + tmp2) * A_long_D;
		else 			// dimer type 'T'
			dUdr_C = (tmp1*b_long_T + tmp2) * A_long_T;
	}



	float Grad_tmp_x = drdx_long * dUdr_C;
	float Grad_tmp_y = drdy_long * dUdr_C;

	float GradU_C_teta_1 = -dUdr_C*( drdx_long*(-Rad*cos_t_1) + drdy_long*(Rad*sin_t_1));
	float GradU_C_teta_3 =  dUdr_C*(-drdx_long*(-Rad*cos_t_3) - drdy_long*(Rad*sin_t_3));

	float Grad_tmp;
	if (type==0)		// dimer type 'D'
		Grad_tmp = B_Koeff*(teta_3 - teta_1 - teta0_D);
	else				// dimer type 'T'
		Grad_tmp = B_Koeff*(teta_3 - teta_1 - teta0_T);

	// поменял тут знак - все заработало!
	float GradU_B_teta_1 = - Grad_tmp;
	float GradU_B_teta_3 = + Grad_tmp;


	if (j1 == (N_d-1)) {

		*grad_long_x_1 		= 0.0f;
		*grad_long_y_1 		= 0.0f;
		*grad_long_teta_1	= 0.0f;

		*grad_long_x_3 		= 0.0f;
		*grad_long_y_3 		= 0.0f;
		*grad_long_teta_3	= 0.0f;

	} else {

		*grad_long_x_1 		= Grad_tmp_x;
		*grad_long_y_1 		= Grad_tmp_y;
		*grad_long_teta_1	= GradU_C_teta_1 + GradU_B_teta_1;

		*grad_long_x_3 		= - Grad_tmp_x;
		*grad_long_y_3 		= - Grad_tmp_y;
		*grad_long_teta_3	= GradU_C_teta_3 + GradU_B_teta_3;


	}


}