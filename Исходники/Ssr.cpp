void Ssr::run(RenderPassWorkContext& rgraphCtx)
{
	RenderingContext& ctx = *m_runCtx.m_ctx;
	CommandBufferPtr& cmdb = rgraphCtx.m_commandBuffer;
	cmdb->bindShaderProgram(m_grProg[m_r->getFrameCount() & 1u]);

	// Bind all
	cmdb->bindSampler(0, 0, m_r->getSamplers().m_trilinearClamp);

	rgraphCtx.bindColorTexture(0, 1, m_r->getGBuffer().getColorRt(1));
	rgraphCtx.bindColorTexture(0, 2, m_r->getGBuffer().getColorRt(2));

	TextureSubresourceInfo hizSubresource; // Only first mip
	rgraphCtx.bindTexture(0, 3, m_r->getDepthDownscale().getHiZRt(), hizSubresource);

	rgraphCtx.bindColorTexture(0, 4, m_r->getDownscaleBlur().getRt());

	rgraphCtx.bindImage(0, 5, m_runCtx.m_rt, TextureSubresourceInfo());

	// Bind uniforms
	SsrUniforms* unis = allocateAndBindUniforms<SsrUniforms*>(sizeof(SsrUniforms), cmdb, 0, 6);
	unis->m_nearPad3 = Vec4(ctx.m_renderQueue->m_cameraNear);
	unis->m_prevViewProjMatMulInvViewProjMat =
		ctx.m_prevMatrices.m_viewProjection * ctx.m_matrices.m_viewProjectionJitter.getInverse();
	unis->m_projMat = ctx.m_matrices.m_projectionJitter;
	unis->m_invProjMat = ctx.m_matrices.m_projectionJitter.getInverse();
	unis->m_normalMat = Mat3x4(ctx.m_matrices.m_view.getRotationPart());

	// Dispatch
	const U sizeX = (m_r->getWidth() / SSR_FRACTION + m_workgroupSize[0] - 1) / m_workgroupSize[0];
	const U sizeY = (m_r->getHeight() / SSR_FRACTION + m_workgroupSize[1] - 1) / m_workgroupSize[1];
	cmdb->dispatchCompute(sizeX / 2, sizeY, 1);
}