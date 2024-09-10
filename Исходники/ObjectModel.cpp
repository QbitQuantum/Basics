bool ObjectModel::FloorRun(
	ID3D11Device* dev,
	ID3D11DeviceContext* devCon)
{
	HRESULT tester = 0;
#pragma region place on map

	ProjView->world = world;// *XMMatrixRotationX(180);


	ProjView->view = XMMatrixInverse(nullptr, ProjView->view);


	D3D11_MAPPED_SUBRESOURCE mapRes;


	ZeroMemory(&mapRes, sizeof(D3D11_MAPPED_SUBRESOURCE));
	tester = devCon->Map(matrixLocationBuffer[1], NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mapRes);
	memcpy(mapRes.pData, ProjView, sizeof(ProjViewMatricies));
	devCon->Unmap(matrixLocationBuffer[1], NULL);

	devCon->VSSetConstantBuffers(0, 1, &matrixLocationBuffer[1]);

	ProjView->view = XMMatrixInverse(nullptr, ProjView->view);

	ProjView->world = XMMatrixIdentity();
#pragma endregion

	ID3D11ShaderResourceView *nullshader = NULL;


#pragma region VS and PS
	UINT strides;
	UINT offsets;

	strides = sizeof(StrideStruct);
	offsets = 0;

	devCon->IASetVertexBuffers(0, 1, &VertBuff, &strides, &offsets);
	devCon->IASetIndexBuffer(IndexBuff, DXGI_FORMAT_R32_UINT, offsets);

	devCon->PSSetShaderResources(0, 1, &ObjTexture[0]);
	devCon->VSSetShader(vertexShader, 0, 0);
	devCon->PSSetShader(pixelShader, 0, 0);

	devCon->IASetInputLayout(layout);

	devCon->OMSetBlendState(0, 0, 0xffffffff);
	devCon->DrawIndexed(vertexIndices.size(), 0, 0);

	devCon->PSSetShaderResources(0, 1, &nullshader);

#pragma endregion
	return true;
}