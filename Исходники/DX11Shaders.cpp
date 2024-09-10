bool DX11::ModelShader::SetParameters(ID3D11DeviceContext * direct3Dcontext, Gpu::Model * model, Gpu::Camera * camera, Gpu::Light ** lights, unsigned numLights, float aspect, Gpu::Effect * effect)
{
	if(!model || !camera) return false;
	if(camera->position == camera->target)
	{
		OutputDebugString(L"Cannot construct view matrix!");
		return false;
	}

	// MATRIX OPS - SIGNIFICANT COST - ~9us //

	glm::mat4 modelMatrix = model->GetMatrix();
	XMMATRIX world((float*)&modelMatrix);

	XMStoreFloat4x4(&vertexConstData.world, world);

	glm::mat4 camMatrix = camera->GetProjMatrix(aspect) * camera->GetViewMatrix();
	XMMATRIX viewProj((float*)&camMatrix);

	XMStoreFloat4x4(&vertexConstData.viewProjection, viewProj);

	XMMATRIX wit = XMMatrixInverse(0, XMMatrixTranspose(world));
	XMStoreFloat4x4(&vertexConstData.worldInverseTranspose, wit);

	vertexConstData.materialColor = XMFLOAT4(model->color.r, model->color.g, model->color.b, model->color.a);

	ID3D11ShaderResourceView * nullResource = 0;

	if(model->texture)
	{
		DX11::Texture* texture = static_cast<DX11::Texture*>(model->texture);
		direct3Dcontext->PSSetShaderResources(0, 1, &texture->shaderView);
	}
	else
	{
		direct3Dcontext->PSSetShaderResources(0, 1, &nullResource);
	}
	
	// BEGIN LIGHTING - VARIABLE COST //

	if(model->cubeMap)
	{
		DX11::CubeMap * cubeMap = static_cast<DX11::CubeMap*>(model->cubeMap);
		direct3Dcontext->PSSetShaderResources(1, 1, &cubeMap->shaderView);
		pixelConstData.cubeMapAlpha = 1.0f;
	}
	else
	{
		direct3Dcontext->PSSetShaderResources(1, 1, &nullResource);
		pixelConstData.cubeMapAlpha = 0.0f;
	}
	if(model->normalMap)
	{
		DX11::Texture * normalMap = static_cast<DX11::Texture*>(model->normalMap);
		direct3Dcontext->PSSetShaderResources(2, 1, &normalMap->shaderView);
	}
	else
	{
		direct3Dcontext->PSSetShaderResources(2, 1, &nullResource);
	}

	pixelConstData.numLights = numLights;
	if(numLights > 0)
	{
		pixelConstData.ambient = 0.0f;
		pixelConstData.cameraPosition = XMFLOAT3(camera->position.x, camera->position.y, camera->position.z);
		pixelConstData.specularPower = model->specPower;
		pixelConstData.specularFactor = model->specFactor;
		pixelConstData.diffuseFactor = model->diffuseFactor;

		for(unsigned i = 0; i < numLights && i < MAX_LIGHTS; ++i)
		{
			// Hmm, really the specular highlight should be calculated
			// from the light's size, position and intensity.
			// Do a little more investigation into Physically Based Lighting

			lightConstData.positionSpecs[i].specPower = 12.0f;

			Gpu::LightType lightType = lights[i]->GetType();
			if(lightType == Gpu::LightType_Directional)
			{
				Gpu::DirectionalLight * dirLight = static_cast<Gpu::DirectionalLight*>(lights[i]);
				XMVECTOR lightDirVec = XMLoadFloat3(&XMFLOAT3(dirLight->direction.x, dirLight->direction.y, dirLight->direction.z));
				XMStoreFloat3(&(lightConstData.positionSpecs[i].position), XMVectorScale(lightDirVec, 10.0e+10f));
				lightConstData.colorAttenuations[i].color = XMFLOAT3(dirLight->color.r, dirLight->color.g, dirLight->color.b);
				lightConstData.colorAttenuations[i].attenuation = 0.0f;
				lightConstData.spotDirPowers[i].direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
				lightConstData.spotDirPowers[i].spotPower = 0.0f;
			}
			if(lightType == Gpu::LightType_Point)
			{
				Gpu::PointLight * pointLight = static_cast<Gpu::PointLight*>(lights[i]);
				lightConstData.positionSpecs[i].position = XMFLOAT3(pointLight->position.x, pointLight->position.y, pointLight->position.z);
				lightConstData.colorAttenuations[i].color = XMFLOAT3(pointLight->color.r, pointLight->color.g, pointLight->color.b);
				lightConstData.colorAttenuations[i].attenuation = pointLight->atten;
				lightConstData.spotDirPowers[i].direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
				lightConstData.spotDirPowers[i].spotPower = 0.0f;
			}
			if(lightType == Gpu::LightType_Spot)
			{
				Gpu::SpotLight * spotLight = static_cast<Gpu::SpotLight*>(lights[i]);
				lightConstData.positionSpecs[i].position = XMFLOAT3(spotLight->position.x, spotLight->position.y, spotLight->position.z);
				lightConstData.colorAttenuations[i].color = XMFLOAT3(spotLight->color.r, spotLight->color.g, spotLight->color.b);
				lightConstData.colorAttenuations[i].attenuation = spotLight->atten;
				XMStoreFloat3(&lightConstData.spotDirPowers[i].direction, XMVector3Normalize(XMLoadFloat3(
					&XMFLOAT3(spotLight->direction.x, spotLight->direction.y, spotLight->direction.z))));
				lightConstData.spotDirPowers[i].spotPower = spotLight->power;

				if(i == 0)
				{
					float lightFOV = XM_PI * 0.15f;

					glm::mat4 lightGlmMatrix = spotLight->GetMatrix(lightFOV, glm::vec3(0.0f, 1.0f, 0.0f));
					XMMATRIX lightXMMatrix((float*)&lightGlmMatrix);

					//XMMATRIX lightView = XMMatrixLookToLH(
					//	XMLoadFloat3(&lightConstData.positionSpecs[i].position),
					//	XMLoadFloat3(&lightConstData.spotDirPowers[i].direction),
					//	XMLoadFloat3(&XMFLOAT3(0.0f, 1.0f, 0.0f)));

					//XMMATRIX lightLens = XMMatrixPerspectiveFovLH(lightFOV, 1.0f, 1.0f, 200.0f);

					XMStoreFloat4x4(&vertexConstData.lightViewProjection, lightXMMatrix);
				}
			}
		}

		static unsigned setCount = 0;

		setCount++;

		direct3Dcontext->UpdateSubresource(lightParamsBuffer, 0, 0, &lightConstData, sizeof(LightConstants), sizeof(LightConstants));

		setCount++;

		direct3Dcontext->PSSetConstantBuffers(1, 1, &lightParamsBuffer);
	}
	else
	{
		pixelConstData.lightPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
		pixelConstData.lightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		pixelConstData.cameraPosition = XMFLOAT3(camera->position.x, camera->position.y, camera->position.z);
		pixelConstData.spotPower = 0.0f;
		pixelConstData.specularPower = FLT_MAX;
		pixelConstData.spotDirection = XMFLOAT3(0.0f, 0.0f, 0.0f);
		pixelConstData.ambient = 1.0f;
	}

	// END LIGHTING //

	// UPDATING CONSTANT BUFFERS - SIGNIFICANT COST - 17us //

	direct3Dcontext->UpdateSubresource(pixelConstBuffer, 0, 0, &pixelConstData, sizeof(PixelConstants), sizeof(PixelConstants));
	direct3Dcontext->PSSetConstantBuffers(0, 1, &pixelConstBuffer);

	direct3Dcontext->UpdateSubresource(vertexConstBuffer, 0, 0, &vertexConstData, sizeof(VertexConstants), sizeof(VertexConstants));
	direct3Dcontext->VSSetConstantBuffers(0, 1, &vertexConstBuffer);

	// SETTING EXTRA PARAMS - VARIABLE COST //

	if(effect)
	{
		return currentTechnique->SetExtraParameters(direct3Dcontext, effect);
	}
	else
	{
		return true;
	}
}