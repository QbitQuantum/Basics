void TBWidgetAnimationRect::OnAnimationUpdate(float progress)
{
    if (m_mode == MODE_DELTA_IN || m_mode == MODE_DELTA_OUT)
    {
        m_dst_rect = m_src_rect = m_widget->GetRect();
        if (m_dst_rect.Equals(TBRect()))
        {
            // Widget hasn't been laid out yet,
            // the animation was started too soon.
            TBAnimationManager::AbortAnimation(this, true);
            return;
        }
        if (m_mode == MODE_DELTA_IN)
        {
            m_dst_rect.x += m_delta_rect.x;
            m_dst_rect.y += m_delta_rect.y;
            m_dst_rect.w += m_delta_rect.w;
            m_dst_rect.h += m_delta_rect.h;
        }
        else
        {
            m_src_rect.x += m_delta_rect.x;
            m_src_rect.y += m_delta_rect.y;
            m_src_rect.w += m_delta_rect.w;
            m_src_rect.h += m_delta_rect.h;
        }
        m_mode = MODE_SRC_TO_DST;
    }
    TBRect rect;
    rect.x = (int) LERP(m_src_rect.x, m_dst_rect.x, progress);
    rect.y = (int) LERP(m_src_rect.y, m_dst_rect.y, progress);
    rect.w = (int) LERP(m_src_rect.w, m_dst_rect.w, progress);
    rect.h = (int) LERP(m_src_rect.h, m_dst_rect.h, progress);
    m_widget->SetRect(rect);
}