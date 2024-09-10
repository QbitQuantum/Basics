// ----------------------------------------------------------------
//	Constructor
// ----------------------------------------------------------------
CD2DText::CD2DText(void)
	: m_pD2DRenderer( & CD2DRenderer::GetInstance() )
	, m_Text( L"" )
	, m_FontFace( L"" )
	, m_FontSize(0)
	, m_ColorR(0)
	, m_ColorG(0)
	, m_ColorB(0)
	, m_Opacity(1.f)
	, m_Bold(false)
	, m_Italic(false)
	, m_DWriteFactory(nullptr)
	, m_TextFormat(nullptr)
	, m_Brush(nullptr)
	, m_PosX(0)
	, m_PosY(0)
{
	DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_DWriteFactory), reinterpret_cast<IUnknown**>(&m_DWriteFactory) );
	m_pD2DRenderer->GetHwndRenderTarget()->CreateSolidColorBrush( D2D1::ColorF(m_ColorR,m_ColorG,m_ColorB), &m_Brush );
}