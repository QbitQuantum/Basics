/**
 * @brief setChildShow  设置子窗口是否显示
 * @param isshow
 */
void WMouseInOutWidget::setChildShow(bool isshow)
{
    if(m_timeId != 0)
    {
        killTimer(m_timeId);
        m_timeId=0;
    }

    m_childWidget->setVisible(isshow);
    if(m_isAudoHide && isshow)
        m_timeId = startTimer(m_timeout);

    if(isshow)
        emit mouseInWidget();
    else
        emit mouseOutWidget();

}