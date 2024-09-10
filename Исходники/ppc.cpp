void PPC::SetPMat(){
	Matrix3x3 cam;
	cam.setColumn(0, a);
	cam.setColumn(1, b);
	cam.setColumn(2, c);
	pMat = cam.inverse();
}