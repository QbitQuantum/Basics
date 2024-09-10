bool TestTriangleStripsDX::InitScene()
{
	XMStoreFloat4(&up, XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));
	XMStoreFloat4(&eye, XMVectorSet(0.0f, 18.0f, 18.0f, 1.0f));
	XMStoreFloat4(&right, XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f));
	XMStoreFloat4(&center, XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	bg[0] = bgColor.r;
	bg[1] = bgColor.g;
	bg[2] = bgColor.b;
	bg[3] = bgColor.a;

	ID3D11RasterizerState1 *rasterizerState;
	D3D11_RASTERIZER_DESC1 rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = true;

	mDevice->CreateRasterizerState1(&rasterizerDesc, &rasterizerState);
	mDeviceContext->RSSetState(rasterizerState);
	rasterizerState->Release();

	BinaryIO::ReadVector4s(binaryPath + "triangle_strip_plane.bin", vertices);

	D3D11_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3DCompileFromFile(Util::s2ws(shaderPath + "TestTriangleStripsVert.hlsl").c_str(), NULL, NULL, "vertexShader", "vs_5_0", NULL, NULL, &vertexShaderBuffer, NULL);
	D3DCompileFromFile(Util::s2ws(shaderPath + "TestTriangleStripsFrag.hlsl").c_str(), NULL, NULL, "pixelShader", "ps_5_0", NULL, NULL, &pixelShaderBuffer, NULL);
	mDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);
	mDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.ByteWidth = vertices.size() * sizeof(Vector4);
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &vertices[0];

	mDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);

	mDevice->CreateInputLayout(vertexLayout, 1, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputLayout);

	// UPLOAD MVP MATRICES
	XMMATRIX modelMatrix = XMMatrixIdentity();
	XMMATRIX viewMatrix = XMMatrixLookAtRH(XMLoadFloat4(&eye), XMLoadFloat4(&center), XMLoadFloat4(&up));
	XMMATRIX projectionMatrix = XMMatrixPerspectiveFovRH(XMConvertToRadians(60.0f), 800 / 800, 1.0f, 500.0f);

	ID3D11Buffer* modelMatrixBuffer = DXUtil::CreateMatrixBuffer(mDevice, modelMatrix);
	mDeviceContext->VSSetConstantBuffers(modelMatrixBufferSlot, 1, &modelMatrixBuffer);
	modelMatrixBuffer->Release();

	viewMatrixBuffer = DXUtil::CreateMatrixBuffer(mDevice, viewMatrix);
	mDeviceContext->VSSetConstantBuffers(viewMatrixBufferSlot, 1, &viewMatrixBuffer);
	viewMatrixBuffer->Release();

	ID3D11Buffer* projectionMatrixBuffer = DXUtil::CreateMatrixBuffer(mDevice, projectionMatrix);
	mDeviceContext->VSSetConstantBuffers(projectionMatrixBufferSlot, 1, &projectionMatrixBuffer);
	projectionMatrixBuffer->Release();

	return true;
}