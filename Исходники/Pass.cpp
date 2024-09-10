void Pass::draw() {
	initDraw();
	
	if (useDefaultWVP) {
		XMFLOAT4X4 view = camera->getViewMatrix();
		XMMATRIX camView = XMLoadFloat4x4(&view);
		XMMATRIX camProjection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, (float)width / height, 1.0f, 1000.0f);
		XMMATRIX w = XMLoadFloat4x4(&world);
		XMMATRIX WVP = XMMatrixTranspose(w * camView * camProjection);

		cbPerObject cbPerObj;
		cbPerObj.WVP = WVP;
		cbPerObj.normalTransform = w;
		cbPerObj.eyePosition = camera->position;
		Constant *wvp = new Constant(&cbPerObj, sizeof(cbPerObj), 0);
		wvp->setConstantForVS(device, context);
	}
	else {
		XMMATRIX w = XMLoadFloat4x4(&world);
		XMMATRIX WVP = XMMatrixTranspose(w);

		MatrixBuffer buffer;
		buffer.matrix = WVP;
		Constant *wvp = new Constant(&buffer, sizeof(buffer), 0);
		wvp->setConstantForVS(device, context);
	}

	model->draw(device, context, vertexShader->buffer);
}