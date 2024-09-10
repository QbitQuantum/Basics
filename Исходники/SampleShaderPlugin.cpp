HRESULT SampleShaderPluginVertexShader::ConfirmDevice(ID3DGraphicsWindow *d3dgw)
{
	pd3dDevice = d3dgw->GetDevice();
	pd3dDevice->AddRef();
	
	D3DCAPS8 d3dCaps;
	pd3dDevice->GetDeviceCaps(&d3dCaps);
	
	return S_OK;
}