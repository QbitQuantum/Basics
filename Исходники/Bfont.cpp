//-------------------------------------------------------------------------------------------------------
BString::BString(StringManager* father, const wstring& wstr, int height, const vector2f& screensize, const vector2d& orgiSize, const Color& clr, RendBuffer* buffer, const vector2d& texSize, const byte* pBuffer )
    :m_String(wstr),
     m_Father( father ),
     m_MaxHeight(height),
     m_isManaged(true),
     m_isShow(true),
     m_fScale(1,1),
     m_StringTextureSize(orgiSize),
     m_ScreenFontSize( screensize ),
     m_eAlign(Center)
{
    m_pTex = NEW Texture2D();
    m_pTex->MakeTexture( Device::PF_A8, 1, texSize, pBuffer );

    const vector2d& resolution = Engine::Instance().GetDevice()->GetResolutionSize();
    m_Size = vector2f(
                 static_cast<float>(orgiSize.m_x) / static_cast<float>(resolution.m_x),
                 static_cast<float>(orgiSize.m_y) / static_cast<float>(resolution.m_y)
             );
    m_Size *= 2.0f;//转换到屏幕级别
    vector2f scrrenPos = m_Size;// * 2.0f;


    vector2f coord;
    coord.m_x = static_cast<float>(orgiSize.m_x) / texSize.m_x;
    coord.m_y = static_cast<float>(orgiSize.m_y) / texSize.m_y;

    m_pVertex = NEW VertexTextureColor[COUNT_OF_VERTEX];
    m_pVertex[0] = VertexTextureColor(vector4f(0,0,0), vector2f(0,0), clr);
    m_pVertex[1] = VertexTextureColor(vector4f(0,-scrrenPos.m_y,0), vector2f(0,coord.m_y), clr);
    m_pVertex[2] = VertexTextureColor(vector4f(scrrenPos.m_x,0,0), vector2f(coord.m_x,0), clr);
    m_pVertex[3] = VertexTextureColor(vector4f(scrrenPos.m_x,-scrrenPos.m_y,0), vector2f(coord.m_x,coord.m_y), clr);

    ASSERT( NULL != buffer );
    m_pRendBuffer = buffer;
    m_pRendBuffer->GetVertexBuffer()->FlushVertexBuffer( COUNT_OF_VERTEX, m_pVertex );
}