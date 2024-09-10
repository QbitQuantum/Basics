void TerrainGrassBatcher::batchRender() {
	if (getRenderScene()->_shaderSwitchesEnabled) {
		_grassRenderShader->bind();
		_grassRenderShader->bindShaderTextures();

		_grassRenderShader->setUniformf("d3dCompletelyVisibleDistance", _completelyVisibleDistance);
		//_grassRenderShader->setUniformf("d3dCompletelyInvisibleDistance", _completelyInvisibleDistance);
		_grassRenderShader->setUniformf("d3dInvFadeRange", 1.0f / (_completelyInvisibleDistance - _completelyVisibleDistance));
		_grassRenderShader->setUniformf("d3dWaveTime", _waveTimer);

		getRenderScene()->setTransform(Matrix4x4f::identityMatrix());

		for (std::list<SceneObjectRef>::iterator it = _grassObjects.begin(); it != _grassObjects.end(); it++) {
			if ((getRenderScene()->_logicCamera._position - (*it)->getAABB().getCenter()).magnitude() - (*it)->getAABB().getRadius() > _completelyInvisibleDistance)
				continue;

			TerrainGrass* pGrass = static_cast<TerrainGrass*>(it->get());

			for (size_t i = 0; i < pGrass->_staticMeshes.size(); i++)
				pGrass->_staticMeshes[i]->render();
		}
	}
	else if (getRenderScene()->_renderingShadows && _renderShadows) {
		Shader* pPrevShader = Shader::getCurrentShader();

		_depthRenderShader->bind();
		_depthRenderShader->bindShaderTextures();

		_depthRenderShader->setUniformf("d3dCompletelyVisibleDistance", _completelyVisibleDistance);
		//_grassRenderShader->setUniformf("d3dCompletelyInvisibleDistance", _completelyInvisibleDistance);
		_depthRenderShader->setUniformf("d3dInvFadeRange", 1.0f / (_completelyInvisibleDistance - _completelyVisibleDistance));
		_depthRenderShader->setUniformf("d3dWaveTime", _waveTimer);

		getRenderScene()->setTransform(Matrix4x4f::identityMatrix());

		for (std::list<SceneObjectRef>::iterator it = _grassObjects.begin(); it != _grassObjects.end(); it++) {
			if ((getRenderScene()->_logicCamera._position - (*it)->getAABB().getCenter()).magnitude() - (*it)->getAABB().getRadius() > _completelyInvisibleDistance)
				continue;

			TerrainGrass* pGrass = static_cast<TerrainGrass*>(it->get());

			for (size_t i = 0; i < pGrass->_staticMeshes.size(); i++)
				pGrass->_staticMeshes[i]->render();
		}

		pPrevShader->bind();
	}

	_grassObjects.clear();
}