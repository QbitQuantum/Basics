static bool normalizeAbsolutePaths( const wxFileName& aPathA,
                                        const wxFileName& aPathB,
                                        wxString*         aResultPath )
{
    wxCHECK_MSG( aPathA.IsAbsolute(), false, aPathA.GetPath() + " is not an absolute path." );
    wxCHECK_MSG( aPathB.IsAbsolute(), false, aPathB.GetPath() + " is not an absolute path." );

    if( aPathA.GetPath() == aPathB.GetPath() )
        return true;

    if( ( aPathA.GetDirCount() > aPathB.GetDirCount() )
      || ( aPathA.HasVolume() && !aPathB.HasVolume() )
      || ( !aPathA.HasVolume() && aPathB.HasVolume() )
      || ( ( aPathA.HasVolume() && aPathB.HasVolume() )
         && ( aPathA.GetVolume() != aPathB.GetVolume() ) ) )
        return false;

    wxArrayString aDirs = aPathA.GetDirs();
    wxArrayString bDirs = aPathB.GetDirs();

    size_t i = 0;

    while( i < aDirs.GetCount() )
    {
        if( aDirs[i] != bDirs[i] )
            return false;

        i++;
    }

    if( aResultPath )
    {
        while( i < bDirs.GetCount() )
        {
            *aResultPath += bDirs[i] + wxT( "/" );
            i++;
        }
    }

    return true;
}