void tst_Q3CString::isNull()
{
    Q3CString a;
    QVERIFY( a.isNull() );

    const char *str = "foo";
    a.sprintf( str );
    QVERIFY( !a.isNull() );
}