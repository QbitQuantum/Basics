/******************************************************************************
* Renders the geometry as with extra information passed to the vertex shader.
******************************************************************************/
void OpenGLArrowPrimitive::renderWithElementInfo(ViewportSceneRenderer* renderer)
{
	QOpenGLShaderProgram* shader = renderer->isPicking() ? _pickingShader : _shader;
	if(!shader)
		return;
	if(!shader->bind())
		throw Exception(QStringLiteral("Failed to bind OpenGL shader."));

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	shader->setUniformValue("modelview_matrix",
			(QMatrix4x4)renderer->modelViewTM());
	shader->setUniformValue("modelview_uniform_scale", (float)pow(std::abs(renderer->modelViewTM().determinant()), (FloatType(1.0/3.0))));
	shader->setUniformValue("modelview_projection_matrix",
			(QMatrix4x4)(renderer->projParams().projectionMatrix * renderer->modelViewTM()));
	shader->setUniformValue("projection_matrix", (QMatrix4x4)renderer->projParams().projectionMatrix);
	shader->setUniformValue("inverse_projection_matrix", (QMatrix4x4)renderer->projParams().inverseProjectionMatrix);
	shader->setUniformValue("is_perspective", renderer->projParams().isPerspective);

	AffineTransformation viewModelTM = renderer->modelViewTM().inverse();
	Vector3 eye_pos = viewModelTM.translation();
	shader->setUniformValue("eye_pos", eye_pos.x(), eye_pos.y(), eye_pos.z());
	Vector3 viewDir = viewModelTM * Vector3(0,0,1);
	shader->setUniformValue("parallel_view_dir", viewDir.x(), viewDir.y(), viewDir.z());

	GLint viewportCoords[4];
	glGetIntegerv(GL_VIEWPORT, viewportCoords);
	shader->setUniformValue("viewport_origin", (float)viewportCoords[0], (float)viewportCoords[1]);
	shader->setUniformValue("inverse_viewport_size", 2.0f / (float)viewportCoords[2], 2.0f / (float)viewportCoords[3]);

	GLint pickingBaseID;
	if(renderer->isPicking()) {
		pickingBaseID = renderer->registerSubObjectIDs(elementCount());
		renderer->activateVertexIDs(shader, _chunkSize * _verticesPerElement, true);
		OVITO_CHECK_OPENGL(shader->setUniformValue("verticesPerElement", (GLint)_verticesPerElement));
	}

	for(int chunkIndex = 0; chunkIndex < _verticesWithElementInfo.size(); chunkIndex++, pickingBaseID += _chunkSize) {
		int chunkStart = chunkIndex * _chunkSize;
		int chunkSize = std::min(_elementCount - chunkStart, _chunkSize);

		if(renderer->isPicking())
			shader->setUniformValue("pickingBaseID", pickingBaseID);

		_verticesWithElementInfo[chunkIndex].bindPositions(renderer, shader, offsetof(VertexWithElementInfo, pos));
		_verticesWithElementInfo[chunkIndex].bind(renderer, shader, "cylinder_base", GL_FLOAT, offsetof(VertexWithElementInfo, base), 3, sizeof(VertexWithElementInfo));
		_verticesWithElementInfo[chunkIndex].bind(renderer, shader, "cylinder_axis", GL_FLOAT, offsetof(VertexWithElementInfo, dir), 3, sizeof(VertexWithElementInfo));
		_verticesWithElementInfo[chunkIndex].bind(renderer, shader, "cylinder_radius", GL_FLOAT, offsetof(VertexWithElementInfo, radius), 1, sizeof(VertexWithElementInfo));
		if(!renderer->isPicking())
			_verticesWithElementInfo[chunkIndex].bindColors(renderer, shader, 4, offsetof(VertexWithElementInfo, color));

		if(_usingGeometryShader && (shadingMode() == FlatShading || renderingQuality() == HighQuality)) {
			OVITO_CHECK_OPENGL(glDrawArrays(GL_POINTS, 0, chunkSize));
		}
		else {
			int stripPrimitivesPerElement = _stripPrimitiveVertexCounts.size() / _chunkSize;
			OVITO_CHECK_OPENGL(renderer->glMultiDrawArrays(GL_TRIANGLE_STRIP, _stripPrimitiveVertexStarts.data(), _stripPrimitiveVertexCounts.data(), stripPrimitivesPerElement * chunkSize));

			int fanPrimitivesPerElement = _fanPrimitiveVertexCounts.size() / _chunkSize;
			OVITO_CHECK_OPENGL(renderer->glMultiDrawArrays(GL_TRIANGLE_FAN, _fanPrimitiveVertexStarts.data(), _fanPrimitiveVertexCounts.data(), fanPrimitivesPerElement * chunkSize));
		}

		_verticesWithElementInfo[chunkIndex].detachPositions(renderer, shader);
		_verticesWithElementInfo[chunkIndex].detach(renderer, shader, "cylinder_base");
		_verticesWithElementInfo[chunkIndex].detach(renderer, shader, "cylinder_axis");
		_verticesWithElementInfo[chunkIndex].detach(renderer, shader, "cylinder_radius");
		if(!renderer->isPicking())
			_verticesWithElementInfo[chunkIndex].detachColors(renderer, shader);
	}
	shader->enableAttributeArray("cylinder_base");
	shader->enableAttributeArray("cylinder_axis");
	shader->enableAttributeArray("cylinder_radius");

	if(renderer->isPicking())
		renderer->deactivateVertexIDs(shader, true);

	shader->release();
}