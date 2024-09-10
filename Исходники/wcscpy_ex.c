int main()
{
    struct record {
      wchar_t name[64];
      int age;
      _Bool male, smoking, discount;
    } this;
    int results;

    wprintf( L"Last name: " );
    results = wscanf( L"%63l[^\n]", this.name );

    if ( results < 1 )
        wcscpy( this.name, L"[Name not available]" );
    // or:
    // wcscpy_s( this.name, sizeof(this.name)/sizeof(wchar_t),
    //           L"[Name not available]" );

    wprintf( L"%ls\n", this.name );

    return 0;
}