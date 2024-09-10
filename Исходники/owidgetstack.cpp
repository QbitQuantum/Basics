/**
 * @internal_resons
 */
void OWidgetStack::resizeEvent( QResizeEvent* ev ) {
    QFrame::resizeEvent( ev );
    if (m_mode == SmallScreen )
        m_stack->setGeometry( frameRect() );
    else
        if (m_mWidget )
            m_mWidget->setGeometry( frameRect() );

}