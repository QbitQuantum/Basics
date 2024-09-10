bool BaseProgramRenderPass::Initialize()
{
	if (mProgramState->Program()!=0)
	{
		Uninitialize();
	}

	uint newProgram=Render::Instance().CreateProgram();
	RETURN_FALSE_IF_ZERO(newProgram);
	mProgramState->SetProgram(newProgram);
	if (mVertexShader!=nullptr)
	{
		Render::Instance().AttachShader(newProgram,mVertexShader->Shader());
	}

	if (mPixelShader!=nullptr)
	{
		Render::Instance().AttachShader(newProgram,mPixelShader->Shader());
	}

	if (!IsLinked())
	{
		Link();
	}

	return true;	
}