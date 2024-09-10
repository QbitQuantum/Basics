static int assemble_shader(wchar_t *filename)
{
	LPD3DXBUFFER shader;
	wchar_t fname[MAX_PATH];
	int rc;
	FILE *outfp;

	rc = D3DXAssembleShaderFromFile(filename, NULL, NULL, 0, &shader, NULL);
	if (rc != D3D_OK)
		return 1;

	_wsplitpath_s(filename, NULL, 0, NULL, 0, fname, 250, NULL, 0);
	lstrcatW(fname, L".out");

	if ((rc = _wfopen_s(&outfp, fname, L"wb")))
		return rc;

	fwrite(shader->GetBufferPointer(), 1, shader->GetBufferSize(), outfp);
	fclose(outfp);

	return 0;
}