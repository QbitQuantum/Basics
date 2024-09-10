//--------------------------------------------------------------------------------------------------
/// Draw the axis labels
//--------------------------------------------------------------------------------------------------
void OverlayNavigationCube::renderAxisLabels(OpenGLContext* oglContext, bool software, const MatrixState& matrixState)
{
    // Multiply with 1.08 will slightly pull the labels away from the corresponding arrow head
    Vec3f xPos(1.08f, 0, 0);
    Vec3f yPos(0, 1.08f, 0);
    Vec3f zPos(0, 0, 1.08f);

    DrawableText drawableText;
    drawableText.setFont(m_font.p());
    drawableText.setCheckPosVisible(false);
    drawableText.setDrawBorder(false);
    drawableText.setDrawBackground(false);
    drawableText.setVerticalAlignment(TextDrawer::CENTER);
    drawableText.setTextColor(m_textColor);

    if (!m_xLabel.isEmpty()) drawableText.addText(m_xLabel, xPos);
    if (!m_yLabel.isEmpty()) drawableText.addText(m_yLabel, yPos);
    if (!m_zLabel.isEmpty()) drawableText.addText(m_zLabel, zPos);


    // Do the actual rendering
    // -----------------------------------------------
    if (software)
    {
        drawableText.renderSoftware(oglContext, matrixState);
    }
    else
    {
        ref<ShaderProgram> textShader = oglContext->resourceManager()->getLinkedTextShaderProgram(oglContext);
        drawableText.render(oglContext, textShader.p(), matrixState);
    }
}