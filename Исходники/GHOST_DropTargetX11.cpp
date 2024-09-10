GHOST_DropTargetX11::~GHOST_DropTargetX11()
{
    m_refCounter--;
    if (m_refCounter == 0) {
        Uninitialize();
        m_xdndInitialized = false;
        GHOST_PRINT("XDND uninitialized\n");
    }
}