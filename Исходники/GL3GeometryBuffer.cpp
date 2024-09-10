//----------------------------------------------------------------------------//
void OpenGL3GeometryBuffer::draw() const
{
    if(d_vertexData.empty())
        return;

    CEGUI::Rectf viewPort = d_owner.getActiveViewPort();

    if (d_clippingActive)
    {
        d_glStateChanger->scissor(static_cast<GLint>(d_clipRect.left()),
            static_cast<GLint>(viewPort.getHeight() - d_clipRect.bottom()),
            static_cast<GLint>(d_clipRect.getWidth()),
            static_cast<GLint>(d_clipRect.getHeight()));

        d_glStateChanger->enable(GL_SCISSOR_TEST);
    }
    else
        d_glStateChanger->disable(GL_SCISSOR_TEST);

    // Update the model view projection matrix
    updateMatrix();

    CEGUI::ShaderParameterBindings* shaderParameterBindings = (*d_renderMaterial).getShaderParamBindings();

    // Set the uniform variables for this GeometryBuffer in the Shader
    shaderParameterBindings->setParameter("modelViewProjMatrix", d_matrix);
    shaderParameterBindings->setParameter("alphaPercentage", d_alpha);

    // activate desired blending mode
    d_owner.setupRenderingBlendMode(d_blendMode);

    if (OpenGLInfo::getSingleton().isVaoSupported())
    {
        // Bind our vao
        d_glStateChanger->bindVertexArray(d_verticesVAO);
    }
    else
    {
        // This binds and sets up a vbo for rendering
        finaliseVertexAttributes();
    }

    const int pass_count = d_effect ? d_effect->getPassCount() : 1;
    for (int pass = 0; pass < pass_count; ++pass)
    {
        // set up RenderEffect
        if (d_effect)
            d_effect->performPreRenderFunctions(pass);

        d_renderMaterial->prepareForRendering();

        // draw the geometry
        drawDependingOnFillRule();
    }

    // clean up RenderEffect
    if (d_effect)
        d_effect->performPostRenderFunctions();

    updateRenderTargetData(d_owner.getActiveRenderTarget());
}