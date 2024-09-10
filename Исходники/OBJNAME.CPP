AL_PROTO ALName::ALName( const char AL_DLL_FAR *s /* = "" */, 
                         ALCase name_case /* = AL_MIXED */ )
     : mCase( name_case )
{
    mszName = new AL_DLL_FAR char[ strlen( s ) + 1 ];
    if ( mszName )
        Strcpy( s );
     mszOldName = 0;
}