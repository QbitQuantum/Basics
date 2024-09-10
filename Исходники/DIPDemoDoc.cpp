void CDIPDemoDoc::Init()
{
    // 初始化

    // 如果图像无效，直接返回
    if ( !m_Image.IsValidate() )
    {
        return;
    }

    // 设置文档大小
    m_sizeDoc = CSize ( m_Image.GetWidthPixel(),
                        m_Image.GetHeight() );

    // 判断调色板是否为空
    if ( m_pPalette != NULL )
    {
        // 删除调色板对象
        delete m_pPalette;
        // 重置调色板为空
        m_pPalette = NULL;
    }

    //不是调色板显示模式，则直接返回
    CClientDC dc ( NULL );

    if ( ( dc.GetDeviceCaps ( RASTERCAPS ) &
            RC_PALETTE ) == 0 )
    {
        return;
    }

    // 创建新调色板
    m_pPalette = new CPalette;
    int nEntries = m_Image.GetColorTableEntriesNum();

    if ( nEntries == 0 )
    {
        return;
    }

    LOGPALETTE* lpPal = ( LOGPALETTE* ) new
                        BYTE[sizeof ( LOGPALETTE ) + ( sizeof (
                                    PALETTEENTRY ) * ( nEntries - 1 ) )];
    // 设置版本号
    lpPal->palVersion = 0x300;
    // 设置颜色数目
    lpPal->palNumEntries = ( WORD ) nEntries;
    RGBQUAD* pPal = ( RGBQUAD* ) (
                        m_Image.GetColorTable() );
    int i;

    // 创建调色板
    for ( i = 0; i < nEntries; i++ )
    {
        // 读取红色分量
        lpPal->palPalEntry[i].peRed = pPal[i].rgbRed;
        // 读取绿色分量
        lpPal->palPalEntry[i].peGreen = pPal[i].rgbGreen;
        // 读取蓝色分量
        lpPal->palPalEntry[i].peBlue = pPal[i].rgbBlue;
        // 保留位
        lpPal->palPalEntry[i].peFlags = 0;
    }

    // 按照逻辑调色板创建调色板，并返回指针
    m_pPalette->CreatePalette ( lpPal );
    delete[] lpPal;
}