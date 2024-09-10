CJbookletApp::CJbookletApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
    m_langCode = GetThreadLocale();
    if ( m_langCode != 0x0411 )
        m_langCode = 0x0409;  // 「日本語」以外の場合は強制的に「英語」にする
    SetThreadLocale( m_langCode );
}