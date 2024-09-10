void mrpt::vision::pnp::posit::POS()
{
	Eigen::Vector3d I0, J0 , r1, r2, r3;
	double I0_norm, J0_norm;
	
	int i;
	double scale;
	
	for(i=0;i<3;i++)
	{
		I0(i)=obj_matrix.row(i).dot(img_vecs.col(0));
		J0(i)=obj_matrix.row(i).dot(img_vecs.col(1));
	}
	
    
	I0_norm=I0.norm();
	J0_norm=J0.norm();
	
	scale=(I0_norm + J0_norm)/2;
	
	/*Computing TRANSLATION */
	t(0)=img_pts(0,0)/scale;
	t(1)=img_pts(0,1)/scale;
	t(2)=f/scale;
	
	/* Computing ROTATION */
	r1=I0/I0_norm;
	r2=J0/J0_norm;
	r3=r1.cross(r2);
	
	R.row(0)=r1;
	R.row(1)=r2;
	R.row(2)=r3;
}