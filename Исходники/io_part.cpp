//---------------------------------------------------------------------------
MyString MYRTLEXP GetFPath( const MyString& nm, char Slash )
  {  char  str[ MAX_PATH_SIZE ];
     char *m;

     StrCpy( str,nm.Text(),sizeof(str) );
     m = StrRChr( str,Slash );
     if (m) *m = 0; else str[0] = 0;

 return MyString( AddLastSlash(str) );
}