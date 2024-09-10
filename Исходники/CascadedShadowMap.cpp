void CascadedShadowMap::buildShadowMaps(Camera *camera, View *view, Frustum *frustum, Level *level)
{
	float slice[] = {0.0, slices[0], slices[1], slices[2], 1.0};

	for (int i=0; i<4; i++) {
		Camera *lightCamera = createLightCamera(slice[i],slice[i+1],camera,view,level->getDirectLight());
		View *lightView = createLightView(slice[i],slice[i+1],camera,lightCamera,view,frustum);
		Frustum *lightFrustum = new Frustum();
		lightFrustum->getOrthoFrustum(lightCamera,lightView);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
			shadowMaps[i]->bind();
			glClearDepth(1.0);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			glPushAttrib( GL_VIEWPORT_BIT );
			glViewport( 0, 0, size, size);
			lightView->use3D(false);
			lightCamera->transform();
			lightMatrix[i].setAsModelViewProjection();
			level->drawNoShaders(lightFrustum);
			glPopAttrib();
			shadowMaps[i]->unbind();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		delete lightCamera;
		delete lightView;
		delete lightFrustum;
	}
	
}