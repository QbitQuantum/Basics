IHLSLCodeGenerator::CodeVersion DxStdMtl2::GetPixelShaderSupport(LPDIRECT3DDEVICE9 pd3dDevice, DWORD & instSlots)
{
	D3DCAPS9	Caps;
	IHLSLCodeGenerator::CodeVersion code;
	pd3dDevice->GetDeviceCaps(&Caps);
	UINT major = D3DSHADER_VERSION_MAJOR(Caps.PixelShaderVersion);
	UINT minor = D3DSHADER_VERSION_MINOR(Caps.PixelShaderVersion);

	instSlots = 96;

	if(major < 2 )
		code = IHLSLCodeGenerator::PS_1_X;
	else if(major == 2)
	{
		instSlots = Caps.PS20Caps.NumInstructionSlots;
		if(minor > 0)
			code = IHLSLCodeGenerator::PS_2_X;
		else
			code = IHLSLCodeGenerator::PS_2_0;
	}
	else if(major >=3)
	{
		instSlots = Caps.MaxPixelShader30InstructionSlots;
		code = IHLSLCodeGenerator::PS_3_0;
	}
	else
	{
		code = IHLSLCodeGenerator::PS_1_X;
	}

	return code;

}