void KisToolLineHelper::end()
{
    if (!m_d->enabled) return;
    KIS_ASSERT_RECOVER_RETURN(isRunning());

    endPaint();
    m_d->linePoints.clear();
}