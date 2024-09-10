// Constructor.
RenderContext::RenderContext(const beGraphics::DeviceContext &context, beGraphics::StateManager *pStateManager)
	: m_pContext( CloneContext(context) ),
	m_pStateManager( LEAN_ASSERT_NOT_NULL(pStateManager) )
{
}