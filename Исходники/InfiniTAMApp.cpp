void InfiniTAMApp::RenderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (!IsInitialized()) return;

	if (mNewWindowSize.x > 0) {
		Vector2i depthImageSize = mMainEngine->GetImageSize();
		float ratio = (float)depthImageSize.x/(float)depthImageSize.y;

//		glViewport(0, 0, newWidth, newHeight);
		if (mNewWindowSize.x >= mNewWindowSize.y) {
			winPos[0] = Vector4f(0.0f, 0.0f, 1.0f/ratio, 1.0f);
			winPos[1] = Vector4f(1.0f/ratio, 0.5f, 1.0f, 1.0f);
			winPos[2] = Vector4f(1.0f/ratio, 0.0f, 1.0f, 0.5f);
		} else {
			winPos[0] = Vector4f(0.0f, 1.0f/3.0f, 1.0f, 1.0f);
			winPos[1] = Vector4f(0.0f, 0.0f, 0.5f, 1.0f/3.0f);
			winPos[2] = Vector4f(0.5f, 0.0f, 1.0f, 1.0f/3.0f);
		}

		mNewWindowSize.x = mNewWindowSize.y = -1;
	}

	int localNumWin = 1;//NUM_WIN
	for (int w = 0; w < localNumWin; w++) mMainEngine->GetImage(outImage[w], winImageType[w]);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glLoadIdentity();
		glOrthof(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			for (int w = 0; w < localNumWin; w++) {
				glBindTexture(GL_TEXTURE_2D, textureId[w]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, outImage[w]->noDims.x, outImage[w]->noDims.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, outImage[w]->GetData(MEMORYDEVICE_CPU));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				float vertices[] = {
					winPos[w][0], winPos[w][3],
					winPos[w][2], winPos[w][3],
					winPos[w][0], winPos[w][1],
					winPos[w][2], winPos[w][1] };
				float texture[] = {
					0.0f, 0.0f,
					1.0f, 0.0f,
					0.0f, 1.0f,
					1.0f, 1.0f };

				glVertexPointer(2, GL_FLOAT, 0, vertices);
				glTexCoordPointer(2, GL_FLOAT, 0, texture);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			}
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}