    return( ptr);   // memory allocation okay.
}

//..........................................................................

//ppc cause access violation
void MyFree( void *UNALIGNED*p)
{
    if ( p && *p )
    {

#ifdef _DEBUG

        FreeMemListItem( *p, NULL);
#else
        HGLOBAL hMem = GlobalHandle( (HANDLE)*p);
        GlobalUnlock( hMem);
        GlobalFree( hMem);

#endif // _DEBUG

        *p = NULL;
    }
}


#ifdef _DEBUG

void FreeMemList( FILE *pfMemFile)
{
    while ( pMemList )