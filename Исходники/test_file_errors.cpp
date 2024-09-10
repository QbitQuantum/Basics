void IniTest()
{
	g_TestFilename = "file";

	/* Read check. */
	do {
		g_TestFile =
			"[test]\n"
			"abc=def";
	
		g_BytesUntilError = -1;

		IniFile test;
		if( !test.ReadFile( "test/file" ) )
			Fail( "INI: ReadFile failed: %s", test.GetError().c_str() );

		RString sStr;
		if( !test.GetValue( "test", "abc", sStr ) )
			Fail( "INI: GetValue failed" );
		if( sStr != "def" )
			Fail( "INI: GetValue failed: expected \"def\", got \"%s\"", sStr.c_str() );
	} while(false);

	/* Read error check. */
	do {
		g_TestFile =
			"[test]\n"
			"abc=def";
	
		g_BytesUntilError = 5;

		IniFile test;
		if( test.ReadFile( "test/file" ) )
			Fail( "INI: ReadFile should have failed" );

		if( test.GetError() != "Fake error" )
			Fail( "INI: ReadFile error check: wrong error return: got \"%s\"", test.GetError().c_str() );
	} while(false);

	/* Write error check. */
	do {
		g_BytesUntilError = 5;

		IniFile test;
		test.SetValue( "foo", "bar", RString("baz") );
		if( test.WriteFile( "test/file" ) )
			Fail( "INI: WriteFile should have failed" );

		if( test.GetError() != "Fake error" )
			Fail( "INI: ReadFile error check: wrong error return: got \"%s\"", test.GetError().c_str() );
	} while(false);
}