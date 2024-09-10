void CPHMovementControl::PathDIrPoint(const xr_vector<DetailPathManager::STravelPathPoint> &path,  int index,  float distance,  float precesition, Fvector &dir  )
{
	Fvector to_path_point;
	Fvector corrected_path_dir;CorrectPathDir(GetPathDir(),path,index,corrected_path_dir);
	to_path_point.sub(vPathPoint,vPosition);	//_new position
	float mag=to_path_point.magnitude();

	if(mag<EPS) //near the point
	{  
		if(0==index||m_path_size-1==index) //on path eidge
		{
			dir.set(corrected_path_dir);//??
			return;
		}
		dir.sub(path[index].position,path[index-1].position);
		dir.normalize_safe();
		dir.add(corrected_path_dir);
		dir.normalize_safe();
	}
	to_path_point.mul(1.f/mag);
	if(m_path_size-1==index)//on_path_edge
	{
		dir.set(to_path_point);
		return;
	}


	if(mag<EPS||fis_zero(dXZMag(to_path_point),EPS))
	{
		dir.set(corrected_path_dir);
		return;//mean dir
	}
	
	Fvector tangent;
	tangent.crossproduct(Fvector().set(0,1,0),to_path_point);

	VERIFY(!fis_zero(tangent.magnitude()));
	tangent.normalize();
	if(dir.square_magnitude()>EPS)
	{
		if(tangent.dotproduct(dir)<0.f)tangent.invert();
	}
	else
	{
		if(tangent.dotproduct(corrected_path_dir)<0.f)tangent.invert();
	}

	if(mag>FootRadius())to_path_point.mul(precesition);
	else to_path_point.mul(mag*precesition);
	dir.add(tangent,to_path_point);
	dir.normalize_safe();
}