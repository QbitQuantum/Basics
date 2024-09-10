double cPEDetection<_DataType>::ComputeAveRadius(double *CurrPt, double *NextPt, _DataType MatMin, _DataType MatMax)
{
	int		i, k, loc[3], DataCoor_i[3], NumBoundaryVoxels_i;
	double	StartPt_d[3], VesselDirection_d[3], VesselDirOrg_d[3], Rays_d[8*3], CurrLoc_d[3];
	double	GradVec_d[3], ZeroCrossingLoc_Ret[3], FirstDAtTheLoc_Ret, DataPosFromZeroCrossingLoc_Ret;
	double	Radius_d[16], CurrCenterPt_d[3], NextCenterPt_d[3], AveRadius_d, Step_d, Increase_d;

	
	Increase_d = 0.5;
	for (k=0; k<3; k++) VesselDirOrg_d[k] = NextPt[k] - CurrPt[k];
	Normalize(VesselDirOrg_d);
	for (k=0; k<3; k++) VesselDirection_d[k] = VesselDirOrg_d[k];

	for (k=0; k<3; k++) StartPt_d[k] = CurrPt[k];
	ComputePerpendicular8Rays(StartPt_d, VesselDirection_d, Rays_d);
	for (k=0; k<3; k++) CurrCenterPt_d[k] = 0.0;
	NumBoundaryVoxels_i = 0;
	for (i=0; i<8; i++) {

		for (Step_d=-0.2; Step_d<=0.2+1e-6; Step_d+=0.4) {
			loc[0] = getANearestBoundary(StartPt_d, &Rays_d[i*3], Step_d, MatMin, MatMax);
			if (loc[0]>0) NumBoundaryVoxels_i++;
			else continue;
			DataCoor_i[2] = (int)(loc[0]/this->WtimesH_mi);
			DataCoor_i[1] = (int)((loc[0] - DataCoor_i[2]*this->WtimesH_mi)/this->Width_mi);
			DataCoor_i[0] = (int)(loc[0] % this->Width_mi);
			for (k=0; k<3; k++) CurrLoc_d[k] = (double)DataCoor_i[k];
			for (k=0; k<3; k++) GradVec_d[k] = (double)this->GradientVec_mf[loc[0]*3 + k];
			this->FindZeroCrossingLocation(CurrLoc_d, GradVec_d, ZeroCrossingLoc_Ret, 
										FirstDAtTheLoc_Ret, DataPosFromZeroCrossingLoc_Ret, 0.2);
			for (k=0; k<3; k++) CurrCenterPt_d[k] += ZeroCrossingLoc_Ret[k];
		}
	}
	for (k=0; k<3; k++) CurrCenterPt_d[k] /= (double)NumBoundaryVoxels_i;


	for (k=0; k<3; k++) StartPt_d[k] = CurrPt[k] + VesselDirection_d[k]*Increase_d;
	ComputePerpendicular8Rays(StartPt_d, VesselDirection_d, Rays_d);
	for (k=0; k<3; k++) NextCenterPt_d[k] = 0.0;
	NumBoundaryVoxels_i = 0;
	for (i=0; i<8; i++) {

		for (Step_d=-0.2; Step_d<=0.2+1e-6; Step_d+=0.4) {
			loc[0] = getANearestBoundary(StartPt_d, &Rays_d[i*3], Step_d, MatMin, MatMax);
			if (loc[0]>0) NumBoundaryVoxels_i++;
			else continue;
			DataCoor_i[2] = (int)(loc[0]/this->WtimesH_mi);
			DataCoor_i[1] = (int)((loc[0] - DataCoor_i[2]*this->WtimesH_mi)/this->Width_mi);
			DataCoor_i[0] = (int)(loc[0] % this->Width_mi);
			for (k=0; k<3; k++) CurrLoc_d[k] = (double)DataCoor_i[k];
			for (k=0; k<3; k++) GradVec_d[k] = (double)this->GradientVec_mf[loc[0]*3 + k];
			this->FindZeroCrossingLocation(CurrLoc_d, GradVec_d, ZeroCrossingLoc_Ret, 
										FirstDAtTheLoc_Ret, DataPosFromZeroCrossingLoc_Ret, 0.2);
			for (k=0; k<3; k++) NextCenterPt_d[k] += ZeroCrossingLoc_Ret[k];
		}
	}
	for (k=0; k<3; k++) NextCenterPt_d[k] /= (double)NumBoundaryVoxels_i;


	for (k=0; k<3; k++) VesselDirection_d[k] = VesselDirOrg_d[k];

#ifdef	DEBUG_PED
	printf ("\n");
#endif

	double	Tempd;
	int		NumRepeat = 0;	
	Step_d = 0.0;
	AveRadius_d = 0.0;
	
	while (NumRepeat<(int)((1.0/Increase_d)*2.0+1e-6)) {

		NumRepeat++;

		ComputePerpendicular8Rays(CurrCenterPt_d, VesselDirection_d, Rays_d);
		for (i=0; i<16; i++) Radius_d[i] = -1.0;
		NumBoundaryVoxels_i = 0;
		for (i=0; i<8; i++) {
			for (Step_d=-0.2; Step_d<=0.2+1e-5; Step_d+=0.4) {
				loc[0] = getANearestBoundary(StartPt_d, &Rays_d[i*3], Step_d, MatMin, MatMax);
				if (loc[0]>0) NumBoundaryVoxels_i++;
				else continue;
				DataCoor_i[2] = (int)(loc[0]/this->WtimesH_mi);
				DataCoor_i[1] = (int)((loc[0] - DataCoor_i[2]*this->WtimesH_mi)/this->Width_mi);
				DataCoor_i[0] = (int)(loc[0] % this->Width_mi);
				for (k=0; k<3; k++) CurrLoc_d[k] = (double)DataCoor_i[k];
				for (k=0; k<3; k++) GradVec_d[k] = (double)this->GradientVec_mf[loc[0]*3 + k];
				this->FindZeroCrossingLocation(CurrLoc_d, GradVec_d, ZeroCrossingLoc_Ret, 
											FirstDAtTheLoc_Ret, DataPosFromZeroCrossingLoc_Ret, 0.2);
				Radius_d[NumBoundaryVoxels_i-1] = Distance (CurrCenterPt_d, ZeroCrossingLoc_Ret);
			}
		}
		
		Tempd = 0.0;
		NumBoundaryVoxels_i=0;
		for (i=0; i<16; i++) {
			if (Radius_d[i]>0.0) {
				Tempd += Radius_d[i];
				NumBoundaryVoxels_i++;
			}
			else continue;
		}
		if (NumBoundaryVoxels_i<=0) AveRadius_d += 0.0;
		else AveRadius_d += (Tempd / (double)NumBoundaryVoxels_i);

#ifdef	DEBUG_PED
		printf ("\nComputeAveRadius(): # Repeats = %d\n", NumRepeat);
		printf ("Sub Ave Radius at (%f %f %f) ", CurrCenterPt_d[0], CurrCenterPt_d[1], CurrCenterPt_d[2]);
		printf ("(%d ", (int)((CurrCenterPt_d[0] - StartLoc_gi[0])*10.0));
		printf ("%d ", (int)((CurrCenterPt_d[1] - StartLoc_gi[1])*10.0));
		printf ("%d)", (int)((CurrCenterPt_d[2] - StartLoc_gi[2])*10.0));
		printf (" = %f ", (Tempd / (double)NumBoundaryVoxels_i));
		printf ("# Boundary Voxels = %d\n", NumBoundaryVoxels_i);
		printf ("Sub Dir = (%f %f %f) ", VesselDirection_d[0], VesselDirection_d[1], VesselDirection_d[2]);
		printf ("Next Center = (%f %f %f) ", NextCenterPt_d[0], NextCenterPt_d[1], NextCenterPt_d[2]);
		printf ("(%d ", (int)((NextCenterPt_d[0] - StartLoc_gi[0])*10.0));
		printf ("%d ", (int)((NextCenterPt_d[1] - StartLoc_gi[1])*10.0));
		printf ("%d)\n", (int)((NextCenterPt_d[2] - StartLoc_gi[2])*10.0));
#endif

		for (k=0; k<3; k++) CurrCenterPt_d[k] = NextCenterPt_d[k];
		for (k=0; k<3; k++) NextCenterPt_d[k] = CurrCenterPt_d[k] + VesselDirection_d[k]*Increase_d;
		for (k=0; k<3; k++) VesselDirection_d[k] = VesselDirOrg_d[k];

#ifdef	DEBUG_PED
		printf ("Curr & Next Center = (%f %f %f) ", CurrCenterPt_d[0], CurrCenterPt_d[1], CurrCenterPt_d[2]);
		printf ("(%f %f %f)\n", NextCenterPt_d[0], NextCenterPt_d[1], NextCenterPt_d[2]);
		printf ("Curr & Next Center in the Sub Volume = ");
		printf ("(%d ", (int)((CurrCenterPt_d[0] - StartLoc_gi[0])*10.0));
		printf ("%d ", (int)((CurrCenterPt_d[1] - StartLoc_gi[1])*10.0));
		printf ("%d) ", (int)((CurrCenterPt_d[2] - StartLoc_gi[2])*10.0));
		printf ("(%d ", (int)((NextCenterPt_d[0] - StartLoc_gi[0])*10.0));
		printf ("%d ", (int)((NextCenterPt_d[1] - StartLoc_gi[1])*10.0));
		printf ("%d) ", (int)((NextCenterPt_d[2] - StartLoc_gi[2])*10.0));
		printf ("Weighted Ave. Sub Dir = (%f %f %f)\n", VesselDirection_d[0], VesselDirection_d[1], VesselDirection_d[2]);
#endif
	
	}

#ifdef	DEBUG_PED
	printf ("# Repeat = %d, Ave. Radius = %f\n", NumRepeat, AveRadius_d);
#endif

	
	AveRadius_d /= (double)NumRepeat;
	
	return AveRadius_d;
}