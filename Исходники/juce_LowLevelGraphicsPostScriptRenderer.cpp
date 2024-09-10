//==============================================================================
void LowLevelGraphicsPostScriptRenderer::fillRect (const Rectangle<int>& r, const bool /*replaceExistingContents*/)
{
    fillRect (r.toFloat());
}