void Camera::doCameraTransform() {

	if(fovSet)
			CoreServices::getInstance()->getRenderer()->setFOV(fov);
	CoreServices::getInstance()->getRenderer()->setExposureLevel(exposureLevel);

	if(matrixDirty) {
		rebuildTransformMatrix();
	}

	Matrix4 camMatrix = getConcatenatedMatrix();
	CoreServices::getInstance()->getRenderer()->setCameraMatrix(camMatrix);	
	camMatrix = camMatrix.inverse();
	CoreServices::getInstance()->getRenderer()->multModelviewMatrix(camMatrix);		
}