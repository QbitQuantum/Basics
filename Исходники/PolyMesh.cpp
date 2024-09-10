void PolyMesh::draw(glm::mat4 parentTransform, Camera *camera, Shader *shadowShader)
{
	Shader* activeShader;
	if (shadowShader == NULL)
		activeShader = shader;
	else 
		activeShader = shadowShader;

	glm::mat4 leafTransform = parentTransform * modelMatrix;
	glm::mat3 normalMatrix = glm::gtx::inverse_transpose::inverseTranspose(glm::mat3(leafTransform));

	if (!dataIsUploaded)
		transferData();


	if (diffuseTextureHandle > 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureHandle);
	}

	if (specularTextureHandle > 0)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularTextureHandle);
	}

	if (normalTextureHandle > 0)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, normalTextureHandle);
	}

	activeShader->bind();
	{

		GLint location;
		if ((location = activeShader->get_uniform_location("cameraPosition")) >= 0)
			glUniform3fv(location, 1, glm::value_ptr(camera->getPosition()));

		if ((location = activeShader->get_uniform_location("projectionMatrix")) >= 0)
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
		if ((location = activeShader->get_uniform_location("viewMatrix")) >= 0)
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
		if ((location = activeShader->get_uniform_location("modelMatrix")) >= 0)
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(leafTransform));

		if ((location = activeShader->get_uniform_location("shadowPV")) >= 0)
		{
			mat4 shadowPV = Kocmoc::getInstance().getOrthoCam()->getProjectionMatrix() * Kocmoc::getInstance().getOrthoCam()->getViewMatrix();
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(shadowPV));
		}

		if (normalPositions != NULL && (location = activeShader->get_uniform_location("normalMatrix")) >= 0)
			glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(normalMatrix));	
	
		glBindVertexArray(vaoHandle);
		glDrawElements(GL_TRIANGLES, triangulatedVertexIndexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);