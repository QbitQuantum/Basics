FramebufferManager::~FramebufferManager()
{
    s_xfbEncoder.Shutdown();

    SAFE_RELEASE(m_efb.color_tex);
    SAFE_RELEASE(m_efb.color_temp_tex);

    D3D::command_list_mgr->DestroyResourceAfterCurrentCommandListExecuted(m_efb.color_staging_buf);

    SAFE_RELEASE(m_efb.resolved_color_tex);
    SAFE_RELEASE(m_efb.depth_tex);

    D3D::command_list_mgr->DestroyResourceAfterCurrentCommandListExecuted(m_efb.depth_staging_buf);

    SAFE_RELEASE(m_efb.depth_read_texture);
    SAFE_RELEASE(m_efb.resolved_depth_tex);
}