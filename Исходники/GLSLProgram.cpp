void GLSLProgram<real>::SetupCamera()
{
	RenderState<real>* glState = RenderState<real>::Get();
	Camera<real>* camera = glState->GetCamera();
	Matrix4<float> projectionMatrix = camera->GetProjectionMatrix();
	Matrix4<float> viewMatrix = camera->GetGlobalToLocal();
	Matrix4<float> modelMatrix = glState->GetModelMatrix();
	Matrix4<float> modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	Matrix3<float> normalMatrix = modelMatrix.SubMatrix3( 0, 0 );
	normalMatrix.Inverse();
	normalMatrix.Transpose();

	// Model, view and projection matrices, camera position
	glUniformMatrix4fv( mModelMatrixLocation, 1, true, modelMatrix.GetArray() );
	glUniformMatrix4fv( mViewMatrixLocation, 1, true, viewMatrix.GetArray() );
	glUniformMatrix4fv( mProjectionMatrixLocation, 1, true, projectionMatrix.GetArray() );
	glUniformMatrix4fv( mModelViewProjectionMatrixLocation, 1, true, modelViewProjectionMatrix.GetArray() );
	glUniformMatrix3fv( mNormalMatrixLocation, 1, true, normalMatrix.GetArray() );
	Vector3<float> cameraPosition = camera->GetGlobalPosition();
	glUniform3fv( mCameraPositionLocation, 1, (float*)&cameraPosition );
}