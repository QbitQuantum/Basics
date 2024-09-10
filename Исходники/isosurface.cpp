// (GL context)
void IsoSurface::render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix)
{
	if (mIsEmpty)
		return;

	if (!mBound)
		bind();

	if (mDirty)
		update();

	// Vertices
	android_assert(mVertexAttrib != -1);
	glEnableVertexAttribArray(mVertexAttrib);
	android_assert(mVertexBuffer != 0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glVertexAttribPointer(mVertexAttrib, 3, GL_FLOAT, false, 0, nullptr);

	// Normals
	android_assert(mNormalAttrib != -1);
	glEnableVertexAttribArray(mNormalAttrib);
	android_assert(mNormalBuffer != 0);
	glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
	glVertexAttribPointer(mNormalAttrib, 3, GL_FLOAT, false, 0, nullptr);

	// Indices
	android_assert(mIndexBuffer != 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);

	// Rendering

	glUseProgram(mMaterial->getHandle());
	glUniformMatrix4fv(mModelViewUniform, 1, false, modelViewMatrix.data_);
	glUniformMatrix4fv(mProjectionUniform, 1, false, projectionMatrix.data_);
	glUniformMatrix3fv(mNormalMatrixUniform, 1, false, modelViewMatrix.inverse().transpose().get3x3Matrix().data_);
	glUniform3iv(mDimensionsUniform, 1, mDimensions);
	if (mValueUniform != -1) glUniform1f(mValueUniform, (mValue-mRange[0])/(mRange[1]-mRange[0]));
	// glUniform1f(mOpacityUniform, (mStream ? 0.5f : 1.0f));
	glUniform1f(mOpacityUniform, 1.0f);
	glUniform4fv(mClipPlaneUniform, 1, mClipEq);

	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(mVertexAttrib);
	glDisableVertexAttribArray(mNormalAttrib);
}