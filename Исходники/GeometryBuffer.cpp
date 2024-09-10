//----------------------------------------------------------------------------//
void OpenGL3GeometryBuffer::draw() const
{
    CEGUI::Rectf viewPort = d_owner->getActiveViewPort();

    d_glStateChanger->scissor(static_cast<GLint>(d_clipRect.left()),
              static_cast<GLint>(viewPort.getHeight() - d_clipRect.bottom()),
              static_cast<GLint>(d_clipRect.getWidth()),
              static_cast<GLint>(d_clipRect.getHeight()));

    // apply the transformations we need to use.
    if (!d_matrixValid)
        updateMatrix();

    // Send ModelViewProjection matrix to shader
    glm::mat4 modelViewProjectionMatrix = d_owner->getViewProjectionMatrix()->d_matrix * d_matrix->d_matrix;
    glUniformMatrix4fv(d_shaderStandardMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));

    // activate desired blending mode
    d_owner->setupRenderingBlendMode(d_blendMode);

    // Bind our vao
    d_glStateChanger->bindVertexArray(d_verticesVAO);

    const int pass_count = d_effect ? d_effect->getPassCount() : 1;
     size_t pos = 0;
    for (int pass = 0; pass < pass_count; ++pass)
    {
        // set up RenderEffect
        if (d_effect)
            d_effect->performPreRenderFunctions(pass);

        // draw the batches
       
        BatchList::const_iterator i = d_batches.begin();
        for ( ; i != d_batches.end(); ++i)
        {
            const BatchInfo& currentBatch = *i;

            if (currentBatch.clip)
                glEnable(GL_SCISSOR_TEST);
            else
                glDisable(GL_SCISSOR_TEST);

            glBindTexture(GL_TEXTURE_2D, currentBatch.texture);

            // draw the geometry
            const unsigned int numVertices = currentBatch.vertexCount;
            glDrawArrays(GL_TRIANGLES, pos, numVertices);

            pos += numVertices;
        }
    }

    

    // clean up RenderEffect
    if (d_effect)
        d_effect->performPostRenderFunctions();
}