void Ssao::runBlur(RenderPassWorkContext& rgraphCtx)
{
	CommandBufferPtr& cmdb = rgraphCtx.m_commandBuffer;

	cmdb->bindShaderProgram(m_blur.m_grProg);

	cmdb->bindSampler(0, 0, m_r->getSamplers().m_trilinearClamp);
	rgraphCtx.bindColorTexture(0, 1, m_runCtx.m_rts[0]);

	if(m_blurUseCompute)
	{
		rgraphCtx.bindImage(0, 2, m_runCtx.m_rts[1], TextureSubresourceInfo());
		dispatchPPCompute(cmdb, m_workgroupSize[0], m_workgroupSize[1], m_width, m_height);
	}
	else
	{
		cmdb->setViewport(0, 0, m_width, m_height);
		drawQuad(cmdb);
	}
}