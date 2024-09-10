void SetUpFrame(GLFrame &cameraFrame,const M3DVector3f origin,
				const M3DVector3f forward,
				const M3DVector3f cameraUpDirection) {
					cameraFrame.SetOrigin(origin);
					cameraFrame.SetForwardVector(forward);
	M3DVector3f side,oUp;
	m3dCrossProduct3(side,forward,cameraUpDirection);
	m3dCrossProduct3(oUp,side,forward);
	cameraFrame.SetUpVector(oUp);
	cameraFrame.Normalize();
};