void TopWindow::onControlRelease( const CtrlGeneric &rCtrl )
{
    // Release the capturing control
    if( m_pCapturingControl == &rCtrl )
    {
        m_pCapturingControl = NULL;
    }
    else
    {
        msg_Dbg( getIntf(), "Control had not captured the mouse" );
    }

    // Send an enter event to the control under the mouse, if it doesn't
    // have received it yet
    if( m_pLastHitControl && m_pLastHitControl != &rCtrl )
    {
        EvtEnter evt( getIntf() );
        m_pLastHitControl->handleEvent( evt );

        // Show the tooltip
        m_rWindowManager.hideTooltip();
        UString tipText = m_pLastHitControl->getTooltipText();
        if( tipText.length() > 0 )
        {
            // Set the tooltip text variable
            VarManager *pVarManager = VarManager::instance( getIntf() );
            pVarManager->getTooltipText().set( tipText );
            m_rWindowManager.showTooltip();
        }
    }
}