//----------------------------------------------------------
void ofCairoRenderer::setupScreenPerspective(float width, float height, float fov, float nearDist, float farDist){
	if(!b3D) return;
	if(width < 0) width = viewportRect.width;
	if(height < 0) height = viewportRect.height;
	ofOrientation orientation = ofGetOrientation();

	float viewW = viewportRect.width;
	float viewH = viewportRect.height;

	float eyeX = viewW / 2;
	float eyeY = viewH / 2;
	float halfFov = PI * fov / 360;
	float theTan = tanf(halfFov);
	float dist = eyeY / theTan;
	float aspect = (float) viewW / viewH;

	if(nearDist == 0) nearDist = dist / 10.0f;
	if(farDist == 0) farDist = dist * 10.0f;

	projection.makePerspectiveMatrix(fov,aspect,nearDist,farDist);
	modelView.makeLookAtViewMatrix(ofVec3f(eyeX,eyeY,dist),ofVec3f(eyeX,eyeY,0),ofVec3f(0,1,0));


	//note - theo checked this on iPhone and Desktop for both vFlip = false and true
	switch(orientation) {
		case OF_ORIENTATION_180:
			modelView.glRotate(-180,0,0,1);
			if(isVFlipped()){
				modelView.glScale(-1,-1,1);
				modelView.glTranslate(width,0,0);
			}else{
				modelView.glTranslate(width,-height,0);
			}

			break;

		case OF_ORIENTATION_90_RIGHT:
			modelView.glRotate(-90,0,0,1);
			if(isVFlipped()){
				modelView.glScale(1,1,1);
			}else{
				modelView.glScale(1,-1,1);
				modelView.glTranslate(-width,-height,0);
			}
			break;

		case OF_ORIENTATION_90_LEFT:
			modelView.glRotate(90,0,0,1);
			if(isVFlipped()){
				modelView.glScale(1,1,1);
				modelView.glTranslate(0,-height,0);
			}else{

				modelView.glScale(1,-1,1);
				modelView.glTranslate(0,0,0);
			}
			break;

		case OF_ORIENTATION_DEFAULT:
		default:
			if(isVFlipped()){
				modelView.glScale(-1,-1,1);
				modelView.glTranslate(-width,-height,0);
			}
			break;
	}
};