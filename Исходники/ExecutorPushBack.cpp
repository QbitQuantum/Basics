//==============================================================================
// Brief  ： コンストラクタ
// Return ：								： なし
// Arg    ： void							： なし
//==============================================================================
CExecutorPushBack::CExecutorPushBack( void )
{
	// メンバ変数の初期化
	m_idCurrent = 0;
	m_pItemTop = nullptr;
	m_isEnable = true;
	ZeroMemory( &m_criticalSection, sizeof( CRITICAL_SECTION ) );

	// クリティカルセクションの初期化
	InitializeCriticalSectionEx( &m_criticalSection, 0, 0 );
}