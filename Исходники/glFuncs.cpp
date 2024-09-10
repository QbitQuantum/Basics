Eigen::Vector3d GetPointEyeToWorld(const Eigen::Ref<const Eigen::Vector3d>& _pt) {
	GLdouble modelmat[16];

	glGetDoublev( GL_MODELVIEW_MATRIX, modelmat);
	Eigen::Matrix4d InvModelMat;
	InvModelMat.setZero();
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			InvModelMat(i,j)=modelmat[4*i+j];
		}
	}
	InvModelMat=(InvModelMat.transpose());
	InvModelMat=(InvModelMat.inverse());
	Eigen::Vector4d cc( _pt(0),_pt(1), _pt(2),1);
	cc=InvModelMat*cc;
	if(cc.norm()!=0) cc=cc/cc[3];
	return Eigen::Vector3d(cc[0], cc[1], cc[2]);
}