int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
#ifdef _WIN64
	_tprintf( _T("Platform : 64-bit\n") );
#else
	_tprintf( _T("Platform : 32-bit\n") );
#endif

#ifdef _DEBUG
	_tprintf( _T("Build    : Debug\n") );
#else
	_tprintf( _T("Build    : Release\n") );
#endif

	SYSTEM_INFO si = {};
	GetSystemInfo( &si );
	_tprintf( _T("CPUs     : %u\n"), si.dwNumberOfProcessors );

	_tprintf( _T("\nHashWord() function tests:\n\n") );
	_tprintf( _T("Hash test 1... %s\n"),
		( HashWord( L"\x30a2\x30cb\x30e1", 0,  3, 10 ) ==  46 ) ? _T("OK") : _T("FAIL") );
	_tprintf( _T("Hash test 2... %s\n"),
		( HashWord( L"\x58f0\x512a",       0,  2, 10 ) == 731 ) ? _T("OK") : _T("FAIL") );
	_tprintf( _T("Hash test 3... %s\n"),
		( HashWord( L"\x0001\x0028",       0,  2, 10 ) == 658 ) ? _T("OK") : _T("FAIL") );
	_tprintf( _T("Hash test 4... %s\n"),
		( HashWord( L"\xff01\x9428",       0,  2, 10 ) == 658 ) ? _T("OK") : _T("FAIL") );
	_tprintf( _T("Hash test 5... %s\n"),
		( HashWord( L"\x0000",             0,  1, 10 ) ==   0 ) ? _T("OK") : _T("FAIL") );
	_tprintf( _T("Hash test 6... %s\n"),
		( HashWord( L"\x0001",             0,  1, 10 ) == 316 ) ? _T("OK") : _T("FAIL") );
	_tprintf( _T("Hash test 7... %s\n"),
		( HashWord( L"0123456789",         0, 10, 10 ) == 551 ) ? _T("OK") : _T("FAIL") );
// No UTF-32 support for unmanaged C++
//	_tprintf( _T("Hash test 8... %s\n"),
//		( HashWord( L"\x10400",            0,  1, 10 ) == 316 ) ? _T("OK") : _T("FAIL") );
//	_tprintf( _T("Hash test 9... %s\n"),
//		( HashWord( L"\x10428",            0,  1, 10 ) == 658 ) ? _T("OK") : _T("FAIL") );

	_tprintf( _T("\nMeasuring performance:\n\n") );

	const int nCount = 10;
	const __int64 nBlock = 100 * 1024 * 1024;	// 100 MB
	LPVOID pBuffer = VirtualAlloc( NULL, nBlock, MEM_COMMIT, PAGE_READWRITE );
	memset( pBuffer, 'A', nBlock );

	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST );

	{
		__int64 nBest = -1, nError = 0, nFast = 0, n = 0;
		do
		{
			__int64 nWorst = 0;
			_tprintf( _T("HashWord : %I64d MB by "), nBlock / 1024 / 1024 );
			DWORD foo;
			for ( int i = 0; i < nCount; ++i )
			{
				const __int64 nBegin = GetMicroCount();
				foo = HashWord( (LPCTSTR)pBuffer, 0, nBlock / sizeof( TCHAR ) - 1, 20 );
				__int64 nTime = GetMicroCount() - nBegin;
				if ( nBest < 0 || nTime < nBest )
					nBest = nTime;
				if ( i == 0 || nTime > nWorst )
					nWorst = nTime;
				if ( foo != 901120 )
				{
					_tprintf( _T("FAILED! ") );
					break;
				}
			}
			nError = ( 100 * ( nWorst - nBest ) ) / nWorst;
			const __int64 nSpeed = ( nBlock * 1000000 ) / nBest;
			if ( nFast < nSpeed )
				nFast = nSpeed;
			_tprintf( _T("%3I64d ms (inaccuracy %2I64d%%), %3I64d MB/s        \r"),
				nBest / 1000, nError, nFast / ( 1024 * 1024 ) );
		} while ( nError > 5 && n++ < 10 );
	}
	_tprintf( _T("\n") );

	{
		__int64 nBest = -1, nError = 0, nFast = 0, n = 0;
		do
		{
			__int64 nWorst = 0;
			_tprintf( _T("MD4  hash: %I64d MB by "), nBlock / 1024 / 1024 );
			for ( int i = 0; i < nCount; ++i )
			{
				const __int64 nBegin = GetMicroCount();
				CMD4 pMD4;
				pMD4.Add( pBuffer, nBlock );
				pMD4.Finish();
				__int64 nTime = GetMicroCount() - nBegin;
				if ( nBest < 0 || nTime < nBest )
					nBest = nTime;
				if ( i == 0 || nTime > nWorst )
					nWorst = nTime;
			}
			nError = ( 100 * ( nWorst - nBest ) ) / nWorst;
			const __int64 nSpeed = ( nBlock * 1000000 ) / nBest;
			if ( nFast < nSpeed )
				nFast = nSpeed;
			_tprintf( _T("%3I64d ms (inaccuracy %2I64d%%), %3I64d MB/s        \r"),
				nBest / 1000, nError, nFast / ( 1024 * 1024 ) );
		} while ( nError > 5 && n++ < 10 );
	}
	_tprintf( _T("\n") );

	{
		__int64 nBest = -1, nError = 0, nFast = 0, n = 0;
		do
		{
			__int64 nWorst = 0;
			_tprintf( _T("MD5  hash: %I64d MB by "), nBlock / 1024 / 1024 );
			for ( int i = 0; i < nCount; ++i )
			{
				const __int64 nBegin = GetMicroCount();
				CMD5 pMD5;
				pMD5.Add( pBuffer, nBlock );
				pMD5.Finish();
				__int64 nTime = GetMicroCount() - nBegin;
				if ( nBest < 0 || nTime < nBest )
					nBest = nTime;
				if ( i == 0 || nTime > nWorst )
					nWorst = nTime;
			}
			nError = ( 100 * ( nWorst - nBest ) ) / nWorst;
			const __int64 nSpeed = ( nBlock * 1000000 ) / nBest;
			if ( nFast < nSpeed )
				nFast = nSpeed;
			_tprintf( _T("%3I64d ms (inaccuracy %2I64d%%), %3I64d MB/s        \r"),
				nBest / 1000, nError, nFast / ( 1024 * 1024 ) );
		} while ( nError > 5 && n++ < 10 );
	}
	_tprintf( _T("\n") );

	{
		__int64 nBest = -1, nError = 0, nFast = 0, n = 0;
		do
		{
			__int64 nWorst = 0;
			_tprintf( _T("SHA1 hash: %I64d MB by "), nBlock / 1024 / 1024 );
			for ( int i = 0; i < nCount; ++i )
			{
				const __int64 nBegin = GetMicroCount();
				CSHA pSHA;
				pSHA.Add( pBuffer, nBlock );
				pSHA.Finish();
				__int64 nTime = GetMicroCount() - nBegin;
				if ( nBest < 0 || nTime < nBest )
					nBest = nTime;
				if ( i == 0 || nTime > nWorst )
					nWorst = nTime;
			}
			nError = ( 100 * ( nWorst - nBest ) ) / nWorst;
			const __int64 nSpeed = ( nBlock * 1000000 ) / nBest;
			if ( nFast < nSpeed )
				nFast = nSpeed;
			_tprintf( _T("%3I64d ms (inaccuracy %2I64d%%), %3I64d MB/s        \r"),
				nBest / 1000, nError, nFast / ( 1024 * 1024 ) );
		} while ( nError > 5 && n++ < 10 );
	}
	_tprintf( _T("\n") );

	VirtualFree( pBuffer, 0, MEM_RELEASE );

	_tprintf( _T("\nPress ENTER to exit") );
	getchar();

	return 0;
}