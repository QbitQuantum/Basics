void CtrlVideo::unsetLayout()
{
    m_pLayout->getActiveVar().delObserver( this );
    getWindow()->getVisibleVar().delObserver( this );
    CtrlGeneric::unsetLayout();
}