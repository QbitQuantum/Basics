zglCoreContextWin::zglCoreContextWin(const zglState& state)
    : m_state(state)
    , m_hDC(NULL)
    , m_Context(NULL)
    , m_tempContext(NULL)
{
    CreateContext();
}