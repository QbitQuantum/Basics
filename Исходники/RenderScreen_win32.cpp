void RenderScreenImpl::swapBuffers()
{
    if (m_hdc)
        SwapBuffers(m_hdc);
}