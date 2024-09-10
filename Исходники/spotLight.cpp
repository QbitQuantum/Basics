	void SpotLight::Initialize(const char *fileName, const DirectX::XMFLOAT3 *_diffuseColor, 
		const DirectX::XMFLOAT3 *_ambientColor, const DirectX::XMFLOAT3 *_specularColor, 
		float _specularPower, float _specularIntensisty, float _cutoff, float _exponent, 
		const DirectX::XMFLOAT3 *_attenuation, float _radius, bool _isEnabled)
	{
		cBufferData.spotLight.enabled = _isEnabled;
		cBufferData.spotLight.diffuseColor = *_diffuseColor; 
		cBufferData.spotLight.ambientColor = *_ambientColor; 
		cBufferData.spotLight.specularColor = *_specularColor; 
		cBufferData.spotLight.specularPower = _specularPower;
		cBufferData.spotLight.specularIntensity = _specularIntensisty;
		cBufferData.spotLight.exponent = _exponent;
		cBufferData.spotLight.cutoff = _cutoff;

		LoadModel(fileName);

		cBufferData.spotLight.attenuation = *_attenuation;
		float adjacent = cBufferData.spotLight.range = _radius;

		float radAngle = acos(cBufferData.spotLight.cutoff);
		float tanr = tan(radAngle);
		float opposite = tanr * adjacent;

		XMMATRIX mat = XMMatrixScaling( opposite, opposite, adjacent);
		renderShape->SetWorldMatrix(((XMFLOAT4X4 *)&mat));

		cBuffer.Release();
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(cBufferData);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		HR(Renderer::theDevicePtr->CreateBuffer(&bd, nullptr, &cBuffer));
	}