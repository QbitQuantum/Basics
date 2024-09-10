    UIContext::UIContext(const Vector2& screenSize) :
        m_screenSize(screenSize)
    {
#if defined(WIN32)
        doubleClickTime = std::chrono::milliseconds(GetDoubleClickTime());
#endif
        pContentManager = oContentManager;
        m_pDownControls[0] = nullptr;
        m_pDownControls[1] = nullptr;
        m_pDownControls[2] = nullptr;
        m_pLastDownControls[0] = nullptr;
        m_pLastDownControls[1] = nullptr;
        m_pLastDownControls[2] = nullptr;
    }