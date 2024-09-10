void Clouds::renderFOM(const Matrix4& inverseViewProjection, const Vector3& cameraDirection, const Vector3& cameraPosition, const Vector3& lightDir)
{	
	fomShader->useProgram();

	// noise tex
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, noiseTexture);	// noise is always on 0; the FOM textures are on 1 and 2
	glBindSampler(0, linearSampler_MipMaps);

	// matrix setup
	createLightMatrices(lightView, lightProjection, lightFarPlane, inverseViewProjection.invert(), cameraDirection, cameraPosition, lightDir);
	lightViewProjection = lightView * lightProjection;

	glUniform3fv(fomShaderUniformIndex_cameraX, 1, Vector3(lightView.m11, lightView.m21, lightView.m31));
	glUniform3fv(fomShaderUniformIndex_cameraY, 1, Vector3(lightView.m12, lightView.m22, lightView.m32));
	glUniform3fv(fomShaderUniformIndex_cameraZ, 1, -Vector3(lightView.m13, lightView.m23, lightView.m33));
	glUniformMatrix4fv(fomShaderUniformIndex_lightViewProjection, 1, false, lightViewProjection);
	lightDistancePlane_Norm[0] = -lightView.m13 / lightFarPlane;
	lightDistancePlane_Norm[1] = -lightView.m23 / lightFarPlane;
	lightDistancePlane_Norm[2] = -lightView.m33 / lightFarPlane;
	lightDistancePlane_Norm[3] = -lightView.m43 / lightFarPlane;
	glUniform4fv(fomShaderUniformIndex_LightDistancePlane_norm, 1, lightDistancePlane_Norm);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);	// additive blending
	glViewport(0,0, fourierOpacityMapSize, fourierOpacityMapSize);

	glBindFramebuffer(GL_FRAMEBUFFER, fourierOpacityMap_FBO[0]);
	glDrawBuffers(2, drawBuffers_Two);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, maxNumCloudParticles);
	
	glDisable(GL_BLEND);

	// samplerstates for fom-textures
	glBindSampler(1, linearSampler_noMipMaps);
	glBindSampler(2, linearSampler_noMipMaps);


	// filter FOM
		// shader
	fomFilterShader->useProgram();
		// horizontal
	glBindFramebuffer(GL_FRAMEBUFFER, fourierOpacityMap_FBO[1]);
	glDrawBuffers(2, drawBuffers_Two);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fourierOpacityMap_Textures[0][0]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, fourierOpacityMap_Textures[0][1]);
	glUniform4f(fomFilterShaderUniformIndex_Offset, 1.5f / fourierOpacityMapSize, 0, -1.5f / fourierOpacityMapSize, 0);
	screenTri.display();
		// vertical
	glBindFramebuffer(GL_FRAMEBUFFER, fourierOpacityMap_FBO[0]);
	glDrawBuffers(2, drawBuffers_Two);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fourierOpacityMap_Textures[1][0]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, fourierOpacityMap_Textures[1][1]);
	glUniform4f(fomFilterShaderUniformIndex_Offset, 0.0f, 1.5f / fourierOpacityMapSize, 0.0f, -1.5f / fourierOpacityMapSize);
	screenTri.display();
	
	// reset to backbuffer rendering
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffers(1, drawBuffers_One);
	glViewport(0,0, screenResolutionX, screenResolutionY); 	
}