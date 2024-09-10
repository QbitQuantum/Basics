void RenderableObject::SetWVPConstantBuffer(bool dynamic) {
	HRESULT hr;

	XMMATRIX worldMat = XMLoadFloat4x4(&worldMatrix);
	XMMATRIX viewProjMat = pD3DEngine->GetViewMatrix() * pD3DEngine->GetOrthoMatrix(); //2d test
	//XMMATRIX viewProjMat = pD3DEngine->GetViewMatrix() * pD3DEngine->GetProjectionMatrix();

	if (dynamic) {
	//Lock the constant buffer so it can be written to.
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	#ifdef USING_BOOST_THREADS
	pD3DEngine->LockDeviceContextMutex();
	#endif
	hr = pDeviceContext->Map(pWVPConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	#ifdef USING_BOOST_THREADS
	pD3DEngine->UnlockDeviceContextMutex();
	#endif
	

	//Get a pointer to the data in the constant buffer.
	WVPConstantBuffer* dataPtr;
	dataPtr = (WVPConstantBuffer*)mappedResource.pData;

	XMStoreFloat4x4(&dataPtr->worldMatrix, XMMatrixTranspose(worldMat));	
	XMStoreFloat4x4(&dataPtr->viewProjMatrix, XMMatrixTranspose(viewProjMat));	

	//Unlock the constant buffer.
	#ifdef USING_BOOST_THREADS
	pD3DEngine->LockDeviceContextMutex();
	#endif
	pDeviceContext->Unmap(pWVPConstantBuffer, 0);
	#ifdef USING_BOOST_THREADS
	pD3DEngine->UnlockDeviceContextMutex();
	#endif
	
	}
	else {
		WVPConstantBuffer cbPerObj;
		XMStoreFloat4x4(&cbPerObj.worldMatrix, XMMatrixTranspose(worldMat));	
		XMStoreFloat4x4(&cbPerObj.viewProjMatrix, XMMatrixTranspose(viewProjMat));	
		#ifdef USING_BOOST_THREADS
		pD3DEngine->LockDeviceContextMutex();
		#endif
		pDeviceContext->UpdateSubresource(pWVPConstantBuffer, 0, NULL, &cbPerObj, 0, 0 );
		#ifdef USING_BOOST_THREADS
		pD3DEngine->UnlockDeviceContextMutex();
		#endif
		
	}
	//Now set the constant buffer in the vertex shader with the updated values.
	#ifdef USING_BOOST_THREADS
	pD3DEngine->LockDeviceContextMutex();
	#endif
	pDeviceContext->VSSetConstantBuffers(0, 1, &pWVPConstantBuffer);
	#ifdef USING_BOOST_THREADS
	pD3DEngine->UnlockDeviceContextMutex();
	#endif
	
}