void D10State::blit(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	HRESULT hr;

	ods("D3D10: Blit %d %d %d %d", x, y, w, h);

	if (! pTexture || ! pSRView || uiLeft == uiRight)
		return;

	D3D10_MAPPED_TEXTURE2D mappedTex;
	hr = pTexture->Map(D3D10CalcSubresource(0, 0, 1), D3D10_MAP_WRITE_DISCARD, 0, &mappedTex);
	if (FAILED(hr)) {
		ods("D3D10: Failed map");
	}

	UCHAR* pTexels = (UCHAR*)mappedTex.pData;

	for (unsigned int r=0;r< uiHeight; ++r) {
		unsigned char *sptr = a_ucTexture + r * uiWidth * 4;
		unsigned char *dptr = reinterpret_cast<unsigned char *>(pTexels) + r * mappedTex.RowPitch;
		memcpy(dptr, sptr, uiWidth * 4);
	}

	pTexture->Unmap(D3D10CalcSubresource(0, 0, 1));
}